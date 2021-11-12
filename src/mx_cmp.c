#include "uls.h"


//return true if 1 > 2
bool mx_default_cmp(long_data_t *first, long_data_t *sec) {
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

//return true if 1 > 2
bool mx_size_cmp(long_data_t *first, long_data_t *sec) {
    if (!first || !sec) {
        mx_printerr("NULL pointer in size cmp");
        return false;
    }
    if (first->f_size < sec->f_size) {
        return true;
    }
    return false;
}

//return true if 1 > 2
bool mx_time_modif_cmp(long_data_t *first, long_data_t *sec) {
    if (!first || !sec) {
        mx_printerr("NULL pointer in time_modif_cmp");
        return false;
    }

    if (first->f_time_modification->tv_nsec < sec->f_time_modification->tv_nsec) {
        return true;
    }
    return false;
}

bool mx_time_access_cmp(long_data_t *first, long_data_t *sec) {
    if (!first || !sec) {
        mx_printerr("NULL pointer in time_modif_cmp");
        return false;
    }

    if (first->f_time_last_acces->tv_sec < sec->f_time_last_acces->tv_sec) {
        return true;
    }
    return false;
}

bool mx_time_status_cmp(long_data_t *first, long_data_t *sec) {
    if (!first || !sec) {
        mx_printerr("NULL pointer in time_modif_cmp");
        return false;
    }

    if (first->f_time_last_status->tv_sec > sec->f_time_last_status->tv_sec) {
        return true;
    }
    return false;
}
