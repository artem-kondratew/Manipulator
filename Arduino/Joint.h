

#ifndef Joint_h
#define Joint_h


#include <cstdint>
#include <cmath>
#include "Servo.h"


//#define PI 3.14

// Lengths of links in mm
#define X0      -25
#define Z0       91
#define LEN1   94.4
#define LEN2    150
#define LEN3    150
#define LEN4    134
#define EPSILON  10


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

    static void set_position(int16_t my_x, int16_t my_y, int16_t my_z);
    static void set_x(uint16_t value);
    static void set_y(uint16_t value);
    static void set_z(uint16_t value);
    static int16_t get_x(uint16_t q0, uint16_t q1, uint16_t q2);
    static int16_t get_y(uint16_t q0, uint16_t q1, uint16_t q2);
    static int16_t get_z(uint16_t q0, uint16_t q1, uint16_t q2);
    static int16_t get_x();
    static int16_t get_y();
    static int16_t get_z();
    static void get_coordinates();
};


Joint::Joint(uint8_t _DXL_ID) {
    DXL_ID = _DXL_ID;
}


Joint joint1(DXL_ID1);
Joint joint2(DXL_ID2);
Joint joint3(DXL_ID3);
Joint joint4(DXL_ID4);


double calc_q0_rad(uint16_t angle) {
    return (map(angle, 0, 1023, 30, 330) - 180) / 180.0 * PI;
}


double calc_q1_rad(uint16_t angle) {
    return (map(angle, 0, 1023, 30, 330) - 90) / 180.0 * PI;
}


double calc_q2_rad(uint16_t angle) {
    return (map(angle, 0, 1023, 30, 330) - 128) / 180.0 * PI;
}


int16_t Joint::get_x(uint16_t q0, uint16_t q1, uint16_t q2) {
    double q0_rad = calc_q0_rad(q0);
    double q1_rad = calc_q1_rad(q1);
    double q2_rad = calc_q2_rad(q2);
    return (X0 + LEN2 * cos(q1_rad) + LEN3 * cos(q2_rad) + LEN4) * cos(q0_rad);
}


int16_t Joint::get_y(uint16_t q0, uint16_t q1, uint16_t q2) {
    double q0_rad = calc_q0_rad(q0);
    double q1_rad = calc_q1_rad(q1);
    double q2_rad = calc_q2_rad(q2);
    return (X0 + LEN2 * cos(q1_rad) + LEN3 * cos(q2_rad) + LEN4) * sin(q0_rad);
}


int16_t Joint::get_z(uint16_t q0, uint16_t q1, uint16_t q2) {
    double q0_rad = calc_q0_rad(q0);
    double q1_rad = calc_q1_rad(q1);
    double q2_rad = calc_q2_rad(q2);
    return Z0 + LEN2 * sin(q1_rad) + LEN3 * sin(q2_rad);
}


int16_t Joint::get_x() {
    get_x(servo1.get_angle(), servo2.get_angle(), servo3.get_angle());
}


int16_t Joint::get_y() {
    get_y(servo1.get_angle(), servo2.get_angle(), servo3.get_angle());
}


int16_t Joint::get_z() {
    get_z(servo1.get_angle(), servo2.get_angle(), servo3.get_angle());
}


bool checkError(int16_t real, int16_t desire) {
    if (abs(real - desire) > EPSILON) {
        return false;
    }
    return true;
}


void Joint::set_position(int16_t my_x, int16_t my_y, int16_t my_z) {
        for (int16_t i = SERVO1_MIN_ANGLE; i <= SERVO1_MAX_ANGLE; i++) {
            for (int16_t j = SERVO2_MIN_ANGLE; j <= SERVO2_MAX_ANGLE; j++) {
                for (int16_t k = SERVO3_MIN_ANGLE; k <= SERVO3_MAX_ANGLE; k++) {
                    if (checkError(get_x(i, j, k), my_x) && checkError(get_y(i, j, k), my_y) && checkError(get_z(i, j, k), my_z)) {
                        servo1.set_angle(i);
                        servo2.set_angle(j);
                        servo3.set_angle(k);
                        return;
                    }
                }
            }
    }
}


void Joint::set_x(uint16_t value) {
    set_position(value, get_y(), get_z());
}


void Joint::set_y(uint16_t value) {
    set_position(get_x(), value, get_z());
}


void Joint::set_z(uint16_t value) {
    set_position(get_x(), get_y(), value);
}


void Joint::get_coordinates() {/*
    Serial.print("Angle q0: ");
    Serial.print(q0); Serial.print(" "); Serial.print(servo1.getAngle()); Serial.print(" "); Serial.println(q0_rad);
    Serial.print("Angle q1: ");
    Serial.print(q1); Serial.print(" "); Serial.print(servo2.getAngle()); Serial.print(" "); Serial.println(q1_rad);
    Serial.print("Angle q2: ");
    Serial.print(q2); Serial.print(" "); Serial.print(servo3.getAngle()); Serial.print(" "); Serial.println(q2_rad);
*/
    Serial.print("Coordinate x: ");
    Serial.println(get_x());
    Serial.print("Coordinate y: ");
    Serial.println(get_y());
    Serial.print("Coordinate z: ");
    Serial.println(get_z());
    Serial.println();
}


/* void Joint::getAngles() {
    int8_t q0 = map(servo1.getAngle(), 0, 1023, -179, 180);
    int8_t q1 = map(servo2.getAngle(), 0, 1023, -240, -88);
    int8_t q2 = map(servo3.getAngle(), 0, 1023, 388, 0);
    double q0_rad = q0 / 180.0 * PI;
    double q1_rad = q1 / 180.0 * PI;
    double q2_rad = q2 / 180.0 * PI;
    

} */



/*    switch (DXL_ID) {
        case 1: {
            x = x0 * cos(q0_rad);
            y = x0 * sin(q0_rad);
            z = z0;
            break;
        }
        case 2: {
            x = (x0 + len2 * cos(q1)) * cos(q0);
            y = (x0 + len2 * cos(q1)) * sin(q0);
            z = z0 + len2 * sin(q1);
            break;  
        }
        case 3: {
            x = (x0 + len2 * cos(q1) + len3 * cos(q2)) * cos(q0);
            y = (x0 + len2 * cos(q1) + len3 * cos(q2)) * sin(q0);
            z = z0 + len1 * sin(q1) + len3 * sin(q2);
            break;  
        }
        case 4: {
            x = (x0 + len2 * cos(q1_rad) + len3 * cos(q2_rad) + len4) * cos(q0_rad);
            y = (x0 + len2 * cos(q1_rad) + len3 * cos(q2_rad) + len4) * sin(q0_rad);
            z = z0 + len2 * sin(q1_rad) + len3 * sin(q2_rad);
            break;
        }
        default:
            Serial.print("Wrong DXL_ID!");
            break;
    } */


#endif
