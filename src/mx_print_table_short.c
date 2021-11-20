#include "uls.h"

// Не работает с выводом в 1 строку
// Не работает с файлом в агрументе
// Нужно фильтровать аргументы исходя из флага

void mx_print_tabs_between(int width) {
    int tabs = (width / 8 + (width % 8 != 0));
    for (int i = 0; i < tabs; i++) mx_printchar('\t');
}

int mx_get_table_params(char **names, int names_count, int *cols, int *rows) {
    struct winsize ws;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	int width = 80;
	if(isatty(1))
    	width = ws.ws_col;  
	if (names_count == 0) {
        *cols = 0;
        *rows = 0;
        return 0;
    }
    int max_len = 0;
    for (int i = 0; i < names_count; i++) {
        int len = mx_strlen(names[i]);
        if (max_len < len)
            max_len = len;
    }

    while (++max_len % 8);
    *cols = width / max_len;
    if (*cols == 0) *cols = 1;
    *rows = (int) ((float) names_count / (float) (*cols)) + (names_count % *cols != 0);
    return max_len;
}

// int mx_get_cols(int file_count, int *cal_col, int *col_max_arr, int max_len) {
//     struct winsize ws;
//     ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
// 	int col = 80;
// 	if(isatty(1))
//     	col = ws.ws_col;      
//     int cur_file_size = 0;     		
// 	int *filenames_len = (int*)malloc(sizeof(int) * file_count);
// 	*cal_col = 0;
// 	int i = 0;
// 	for (int j = 0; j < file_count; j++) {
// 		filenames_len[i] = max_len;
// 		if(filenames_len[i] > col) {
// 			*cal_col = 1;
// 			col_max_arr[0] = filenames_len[i];
// 			return file_count;
// 		}				
// 		cur_file_size += filenames_len[i];
//         i++;
// 	}
// 	int base_row = cur_file_size / col;
// 	if(cur_file_size % col){
// 		base_row++;
// 	}
// 	int flag_succeed = 0;
// 	while (!flag_succeed) {
// 		int remind_width = col;
// 		*cal_col = -1;
// 		for (i = 0; i < file_count; ++i) {
// 			if (filenames_len[i] > remind_width) {
// 				break;	
// 			}
// 			if (i % base_row == 0) {
// 				++(*cal_col);
// 				col_max_arr[*cal_col] = filenames_len[i]; 
// 			}
// 			else {
// 				col_max_arr[*cal_col] = (filenames_len[i] > col_max_arr[*cal_col]) ? filenames_len[i] : col_max_arr[*cal_col];
// 			}
// 			if (i % base_row == base_row - 1) {
// 				remind_width -= col_max_arr[*cal_col];	
// 			}
// 		}
// 		if (i == file_count) {
// 			flag_succeed = 1;
// 		}
// 		else {
// 			int extra = 0;
// 			while(i < file_count) {
// 				extra += filenames_len[i++];
// 			}
// 			if(extra % col) {
// 				base_row += (extra / col + 1);
// 			}
// 			else {
// 				base_row += (extra / col);
// 			} 
// 		}
// 	}   
// 	++(*cal_col);
//     free(filenames_len);
// 	return base_row;
// }
// dobavit flags 
// В эту функцию не дожны прилетать -а -А
// Надо сортировать выше
#include <stdio.h>
void mx_print_table_short(char *temp_string ,long_data_t **all_long_data, int size, all_flags_t *cur) {
    // if (files == NULL || *files == NULL) {
    //     return;
    // }

    // if(flags->m){
    //     mx_print_comma(*files, flags, full_name);
    //     return ;
    // }
    // if(cur->is_list){
    //     mx_print_files_in_line(data, size, cur);
    //     return;
    // }

    int cols = 0;
	int rows = 0;
    
    char **file_array = mx_strsplit(temp_string, '\n');
	int file_count = mx_get_rows_count(temp_string);
    
    free(temp_string);


    // int max_len = mx_strlen(file_array[0]);
    // for (int i = 1; i < file_count; i++) {
    //     if (mx_strlen(file_array[i]) > max_len) {
    //         max_len = mx_strlen(file_array[i]);
    //     }
    // }
    // if (max_len % 8 == 0) {
    //     max_len++;
    // }
    // while (max_len % 8 != 0) {
    //     max_len++;
    // }

	int max_len = mx_get_table_params(file_array, file_count, &cols, &rows);

    // int max_len = mx_get_cols(file_count, &cols, col_max_arr, max_len);
    
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
