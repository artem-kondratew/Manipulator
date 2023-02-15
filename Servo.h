//
// Created by user on 15.02.23.
//

#ifndef MANIPULATOR_SERVO_H
#define MANIPULATOR_SERVO_H


#include <cstdint>


class Servo {
private:
    uint16_t min_angle;
    uint16_t max_angle;
    uint16_t angle;
public:
    Servo(uint16_t _min_angle, uint16_t _max_angle);
    Servo(uint16_t _min_angle, uint16_t _max_angle, uint16_t _angle);
    ~Servo() = default;
    void setAngle(uint16_t _angle);
    [[nodiscard]] uint16_t getAngle() const;

};


#endif //MANIPULATOR_SERVO_H
