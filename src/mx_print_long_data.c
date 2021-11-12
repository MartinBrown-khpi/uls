#include "uls.h"

#include <stdio.h>
void mx_print_long_data(long_data_t **all_long_data) {
    printf("%lld", all_long_data[0]->f_size);
}
