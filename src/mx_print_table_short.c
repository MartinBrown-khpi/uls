#include "uls.h"

void mx_print_tabs_between(int width) {
    int tabs = (width / 8 + (width % 8 != 0));
    for (int i = 0; i < tabs; i++) mx_printchar('\t');
}

int mx_get_table_params(char **names, int names_count, int *cols, int *rows) {
    struct winsize ws;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	int width = 80;
	if(isatty(1)) {
    	width = ws.ws_col; 
    }
	if (names_count == 0) {
        *cols = 0;
        *rows = 0;
        return 0;
    }
    int max_len = 0;
    for (int i = 0; i < names_count; i++) {
        int len = mx_strlen(names[i]);
        if (max_len < len) {
            max_len = len;
        }       
    }
    
    if (max_len % 8 == 0) {
        max_len++;
    }

    while (max_len % 8 != 0) {
        max_len++;
    }
    
    *cols = width / max_len;
    
    if (*cols == 0) {
        *cols = 1;
    }
    
    *rows = (int) ((float) names_count / (float) (*cols)) + (names_count % *cols != 0);
    return max_len;
}
 
void mx_print_table_short(char *temp_string ,long_data_t **all_long_data, int size, all_flags_t *cur) {
    int cols = 0;
	int rows = 0;
    char **file_array = mx_strsplit(temp_string, '\n');
	int file_count = mx_get_rows_count(temp_string);
    free(temp_string);
	int max_len = mx_get_table_params(file_array, file_count, &cols, &rows);
    
    for (int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){     
            if ((j * rows + i ) < file_count) {
                for (int q = 0; q < size; q++) {
                    if (mx_strcmp(all_long_data[q]->f_namefile, file_array[j * rows + i]) == 0) {
                        mx_print_namefile(all_long_data[q], cur);
                    }
                }
                if((j + 1) * rows + i < file_count) {
					int wigth = 0;
                    while (wigth < max_len - mx_strlen(file_array[j * rows + i])) {
						wigth++;
                    }
					mx_print_tabs_between(wigth);
                }
            }
        }
        mx_printchar('\n');
    }
    mx_del_strarr(&file_array);
}
