
#ifndef Config_h
#define Config_h


#include <cstdint>


#define DEVICE_NAME             "3"

#define SERVO_BAUDRATE      1000000
#define SERIAL_BAUDRATE        9600

#define DXL_ID1                   1
#define DXL_ID2                   2
#define DXL_ID3                   3
#define DXL_ID4                   4

#define DEFAULT_SPEED           100
#define DEFAULT_BOOST            40

#define SERVO1_START_POSITION   512
#define SERVO2_START_POSITION   512
#define SERVO3_START_POSITION   512
#define SERVO4_START_POSITION   512


#define TIMER                   100
#define START_BYTE               64

#define PING_DXL_ID               0
#define PING_TASK                 0
#define PING_VALUE1               0
#define PING_VALUE2               0

#define COMMAND_START_BYTE1_CELL  0
#define COMMAND_START_BYTE2_CELL  1
#define COMMAND_ID_CELL           2
#define COMMAND_TASK_CELL         3
#define COMMAND_VALUE1_CELL       4
#define COMMAND_VALUE2_CELL       5
#define COMMAND_CHECKSUM_CELL     6
#define COMMAND_SIZE              7

#define SHORT_COMMAND_ID_CELL     0
#define SHORT_COMMAND_TASK1_CELL  1
#define SHORT_COMMAND_TASK2_CELL  2
#define SHORT_COMMAND_VALUE1_CELL 3
#define SHORT_COMMAND_VALUE2_CELL 4
#define SHORT_COMMAND_SIZE        5

#define MESSAGE_START_BYTE1_CELL  0
#define MESSAGE_START_BYTE2_CELL  1
#define MESSAGE_ID_CELL           2
#define MESSAGE_ANGLE1_CELL       3
#define MESSAGE_ANGLE2_CELL       4
#define MESSAGE_SPEED1_CELL       5
#define MESSAGE_SPEED2_CELL       6
#define MESSAGE_TORQUE1_CELL      7
#define MESSAGE_TORQUE2_CELL      8
#define MESSAGE_IS_MOVING_CELL    9
#define MESSAGE_X1_CELL          10
#define MESSAGE_X2_CELL          11
#define MESSAGE_X_SIGN           12
#define MESSAGE_Y1_CELL          13
#define MESSAGE_Y2_CELL          14
#define MESSAGE_Y_SIGN           15
#define MESSAGE_Z1_CELL          16
#define MESSAGE_Z2_CELL          17
#define MESSAGE_Z_SIGN           18
#define MESSAGE_CHECKSUM_CELL    19
#define MESSAGE_SIZE             20

#define TASK_NUMBER              12

#define SET_ANGLE_TASK            1
#define SET_SPEED_TASK            2
#define TOOL_PUSH_TASK            3
#define TOOL_POP_TASK             4
#define GO_HOME_TASK              5


#define TOOL_MAX_LOAD           300
#define TOOL_TIMER               50


#define SERVO1_MIN_ANGLE        150
#define SERVO1_MAX_ANGLE        853

#define SERVO2_MIN_ANGLE        240
#define SERVO2_MAX_ANGLE        570

#define SERVO3_MIN_ANGLE          0
#define SERVO3_MAX_ANGLE       1023

#define SERVO4_MIN_ANGLE        512
#define SERVO4_MAX_ANGLE       1023


#endif
