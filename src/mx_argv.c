#include "uls.h"


char *agruments_filter(long_data_t **data, int size_dirp, all_flags_t *cur) {
    char *str;
    char *temp_string = NULL;

    for (int i = 0; i < size_dirp; i++) {
        if (cur->is_A) {
            if (mx_strcmp(data[i]->f_namefile, ".") == 0 ||
                mx_strcmp(data[i]->f_namefile, "..") == 0) {
                    continue;
                }
        }
        //seg fault
        if (!cur->is_a && !cur->is_A) {
            if (data[i]->f_namefile[0] == '.') {
                continue;
            }
        }

        if (data[i]->f_pathfile || (str = mx_memrchr(data[i]->f_namefile , '/', mx_strlen(data[i]->f_namefile))) == NULL) {
            temp_string = mx_strjoin(temp_string, data[i]->f_namefile);
        }
        else {
            str++;
            temp_string = mx_strjoin(temp_string, str);
        }
        if(data[i]->f_mode == DT_DIR)
            temp_string = mx_strjoin(temp_string, "/");
        temp_string = mx_strjoin(temp_string, "\n");
    }
    return temp_string;
}

int mx_get_rows_count(const char* str) {
    int rows_count = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            rows_count++;
        }
    }
    return rows_count;
}

int count_dir_and_files(int argc, char const *argv[]) {
    int arguments_count = -1;
    int first_file = mx_get_first_file(argc, argv);
    if (first_file == -1) first_file = 100;
    for (int i = 0; i < argc; i++) {
        if (argv[i][0] != '-' || i > first_file) {
            arguments_count++;
        }
    }
    return arguments_count;
}


char **parse_arguments(int argc, char const *argv[], int *arguments_count) {
    struct stat buff;
    int first_file = mx_get_first_file(argc, argv);
    if (first_file == -1) first_file = 100;
    char **arguments = malloc(sizeof(char *) * *arguments_count);
    for (int i = 1, j = 0; i < argc && j < *arguments_count; i++) {
        if (argv[i][0] != '-' || i > first_file) {
            if (stat(argv[i], &buff) == -1) {
                mx_printerr("uls");
                mx_printerr(": ");
                mx_printerr(argv[i]);
                mx_printerr(": ");
                mx_printerr(strerror(errno));
                mx_printerr("\n");
                *arguments_count = *arguments_count - 1;
            }
            else {
                arguments[j] = mx_strdup(argv[i]);
                j++;
            }


        }
    }
    return arguments;
}
