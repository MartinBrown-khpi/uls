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
*/
#include <stdio.h>

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
    const int COUNT_FLAGS = 9;
    const char FLAGS[9] = {'l', 'a', 'A', '1', 'r', 't', 'u', 'c', 'S'};

    cur_flags_t *cur_flags = mx_get_flags(COUNT_FLAGS, FLAGS, argc, argv);
    
    int arguments_count = count_dir_and_files(argc, argv);

    if (arguments_count) {
        printf("%d", arguments_count);
    }

    char **arguments = parse_arguments(argc, argv, arguments_count);

    args_validator(arguments, arguments_count);

    int size_dirp = 0;
    
    struct dirent **dirp = get_inf_from_dir(".", &size_dirp);

    for (int i = 0; i < size_dirp; i ++) {
        printf("%s\n", dirp[i]->d_name);
    }
    all_flags_t *usable_flags = malloc(sizeof(all_flags_t));

    usable_flags->is_list = true;
    usable_flags->is_long = false;
    usable_flags->is_A = false;
    usable_flags->is_a = false;
    
    usable_flags->is_reverse = false;
    usable_flags->is_common_sort = true;
    usable_flags->is_c_sort = false;
    usable_flags->is_S_sort = false;
    usable_flags->is_t_sort = false;
    usable_flags->is_u_sort = false;


    for (int i = 0; i < cur_flags->count; i++) {
        switch (cur_flags->flags[i]) {
        case 'l':
            usable_flags->is_long = true;
            usable_flags->is_list = false;
            break;
        case '1':
            usable_flags->is_list = true;
            usable_flags->is_long = false;
            break;
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
        
        default:
            break;
        }
    }

    long_data_t **all_long_data = mx_get_all_long_data(size_dirp, dirp);
        for (int i = 0; i < size_dirp; i++) {
            get_redable_mode(all_long_data[i]);
            get_redable_uid(all_long_data[i]);
            get_redable_gid(all_long_data[i]);
            // printf("%s ", all_long_data[i]->f_redable_mode);
            // printf("%d ", all_long_data[i]->f_links);
            // printf("%s ", all_long_data[i]->f_redable_id);
            // printf("%s ", all_long_data[i]->f_redable_gid);
            // printf("%lld ", all_long_data[i]->f_size);
            // printf("%s ", ctime(&all_long_data[i]->f_time_modification->tv_nsec));
            // printf("%s\n", all_long_data[i]->f_namefile);
            
        }
        /* Select a sort function. */
        bool (*sort_func)(long_data_t *, long_data_t *)  = NULL;
        if (usable_flags->is_S_sort) {
            sort_func = mx_size_cmp;
        }
        else if (usable_flags->is_t_sort) {
            //time sort
            sort_func = mx_time_modif_cmp;
        }
        else if (usable_flags->is_u_sort) {
            //vremya последнего доступа для сортировки 
            sort_func = mx_time_access_cmp;
        }
        else if (usable_flags->is_c_sort) {
            //использовать время последней модификации описателя файла 
            sort_func = mx_time_status_cmp;
        } 
        else {
            sort_func = mx_default_cmp;
        }

    mx_insertion_sort(all_long_data, size_dirp, sort_func);
    printf("------------------------------------\n\n\n\n");
    for (int i = 0; i < size_dirp; i++) {
        printf("%s\n", all_long_data[i]->f_namefile);
    }
        //print

    // else if (usable_flags->is_list) {
    //     "stuktura" *t_dirs_list = mx_get_dirs_list((is_A, is_a));
    //     //sort
    //     //print 
    // }
    if (cur_flags->count != 0) {
        mx_strdel(&cur_flags->flags);
        free(cur_flags);
    }

    return 0;
}
