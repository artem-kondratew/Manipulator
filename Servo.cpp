//
// Created by user on 15.02.23.
//

#include "Servo.h"


Servo::Servo(uint16_t _min_angle, uint16_t _max_angle) {
    min_angle = _min_angle;
    max_angle = _max_angle;
    angle = min_angle;
}

Servo::Servo(uint16_t _min_angle, uint16_t _max_angle, uint16_t _angle): Servo(_min_angle, _max_angle) {
    angle = _angle;
}


void Servo::setAngle(uint16_t _angle) {
    if (_angle < min_angle) {
        angle = min_angle;
        return;
    }
    if (_angle > max_angle) {
        angle = max_angle;
        return;
    }
    angle = _angle;
}

uint16_t Servo::getAngle() const {
    return angle;
}
