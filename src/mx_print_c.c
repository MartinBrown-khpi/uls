#include "uls.h"

// Не работает с выводом в 1 строку
// Не работает с файлом в агрументе
// Нужно фильтровать аргументы исходя из флага

int mx_get_cols(int file_count, int *cal_col, int *col_max_arr, int max_len) {
    struct winsize ws;
    ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	int col = 80;
	if(isatty(1))
    col = ws.ws_col;      
    int cur_file_size = 0;		
	int *filenames_len = (int*)malloc(sizeof(int) * file_count);
	*cal_col = 0;
	int i = 0;
	for (int j = 0; j < file_count; j++) {
		filenames_len[i] = max_len;
		if(filenames_len[i] > col) {
			*cal_col = 1;
			col_max_arr[0] = filenames_len[i];
			return file_count;
		}				
		cur_file_size += filenames_len[i];
        i++;
	}
	int base_row = cur_file_size / col;
	if(cur_file_size % col){
		base_row++;
	}
	int flag_succeed = 0;
	while (!flag_succeed) {
		int remind_width = col;
		*cal_col = -1;
		for (i = 0; i < file_count; ++i) {
			if (filenames_len[i] > remind_width) {
				break;	
			}
			if (i % base_row == 0) {
				++(*cal_col);
				col_max_arr[*cal_col] = filenames_len[i]; 
			}
			else {
				col_max_arr[*cal_col] = (filenames_len[i] > col_max_arr[*cal_col]) ? filenames_len[i] : col_max_arr[*cal_col];
			}
			if (i % base_row == base_row - 1) {
				remind_width -= col_max_arr[*cal_col];	
			}
		}
		if (i == file_count) {
			flag_succeed = 1;
		}
		else {
			int extra = 0;
			while(i < file_count) {
				extra += filenames_len[i++];
			}
			if(extra % col) {
				base_row += (extra / col + 1);
			}
			else {
				base_row += (extra / col);
			} 
		}
	}   
	++(*cal_col);
    free(filenames_len);
	return base_row;
}
// dobavit flags 
// В эту функцию не дожны прилетать -а -А
// Надо сортировать выше
#include <stdio.h>
void mx_print_files(char *temp_string, int size, all_flags_t *cur) {
    // if (files == NULL || *files == NULL) {
    //     return;
    // }

    // if(flags->m){
    //     mx_print_comma(*files, flags, full_name);
    //     return ;
    // }
    cur->is_A = false;
    // if(cur->is_list){
    //     mx_print_files_in_line(data, size, cur);
    //     return;
    // }

    int file_count = size;
    int cols = 0;
    int col_max_arr[256];
    
    
    int i = 0;

    char **file_array = mx_strsplit(temp_string, '\n');
    free(temp_string);

    // for(int i = 0; i < file_count; i++) {
    //     printf("%s\n", file_array[i]);
    // }

    int max_len = mx_strlen(file_array[0]);
    for (int i = 1; i < file_count; i++) {
        if (mx_strlen(file_array[i]) > max_len) {
            max_len = mx_strlen(file_array[i]);
        }
    }
    int max_temp = max_len;
    if (max_len % 8 == 0) {
        max_len++;
    }
    while (max_len % 8 != 0) {
        max_len++;
    }
    // if (cur->is_A) {
    //     file_count -= 2;
    // }
    int rows = mx_get_cols(file_count, &cols, col_max_arr, max_len);
    i = 0;
    printf("%d\n", rows);
    max_temp++;
    // eto iskusstvo 
        for (int i = 0; i < rows; i++){
            bool is_flag = false;
            for(int j = 0; j < cols; j++){     
                if ((j * rows + i ) < file_count) {
                    mx_printstr(file_array[j * rows + i]);
                    is_flag = true;
                    
                    if((j + 1) * rows + i < file_count) {
                        for (int k = 0; k < max_len - mx_strlen(file_array[j * rows + i]); k++) {
                            mx_printchar(' ');
                        }
                    }
                    
                    // if (flags->G) {
                    //     mx_find_color(file_array[j * rows + i], files, full_name);
                    // }
                }
            }
            mx_printchar('\n');
        }
    mx_del_strarr(&file_array);
}
