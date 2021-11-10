#ifndef ULS_H
#define ULS_H

#include "libmx.h"
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <dirent.h>
static int COUNT_FLAGS = 4;
static char FLAGS[4] = {'l', 'a', 'A', '1'};

typedef struct cur_flags {
    char *flags;
    int count;
} cur_flags_t;

typedef struct all_flags {
    bool is_long;
    bool is_list;
    bool is_A;
    bool is_a;
}all_flags_t;



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
#endif /* ULS_H */
