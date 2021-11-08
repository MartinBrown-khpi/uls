#include "uls.h"

void mx_usage(int argc) {
    if (argc < 2) {
        mx_print_usage();
        exit(1);
    }
}


void mx_print_usage() {
    mx_printerr("usage : uls ");
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
