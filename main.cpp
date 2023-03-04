
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>


int main () {
    struct termios oldsettings, newsettings;
    tcgetattr(fileno(stdin), &oldsettings);
    newsettings = oldsettings;

    newsettings.c_lflag &= ~(ECHO|ICANON|ISIG);
    newsettings.c_cc[VMIN] = 1;
    newsettings.c_cc[VTIME] = 1;
    tcsetattr(fileno(stdin), TCSANOW, &newsettings);

    printf("press [q] to quit\n");

    char rd_ch = '\0';
    int fd_in = open ("/dev/tty", O_RDONLY);
    while(rd_ch != 'q') {
        read(fd_in, &rd_ch, 1);
    }
    tcsetattr(fileno(stdin), TCSANOW, &oldsettings);
    return 0;
}