#ifndef ULS_H
#define ULS_H

#include "libmx.h"
#include <sys/stat.h>

static int COUNT_FLAGS = 1;
static char FLAGS[1] = {'l'};

typedef struct cur_flags {
    char *flags;
    int count;
} cur_flags_t;

//ERRORS
void mx_printerr(const char *err);
void mx_usage(int argc);
void mx_print_usage();
// PARSE FLAGS 
cur_flags_t *mx_get_flags(int argc, char const *argv[]);

bool is_valid_flag(char flag);
bool is_in_cur_flags(cur_flags_t *cur_flags, char flag);

#endif /* ULS_H */
