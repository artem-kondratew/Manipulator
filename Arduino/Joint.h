
#ifndef Joint_h
#define Joint_h


#include <cstdint>
#include <cmath>
#include "Servo.h"


// Lengths of links in mm
#define X0    -30
#define Z0     87
#define LEN1 94.4
#define LEN2  150
#define LEN3  150
#define LEN4  141


class Joint {
private:
    uint8_t DXL_ID;
    // Coordinates in mm
    int16_t x;
    int16_t y;
    int16_t z;
    int16_t q0;
    int16_t q1;
    int16_t q2;
    double q0_rad;
    double q1_rad;
    double q2_rad;

public:
    Joint(uint8_t _DXL_ID);
    ~Joint() = default;

    void get_radians();
    int16_t get_x();
    int16_t get_y();
    int16_t get_z();
    void get_coordinates();
};


Joint::Joint(uint8_t _DXL_ID) {
    DXL_ID = _DXL_ID;
}


void Joint::get_radians() {
    //q0 = map(servo1.get_angle(), 0, 1023, 30, 330) - 180;
    //q1 = map(servo2.get_angle(), 0, 1023, 30, 330) - 90;
    //q2 = map(servo3.get_angle(), 0, 1023, 330, 30) - 232;
    q0_rad = (map(servo1.get_angle(), 0, 1023, 30, 330) - 180) / 180.0 * PI;
    q1_rad = (map(servo2.get_angle(), 0, 1023, 30, 330) - 90) / 180.0 * PI;
    q2_rad = (map(servo3.get_angle(), 0, 1023, 30, 330) - 128) / 180.0 * PI;
}


int16_t Joint::get_x() {
    get_radians();
    switch (DXL_ID) {
        case 1: {
            x = X0 * cos(q0_rad);
            break;
        }
        case 2: {
            x = (X0 + LEN2 * cos(q1_rad)) * cos(q0_rad);
            break;
        }
        case 3: {
            x = (X0 + LEN2 * cos(q1_rad) + LEN3 * cos(q2_rad)) * cos(q0_rad);
            break;
        }
        case 4: {
            x = (X0 + LEN2 * cos(q1_rad) + LEN3 * cos(q2_rad) + LEN4) * cos(q0_rad);
            break;
        }
        default:
            break;
    }
    return x;
}


int16_t Joint::get_y() {
    get_radians();
    switch (DXL_ID) {
        case 1: {
            y = X0 * sin(q0_rad);
            break;
        }
        case 2: {
            y = (X0 + LEN2 * cos(q1_rad)) * sin(q0_rad);
            break;
        }
        case 3: {
            y = (X0 + LEN2 * cos(q1_rad) + LEN3 * cos(q2_rad)) * sin(q0_rad);
            break;
        }
        case 4: {
            y = (X0 + LEN2 * cos(q1_rad) + LEN3 * cos(q2_rad) + LEN4) * sin(q0_rad);
            break;
        }
    }
    return y;
}


int16_t Joint::get_z() {
    get_radians();
    switch (DXL_ID) {
        case DXL_ID1: {
            z = Z0;
            break;
        }
        case 2: {
            z = Z0 + LEN2 * sin(q1_rad);
            break;
        }
        case 3: {
            z = Z0 + LEN2 * sin(q1_rad) + LEN3 * sin(q2_rad);
            break;
        }
        case 4: {
            z = Z0 + LEN2 * sin(q1_rad) + LEN3 * sin(q2_rad) - 17;
            break;
        }
        default:
            break;
    }
    return z;
}


void Joint::get_coordinates() {
    //Serial.print("Angle q0: ");
    //Serial.print(q0); Serial.print("  "); Serial.print(q0_rad); Serial.print("  "); Serial.println(servo1.get_angle());
    //Serial.print("Angle q1: ");
    //Serial.print(q1); Serial.print("  "); Serial.print(q1_rad); Serial.print("  "); Serial.println(servo2.get_angle());
    //Serial.print("Angle q2: ");
    //Serial.print(q2); Serial.print("  "); Serial.print(q2_rad); Serial.print("  "); Serial.println(servo3.get_angle());
}


Joint joint1(DXL_ID1);
Joint joint2(DXL_ID2);
Joint joint3(DXL_ID3);
Joint joint4(DXL_ID4);


#undef X0
#undef Z0
#undef LEN1
#undef LEN2
#undef LEN3
#undef LEN4

#endif
