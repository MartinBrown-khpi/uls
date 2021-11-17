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
            mx_strcmp(all_long_data[i]->f_namefile, ".") != 0 &&
            mx_strcmp(all_long_data[i]->f_namefile, "..") != 0) {
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

int mx_get_max_link_rank(long_data_t **all_long_data, int size, all_flags_t *usable_flags) {
    int bigger_dog = 0;

    if (usable_flags->is_a) {
        for (int i = 0; i < size; i++) {
            if (all_long_data[i]->f_links > bigger_dog) {
                bigger_dog = all_long_data[i]->f_links;
            }
        }
    }
    else if (usable_flags->is_A) {
        for (int i = 0; i < size; i++) {
            if (all_long_data[i]->f_links > bigger_dog && 
            mx_strcmp(all_long_data[i]->f_namefile, ".") != 0 &&
            mx_strcmp(all_long_data[i]->f_namefile, "..") != 0) {
                bigger_dog = all_long_data[i]->f_links;
            }
        }
    }
    else {
        for (int i = 0; i < size; i++) {
            if (all_long_data[i]->f_links > bigger_dog && all_long_data[i]->f_namefile[0] != '.') {
                bigger_dog = all_long_data[i]->f_links;
            }
        }
    }

    return bigger_dog;
}

int mx_get_biggest_uid(long_data_t **all_long_data, int size, all_flags_t *usable_flags) {
    int bigger_dog = 0;

    if (usable_flags->is_a) {
        for (int i = 0; i < size; i++) {
            if (mx_strlen(all_long_data[i]->f_redable_id) > bigger_dog) {
                bigger_dog = mx_strlen(all_long_data[i]->f_redable_id);
            }
        }
    }
    else if (usable_flags->is_A) {
        for (int i = 0; i < size; i++) {
            if (mx_strlen(all_long_data[i]->f_redable_id) > bigger_dog && 
            mx_strcmp(all_long_data[i]->f_namefile, ".") != 0 &&
            mx_strcmp(all_long_data[i]->f_namefile, "..") != 0) {
                bigger_dog = mx_strlen(all_long_data[i]->f_redable_id);
            }
        }
    }
    else {
        for (int i = 0; i < size; i++) {
            if (mx_strlen(all_long_data[i]->f_redable_id) > bigger_dog && all_long_data[i]->f_namefile[0] != '.') {
                bigger_dog = mx_strlen(all_long_data[i]->f_redable_id);
            }
        }
    }
    
    return bigger_dog;
}

int mx_get_biggest_gid(long_data_t **all_long_data, int size, all_flags_t *usable_flags) {
    int bigger_dog = 0;

    if (usable_flags->is_a) {
        for (int i = 0; i < size; i++) {
            if (mx_strlen(all_long_data[i]->f_redable_gid) > bigger_dog) {
                bigger_dog = mx_strlen(all_long_data[i]->f_redable_gid);
            }
        }
    }
    else if (usable_flags->is_A) {
        for (int i = 0; i < size; i++) {
            if (mx_strlen(all_long_data[i]->f_redable_gid) > bigger_dog && 
            mx_strcmp(all_long_data[i]->f_namefile, ".") != 0 &&
            mx_strcmp(all_long_data[i]->f_namefile, "..") != 0) {
                bigger_dog = mx_strlen(all_long_data[i]->f_redable_gid);
            }
        }
    }
    else {
        for (int i = 0; i < size; i++) {
            if (mx_strlen(all_long_data[i]->f_redable_gid) > bigger_dog && all_long_data[i]->f_namefile[0] != '.') {
                bigger_dog = mx_strlen(all_long_data[i]->f_redable_gid);
            }
        }
    }
    
    return bigger_dog;
}
