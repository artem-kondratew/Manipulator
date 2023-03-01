
#include <stdint.h>


class Joystick {
private:
    uint8_t PIN;
    uint16_t value;
    bool inv;
public:
    Joystick(uint8_t _PIN, bool _inv=0);
    ~Joystick() = default;

    uint16_t getValue();
    void setValue();
    static void refresh();
    static bool checkAngles();
};


Joystick joystick1(ANALOG_PIN1, 0);
Joystick joystick2(ANALOG_PIN2, 1);
Joystick joystick3(ANALOG_PIN3, 1);
Joystick joystick4(ANALOG_PIN4, 0);


Joystick::Joystick(uint8_t _PIN, bool _inv) {
    PIN = _PIN;
    value = 0;
    inv = _inv;
}


uint16_t Joystick::getValue() {
    /*if (inv) {
      return 1023 - value;
    }*/
    return value;   
}


void Joystick::setValue() {
    if (abs(value - analogRead(PIN)) < 5) {
        return;
    }
    value = analogRead(PIN);
}


void Joystick::refresh() {
    joystick1.setValue();
    joystick2.setValue();
    joystick3.setValue();
    joystick4.setValue();
}


bool Joystick::checkAngles() {
    uint16_t alpha = joystick2.value * 120 / 1024 /180 * 3.14;
    uint16_t beta = ((joystick3.value - 270) * 70 / 754 + 145) / 180 * 3.14;
    if (sin(alpha) + sin(beta) > -0.6) {
        return 0;
    }
    return 1;
}
