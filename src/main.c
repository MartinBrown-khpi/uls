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

*/


#include <stdio.h>
int main(int argc, char const *argv[]) {
    mx_usage(argc);
    cur_flags_t *cur_flags = mx_get_flags(argc, argv);
    printf("count flags = %d\n", cur_flags->count);
    for (int i = 0; i < cur_flags->count; i++) {
        printf("%c\t", cur_flags->flags[i]);
    }
    // get winsize
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    printf("%d\n%d\n", w.ws_col, w.ws_row);

    mx_strdel(&cur_flags->flags);
    free(cur_flags);
    return 0;
}
