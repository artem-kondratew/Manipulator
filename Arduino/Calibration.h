
#ifndef Calibration_h
#define Calibration_h


#include "Servo.h"


class Calibration {
public:
    static void Calibration_min(Servo servo);
    static void Calibration_max(Servo servo);
    static void Calibration_setup();
};


void Calibration::Calibration_max(Servo servo) {
    uint16_t servo_max_angle = 512;
    servo.set_speed(100);

    while (true) {
        Serial.println(servo.get_load());  // DEBUG
        Serial.println(servo_max_angle);
        Serial.println(servo.get_angle());
        Serial.println(" ");

        servo.set_angle(servo_max_angle);
        delay(100);
        if (servo.is_moving() == 0) servo_max_angle += 50;
        else if (servo.get_load() > 670) {
            servo_max_angle -= 50;
            servo.set_angle(servo_max_angle);
            break;
        }
    }

    servo.set_max_angle(servo_max_angle);

    Serial.println(" ");
    Serial.println(servo_max_angle);
}


void Calibration::Calibration_min(Servo servo) {
    uint16_t servo_min_angle = 512;
    servo.set_speed(100);
    while (true) {
        Serial.println(servo.get_load());  // DEBUG
        Serial.println(servo_min_angle);
        Serial.println(servo.get_angle());
        Serial.println(" ");

        servo.set_angle(servo_min_angle);
        delay(100);
        if (servo.is_moving() == 0) servo_min_angle -= 50;
        else if (servo.get_load() > 670) {
            servo_min_angle += 50;
            servo.set_angle(servo_min_angle);
            break;
        }
    }

    servo.set_min_angle(servo_min_angle);

    Serial.println(" ");
    Serial.println(servo_min_angle);
}


void Calibration::Calibration_setup() {
    Calibration_max(servo2);
    Calibration_min(servo2);
    servo2.set_angle((servo2.get_min_angle() + servo2.get_max_angle()) / 2);
    delay(2000);
    Calibration_max(servo3);
    Calibration_min(servo3);
}


#endif
