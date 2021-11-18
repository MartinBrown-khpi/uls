#ifndef ULS_H
#define ULS_H

#include "libmx.h"
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/xattr.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/types.h>
#include <sys/acl.h>

//COLORS
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


typedef struct cur_flags {
    char *flags;
    int count;
} cur_flags_t;

typedef struct all_flags {
    bool is_C_print;
    bool is_long;
    bool is_list;
    bool is_A;
    bool is_a;
    bool is_reverse;
    bool is_common_sort;
    bool is_t_sort;
    bool is_u_sort;
    bool is_c_sort;
    bool is_S_sort;
    bool is_h_long;
    bool is_T_long;
    bool is_G_color;
    bool is_at;
}all_flags_t;

typedef struct long_data {
    mode_t f_mode;
    char *f_redable_mode;
    nlink_t f_links;
    uid_t f_uid;
    char *f_redable_id;
    gid_t f_gid;
    char *f_redable_gid;
    off_t f_size;
    int size_remainder;
    struct timespec *f_time_modification;
    struct timespec *f_time_last_acces;
    struct timespec *f_time_last_status;
    char *f_namefile;
    char *f_pathfile;
    char *at_link;
    char *readlink;
    int xattr;
    bool is_plus;
    bool is_link;
    char type_size;
}long_data_t;

// help func
int mx_atoi(const char *str);
int mx_get_first_file(int argc, char const *argv[]);
int mx_get_max_int(int *arr, int size);
int mx_get_rank(int digit);

//ERRORS
void mx_printerr(const char *err);

void mx_illegal_option(char const *argv[] ,char flag);

void mx_print_usage(char const FLAGS[]);
// PARSE FLAGS 
cur_flags_t *mx_get_flags(const int COUNT_FLAGS, char const FLAGS[] , int argc, char const *argv[]);

bool is_valid_flag(const int COUNT_FLAGS, char const FLAGS[], char flag);
bool is_in_cur_flags(cur_flags_t *cur_flags, char flag);
void move_char_back(char *arr, int size, char ch);

//LS -l
long_data_t **mx_get_all_long_data(int size_dirp, struct dirent **dirp, const char *namedir);
long_data_t *mx_get_long_info(const char *filename, const char *path);

void get_redable_mode(long_data_t *long_data);
void get_redable_uid(long_data_t *long_data);
void get_redable_gid(long_data_t *long_data);

//sort 
void mx_insertion_sort(long_data_t **arr, int size, bool (*cmp) (long_data_t *first, long_data_t *sec));
bool mx_default_cmp(long_data_t *first, long_data_t *sec);
bool mx_size_cmp(long_data_t *first, long_data_t *sec);
bool mx_time_modif_cmp(long_data_t *first, long_data_t *sec);
bool mx_time_access_cmp(long_data_t *first, long_data_t *sec);
bool mx_time_status_cmp(long_data_t *first, long_data_t *sec);
void reverse_array(long_data_t **arr, int size);
// dir info
struct dirent **get_inf_from_dir(const char *dir_name, int *size_dirp);
// print -1 flag
void mx_print_list(long_data_t **all_long_data, int size_dirp, all_flags_t *usable_flags);
// translate -h flag
void mx_translate_size(long_data_t **all_long_data, int size);
//print -l flag
void mx_print_long_data(long_data_t **all_long_data, int size, all_flags_t *usable_flags);
void mx_print_redable_mode(long_data_t *long_data);
void mx_print_links(long_data_t *long_data, int biggest_link_rank);
void mx_print_redable_uid(long_data_t *long_data, int biggest_uid_size);
void mx_print_redable_gid(long_data_t *long_data, int biggest_gid_size);
void mx_print_size(long_data_t **all_long_data, int i, int size, all_flags_t *usable_flags);
void mx_print_date_time(long_data_t *long_data, all_flags_t *usable_flags);
    // time print func
    void mx_print_month(char **splitarrtime);
    void mx_print_day(char **splitarrtime);
    void mx_print_time(char **splitarrtime);
    void mx_print_year(char **splitarrtime);
void mx_print_namefile(long_data_t *long_data, all_flags_t *usable_flags);
// func for spaces -l
int mx_get_max_size_rank(long_data_t **all_long_data, int size, all_flags_t *usable_flags);
int mx_get_max_link_rank(long_data_t **all_long_data, int size, all_flags_t *usable_flags);
int mx_get_biggest_uid(long_data_t **all_long_data, int size, all_flags_t *usable_flags);
int mx_get_biggest_gid(long_data_t **all_long_data, int size, all_flags_t *usable_flags);
// -G color func


//print -c flag
int mx_get_cols(int file_count, int *cal_col, int *col_max_arr, int max_len);

void mx_print_files(char *temp_string, int size, all_flags_t *cur);

#endif /* ULS_H */
