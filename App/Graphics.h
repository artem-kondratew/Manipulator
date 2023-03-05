//
// Created by user on 05.03.23.
//

#ifndef MANIPULATOR_GRAPHICS_H
#define MANIPULATOR_GRAPHICS_H


#include <csignal>
#include "ncurses.h"


void finish() {
    clear();
    refresh();
    resetty();
    endwin();
    exit(0);
}


void sigHandler(int sig) {
    if (sig == SIGINT) {
        finish();
    }
}


void printTable() {
    for (int i = 1; i < 5; i++) {
        move(i, 0);
        printw("servo%d", i);
    }

    move(0, 8);
    printw("angle");
    move(0, 16);
    printw("speed");
    move(0, 24);
    printw("boost");

    move(0, 32);
    printw("old_angle");
    move(0, 42);
    printw("old_speed");
    move(0, 52);
    printw("old_boost");

    move(0, 70);
    printw("torque");
    move(0, 78);
    printw("old_torque");

    move(6, 0);
    printw("Set command:");
    move(6, 13);
    refresh();
}


void initGraphics() {
    initscr();
    savetty();  //  save terminal settings

    //nonl();  //  deny going to the new line

    //cbreak();  //  буфер передается без нажатия enter
    echo();  //  не отображается печать символов
    //timeout(0); //  буфер передается без нажатия enter

    //leaveok(stdscr, TRUE);  //  сдвиг курсора - нормально
    //curs_set(0);  //  hide cursor
    //keypad(stdscr, TRUE);

    signal(SIGINT, sigHandler);
    clear();
    refresh();
    printTable();
}


#endif //MANIPULATOR_GRAPHICS_H
