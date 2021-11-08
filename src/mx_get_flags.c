#include "uls.h"

cur_flags_t *mx_get_flags(int argc, char const *argv[]) {
    cur_flags_t *cur_flags = malloc(sizeof(cur_flags_t));
    cur_flags->flags = NULL;
    cur_flags->count = 0;
    
    char *cur_flags_tmp;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            
            return cur_flags;
        }
        for (int j = 1; j < mx_strlen(argv[i]); j++) {
            if (!is_valid_flag(argv[i][j])) {
                mx_print_usage();
                exit(1);
            }
            else {
                if (!is_in_cur_flags(cur_flags, argv[i][j])) {
                    cur_flags->count++;
                    cur_flags_tmp = mx_strnew(cur_flags->count);
                    mx_strcpy(cur_flags_tmp, cur_flags->flags);
                    cur_flags_tmp[cur_flags->count - 1]  = argv[i][j];

                    if (cur_flags->flags != NULL) {
                        free(cur_flags->flags);
                    }
                    cur_flags->flags = cur_flags_tmp;
                }
            }
        }    
    }
    return cur_flags;
}

bool is_in_cur_flags(cur_flags_t *cur_flags, char flag) {
    if (cur_flags->count == 0) {
        return false;
    }
    for (int i = 0; i < cur_flags->count; i++) {
        if (cur_flags->flags[i] == flag) {
            return true;
        }
    }

    return false;
}

bool is_valid_flag(char flag)  {
    for (int i = 0; i < COUNT_FLAGS; i++) {
        if (FLAGS[i] == flag) {
            return true;
        }
    }
    return false;
}

