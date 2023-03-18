#include <chrono>
#include "graphics.h"


int main() {

    Connect::setConnection();

    init_graphics();

    auto start_timer = std::chrono::system_clock::now();
    while (true) {

        key_proc(getch());

        auto end_timer = std::chrono::system_clock::now();
        if (std::chrono::duration_cast<std::chrono::milliseconds>(end_timer - start_timer).count() > int(TIMER)) {
            Connect::sendCommand();
            if (Connect::receiveMessage()) {
                Connect::decodeMessage();
                print_params();
            }
            start_timer = std::chrono::system_clock::now();
        }
    }
}
