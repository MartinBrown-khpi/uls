#include "uls.h"

int mx_get_total(long_data_t **all_long_data, int size, all_flags_t *usable_flags) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        if (usable_flags->is_a) {
            sum += all_long_data[i]->f_bloks;
        }
        else if (usable_flags->is_A) {
            if (mx_strcmp(all_long_data[i]->f_namefile, ".") != 0 &&
                mx_strcmp(all_long_data[i]->f_namefile, "..")) {
                sum += all_long_data[i]->f_bloks;
                }
        }
        else{
            if (all_long_data[i]->f_namefile[0] != '.') {
                sum += all_long_data[i]->f_bloks;
            }
        }
        
    }
    return sum;
}
