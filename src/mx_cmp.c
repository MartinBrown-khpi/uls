#include "uls.h"


//return true if 1 > 2
bool default_cmp(long_data_t *first, long_data_t *sec) {
    if (!first || !sec) {
        mx_printerr("NULL pointer in default cmp");
        return false;
    }

    if (mx_strcmp(first->f_namefile, ".") == 0) {
        return false;
    }

    if (mx_strcmp(first->f_namefile, "..") == 0 && mx_strcmp(sec->f_namefile, ".") != 0) {
        return false;
    }

    if (mx_strcmp(first->f_namefile, sec->f_namefile) > 0) {
        return true;
    }

    return false;
} 
