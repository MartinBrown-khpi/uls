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
    //mx_usage(argc);
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    cur_flags_t *cur_flags = mx_get_flags(argc, argv);
    //printf("%d\n%d\n", w.ws_col, w.ws_row);
    DIR *dp;
    struct dirent *dirp;
    if (cur_flags->count == 0) {
        dp = opendir(".");
        while ((dirp = readdir(dp)) != NULL)
            printf("%s\n", dirp->d_name);
        printf("%d", w.ws_row);
        free(cur_flags->flags);
        closedir(dp);
        return 0;
    }
    
    printf("count flags = %d\n", cur_flags->count);
    for (int i = 0; i < cur_flags->count; i++) {
        printf("%c\t", cur_flags->flags[i]);
    }
    
    all_flags_t *usable_flags = malloc(sizeof(all_flags_t));

    usable_flags->is_list = true;
    usable_flags->is_long = false;
    usable_flags->is_A = false;
    usable_flags->is_a = false;

    for (int i = 0; i < cur_flags->count; i++) {
        switch (cur_flags->flags[i]) {
        case 'l':
            usable_flags->is_long = true;
            break;
        case '1':
            usable_flags->is_list = true;
            break;
        case 'a':
            usable_flags->is_a = true;
            usable_flags->is_A = false;   
            break;
        case 'A':
            usable_flags->is_A = true;
            usable_flags->is_a = false;

        default:
            break;
        }
    }
    //set color (придумаем)

    // if(usable_flags->is_long) {
    //     "struktura 2" *t_dirs_long = mx_get_dirs_long();
    //     //sort 
    //     //print

    // }
    // else if (usable_flags->is_list) {
    //     "stuktura" *t_dirs_list = mx_get_dirs_list((is_A, is_a));
    //     //sort
    //     //print 
    // }


    return 0;
}
