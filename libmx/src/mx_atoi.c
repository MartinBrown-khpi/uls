#include "libmx.h"

int mx_atoi(const char *str) {
    int i = 0;
    int is_minus = 0;
    long long res_res = 0;
    long res = 0;
    while (mx_isspace(str[i]) == 1) {
        i++;
    }
    if (str[i] == '+' || str[i] == '-') {
        if(str[i] == '-') is_minus = 1;
        i++;
    }

    while (str[i] == '0') i++;

    while (mx_isdigit(str[i]) == 1) {
        res_res = res;
        res = res * 10 + str[i] - '0';
        i++;
        if (res <= res_res) {
            return res * is_minus >= 0 ? 0 : -1;
        }
    }
    if(is_minus == 1) {
        return -res;
    }
    return res;
}
