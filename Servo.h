#include <stdint.h>
#include <DynamixelWorkbench.h>
#include "Config.h"


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
    void setAngle(uint16_t _angle);
};


Servo::Servo(uint8_t _DXL_ID, uint16_t _min_angle, uint16_t _max_angle) {
    DXL_ID = _DXL_ID;
    min_angle = _min_angle;
    max_angle = _max_angle;
    servos.ping(DXL_ID, 0, 0);
}


void Servo::setAngle(uint16_t _angle) {
    if (_angle < min_angle) {
        angle = min_angle;
    }
    if (_angle > max_angle) {
        angle = max_angle;
    }
    if (min_angle <= _angle <= max_angle) {
        angle = _angle;
    }
    servos.goalPosition(DXL_ID, angle);
}


//test_comment
