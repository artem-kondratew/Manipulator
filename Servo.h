
#ifndef Servo_h
#define Servo_h


#include <stdint.h>
#include <string>
#include <DynamixelWorkbench.h>
#include "Config.h"


DynamixelWorkbench servos;


class Servo {
private:
    uint8_t DXL_ID;
    uint16_t min_angle;
    uint16_t max_angle;
    uint16_t angle;
    bool inv;
    uint16_t new_angle;
    uint16_t speed;
    uint16_t boost;
public:
    Servo(uint8_t _DXL_ID, uint16_t _min_angle, uint16_t _max_angle, bool _inv = 0);
    static void init();
    static void pingServos();
    static void getStartPosition();

    void setAngle(uint16_t _angle);
    static void setAngle(uint16_t _angle, uint8_t _DXL_ID);
    uint16_t getAngle();
    
    static void talk(uint16_t _angle);
    static void anglePrint();

    static uint16_t checkGamma(uint16_t alpha, uint16_t beta);
    static void test(uint16_t msg);

    void setSpeed(uint16_t _speed);
    void setBoost(uint16_t _boost);
    void setMoveMode(uint16_t _speed, uint16_t _boost);
};


Servo servo1(DXL_ID1, SERVO1_MIN_ANGLE, SERVO1_MAX_ANGLE, 0);
Servo servo2(DXL_ID2, SERVO2_MIN_ANGLE, SERVO2_MAX_ANGLE, 0);
Servo servo3(DXL_ID3, SERVO3_MIN_ANGLE, SERVO3_MAX_ANGLE, 1);
Servo servo4(DXL_ID4, SERVO4_MIN_ANGLE, SERVO4_MAX_ANGLE, 1);


Servo::Servo(uint8_t _DXL_ID, uint16_t _min_angle, uint16_t _max_angle, bool _inv) {
    DXL_ID = _DXL_ID;
    min_angle = _min_angle;
    max_angle = _max_angle;
    angle = 0;
    new_angle = 0;
    inv = _inv;
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


uint16_t reformatAngle(uint16_t angle, uint16_t min_angle, uint16_t max_angle) {
    if (angle < min_angle) {
        return min_angle;
    }
    if (angle > max_angle) {
        return max_angle;
    }
    return angle;
}


void Servo::setAngle(uint16_t _angle) {
    if (inv == 1) {
        _angle = 1023 - _angle;
    }
    if (_angle < min_angle) {
        angle = min_angle;
        servos.goalPosition(DXL_ID, angle);
        if (inv == 1) {
            angle = 1023 - angle;
        }
        return;
    }
    if (_angle > max_angle) {
        angle = max_angle;
        servos.goalPosition(DXL_ID, angle);
        if (inv == 1) {
            angle = 1023 - angle;
        }
        return;
    }
    angle = _angle;
    servos.goalPosition(DXL_ID, angle);
    if (inv == 1) {
        angle = 1023 - angle;
    }
}


void Servo::setAngle(uint16_t _angle, uint8_t _DXL_ID) {
    if (_DXL_ID == 1) {
        servo1.setAngle(_angle);
    }
    if (_DXL_ID == 2) {
        servo2.setAngle(_angle);
    }
    if (_DXL_ID == 3) {
        servo3.setAngle(_angle);
    }
    if (_DXL_ID == 4) {
        servo4.setAngle(_angle);
    }
}


uint16_t Servo::getAngle() {
    return angle;
}


Servo *findServo(uint8_t id) {
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


void Servo::getStartPosition() {
    servo1.setAngle(512);
    servo2.setAngle(1023);
    servo3.setAngle(512);
    servo4.setAngle(512);
    delay(5000);
}


void Servo::anglePrint() {
    Serial.println();
    Serial.print("angle1: ");
    Serial.println(servo1.getAngle());
    Serial.print("angle2: ");
    Serial.println(servo2.getAngle());
    Serial.print("angle3: ");
    Serial.println(servo3.getAngle());
    Serial.print("angle4: ");
    Serial.println(servo4.getAngle());
}


void Servo::talk(uint16_t msg) {
    if (msg < 10000) {
        return;
    }
    uint8_t id = msg / 10000;
    Servo *servo = findServo(id);

    uint16_t msg_angle = msg % 10000;
    if (id == 2) {
        servo2.new_angle = reformatAngle(msg_angle, servo2.min_angle, servo2.max_angle);
        servo3.new_angle = servo3.angle + checkGamma(servo2.new_angle, servo3.angle);
        servo3.setAngle(servo3.new_angle);
        servo2.setAngle(servo2.new_angle);
        return;
    }
    if (id == 3) {
        servo3.new_angle = msg_angle + checkGamma(servo2.angle, msg_angle);
        servo3.setAngle(servo3.new_angle);
        return;
    }
    servo->setAngle(msg_angle);
}


uint16_t Servo::checkGamma(uint16_t alpha, uint16_t beta) {
    beta = beta - BETA0;
    int16_t gamma = 1023 - alpha + beta;
    if (gamma < MIN_GAMMA) {
        return MIN_GAMMA - gamma;
    }
    if (gamma > MAX_GAMMA) {
        return MAX_GAMMA - gamma;
    }
    return 0;
}


void Servo::setSpeed(uint16_t _speed) {
    speed = _speed;
    servos.jointMode(DXL_ID, speed, boost);
}


void Servo::setBoost(uint16_t _boost) {
    boost = _boost;
    servos.jointMode(DXL_ID, speed, boost);
}


void Servo::setMoveMode(uint16_t _speed, uint16_t _boost) {
    speed = _speed;
    boost = _boost;
    servos.jointMode(DXL_ID, speed, boost);
}


#endif
