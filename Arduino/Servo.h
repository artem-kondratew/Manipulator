
#ifndef Servo_h
#define Servo_h


#include <stdint.h>
#include <string>
#include <DynamixelWorkbench.h>
#include "Config.h"


DynamixelWorkbench servos;


static bool tool_flag = false;


class Servo {
private:
    uint8_t DXL_ID;
    uint16_t min_angle;
    uint16_t max_angle;
    uint16_t angle;
    uint16_t new_angle;
    uint16_t speed;

public:
    Servo(uint8_t _DXL_ID, uint16_t _min_angle, uint16_t _max_angle);

    static void init();
    static void pingServos();
    static void setStartPosition();
    uint16_t reformatAngle(uint16_t _angle);
    static Servo* findServo(uint8_t id);

    void set_angle(uint16_t _angle);
    static void set_angle(uint16_t _angle, uint8_t _DXL_ID);
    void set_max_angle(uint16_t _max_angle);
    void set_min_angle(uint16_t _min_angle);

    void set_speed(uint16_t _speed);
    static void set_speed(uint16_t _speed, uint8_t _DXL_ID);

    void set_torque(bool status);

    void set_x(int32_t _x);
    void set_y(int32_t _y);
    void set_z(int32_t _z);

    static void test(uint16_t msg);
    static bool talk(uint16_t _angle);
    static void mv(uint16_t msg);

private:
    int32_t readRegister(char* command);

public:
    uint8_t get_DXL_ID();

    uint16_t get_angle();
    uint16_t get_max_angle();
    uint16_t get_min_angle();

    uint16_t get_goal();

    uint16_t get_load();

    uint8_t is_moving();

    uint16_t get_speed();

    static void toolPush(bool start=false);
    static void toolPop();
};


Servo servo1(DXL_ID1, SERVO1_MIN_ANGLE, SERVO1_MAX_ANGLE);
Servo servo2(DXL_ID2, SERVO2_MIN_ANGLE, SERVO2_MAX_ANGLE);
Servo servo3(DXL_ID3, SERVO3_MIN_ANGLE, SERVO3_MAX_ANGLE);
Servo servo4(DXL_ID4, SERVO4_MIN_ANGLE, SERVO4_MAX_ANGLE);


Servo::Servo(uint8_t _DXL_ID, uint16_t _min_angle, uint16_t _max_angle) {
    DXL_ID = _DXL_ID;
    min_angle = _min_angle;
    max_angle = _max_angle;
    angle = 0;
    new_angle = 0;
}


void Servo::init() {
    servos.init(DEVICE_NAME, SERVO_BAUDRATE);
}


void Servo::pingServos() {
    servos.ping(DXL_ID1, 0, 0);
    servos.ping(DXL_ID2, 0, 0);
    servos.ping(DXL_ID3, 0, 0);
    servos.ping(DXL_ID4, 0, 0);
}


void Servo::setStartPosition() {
    servo1.set_angle(SERVO1_START_POSITION);
    servo2.set_angle(SERVO2_START_POSITION);
    servo3.set_angle(SERVO3_START_POSITION);
    delay(1000);
}


uint16_t Servo::reformatAngle(uint16_t _angle) {
    if (_angle < min_angle) {
        return min_angle;
    }
    if (_angle > max_angle) {
        return max_angle;
    }
    return _angle;
}


Servo* Servo::findServo(uint8_t id) {
    if (id == 1) {
        return &servo1;
    }
    if (id == 2) {
        return &servo2;
    }
    if (id == 3) {
        return &servo3;
    }
    if (id == 4) {
        return &servo4;
    }
}


void Servo::set_angle(uint16_t _angle) {
    uint16_t _min_angle = min_angle;;
    uint16_t _max_angle = max_angle;
    
    if (_angle < _min_angle) {
        angle = _min_angle;
        servos.goalPosition(DXL_ID, angle);
        return;
    }
    if (_angle > _max_angle) {
        angle = _max_angle;
        servos.goalPosition(DXL_ID, angle);
        return;
    }
    angle = _angle;
    servos.goalPosition(DXL_ID, angle);
}


