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
#include "../Arduino/Config.h"
#include "str.h"
#include "Gservo.h"


class Connect {
private:
    //inline static bool message_flag = false;
    inline static int Arduino = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NONBLOCK);
public:
    inline static char command[COMMAND_SIZE];
    inline static char message[MESSAGE_SIZE];
    inline static str key_cmd;

    static void clearCommand();

    static bool openArduino();

    static void setConnection();

    static void disconnectArduino();

    static void calcCommandCheckSum();

    static char calcMessageCheckSum(const char buffer[]);

    static void sendCommand();

    static void setId(char id);

    static void setTask(char task);

    static void setValue(uint16_t value);

    static void encodeCommand(uint64_t cmd);

    static bool receiveMessage();

    static void decodeMessage();

    static void decodeKeyInput(const std::string& cmd);
};


#endif //MANIPULATOR_CONNECT_H
