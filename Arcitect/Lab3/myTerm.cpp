#include "myTerm.h"

int mt_clrscr (void){
    printf("\033[H\033[2J\033[3J");
    return 1;
}

int mt_gotoXY(int x, int y) {
    printf("\033[%d;%dH", y, x);
    return 1;
}

int mt_getscreensize (int* rows, int* cols){
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    *rows = w.ws_row;
    *cols = w.ws_col;
    return 1;
}

int mt_setfgcolor (enum Colors colors){
    switch(colors){
        case Black:
            printf("\033[0;30m");
            break;
        case Dark_Gray:
            printf("\033[1;30m");
            break;
        case Blue:
            printf("\033[0;34m");
            break;
        case Light_Blue:
            printf("\033[1;34m");
            break;
        case Green:
            printf("\033[0;32m");
            break;
        case Light_Green:
            printf("\033[1;32m");
            break;
        case Cyan:
            printf("\033[0;36m");
            break;
        case Light_Cyan:
            printf("\033[1;36m");
            break;
        case Red:
            printf("\033[0;31m");
            break;
        case Light_Red:
            printf("\033[1;31m");
            break;
        case Purple:
            printf("\033[0;35m");
            break;
        case Light_Purple:
            printf("\033[1;35m");
            break;
        case Brown:
            printf("\033[0;33m");
            break;
        case Yellow:
            printf("\033[1;33m");
            break;
        case Light_Gray:
            printf("\033[0;37m");
            break;
        case White:
            printf("\033[1;37m");
            break;
        default:
            break;
    }
    return 1;
}

int mt_setbgcolor (enum Colors colors){
    switch(colors){
        case Black:
            printf("\033[40m");
            break;
        case Blue:
            printf("\033[44m");
            break;
        case Green:
            printf("\033[42m");
            break;
        case Cyan:
            printf("\033[46m");
            break;
        case Red:
            printf("\033[41m");
            break;
        case Purple:
            printf("\033[45m");
            break;
        case Brown:
            printf("\033[43m");
            break;
        default:
            break;
    }
    return 1;
}
