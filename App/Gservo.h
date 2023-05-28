//
// Created by artem-kondratew on 3/18/23.
//

#ifndef MANIPULATOR_GSERVO_H
#define MANIPULATOR_GSERVO_H


#include <cstdint>


class Gservo {
private:
    uint8_t id;
    uint16_t angle;
    uint16_t speed;
    uint16_t torque;
    uint8_t is_moving;
    inline static int x;
    inline static int y;
    inline static int z;

public:
    explicit Gservo(uint8_t _id);

    uint8_t get_id() const;
    uint16_t get_angle() const;
    uint16_t get_speed() const;
    uint16_t get_torque() const;
    uint16_t get_is_moving() const;
    static uint16_t get_x();
    static uint16_t get_y();
    static uint16_t get_z();

    void set_angle(uint8_t _angle1, uint8_t _angle2);
    void set_speed(uint8_t _speed1, uint8_t _speed2);
    void set_torque(uint8_t _torque1, uint8_t _torque2);
    void set_is_moving(uint8_t _is_moving);
    static void set_x(uint8_t _x1, uint8_t _x2, bool x_sign);
    static void set_y(uint8_t _y1, uint8_t _y2, bool y_sign);
    static void set_z(uint8_t _z1, uint8_t _z2, bool z_sign);
};


inline Gservo gservo1(1);
inline Gservo gservo2(2);
inline Gservo gservo3(3);
inline Gservo gservo4(4);


#endif //MANIPULATOR_GSERVO_H
