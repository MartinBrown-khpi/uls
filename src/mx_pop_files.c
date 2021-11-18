#include "uls.h"

char **mx_pop_files(char **arguments, int *count_arguments, int *count_files) {
    char **files = malloc(sizeof(char *) *  *count_arguments);
    struct stat buff;
    int is_fault = 0;
    for (int i = 0; i < *count_arguments; i++) {
        is_fault = lstat(arguments[i], &buff);
        if (!S_ISDIR(buff.st_mode)) {
            files[*count_files] = mx_strdup(arguments[i]);
            mx_strdel(&arguments[i]);
            arguments[i] = NULL;
            *count_files = *count_files + 1;
        }
    }
    return files;
}
