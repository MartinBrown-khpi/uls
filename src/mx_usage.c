#include "uls.h"


void mx_print_usage(char const FLAGS[]) {
    mx_printerr("usage: uls ");
    mx_printerr("[-");
    mx_printerr(FLAGS);
    mx_printerr("] ");
    mx_printerr("[file ...]\n");
}


void mx_illegal_option(char const *argv[], char flag) {
    mx_printerr(argv[0]);
    mx_printerr(": illegal option -- ");
    write(2, &flag, 1);
    mx_printerr("\n");
}
