
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
    uint16_t speed;

public:
    Servo(uint8_t _DXL_ID, uint16_t _min_angle, uint16_t _max_angle);

    static void init();
    static void pingServos();
    static void setStartPosition();
    static Servo* findServo(uint8_t id);

    void set_angle(uint16_t _angle);
    static void set_angle(uint16_t _angle, uint8_t _DXL_ID);

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
    void findCommand(int id, int task, int value);

public:
    bool parseCommand(uint64_t command);

private:
    int32_t readRegister(char* command);

public:
    uint8_t get_DXL_ID();

    uint16_t get_angle();

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
    angle = get_angle();
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
    if (_angle < min_angle) {
        angle = min_angle;
        servos.goalPosition(DXL_ID, angle);
        return;
    }
    if (_angle > max_angle) {
        angle = max_angle;
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


void Servo::mv(uint16_t msg) {
    if (msg < 10000) {
      return;
    }
    uint8_t id = msg / 10000;
    Servo* servo = findServo(id);

    uint16_t msg_angle = msg % 10000;

    servo->set_angle(msg_angle);
}


void Servo::findCommand(int id, int task, int value) {
    if (task == PING_TASK) {
        return;
    }
    if (task == SET_ANGLE_TASK) {
        return Servo::set_angle(value, id);
    }
    if (task == SET_SPEED_TASK) {
        return Servo::set_speed(value, id);
    }
    if (task == TOOL_PUSH_TASK) {
        return Servo::toolPush(true);
    }
    if (task == TOOL_POP_TASK) {
        return Servo::toolPop();
    }
    if (task == GO_HOME_TASK) {
        return Servo::setStartPosition();
    }
}


bool Servo::parseCommand(uint64_t command) {
    if (command < 1000000 || command > 4999999) {
        return false;
    }
    int id = command / 1000000;
    int task = (command % 1000000) / 10000;
    int value = (command % 10000);
    findCommand(id, task, value);
    return true;
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
    if (servo4.get_load() > TOOL_MAX_LOAD || servo4.get_goal() >= SERVO4_MAX_ANGLE) {
        servo4.set_angle(servo4.get_goal() - 10);
        tool_flag = false;
    }
}


void Servo::toolPop() {
    tool_flag = false;
    servo4.set_angle(SERVO4_MIN_ANGLE);
}


#endif
