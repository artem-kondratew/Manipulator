//
// Created by user on 05.03.23.
//

#ifndef MANIPULATOR_CONNECT_H
#define MANIPULATOR_CONNECT_H


#include <iostream>
#include <fcntl.h>
#include <unistd.h>


#define START_BYTE 64
#define CONNECT_DXL_ID 0
#define CONNECT_TASK 0
#define CONNECT_MID 43
#define COMMAND_SIZE 7
#define MESSAGE_SIZE 7


class Connect {
private:
    inline static int Arduino = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NONBLOCK);
public:
    inline static char command[COMMAND_SIZE];
    inline static char message[MESSAGE_SIZE];

    static void clearCommand();

    static bool setConnection();

    static bool openArduino();

    static void calcCommandCheckSum();
    static char calcMessageCheckSum();

    static void sendCommand();

    static void receiveMessage();

    static bool checkMessage();
};


#endif //MANIPULATOR_CONNECT_H