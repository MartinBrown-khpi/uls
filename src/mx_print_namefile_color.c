#include "uls.h"

void mx_print_namefile(long_data_t *long_data, all_flags_t *usable_flags) {
    if (usable_flags->is_long) {
        mx_printchar(' ');
    }

    if (usable_flags->is_G_color) {
        if (long_data->f_redable_mode[0] == 'd') {
            mx_printstr(ANSI_COLOR_BLUE);
            mx_printstr(long_data->f_namefile);
            mx_printstr(ANSI_COLOR_RESET);
        }
        else if (long_data->f_redable_mode[0] == '-' && long_data->f_redable_mode[3] == 'x') {
            mx_printstr(ANSI_COLOR_RED);
            mx_printstr(long_data->f_namefile);
            mx_printstr(ANSI_COLOR_RESET);
        }
        else if S_ISLNK( long_data->f_mode ) {
            mx_printstr(ANSI_COLOR_MAGENTA);
            mx_printstr(long_data->f_namefile);
            mx_printstr(ANSI_COLOR_RESET);
        }
        else {
            mx_printstr(long_data->f_namefile);
        }
        
    }
    else {
        mx_printstr(long_data->f_namefile);
    }
}
