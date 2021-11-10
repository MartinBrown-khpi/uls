#include "uls.h"

long_data_t *mx_get_long_info(const char *filename) {
    struct stat buff;
    long_data_t *long_data = malloc(sizeof(long_data_t));
    long_data->f_time_change = malloc(sizeof(long_data->f_time_change));
    if (stat(filename, &buff) == -1 ) {
        mx_printerr("cant get file stat");
        return NULL;
    }

    long_data->f_mode  = buff.st_mode;
    long_data->f_links = buff.st_nlink;
    long_data->f_size = buff.st_size;
    long_data->f_uid = buff.st_uid;
    long_data->f_gid = buff.st_gid;
    long_data->f_time_change->tv_nsec = buff.st_mtimespec.tv_nsec;
    long_data->f_time_change->tv_sec = buff.st_mtimespec.tv_sec;
    long_data->f_namefile = mx_strdup(filename);
    return long_data;
}
