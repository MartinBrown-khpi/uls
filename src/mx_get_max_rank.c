#include "uls.h"

int mx_get_max_size_rank(long_data_t **all_long_data, int size, all_flags_t *usable_flags) {
    int bigger_dog = 0;

    if (usable_flags->is_a) {
        for (int i = 0; i < size; i++) {
            if (all_long_data[i]->f_size > bigger_dog) {
                bigger_dog = all_long_data[i]->f_size;
            }
        }
    }
    else if (usable_flags->is_A) {
        for (int i = 0; i < size; i++) {
            if (all_long_data[i]->f_size > bigger_dog && 
            mx_strcmp(all_long_data[i]->f_namefile, "." != 0) &&
            mx_strcmp(all_long_data[i]->f_namefile, ".." != 0)) {
                bigger_dog = all_long_data[i]->f_size;
            }
        }
    }
    else {
        for (int i = 0; i < size; i++) {
            if (all_long_data[i]->f_size > bigger_dog && all_long_data[i]->f_namefile[0] != '.') {
                bigger_dog = all_long_data[i]->f_size;
            }
        }
    }

    return bigger_dog;
}
