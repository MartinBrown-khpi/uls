#include "uls.h"

#include <stdio.h>

// TODO getxattr @ + ровняние типа
void mx_print_long_data(long_data_t **all_long_data, int size, all_flags_t *usable_flags) {

    for (int i = 0; i < size; i++) {
        if (usable_flags->is_a) {
            mx_print_redable_mode(all_long_data[i]);
            mx_print_links(all_long_data[i]);
            mx_print_redable_uid(all_long_data[i]);
            mx_print_redable_gid(all_long_data[i]);
            mx_print_size(all_long_data, i, size, usable_flags);
            mx_print_date_time(all_long_data[i], usable_flags);
            mx_print_namefile(all_long_data[i], usable_flags);
            mx_printchar('\n');
        }
        else if (usable_flags->is_A) {
            if (mx_strcmp(all_long_data[i]->f_namefile, ".") != 0 &&
                mx_strcmp(all_long_data[i]->f_namefile, "..")) {
                mx_print_redable_mode(all_long_data[i]);
                mx_print_links(all_long_data[i]);
                mx_print_redable_uid(all_long_data[i]);
                mx_print_redable_gid(all_long_data[i]);
                mx_print_size(all_long_data, i, size, usable_flags);
                mx_print_date_time(all_long_data[i], usable_flags);
                mx_print_namefile(all_long_data[i], usable_flags);
                mx_printchar('\n');
            } 
        }  
        else {
            if (all_long_data[i]->f_namefile[0] != '.') {
                mx_print_redable_mode(all_long_data[i]);
                mx_print_links(all_long_data[i]);
                mx_print_redable_uid(all_long_data[i]);
                mx_print_redable_gid(all_long_data[i]);
                mx_print_size(all_long_data, i, size, usable_flags);
                mx_print_date_time(all_long_data[i], usable_flags);
                mx_print_namefile(all_long_data[i], usable_flags);
                mx_printchar('\n');
            }
        }
    }
}

void mx_print_redable_mode(long_data_t *long_data) {
    mx_printstr(long_data->f_redable_mode);
}

void mx_print_links(long_data_t *long_data) {
    mx_printchar(' ');
    mx_printint(long_data->f_links);
}

void mx_print_redable_uid(long_data_t *long_data) {
    mx_printchar(' ');
    mx_printstr(long_data->f_redable_id);
}

void mx_print_redable_gid(long_data_t *long_data) {
    mx_printchar(' ');
    mx_printstr(long_data->f_redable_gid);
}

void mx_print_size(long_data_t **all_long_data, int i, int size, all_flags_t *usable_flags) {
    size++;

    if (usable_flags->is_h_long) {
        char sizes[5] = {'B', 'K', 'M', 'G', 'T'}; 
        int current_size = 0;
        float remainder = (float)all_long_data[i]->f_size;
        while (all_long_data[i]->f_size >= 1024) {
            remainder /= 1042.f;
            all_long_data[i]->f_size /= 1024;
            current_size++;

        }
        if (remainder > 0.5f) {
            all_long_data[i]->f_size++;
        }
        
        mx_printint(all_long_data[i]->f_size);
        mx_printchar(sizes[current_size]);
    }
    else {
        mx_printint(all_long_data[i]->f_size);
    }

}
// TODO неправиьно считает ранг
void mx_print_date_time(long_data_t *long_data, all_flags_t *usable_flags) {
    char *strtime = ctime(&long_data->f_time_modification->tv_sec);
    char **splitarrtime = mx_strsplit(strtime, ' ');
    if (usable_flags->is_T_long) {
        mx_print_month(splitarrtime);
        mx_print_day(splitarrtime);
        mx_printchar(' ');
        mx_printstr(splitarrtime[3]);
        mx_print_year(splitarrtime);
        mx_del_strarr(&splitarrtime);
    }
    else {

        mx_print_month(splitarrtime);
        mx_print_day(splitarrtime);
        mx_print_time(splitarrtime);    
    }
    mx_del_strarr(&splitarrtime);
}



int mx_get_max_int(int *arr, int size) {
    int max = 0;
    for (int i = 0; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    return max;
}

int mx_get_rank(int digit) {
    int rank = 0;
    while (digit > 0) {
        digit /= 10;
        rank++;
    }
    if (rank == 0) {
        return 1;
    }
    return rank;
}
