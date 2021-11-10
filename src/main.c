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

#include <stdio.h>
int main(int argc, char const *argv[]) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    cur_flags_t *cur_flags = mx_get_flags(argc, argv);
    DIR *dp;
    int size_dirp = 0;
    struct dirent *tmp;
    dp = opendir(".");
    while ((tmp= readdir(dp)) != NULL) {
            size_dirp++;
        }
        closedir(dp);
    struct dirent **dirp = (struct dirent **)malloc(sizeof(struct dirent *) * size_dirp);
    size_dirp = 0;
        dp = opendir(".");
        while ((dirp[size_dirp] = readdir(dp)) != NULL) {
            //printf("%s\n", dirp[size_dirp]->d_name);
            dirp = mx_realloc(dirp, size_dirp);
            size_dirp++;
        }
        closedir(dp);


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
            break;
        case 'c':
            usable_flags->is_c_sort = true;
            break;
        case 'S':
            usable_flags->is_S_sort = true;
            break;
        
        default:
            break;
        }
    }

    //set color (придумаем)
    // get first !flag 
    if(usable_flags->is_long) {
        //printf("dirp = %s\n", dirp[2]->d_name);
        long_data_t **all_long_data = mx_get_all_long_data(size_dirp, dirp);
    
        //sort 
        //print
        printf("lonng name = %s\n", all_long_data[1]->f_namefile);

    }
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
