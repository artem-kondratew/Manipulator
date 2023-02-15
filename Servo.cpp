//
// Created by user on 15.02.23.
//

#include "Servo.h"

void Servo::setAngle(uint8_t _angle) {
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
