#include "uls.h"

#include <stdio.h>

char **mx_get_inf_from_dir(const char *dir_name, int *size_dirp) {
    DIR *dp;
    struct dirent *tmp;

    dp = opendir(dir_name);
    if (!dp) {
        return NULL;
    }

    while ((tmp= readdir(dp)) != NULL) {
        *size_dirp = *size_dirp + 1;
    }
    closedir(dp);

    char **dirp = (char **)malloc(sizeof(char *) * (*size_dirp));
    tmp = NULL;
    dp = opendir(dir_name);

    for (int i = 0; i < *size_dirp; i++) {
        tmp = readdir(dp);
        dirp[i] = mx_strdup(tmp->d_name);
        if (mx_strcmp(dirp[i], "uls") == 0) {
            i--;
            *size_dirp = *size_dirp - 1;
        }
        if (dirp[i] == NULL) {
            mx_printerr("cant read\n");
            exit(1);
        }
    }
    // Vozmozhno mesto ute4ki ili oshibki
    // Elsi naebnetsa, smotret suda 
    dirp = mx_realloc(dirp, *size_dirp);

    closedir(dp);
    return dirp;
}

