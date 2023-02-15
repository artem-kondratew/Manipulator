//
// Created by user on 15.02.23.
//

#ifndef MANIPULATOR_SERVO_H
#define MANIPULATOR_SERVO_H


#include <cstdint>


class Servo {
private:
    uint8_t min_angle;
    uint8_t max_angle;
    uint8_t angle;
public:
    void setAngle(uint8_t _angle);
};


#endif //MANIPULATOR_SERVO_H
