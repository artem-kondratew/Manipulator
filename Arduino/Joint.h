
#include <cstdint>
#include <cmath>
#include "Servo.h"


#define PI 3.14


class Joint {
private:
    uint8_t DXL_ID;
    // Coordinates in mm.
    int32_t x;
    int32_t y;
    int32_t z;    
public:
    Joint(uint8_t _DXL_ID);
    ~Joint() = default;
    void GoTo(int32_t my_x, int32_t my_y, int32_t my_z);
    void getCoordinates();
    static void getAngles();
    
};


Joint::Joint(uint8_t _DXL_ID) {
    DXL_ID = _DXL_ID;

    // Lengths of links in mm:
    const uint8_t x0 = -25;
    const uint8_t z0 = 100;
    const uint8_t len1 = 103;
    const uint8_t len2 = 150;
    const uint8_t len3 = 150;
    const uint8_t len4 = 120;
    int8_t q0 = map(servo1.getAngle(), 0, 1023, -179, 180);
    int8_t q1 = map(servo2.getAngle(), 0, 1023, -240, -88);
    int8_t q2 = map(servo3.getAngle(), 0, 1023, -233, 126);
    double q0_rad = q0 / 180 * PI;
    double q1_rad = q1 / 180 * PI;
    double q2_rad = q2 / 180 * PI;
    
    switch (DXL_ID) {
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
            x = (x0 + len2 * cos(1.5708) + len3 * cos(0) + len4) * cos(0);
            y = (x0 + len2 * cos(1.5708) + len3 * cos(0) + len4) * sin(0);
            z = z0 + len2 * sin(1.5708) + len3 * sin(0);
            break;  
        }
        default:
            Serial.print("Wrong DXL_ID!");
            break;
    }
}


void GoTo(int32_t x, int32_t y, int32_t z);


void Joint::getCoordinates() {
    Serial.print("Coordinate x: ");
    Serial.println(x);
    Serial.print("Coordinate y: ");
    Serial.println(y);  
    Serial.print("Coordinate z: ");
    Serial.println(z);
    Serial.println();
}


void Joint::getAngles() {
    int8_t q0 = map(servo1.getAngle(), 0, 1023, -179, 180);
    int8_t q1 = map(servo2.getAngle(), 0, 1023, -240, -88);
    int8_t q2 = map(servo3.getAngle(), 0, 1023, 388, 0);
    double q0_rad = q0 / 180.0 * PI;
    double q1_rad = q1 / 180.0 * PI;
    double q2_rad = q2 / 180.0 * PI;
    
    Serial.print("Angle q0: ");
    Serial.print(q0); Serial.print(" "); Serial.println(q0_rad);
    Serial.print("Angle q1: ");
    Serial.print(q1); Serial.print(" "); Serial.println(q1_rad); 
    Serial.print("Angle q2: ");
    Serial.print(q2); Serial.print(" "); Serial.println(q2_rad);
}


Joint joint1(1);
Joint joint2(2);
Joint joint3(3);
Joint joint4(4);
