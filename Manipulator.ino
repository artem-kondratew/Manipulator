
#include <DynamixelWorkbench.h>
#include "Servo.h"





void setup() {
    Servo servo1(DXL_ID1, 150, 873);
    Servo servo2(DXL_ID2, 0, 1023);
    Servo servo3(DXL_ID3, 0, 1023);
    Servo servo4(DXL_ID4, 0, 1023);

    pinMode(ANALOG_PIN1, INPUT);
    pinMode(ANALOG_PIN2, INPUT);
    pinMode(ANALOG_PIN3, INPUT);
    pinMode(ANALOG_PIN4, INPUT);

    Serial.begin(SERIAL_BAUDRATE);
    
    servos.init(DEVICE_NAME, SERVO_BAUDRATE);


//Включение сервоприводов для движения: (ID, скорость, ускорение)
    servos.jointMode(DXL_ID1, 40, 40);
    servos.jointMode(DXL_ID2, 40, 40);
    servos.jointMode(DXL_ID3, 40, 40);
    servos.jointMode(DXL_ID4, 40, 40);

//Ставим манипулятор в "центральное" положение
    servos.goalPosition(DXL_ID1, 500);
    servos.goalPosition(DXL_ID2, 500);
    servos.goalPosition(DXL_ID3, 500);
    servos.goalPosition(DXL_ID4, 500);
    delay (2000);
}


void loop() {
    Serial.print("Потенциометр 1: ");
    Serial.println(analogRead(ANALOG_PIN1));
    Serial.print("Потенциометр 2: ");
    Serial.println(analogRead(ANALOG_PIN2));
    Serial.print("Потенциометр 3: ");
    Serial.println(analogRead(ANALOG_PIN3));
    Serial.print("Потенциометр 4: ");
    Serial.println(analogRead(ANALOG_PIN4));
    Serial.print("\n");

    //servo1.setAngle(map((int)analogRead(ANALOG_PIN1), 0, 1023, 150, 873));
    servos.goalPosition(DXL_ID2, map((int)analogRead(ANALOG_PIN2), 0, 1023, 400, 660));
    servos.goalPosition(DXL_ID3, map((int)analogRead(ANALOG_PIN3), 0, 1023, 200, 600));
    servos.goalPosition(DXL_ID4, map((int)analogRead(ANALOG_PIN4), 0, 1023, 500, 1000));
}
