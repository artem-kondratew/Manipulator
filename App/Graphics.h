//
// Created by user on 05.03.23.
//

#ifndef MANIPULATOR_GRAPHICS_H
#define MANIPULATOR_GRAPHICS_H


#include <csignal>
#include "ncurses.h"
#include "Connect.h"


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
        move(i + 1, 0);
        printw("servo%d", i);
    }

    move(0, 9);
    printw("id");

    move(0, 17);
    printw("goal");
    move(0, 23);
    printw("angle");

    move(0, 34);
    printw("speed");
    move(0, 41);
    printw("boost");

    move(0, 52);
    printw("torque");

    move(0, 62);
    printw("is_moving");

    move(7, 0);
    printw("Set command:");

    refresh();
}


void print_id() {
    for (int i = 1; i < 5; i++) {
        move(i + 1, 9);
        printw("%d", i);
    }
    refresh();
}


void initGraphics() {
    initscr();
    savetty();  //  save terminal settings

    //nonl();  //  deny going to the new line

    //cbreak();  //  буфер передается без нажатия enter
    //echo();  //  не отображается печать символов
    //timeout(0); //  буфер передается без нажатия enter

    //leaveok(stdscr, TRUE);  //  сдвиг курсора - нормально
    //curs_set(0);  //  hide cursor
    //keypad(stdscr, TRUE);

    signal(SIGINT, sigHandler);

    clear();
    printTable();
    print_id();
    move(7, 13);
    refresh();

    while (true) {}
}


#endif //MANIPULATOR_GRAPHICS_H
