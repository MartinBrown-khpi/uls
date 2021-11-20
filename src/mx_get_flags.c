#include "uls.h"

static bool is_in_cur_flags(cur_flags_t *cur_flags, char flag) {
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

static bool is_valid_flag(const int COUNT_FLAGS, char const FLAGS[], char flag)  {
    for (int i = 0; i < COUNT_FLAGS; i++) {
        if (FLAGS[i] == flag) {
            return true;
        }
    }
    return false;
}

static void move_char_back(char *arr, int size, char ch) {
    int index = mx_get_char_index(arr, ch);
    for (int i = index; i < size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    arr[size - 1] = ch;
}

cur_flags_t *mx_get_flags(const int COUNT_FLAGS, char const FLAGS[], int argc, char const *argv[]) {
    cur_flags_t *cur_flags = malloc(sizeof(cur_flags_t));
    cur_flags->flags = NULL;
    cur_flags->count = 0;
    
    char *cur_flags_tmp;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            return cur_flags;
        }
        for (int j = 1; j < mx_strlen(argv[i]); j++) {
            if (!is_valid_flag(COUNT_FLAGS, FLAGS, argv[i][j])) {
                mx_illegal_option(argv, argv[i][j]);
                mx_print_usage(FLAGS);
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
                else {
                    move_char_back(cur_flags->flags, cur_flags->count, argv[i][j]);
                }
            }
        }    
    }
    return cur_flags;
}
