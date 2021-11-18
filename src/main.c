#include "uls.h"
/*
Тип файла   ?
Файл разрешений stat
Количество жестких ссылок на файл stat
Владелец файла stat
Файловая группа хз
Размер файла stat
Дата и время stat
Имя файла argv

разбито на блоки
как выводить 
как сортировать 
    // struct winsize w;
    // ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    // printf("%d\n%d\n", w.ws_col, w.ws_row);

*/
/* TODO
Разобраться со списком доступных хедеров и библиотек
Спиздить у Вовы ахуенную структуру айтемов
По возможности начать убирать хардкод и утечки памяти
Написать парсер для файлнеймов, у Вовы тоже есть
Убратть нахуй глобальные переменные, оставить доступ к флагам только функции, которая будет устанавливать булевские клюки
Добавить иф на парсер флагов, что бы не работал просто минус
Добавить проверку на корректность введенных файлов/директорий в качестве агрументов, начать обрабатывать ошибки ввода
File path + file name struct 
int xui = listxattr("/.ssh", l, 1024,  XATTR_SHOWCOMPRESSION);
если list возвращает не -1 то принтим @
 -> /Volumes/Storage/cache/ayevtushen/.cocoapods
*/
#include <stdio.h>

char *agruments_filter(long_data_t **data, int size_dirp, all_flags_t *cur) {
    char *str;
    char *temp_string = NULL;

    for (int i = 0; i < size_dirp; i++) {
        if (cur->is_A) {
            if (mx_strcmp(data[i]->f_namefile, ".") == 0 ||
                mx_strcmp(data[i]->f_namefile, "..") == 0) {
                    continue;
                }
        }
        if (cur->is_a) {
            if (data[i]->f_namefile[0] == '.') {
                continue;
            }
        }
        printf("%s\n", data[i]->f_namefile);

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
    }
    return temp_string;
}

static int count_dir_and_files(int argc, char const *argv[]) {
    int arguments_count = -1;
    for (int i = 0; i < argc; i++) {
        if (argv[i][0] != '-') {
            arguments_count++;
        }
    }
    return arguments_count;
}

static void args_validator(char **arguments, int arguments_count) { 
    struct stat buff;
    for (int i = 0; i < arguments_count; i++) {
        if (stat(arguments[i], &buff) == -1) {
            // popravit vivod oshibki
            // 4istit pam9t pri exit() ili sdelat bool i vozvrashat v main
            printf("Invalid file_name\n");
        }
    }
}

static char **parse_arguments(int argc, char const *argv[], int arguments_count) {
    char **arguments = malloc(sizeof(char *) * arguments_count);
    for (int i = 1, j = 0; i < argc && j < arguments_count; i++) {
        if (argv[i][0] != '-') {
            arguments[j] = mx_strdup(argv[i]);
            j++;
        }
    }
    return arguments;
}

