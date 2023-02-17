//
// Created by artem-kondratew on 15.02.23.
//

#include "Servo.h"


Servo::Servo(unsigned int dxl_id, unsigned int _min_angle, unsigned int _max_angle) {
    DXL_ID = dxl_id;
    min_angle = _min_angle;
    max_angle = _max_angle;
    angle = min_angle;
    //SERVOS.ping(DXL_ID, 0, 0);
}


void Servo::setAngle(unsigned int _angle) {
    if (_angle < min_angle) {
        angle = min_angle;
    }
    if (_angle > max_angle) {
        angle = max_angle;
    }
    if (min_angle <= angle <= max_angle) {
        angle = _angle;
    }
}

unsigned int Servo::getAngle() const {
    return angle;
}
