#include "DynamixelWorkbench.h"
#include "Servo.h"
#include "dft.h"

//Требуется для инициализации
#define DEVICE_NAME "3"

#define SERIAL_BAUDRATE 57600  //  Боудрейт для Serial порта - 57600

//ID моторов, должны идти по возрастанию
#define DXL_ID1 1
#define DXL_ID2 2
#define DXL_ID3 3
#define DXL_ID4 4

//Пины для потенциометров
#define ANALOG_PIN1 A0
#define ANALOG_PIN2 A1
#define ANALOG_PIN3 A2
#define ANALOG_PIN4 A3


//Создание рабочего пространства servos
    DynamixelWorkbench servos;

void setup() {
    
//Задаем всем аналоговым пинам то, что они работают на вход, также и
//0для цифровых, кроме звукоизлучателя, для него - выход.
    pinMode(ANALOG_PIN1, INPUT);
    pinMode(ANALOG_PIN2, INPUT);
    pinMode(ANALOG_PIN3, INPUT);
    pinMode(ANALOG_PIN4, INPUT);
    pinMode(8, INPUT);
    pinMode(9, INPUT);

    Serial.begin(SERIAL_BAUDRATE);

//Инициализируем сервоприводы
    servos.init(DEVICE_NAME, Servo::SERVO_BAUDRATE);

//"Включаем" сервоприводы,
    servos.ping(DXL_ID1, 0, 0);
    servos.ping(DXL_ID2, 0, 0);
    servos.ping(DXL_ID3, 0, 0);
    servos.ping(DXL_ID4, 0, 0);

//Включение сервоприводов для движения: (ID, скорость, ускорение)
    servos.jointMode(DXL_ID1, 40, 40);
    servos.jointMode(DXL_ID2, 40, 40);
    servos.jointMode(DXL_ID3, 40, 40);
    servos.jointMode(DXL_ID4, 40, 40);

//Ставим манипулятор в "центральное" положение. Ждем 5 секунд для
//выполнения
    servos.goalPosition(DXL_ID1, 500);
    servos.goalPosition(DXL_ID2, 500);
    servos.goalPosition(DXL_ID3, 500);
    servos.goalPosition(DXL_ID4, 500);
    //delay (2000);
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

    servos.goalPosition(DXL_ID1, map((int)analogRead(ANALOG_PIN1), 0, 1023, 300, 800));
    servos.goalPosition(DXL_ID2, map((int)analogRead(ANALOG_PIN2), 0, 1023, 400, 660));
    servos.goalPosition(DXL_ID3, map((int)analogRead(ANALOG_PIN3), 0, 1023, 200, 600));
    servos.goalPosition(DXL_ID4, map((int)analogRead(ANALOG_PIN4), 0, 1023, 500, 1000));
}
