#include "uls.h"

void mx_print_month(char **splitarrtime) {
    mx_printstr(splitarrtime[1]);
}

void mx_print_day(char **splitarrtime) {
    mx_printchar(' ');
    int day = mx_atoi(splitarrtime[2]);
    if (day < 10) {
        mx_printchar(' ');
    }
    mx_printint(day);
}

void mx_print_time(char **splitarrtime) {
    mx_printchar(' ');
    int sec = 2; 
    for (int i = 0; sec != 0; i++) {
        mx_printchar(splitarrtime[3][i]);
        if (splitarrtime[3][i + 1] == ':') {
            sec--;
        }
    }
}

void mx_print_year(char **splitarrtime) {
    mx_printchar(' ');
    for (int i = 0; splitarrtime[4][i] != '\n'; i++) {
        mx_printchar(splitarrtime[4][i]);
    }
}
