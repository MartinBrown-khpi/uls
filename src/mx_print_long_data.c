#include "uls.h"

#include <stdio.h>

// TODO getxattr @ + ровняние типа
void mx_print_long_data(long_data_t **all_long_data, int size, all_flags_t *usable_flags) {
    // размер  большего элемнта считается здесь для всех фуннкций кроме size (нужен пересчет для флага -h)
    int biggest_link_rank = mx_get_rank(mx_get_max_link_rank(all_long_data, size, usable_flags));
    int biggest_uid_size = mx_get_biggest_uid(all_long_data, size, usable_flags);
    int biggest_gid_size = mx_get_biggest_gid(all_long_data, size, usable_flags);
    for (int i = 0; i < size; i++) {

        if (usable_flags->is_a) {
            mx_print_redable_mode(all_long_data[i]);
            mx_print_links(all_long_data[i], biggest_link_rank);
            mx_print_redable_uid(all_long_data[i], biggest_uid_size);
            mx_print_redable_gid(all_long_data[i], biggest_gid_size);
            mx_print_size(all_long_data, i, size, usable_flags);
            mx_print_date_time(all_long_data[i], usable_flags);
            mx_print_namefile(all_long_data[i], usable_flags);
            mx_printchar('\n');
        }
        else if (usable_flags->is_A) {
            if (mx_strcmp(all_long_data[i]->f_namefile, ".") != 0 &&
                mx_strcmp(all_long_data[i]->f_namefile, "..")) {
                mx_print_redable_mode(all_long_data[i]);
                mx_print_links(all_long_data[i], biggest_link_rank);
                mx_print_redable_uid(all_long_data[i], biggest_uid_size);
                mx_print_redable_gid(all_long_data[i], biggest_gid_size);
                mx_print_size(all_long_data, i, size, usable_flags);
                mx_print_date_time(all_long_data[i], usable_flags);
                mx_print_namefile(all_long_data[i], usable_flags);
                mx_printchar('\n');
            } 
        }  
        else {
            if (all_long_data[i]->f_namefile[0] != '.') {
                mx_print_redable_mode(all_long_data[i]);
                mx_print_links(all_long_data[i], biggest_link_rank);
                mx_print_redable_uid(all_long_data[i], biggest_uid_size);
                mx_print_redable_gid(all_long_data[i], biggest_gid_size);
                mx_print_size(all_long_data, i, size, usable_flags);
                mx_print_date_time(all_long_data[i], usable_flags);
                mx_print_namefile(all_long_data[i], usable_flags);
                mx_printchar('\n');
            }
        }
    }
}

// ставит пробелы после себя 
void mx_print_redable_mode(long_data_t *long_data) {
    mx_printstr(long_data->f_redable_mode);
    if (long_data->is_link) {
        mx_printchar('@');
    }
    else if (long_data->is_plus) {
        mx_printchar('+');
    }
    else {
        mx_printchar(' ');
    }
    mx_printchar(' ');
}

// ставит пробел после себя и выводит числа по правому краю
void mx_print_links(long_data_t *long_data, int biggest_link_rank) {
    int link_rank = mx_get_rank(long_data->f_links);
    for (int i = 0; i < biggest_link_rank - link_rank; i++) {
        mx_printchar(' ');
    }
    mx_printint(long_data->f_links);
    mx_printchar(' ');
}

// выводит пользователя ставит 2 пробела после себя и ровняет по левому краю
void mx_print_redable_uid(long_data_t *long_data, int biggest_uid_size) {
    int size_uid = mx_strlen(long_data->f_redable_id);
    mx_printstr(long_data->f_redable_id);
    for (int i = 0; i < biggest_uid_size - size_uid; i++) {
        mx_printchar(' ');
    }
    mx_printchar(' ');
    mx_printchar(' ');
}

// выводи группу, ставит 2 пробела после себя и ровняет по левому краю
void mx_print_redable_gid(long_data_t *long_data, int biggest_gid_size) {
    int size_gid = mx_strlen(long_data->f_redable_gid);
    mx_printstr(long_data->f_redable_gid);
    for (int i = 0; i < biggest_gid_size - size_gid; i++) {
        mx_printchar(' ');
    }
    mx_printchar(' ');
    mx_printchar(' ');
}

// выводдит размер, ставит пробел после себя ровняет по правому краю
void mx_print_size(long_data_t **all_long_data, int i, int size, all_flags_t *usable_flags) {
    int bigger_size_rank = mx_get_rank(mx_get_max_size_rank(all_long_data, size, usable_flags));
    int size_rank = mx_get_rank(all_long_data[i]->f_size);

        if (all_long_data[i]->size_remainder != 0) {
            size_rank++;
        }

    if (usable_flags->is_h_long) {
        for (int j = 0; j < bigger_size_rank - size_rank; j++) {
            mx_printchar(' ');
        }
        
        if (all_long_data[i]->size_remainder != 0) {
            mx_printint(all_long_data[i]->f_size);
            mx_printchar('.');
            mx_printint(all_long_data[i]->size_remainder);
            mx_printchar(all_long_data[i]->type_size);
        }
        else {
            mx_printchar(' ');
            mx_printint(all_long_data[i]->f_size);
            mx_printchar(all_long_data[i]->type_size);
        }
    }
    else {
        for (int j = 0; j < bigger_size_rank - size_rank; j++) {
            mx_printchar(' ');
        } 
        mx_printint(all_long_data[i]->f_size);
    }
    mx_printchar(' ');
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
