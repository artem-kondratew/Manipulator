#include <chrono>
#include "Graphics.h"
#include "Connect.h"


int main() {

    //Connect::setConnection();

    initGraphics();

    Connect::command[0] = 64;
    Connect::command[1] = 64;
    Connect::command[2] = 43;
    Connect::command[3] = 84;
    Connect::command[4] = 89;
    Connect::command[5] = 65;
/*
    auto start_timer = std::chrono::system_clock::now();
    while (true) {

        uint64_t cmd;
        std::cin >> cmd;
        Connect::encodeCommand(cmd);

        auto end_timer = std::chrono::system_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(end_timer - start_timer).count() > int(TIMER)) {
            Connect::sendCommand();
            Connect::receiveMessage();
            start_timer = std::chrono::system_clock::now();
        }
    }
*/


    while (true) {
        int key = getch();
        char symbol = (char)key;
        if (key == KEY_RETURN) {
            //Connect::decodeKeyInput(command);
            print_last_command();
            clear_command_line();
            Connect::key_cmd.reset();
            continue;
        }
        if (key == KEY_BACKSPACE) {
            getsyx(CURS_Y, CURS_X);
            Connect::key_cmd.setCurs(CURS_X + 1);
            Connect::key_cmd.keyBackspace();
            clear_command_line();
            print_command_line();
            move(CURS_Y, CURS_X);
            continue;
        }
        if (key == KEY_DC) {
            getsyx(CURS_Y, CURS_X);
            Connect::key_cmd.setCurs(CURS_X);
            Connect::key_cmd.keyDelete();
            clear_command_line();
            print_command_line();
            move(CURS_Y, CURS_X);
            continue;
        }
        if (key == KEY_LEFT) {
            getsyx(CURS_Y, CURS_X);
            move(CURS_Y, CURS_X - 1);
            continue;
        }
        if (key == KEY_RIGHT) {
            getsyx(CURS_Y, CURS_X);
            if (CURS_X == Connect::key_cmd.size()) {
                continue;
            }
            move(CURS_Y, CURS_X + 1);
            continue;
        }
        getsyx(CURS_Y, CURS_X);
        Connect::key_cmd.push(symbol, CURS_X - 1);
        clear_command_line();
        print_command_line();
        move(CURS_Y, Connect::key_cmd.getCurs() + 1);
        refresh();
    } // КУРСОР УЛЕТАЕТ ВПРАВО
}
