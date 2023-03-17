
#ifndef Config_h
#define Config_h


#include <cstdint>


#define DEVICE_NAME "3"

#define SERVO_BAUDRATE 1000000
#define SERIAL_BAUDRATE 57600

#define DXL_ID1 1
#define DXL_ID2 2
#define DXL_ID3 3
#define DXL_ID4 4


#define START_BYTE 64
#define CONNECT_DXL_ID 0
#define CONNECT_TASK 0
#define CONNECT_VALUE 43
#define COMMAND_SIZE 7
#define MESSAGE_SIZE 10
#define TIMER 200

#define ID_CELL 2
#define TASK_CELL 3
#define VALUE1_CELL 4
#define VALUE2_CELL 5
#define CHECKSUM_CELL 6


#define SERVO1_MIN_ANGLE 150
#define SERVO1_MAX_ANGLE 853

#define SERVO2_MIN_ANGLE 0 //200
#define SERVO2_MAX_ANGLE 1023 //550

#define SERVO3_MIN_ANGLE 0 //250
#define SERVO3_MAX_ANGLE 1023 //1023

#define SERVO4_MIN_ANGLE 511
#define SERVO4_MAX_ANGLE 1023


#define ALPHA0 SERVO2_MAX_ANGLE
#define BETA0 660
const uint16_t MIN_GAMMA = 1023 + BETA0 - ALPHA0;//1023 - ALPHA0 + SERVO4_MIN_ANGLE - BETA0; // pos 512 instead of 1023
const uint16_t MAX_GAMMA = 2 ^ 16;


#endif