void Servo::set_angle(uint16_t _angle, uint8_t _DXL_ID) {
    Servo* servo = findServo(_DXL_ID);
    servo->set_angle(_angle);
}


void Servo::set_max_angle(uint16_t _max_angle) {
    max_angle = _max_angle;
}


void Servo::set_min_angle(uint16_t _min_angle) {
    min_angle = _min_angle;
}


void Servo::set_speed(uint16_t _speed) {
    speed = _speed;
    servos.jointMode(DXL_ID, speed, DEFAULT_BOOST);
}


void Servo::set_speed(uint16_t _speed, uint8_t _DXL_ID) {
    Servo* servo = findServo(_DXL_ID);
    servo->set_speed(_speed);
}


void Servo::set_torque(bool status) {
    if (status == 1)
        servos.torqueOn(DXL_ID);
    if (status == 0)
        servos.torqueOff(DXL_ID);
}


void Servo::test(uint16_t msg) {

    uint16_t neutral_angle_2 = (servo2.max_angle + servo2.min_angle) / 2 - 20;
    uint16_t neutral_angle_3 = (servo3.max_angle + servo3.min_angle) / 2 + 20;

    uint16_t num2 = servo3.max_angle - neutral_angle_2;
    uint16_t num3 = neutral_angle_2 + servo3.min_angle;
    uint16_t num4 = neutral_angle_2 - servo3.min_angle;

    uint16_t angle_3 = 1023 - servo3.get_angle();
    uint16_t angle_2 = servo2.get_angle();

    uint8_t id = msg / 10000;
    uint16_t msg_angle = msg % 10000;

    if (id == 2) {

        uint8_t quart;
        uint16_t correct_angle_3;

        msg_angle = servo2.reformatAngle(msg_angle);

        if (angle_3 > neutral_angle_3) {
            if (msg_angle > neutral_angle_2)
                quart = 1; // Определяем четверть
            else
                quart = 2;
        } else {
            if (msg_angle <= neutral_angle_2)
                quart = 3;
            else
                quart = 4;
        }

        switch (quart) { // Действия для каждой четверти
            case 1:
                servo2.set_angle(msg_angle);
                break;

            case 2:
                correct_angle_3 = num2 + msg_angle;
                if (angle_3 > correct_angle_3)
                    servo3.set_angle(correct_angle_3);
                servo2.set_angle(msg_angle);
                break;

            case 3:
                correct_angle_3 = num3 - msg_angle;
                if (angle_3 < correct_angle_3 && msg_angle < 320)
                    servo3.set_angle(correct_angle_3 + (320 - msg_angle) / 6);
                servo2.set_angle(msg_angle);
                break;

            case 4:
                correct_angle_3 = msg_angle - num4;
                if (angle_3 < correct_angle_3)
                    servo3.set_angle(correct_angle_3);
                servo2.set_angle(msg_angle);
                break;

            default:
                servo2.set_angle(msg_angle);
                break;
        }
        return;
    }

    if (id == 3) {

        uint8_t place;
        uint16_t correct_angle_2;

        msg_angle = servo3.reformatAngle(msg_angle);

        if (msg_angle < neutral_angle_3 - 200) {
            if (angle_2 > neutral_angle_2) {
                place = 7;
            } else {
                place = 8;
            }
        } else if (msg_angle < neutral_angle_3 - 100 &&
                   msg_angle >= neutral_angle_3 - 200) {
            if (angle_2 > neutral_angle_2) {
                place = 5;
            } else {
                place = 6;
            }
        } else if (msg_angle < neutral_angle_3 &&
                   msg_angle >= neutral_angle_3 - 100) {
            if (angle_2 > neutral_angle_2) {
                place = 3;
            } else {
                place = 4;
            }
        } else {
            if (angle_2 > neutral_angle_2) {
                place = 1;
            } else {
                place = 2;
            }
        }

        switch (place) { // Действия для каждой четверти
            case 1:
                servo3.set_angle(msg_angle);
                break;

            case 2:
                correct_angle_2 = msg_angle - num2;
                if (angle_2 < correct_angle_2) {
                    servo2.set_angle(correct_angle_2);
                }
                servo3.set_angle(msg_angle);
                break;

            case 3:
            case 7:
                correct_angle_2 = servo2.max_angle - (neutral_angle_3 - msg_angle) / 2;
                if (angle_2 > correct_angle_2) {
                    servo2.set_angle(correct_angle_2);
                }
                servo3.set_angle(msg_angle);
                break;

            case 4:
            case 6:
                correct_angle_2 = servo2.min_angle + (neutral_angle_3 - msg_angle) / 2;
                if (angle_2 < correct_angle_2) {
                    servo2.set_angle(correct_angle_2);
                }
                servo3.set_angle(msg_angle);
                break;

            case 5:
                correct_angle_2 = msg_angle + 50;
                if (angle_2 > correct_angle_2) {
                    servo2.set_angle(correct_angle_2);
                }
                servo3.set_angle(msg_angle);
                break;

            case 8:
                correct_angle_2 = 300;
                if (angle_2 < correct_angle_2) {
                    servo2.set_angle(correct_angle_2);
                }
                servo3.set_angle(msg_angle);
                break;

            default:
                break;
        }
    }
}


