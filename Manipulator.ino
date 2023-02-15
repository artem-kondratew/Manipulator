//Подключение библиотеки
#include <DynamixelWorkbench.h>
#include "Servo.h"

//Требуется для инициализации
#define DEVICE_NAME "3"

//Боудрейт, для моторов - 1000000, для Serial порта - 57600
#define BAUDRATE 1000000
#define SERIAL_BAUDRATE 57600

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

//Пин для ИК датчика
#define IR_SENSOR_PIN A8
//Пин для кнопки
#define BUTTON_PIN 10
//Пин для звукоизлучателя
#define BUZZ_PIN 11

//Создание рабочего пространства servos
DynamixelWorkbench servos;

void setup() {
//const char *log;
//Задаем всем аналоговым пинам то, что они работают на вход, также и
//0для цифровых, кроме звукоизлучателя, для него - выход.
pinMode(ANALOG_PIN1, INPUT);
pinMode(ANALOG_PIN2, INPUT);
pinMode(ANALOG_PIN3, INPUT);
pinMode(ANALOG_PIN4, INPUT);
pinMode(IR_SENSOR_PIN, INPUT);
pinMode(BUTTON_PIN, INPUT);
pinMode(BUZZ_PIN, OUTPUT);
Serial.begin(SERIAL_BAUDRATE);
//Инициализируем сервоприводы
servos.init(DEVICE_NAME, BAUDRATE);
//"Включаем" сервоприводы,
servos.ping(DXL_ID1, 0, 0);
servos.ping(DXL_ID2, 0, 0);
servos.ping(DXL_ID3, 0, 0);
servos.ping(DXL_ID4, 0, 0);
//Включение сервоприводов для движения: (ID, скорость, ускорение)
servos.jointMode(DXL_ID1, 100, 40);
servos.jointMode(DXL_ID2, 40, 40);
servos.jointMode(DXL_ID3, 40, 40);
servos.jointMode(DXL_ID4, 40, 40);
//Ставим манипулятор в "центральное" положение. Ждем 5 секунд для
//выполнения
servos.goalPosition(DXL_ID1, 500);
servos.goalPosition(DXL_ID2, 500);
servos.goalPosition(DXL_ID3, 500);
servos.goalPosition(DXL_ID4, 500);
delay (5000);
}
void loop() {
//Считываем значения с потенциометров и выводим в Serial порт
Serial.print("\nПотенциометр 1: ");
Serial.println(analogRead(ANALOG_PIN1));
Serial.print("Потенциометр 2: ");
Serial.println(analogRead(ANALOG_PIN2));
Serial.print("Потенциометр 3: ");
Serial.println(analogRead(ANALOG_PIN3));
Serial.print("Потенциометр 4: ");
Serial.println(analogRead(ANALOG_PIN4));
Serial.print("ИК датчик: ");
Serial.println(analogRead(IR_SENSOR_PIN));
//Если нажать на кнопку, будет сигнал на звукоизлучателе
if (digitalRead(BUTTON_PIN) == HIGH)
digitalWrite(BUZZ_PIN, HIGH);
else
digitalWrite(BUZZ_PIN, LOW);
delay (100);

Servo A(1, 200, 800);
servos.goalPosition(DXL_ID1, (int)analogRead(A0));
servos.goalPosition(DXL_ID2, (int)analogRead(A1));
servos.goalPosition(DXL_ID3, (int)analogRead(A2));
servos.goalPosition(DXL_ID4, (int)analogRead(A3));
}
