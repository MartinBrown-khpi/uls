#include "uls.h"
#include <stdio.h>

long_data_t **mx_get_all_long_data(int size_dirp, struct dirent **dirp, const char *namedir){
    char *dir_path;
    long_data_t ** all_data;
    printf("size dirp = %d\n", size_dirp);
    if (dirp == NULL) {
        all_data =  malloc(sizeof(long_data_t*));
        all_data[0] = mx_get_long_info(namedir);
        return all_data;
    }
    all_data = malloc(sizeof(long_data_t*) * size_dirp);
    for (int i = 0; i < size_dirp; i++) {
        dir_path = mx_strjoin(namedir, "/");
        all_data[i] = mx_get_long_info( mx_strjoin(dir_path, dirp[i]->d_name));
    }
    return all_data;
}


long_data_t *mx_get_long_info(const char *filename) {
    struct stat buff;
    long_data_t *long_data = malloc(sizeof(long_data_t));
    long_data->f_time_last_acces = malloc(sizeof(long_data->f_time_last_acces));
    long_data->f_time_last_status = malloc(sizeof(long_data->f_time_last_status));
    long_data->f_time_modification = malloc(sizeof(long_data->f_time_modification));
    if (lstat(filename, &buff) == -1 ) {
        mx_printerr("cant get file stat");
        printf("%s\n", filename);
        return NULL;
    }
    //popravit
    long_data->f_mode  = buff.st_mode;
    long_data->f_links = buff.st_nlink;
    long_data->f_size = buff.st_size;
    long_data->f_uid = buff.st_uid;
    long_data->f_gid = buff.st_gid;
    // long_data->f_time_last_acces->tv_nsec = buff.st_atime;
    long_data->f_time_last_acces->tv_sec = buff.st_atimespec.tv_sec;
    // long_data->f_time_last_status->tv_nsec  = buff.st_ctime;
    long_data->f_time_last_status->tv_sec = buff.st_ctimespec.tv_sec;
    // long_data->f_time_modification->tv_nsec = buff.st_mtime;
    long_data->f_time_modification->tv_sec = buff.st_mtimespec.tv_sec;
    long_data->f_namefile = mx_strdup(filename);
    return long_data;
}

void get_redable_mode(long_data_t *long_data) {
    char *redable_mode = (char *)malloc(sizeof(char) * 10);
    // Test for a type file.
    
    if (S_ISLNK(long_data->f_mode)) redable_mode[0] = 'l';
    else if (S_ISCHR(long_data->f_mode)) redable_mode[0] = 'c';
    else if (S_ISBLK(long_data->f_mode)) redable_mode[0] = 'b';
    else if (S_ISFIFO(long_data->f_mode)) redable_mode[0] = 'p';
    else if (S_ISSOCK(long_data->f_mode)) redable_mode[0] = 's';
    else redable_mode[0] = (S_ISDIR(long_data->f_mode) ? 'd' : '-');

    // Is REDABLE
    redable_mode[1] = (long_data->f_mode & S_IRUSR ? 'r' : '-');

    // is WRITABLE
    redable_mode[2] = (long_data->f_mode & S_IWUSR ? 'w' : '-');

    // is 
    if (long_data->f_mode & S_ISUID) {
            redable_mode[3] = (long_data->f_mode & S_IXUSR ? 's' : 'S');
    }
    else  redable_mode[3] = (long_data->f_mode & S_IXUSR ? 'x' : '-');

    redable_mode[4] = (long_data->f_mode & S_IRGRP ? 'r' : '-');
    redable_mode[5] = (long_data->f_mode & S_IWGRP ? 'w' : '-');
        
    if (long_data->f_mode & S_ISGID) {
        redable_mode[6] = (long_data->f_mode & S_IXGRP ? 's' : 'S');
    }
    else redable_mode[6] = (long_data->f_mode & S_IXUSR ? 'x' : '-');
    
    redable_mode[7] = (long_data->f_mode & S_IROTH ? 'r' : '-');
    
    redable_mode[8] = (long_data->f_mode & S_IWOTH ? 'w' : '-');
        
    if (long_data->f_mode & S_ISVTX) {
        redable_mode[9] = (long_data->f_mode & S_IXOTH ? 't' : 'T');
    }
    else redable_mode[9] = (long_data->f_mode & S_IXUSR ? 'x' : '-');

    long_data->f_redable_mode = redable_mode;
}

void get_redable_uid(long_data_t *long_data) {
    struct passwd *user = getpwuid(long_data->f_uid);
    if (user == NULL) {
        mx_printerr("cant get pwuid");
        exit(1);
    }
    char *user_name = malloc(sizeof(char) * mx_strlen(user->pw_name));
    mx_strcpy(user_name, user->pw_name);
    long_data->f_redable_id = user_name;
}

void get_redable_gid(long_data_t *long_data) {
    struct group *char_group = getgrgid(long_data->f_gid);
    if (char_group == NULL) {
        long_data->f_redable_gid = mx_strdup(mx_itoa(long_data->f_gid));
    }
    else {
        long_data->f_redable_gid = mx_strdup(char_group->gr_name);
    }

}
