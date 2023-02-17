//
// Created by artem-kondratew on 15.02.23.
//

#ifndef MANIPULATOR_SERVO_H
#define MANIPULATOR_SERVO_H


#include <cstdint>


class Servo {
private:
    unsigned int min_angle;
    unsigned int max_angle;
    unsigned int angle;
    unsigned int DXL_ID;
public:
    static const uint32_t SERVO_BAUDRATE = 1000000;
    Servo(unsigned int dxl_id, unsigned int _min_angle, unsigned int _max_angle);
    ~Servo() = default;
    void setAngle(unsigned int _angle);
    unsigned int getAngle() const;
};


#endif //MANIPULATOR_SERVO_H
