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
