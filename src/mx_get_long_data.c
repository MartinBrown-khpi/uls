#include "uls.h"
#include <stdio.h>

long_data_t **mx_get_all_long_data(int size_dirp, struct dirent **dirp){

    long_data_t ** all_data = malloc(sizeof(long_data_t*) * size_dirp);
    for (int i = 0; i < size_dirp; i++) {
        all_data[i] = mx_get_long_info(dirp[i]->d_name);
    }
    return all_data;
}



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
