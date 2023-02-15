//
// Created by artem-kondratew on 15.02.23.
//

#ifndef MANIPULATOR_SERVO_H
#define MANIPULATOR_SERVO_H


#include <cstdint>


class Servo {
private:

    uint16_t min_angle;
    uint16_t max_angle;
    uint16_t angle;
    uint8_t DXL_ID;
public:
    //static DynamixelWorkbench SERVOS;
    Servo(uint8_t dxl_id, uint16_t _min_angle, uint16_t _max_angle);
    ~Servo() = default;
    void setAngle(uint16_t _angle);
    [[nodiscard]] uint16_t getAngle() const;
};


#endif //MANIPULATOR_SERVO_H
