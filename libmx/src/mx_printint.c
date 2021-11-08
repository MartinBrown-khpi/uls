#include "libmx.h"

void mx_printint(int n) {
    long num = n;
    
    unsigned long rank = 1;
    if (num == 0) {
        mx_printchar('0');
        return;
    }
    else if (num < 0) {
        num *= -1;
        mx_printchar('-');
    }

    long buf = num;
    while(buf > 0) {
        buf /= 10;
        rank *= 10;
    }

    while (rank > 9) {
        rank /= 10;
        mx_printchar(num / rank % 10 + '0');  
    }
}
