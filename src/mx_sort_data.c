#include "uls.h"

void mx_insertion_sort(long_data_t **arr, int size, bool (*cmp) (long_data_t *first, long_data_t *sec)) {
    int i, j;
    long_data_t *key = NULL;
    for (i = 0; i < size; i++) {
        key = arr[i];
        j = i - 1;
 
        /* arr[j] > key */
        while (j >= 0 && (*cmp) (arr[j], key)) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void mx_reverse_array(long_data_t **arr, int size) {
    long_data_t *tmp;
    for (int i = 0; i < size / 2; i++) {
        tmp = arr[i];
        arr[i] = arr[size-i-1];
        arr[size-i-1] = tmp;
    }
}
