#ifndef ULS_H
#define ULS_H

#include "libmx.h"
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <dirent.h>
static int COUNT_FLAGS = 9;
static char FLAGS[9] = {'l', 'a', 'A', '1', 'r', 't', 'u', 'c', 'S'};

typedef struct cur_flags {
    char *flags;
    int count;
} cur_flags_t;

typedef struct all_flags {
    bool is_long;
    bool is_list;
    bool is_A;
    bool is_a;
    bool is_reverse;
    bool is_common_sort;
    bool is_t_sort;
    bool is_u_sort;
    bool is_c_sort;
    bool is_S_sort;
}all_flags_t;

typedef struct long_data {
    mode_t f_mode;
    nlink_t f_links;
    uid_t f_uid;
    gid_t f_gid;
    off_t f_size;
    struct timespec *f_time_change;
    char *f_namefile;
}long_data_t;

// help func
int mx_get_first_file(int argc, char const *argv[]);

//ERRORS
void mx_printerr(const char *err);

void mx_illegal_option(char const *argv[] ,char flag);
void mx_usage(int argc);
void mx_print_usage();
// PARSE FLAGS 
cur_flags_t *mx_get_flags(int argc, char const *argv[]);

bool is_valid_flag(char flag);
bool is_in_cur_flags(cur_flags_t *cur_flags, char flag);
void move_char_back(char *arr, int size, char ch);

//LS -l
long_data_t **mx_get_all_long_data(int size_dirp, struct dirent **dirp);
long_data_t *mx_get_long_info(const char *filename);
#endif /* ULS_H */
