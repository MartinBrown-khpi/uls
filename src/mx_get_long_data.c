#include "uls.h"
#include <stdio.h>

long_data_t **mx_get_all_long_data(int first_file, int argc, char const *argv[]){

    long_data_t ** all_data = malloc(sizeof(long_data_t*) * 15);
    printf("%c\r", argv[0][0]);
    argc++;
    int index = 0;
    for (int i = first_file; i < 15; i++) {
        all_data[index] = mx_get_long_info("src");
        index++;
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
