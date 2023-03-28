
#include <cstdint>
#include <cmath>
#include "Servo.h"


#define PI 3.14

// Lengths of links in mm:
#define X0 -25
#define Z0 100
#define LEN1 103
#define LEN2 150
#define LEN3 150
#define LEN4 120


class Joint {
private:
    uint8_t DXL_ID;
    // Coordinates in mm.
    int32_t x;
    int32_t y;
    int32_t z;
    int8_t q0;
    int8_t q1;
    int8_t q2;
    double q0_rad;
    double q1_rad;
    double q2_rad;
public:
    Joint(uint8_t _DXL_ID);
    ~Joint() = default;
    void GoTo(int32_t my_x, int32_t my_y, int32_t my_z);
    void getRadians();
    int32_t getX();
    int32_t getY();
    int32_t getZ();
    void getCoordinates();
    
};


Joint::Joint(uint8_t _DXL_ID) {
    DXL_ID = _DXL_ID;
}


void Joint::getRadians() {
    q0 = map(servo1.getAngle(), 0, 1023, -179, 180);
    q1 = map(servo2.getAngle(), 0, 1023, -240, -88);
    q2 = map(servo3.getAngle(), 0, 1023, -122, 237);
    q0_rad = q0 / 180.0 * PI;
    q1_rad = q1 / 180.0 * PI;
    q2_rad = q2 / 180.0 * PI;
}


int32_t Joint::getX() {
    getRadians();
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
            Serial.print("Wrong DXL_ID!");
            break;
    }
    
    return x;
}


int32_t Joint::getY() {
    getRadians();
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
}


int32_t Joint::getZ() {
    getRadians();
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
            z = Z0 + LEN2 * sin(q1_rad) + LEN3 * sin(q2_rad);
            break;
        }
        default:
            Serial.print("Wrong DXL_ID!");
            break;
    }
    
    return z;
}


void Joint::getCoordinates() {
    Serial.print("Angle q0: ");
    Serial.print(q0); Serial.print(" "); Serial.println(q0_rad);
    Serial.print("Angle q1: ");
    Serial.print(q1); Serial.print(" "); Serial.println(q1_rad); 
    Serial.print("Angle q2: ");
    Serial.print(q2); Serial.print(" "); Serial.println(q2_rad);
    
    Serial.print("Coordinate x: ");
    Serial.println(getX());
    Serial.print("Coordinate y: ");
    Serial.println(getY());  
    Serial.print("Coordinate z: ");
    Serial.println(getZ());
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


Joint joint1(DXL_ID1);
Joint joint2(DXL_ID2);
Joint joint3(DXL_ID3);
Joint joint4(DXL_ID4);


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
