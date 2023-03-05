#include <chrono>
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include "Graphics.h"
#include "Connect.h"


int main() {

    //Connect::setConnection();

    //initGraphics();

    Connect::command[0] = 64;
    Connect::command[1] = 64;
    Connect::command[2] = 43;
    Connect::command[3] = 84;
    Connect::command[4] = 89;
    Connect::command[5] = 65;

            auto start_timer = std::chrono::system_clock::now();
    while (true) {
        auto end_timer = std::chrono::system_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(end_timer - start_timer).count() > int(200)) {
            Connect::sendCommand();
            Connect::receiveMessage();
            start_timer = std::chrono::system_clock::now();
        }

    }
}
