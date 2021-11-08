#include "libmx.h"

char *mx_del_extra_spaces(const char *str) {
    char *str_trim = mx_strtrim(str);
    bool isspace = false;
    int len_res = 0;
    for (int i = 0; i < mx_strlen(str_trim); i++) {
        if (mx_isspace(*(str_trim + i))) {
            isspace = true;
        }
        else {
            isspace = false;
            len_res++;
        }
    }

    char *str_res = mx_strnew(len_res);
    
    int j = 0;
    for (int i = 0; i < mx_strlen(str_trim); i++) {
        if (mx_isspace(*(str_trim + i)) && mx_isspace(*(str_trim + i + 1))
        ) {
            isspace = true;
        }
        else {
            *(str_res + j) = *(str_trim + i);
            j++;
            
        }
    }
    mx_strdel(&str_trim);
    return str_res;
}
