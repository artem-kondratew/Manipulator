//
// Created by user on 05.03.23.
//

#ifndef MANIPULATOR_CONNECT_H
#define MANIPULATOR_CONNECT_H


#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <chrono>
#include <cstring>
#include "../Config.h"

/*
#define START_BYTE 64
#define CONNECT_DXL_ID 43
#define CONNECT_TASK 0
#define CONNECT_VALUE 43
#define COMMAND_SIZE 7
#define MESSAGE_SIZE 7
#define TIMER 200
*/

class Connect {
private:
    inline static bool message_flag = false;
    inline static int Arduino = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NONBLOCK);
public:
    inline static char command[COMMAND_SIZE];
    inline static char message[MESSAGE_SIZE];

    static void clearCommand();

    static void setConnection();

    static bool openArduino();

    static void calcCommandCheckSum();

    static char calcMessageCheckSum(const char buffer[]);

    static void sendCommand();

    static void receiveMessage();

    static void setId(char id);

    static void setTask(char task);

    static void setValue(uint16_t value);

    static void decodeCommand(uint64_t com);
};


#endif //MANIPULATOR_CONNECT_H
