#include "uls.h"

void mx_print_list(long_data_t **all_long_data, int size_dirp, all_flags_t *usable_flags) {
    for (int i = 0; i < size_dirp; i++) {
        if (usable_flags->is_a) {
            mx_print_namefile(all_long_data[i], usable_flags);
            mx_printchar('\n');
        }
        else if (usable_flags->is_A) {
            if (mx_strcmp(all_long_data[i]->f_namefile, ".") != 0 &&
                mx_strcmp(all_long_data[i]->f_namefile, "..")) {
                mx_print_namefile(all_long_data[i], usable_flags);
                mx_printchar('\n');
            }
        }
        else {
            if (all_long_data[i]->f_namefile[0] != '.') {
                mx_print_namefile(all_long_data[i], usable_flags);
                mx_printchar('\n');
            }
        }
    }
}
