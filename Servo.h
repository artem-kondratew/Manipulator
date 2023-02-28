
#include <stdint.h>
#include <DynamixelWorkbench.h>


DynamixelWorkbench servos;


class Servo {
private:
    uint8_t DXL_ID;
    uint16_t min_angle;
    uint16_t max_angle;
    uint16_t angle;
public:
    Servo(uint8_t _DXL_ID, uint16_t _min_angle, uint16_t _max_angle);
    ~Servo() = default;
    void pingServo();
    void setAngle(uint16_t _angle);
    uint16_t getAngle();
};


Servo servo1(DXL_ID1, 150, 853);
Servo servo2(DXL_ID2, 0, 590);
Servo servo3(DXL_ID3, 270, 1023);
Servo servo4(DXL_ID4, 0, 1023);


Servo::Servo(uint8_t _DXL_ID, uint16_t _min_angle, uint16_t _max_angle) {
    DXL_ID = _DXL_ID;
    min_angle = _min_angle;
    max_angle = _max_angle;
}


void Servo::pingServo() {
    servos.ping(DXL_ID, 0, 0);
}


void Servo::setAngle(uint16_t _angle) {
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
    return;
}


uint16_t Servo::getAngle() {
    return angle;
}
