//
// Created by artem-kondratew on 15.02.23.
//

#include "Servo.h"


Servo::Servo(uint8_t dxl_id, uint16_t _min_angle, uint16_t _max_angle) {
    DXL_ID = dxl_id;
    min_angle = _min_angle;
    max_angle = _max_angle;
    angle = min_angle;
    //SERVOS.ping(DXL_ID, nullptr, nullptr);
}


void Servo::setAngle(uint16_t _angle) {
    if (_angle < min_angle) {
        angle = min_angle;
    }
    if (_angle > max_angle) {
        angle = max_angle;
    }
    if (min_angle <= angle <= max_angle) {
        angle = _angle;
    }
    //SERVOS.goalPosition(DXL_ID, angle);
}

uint16_t Servo::getAngle() const {
    return angle;
}