bool Servo::talk(uint16_t msg) {
    if (msg < 1) {
        return false;
    }
    if (msg == 1) {
        servo1.set_torque(0);
        return true;
    }
    if (msg == 2) {
        servo2.set_torque(0);
        return true;
    }
    if (msg == 3) {
        servo3.set_torque(0);
        return true;
    }
    if (msg == 4) {
        servo4.set_torque(0);
        return true;
    }

    uint8_t id = msg / 10000;
    Servo* servo = findServo(id);

    uint16_t msg_angle = msg % 10000;

    if (id == 2 || id == 3)
        test(msg);
    if (id == 3) {
        // servo3.new_angle = msg_angle + checkGamma(servo2.angle, msg_angle);
        servo3.set_angle(msg_angle);
        return true;
    }
}


void Servo::mv(uint16_t msg) {
    if (msg < 10000) {
      return;
    }
    uint8_t id = msg / 10000;
    Servo* servo = findServo(id);

    uint16_t msg_angle = msg % 10000;

    servo->set_angle(msg_angle);
}


int32_t Servo::readRegister(char* command) {
    int32_t data;
    servos.readRegister(DXL_ID, command, &data);
    return data;
}


uint8_t Servo::get_DXL_ID() {
    return DXL_ID;
}


uint16_t Servo::get_angle() {
    int32_t data;
    servos.readRegister(DXL_ID, "Present_Position", &data);
    return (uint16_t)data;
}


uint16_t Servo::get_max_angle() {
    return max_angle;
}


uint16_t Servo::get_min_angle() {
    return min_angle;
}


uint16_t Servo::get_goal() {
    return angle;
}


uint16_t Servo::get_load() {
    int32_t data;
    servos.readRegister(DXL_ID, "Present_Load", &data);
    if (data > 1023)
        data -= 1023;
    return (uint16_t)data;
}


uint8_t Servo::is_moving() {
    int32_t data;
    servos.readRegister(DXL_ID, "Moving", &data);
    return (uint8_t)data;
}


uint16_t Servo::get_speed() {
    return speed;
}


void Servo::toolPush(bool start) {
    if (start) {
        tool_flag = true;
    }
    if (!tool_flag) {
        return;
    }
    servo4.set_angle(servo4.get_goal() + 10);
    if (servo4.get_load() > TOOL_MAX_LOAD) {
        servo4.set_angle(servo4.get_goal() - 10);
        tool_flag = false;
    }
}


void Servo::toolPop() {
    servo4.set_angle(SERVO4_MIN_ANGLE);
}


#endif
