#include "uls.h"
//   int arguments_count = -1;
//     for (int i = 0; i < argc; i++) {
//         if (argv[i][0] != '-') {
//             arguments_count++;
//         }
//     }
struct dirent **get_inf_from_dir(char *dir_name) {
        DIR *dp;
    struct dirent *tmp;
    dp = opendir(".");
    while ((tmp= readdir(dp)) != NULL) {
            size_dirp++;
        }
    closedir(dp);
    
    struct dirent **dirp = (struct dirent **)malloc(sizeof(struct dirent *) * size_dirp);
    dp = opendir(".");
    for (int i = 0; i < size_dirp; i++) {
        dirp[i] = readdir(dp);
        if (mx_strcmp(dirp[i]->d_name, "uls") == 0) {
            i--;
            size_dirp--;
        }
        if (dirp[i] == NULL) {
            mx_printerr("cant read\n");
            exit(1);
        }
    }
    // Vozmozhno mesto ute4ki ili oshibki
    // Elsi naebnetsa, smotret suda 
    dirp = mx_realloc(dirp, size_dirp);

    closedir(dp);
}