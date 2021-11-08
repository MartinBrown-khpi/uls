#include "libmx.h"

char *mx_strdup(const char *str) {
    char *dup = NULL;
    if (str) {
        dup = mx_strnew(mx_strlen(str));
    }

    if (dup != NULL) {
        mx_strcpy(dup, str);
        return dup;
    }
    return NULL;
}
