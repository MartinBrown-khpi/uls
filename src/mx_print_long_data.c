#include "uls.h"

#include <stdio.h>
void mx_print_long_data(long_data_t **all_long_data, int size, all_flags_t *usable_flags) {
    int *arr = malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        arr[i] = all_long_data[i]->f_links;
    }
    int max_rank_link = mx_get_rank(mx_get_max_int(arr, size));
    free(arr);

    arr = malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        arr[i] = all_long_data[i]->f_size;
    }
    int max_rank_size = mx_get_rank(mx_get_max_int(arr, size));
    free(arr);

    for (int i = 0; i < size; i++) {
        if (usable_flags->is_a) {
            mx_print_redable_mode(all_long_data[i]);
            mx_print_links(all_long_data[i], max_rank_link);
            mx_print_redable_uid(all_long_data[i]);
            mx_print_redable_gid(all_long_data[i]);
            mx_print_size(all_long_data[i], max_rank_size);
            mx_printchar('\n');
        }
    }
}

void mx_print_redable_mode(long_data_t *long_data) {
    mx_printstr(long_data->f_redable_mode);
}

void mx_print_links(long_data_t *long_data, int max_rank_link) {
    int rank_data = mx_get_rank(long_data->f_links);
    for (int i = 0; i < 2 + max_rank_link - rank_data; i++) {
        mx_printchar(' ');
    }
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

void mx_print_size(long_data_t *long_data, int max_rank_size) {
    int rank_data = mx_get_rank(long_data->f_size);
    for (int i = 0; i < 2 + max_rank_size - rank_data; i++) {
        mx_printchar(' ');
    }
    mx_printint(long_data->f_size);
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