int main(int argc, char const *argv[]) {
    const int COUNT_FLAGS = 14;
    const char FLAGS[14] = {'l', 'a', 'A', '1', 'r', 't', 'u', 'c', 'S', 'h', 'C', 'T', 'G', '@'};

    // char buf[1024];  
    // long jj= readlink("/Users/ayevtushen/", buf, 1024);  
    // printf("jj = %ld\n", jj);
    // printf("buf = %s\n", buf);
    
    // char  l[1024];
    // int xui = listxattr("/Users/ayevtushen/.DS_Store", l, 1024,  XATTR_NOFOLLOW);

    // printf("l = %s\n", l);
    // printf("xui = %d\n", xui);

    cur_flags_t *cur_flags = mx_get_flags(COUNT_FLAGS, FLAGS, argc, argv);
    
    int arguments_count = count_dir_and_files(argc, argv);
    char **arguments = NULL;
    // printf("arg count = %d", arguments_count);
    if (arguments_count == 0) {
        arguments = malloc(sizeof(char *));
        arguments[0] = mx_strdup(".");
        arguments_count++;
    }
    else {
        arguments = parse_arguments(argc, argv, arguments_count);
        args_validator(arguments, arguments_count);
        mx_bubble_sort(arguments, arguments_count);
    }
        all_flags_t *usable_flags = malloc(sizeof(all_flags_t));

        usable_flags->is_C_print = true;
        usable_flags->is_list = false;
        usable_flags->is_long = false;
        usable_flags->is_A = false;
        usable_flags->is_a = false;
        

        usable_flags->is_reverse = false;
        usable_flags->is_common_sort = true;
        usable_flags->is_c_sort = false;
        usable_flags->is_S_sort = false;
        usable_flags->is_t_sort = false;
        usable_flags->is_u_sort = false;
        
        usable_flags->is_h_long = false;
        usable_flags->is_T_long = false;
        usable_flags->is_G_color = false;
        usable_flags->is_at = false;
        for (int i = 0; i < cur_flags->count; i++) {
            switch (cur_flags->flags[i]) {
            case 'l':
                usable_flags->is_long = true;
                usable_flags->is_list = false;
                usable_flags->is_C_print = false;
                break;
            case '1':
                usable_flags->is_list = true;
                usable_flags->is_long = false;
                usable_flags->is_C_print = false;
                break;
            case 'C':
                usable_flags->is_C_print = true;
                usable_flags->is_list = false;
                usable_flags->is_long = false;
            case 'a':
                usable_flags->is_a = true;
                usable_flags->is_A = false;   
                break;
            case 'A':
                usable_flags->is_A = true;
                usable_flags->is_a = false;
                break;
            case 'r':
                usable_flags->is_reverse = true;
                break;
            case 't':
                usable_flags->is_t_sort = true;
                break;
            case 'u':
                usable_flags->is_u_sort= true;
                usable_flags->is_c_sort = false;
                break;
            case 'c':
                usable_flags->is_c_sort = true;
                usable_flags->is_u_sort= false;
                break;
            case 'S':
                usable_flags->is_S_sort = true;
                break;
            case 'h':
                usable_flags->is_h_long = true;
                break;
            case 'T':
                usable_flags->is_T_long = true;
                break;
            case 'G':
                usable_flags->is_G_color = true;
                break;
            case '@':
                usable_flags->is_at = true;
                break;
            default:
                break;
            }
        }

        /* Select a sort function. */
        bool (*sort_func)(long_data_t *, long_data_t *)  = NULL;
        if (usable_flags->is_S_sort) {
               sort_func = mx_size_cmp;
        }
        else if (usable_flags->is_t_sort && !usable_flags->is_u_sort && !usable_flags->is_c_sort) {
            //time sort
            sort_func = mx_time_modif_cmp;
        }
        else if (usable_flags->is_u_sort && usable_flags->is_t_sort) {
            //vremya последнего доступа для сортировки 
            sort_func = mx_time_access_cmp;
        }
        else if (usable_flags->is_c_sort && usable_flags->is_t_sort) {
           //использовать время последней модификации описателя файла 
            sort_func = mx_time_status_cmp;
        } 
        else {
            sort_func = mx_default_cmp;
        }

        // цикл проходит через все аргументы
        int size_dirp;
        struct dirent **dirp;
        long_data_t **all_long_data;
        
        for (int i = 0; i < arguments_count; i++) {
            size_dirp = 0;
            dirp = get_inf_from_dir(arguments[i], &size_dirp);
            if (size_dirp == 0) size_dirp++;
            all_long_data = mx_get_all_long_data(size_dirp, dirp, arguments[i]);

            for (int j = 0; j < size_dirp; j++) {
                get_redable_mode(all_long_data[j]);
                get_redable_uid(all_long_data[j]);
                get_redable_gid(all_long_data[j]); 
                all_long_data[j]->type_size = 'B';
                all_long_data[j]->size_remainder = 0;
                all_long_data[j]->at_link = NULL;
                all_long_data[j]->readlink = NULL;
            }
            // есть ли @ и +
            acl_t acl;
            char buff[1024];
            char sec_buff[1024];
            int check;
            int at_xattr;
            for (int j = 0; j < size_dirp; j++) {
                char *path_namefile = mx_strcat(all_long_data[j]->f_pathfile, all_long_data[j]->f_namefile);
                check = listxattr(path_namefile, buff, 1024,  XATTR_NOFOLLOW);
                at_xattr = getxattr(path_namefile, buff, sec_buff, 1024, 0, 0);
                if (check > 0) {
                    all_long_data[j]->is_link = true; 
                    all_long_data[j]->at_link = mx_strdup(buff);
                    all_long_data[j]->xattr = at_xattr;

                }

                acl = acl_get_file(path_namefile, ACL_TYPE_EXTENDED);
                if (acl != NULL) {
                    all_long_data[j]->is_plus = true;
                }

                if ( S_ISLNK( all_long_data[j]->f_mode )) {
                    char *linkname = mx_strnew(all_long_data[j]->f_size);
                    readlink(path_namefile, linkname, all_long_data[j]->f_size );
                    all_long_data[j]->readlink = linkname;
                }
            }
            // сортировка 
            mx_insertion_sort(all_long_data, size_dirp, sort_func);
            if (usable_flags->is_reverse) {
                reverse_array(all_long_data, size_dirp);
            }
            if (usable_flags->is_list) {
                mx_print_list(all_long_data, size_dirp, usable_flags);
            } 
            else if (usable_flags->is_long) {

            if (usable_flags->is_h_long) {
                    mx_translate_size(all_long_data, size_dirp);
                }
                mx_print_long_data(all_long_data, size_dirp, usable_flags);
            }
            else if (usable_flags->is_C_print) {
            // Добавить сортировку по -А -а
            // Все ФАЙЛЫ должны заносится в темп спринг для их вывода
            // после вывода файла ставится некст лайн
            // Обрезать из названия дир ./
            // Все названия для вывода заносятся в темп стринг
            // Выводить название директории надо только тогда когда 2 или больше агрумента
            // Сначала выводятся файлы потом диры
                char *temp_string = agruments_filter(all_long_data, size_dirp, usable_flags);
                if (mx_strcmp(all_long_data[i]->f_pathfile, "./.") != 0) {
                    printf("%s:\n", all_long_data[i]->f_pathfile);
                }
                mx_print_files(temp_string, size_dirp, usable_flags);
            }
            
        }
    // else if (usable_flags->is_list) {
    //     "stuktura" *t_dirs_list = mx_get_dirs_list((is_A, is_a));
    //     //sort
    //     //print 
    // }
    

    return 0;
}
