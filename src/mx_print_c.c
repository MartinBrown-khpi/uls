#include "uls.h"

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

void mx_print_files(long_data_t **data, int size) {
    // if (files == NULL || *files == NULL) {
    //     return;
    // }

    // if(flags->m){
    //     mx_print_comma(*files, flags, full_name);
    //     return ;
    // }

    // if(flags->one){
    //     mx_print_files_in_line(*files, flags, full_name);
    //     return;
    // }

    int file_count = size;
    int cols = 0;
    int col_max_arr[256];
    char *str = NULL;
    
    char *temp_string = NULL;
    int i = 0;
    while(i < size) {
        if (data[i]->f_pathfile || (str = mx_memrchr(data[i]->f_namefile , '/', mx_strlen(data[i]->f_namefile))) == NULL) {
            temp_string = mx_strjoin(temp_string, data[i]->f_namefile);
        }
        else {
            str++;
            temp_string = mx_strjoin(temp_string, str);
        }
        if(data[i]->f_mode == DT_DIR)
            temp_string = mx_strjoin(temp_string, "/");
        temp_string = mx_strjoin(temp_string, "\n");
        i++;
    }
    char **file_array = mx_strsplit(temp_string, '\n');
    free(temp_string);

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

    int rows = mx_get_cols(file_count, &cols, col_max_arr, max_len);
    i = 0;
    if(rows == 1){
        while(i < size){
            // if (flags->G)
            // {
            //     mx_print_color(temp);
            //}
            if (data[i]->f_pathfile || (str = mx_memrchr(data[i]->f_namefile, '/', mx_strlen(data[i]->f_namefile))) == NULL) {
                str = data[i]->f_namefile;
            }
            else {
                str++;
            }
            mx_printstr(str);
            if(data[i] == NULL) mx_printchar('\n');
            else {
                mx_printchar(' ');
                int size = mx_strlen(str);
                while (size != max_temp) {
                    mx_printchar(' ');
                    size++;
                }
            }
            // if (flags->G)
            // {
            //     mx_printstr(NO_COLOR);
            // }
            i++;
        }
    }
    else {
        for (int i = 0; i < rows; i++){
            for(int j = 0; j < cols; j++){
                if ((j * rows + i ) < file_count) {
                    // if (flags->G) {
                    //     mx_find_color(file_array[j * rows + i], files, full_name);
                    // }
                    mx_printstr(file_array[j * rows + i]);
                    // if (flags->G) {
                    //     mx_printstr(NO_COLOR);
                    // }
                    if((j + 1) * rows + i < file_count) {
                        for (int k = 0; k < max_len - mx_strlen(file_array[j * rows + i]); k++) {
                            mx_printchar(' ');
                        }
                    }
                }
            }
            mx_printchar('\n');
        }
    }

    mx_del_strarr(&file_array);
}
