#include "libmx.h"

void * mx_memset(void *b, int c, size_t len) {
    unsigned char *tmp = (unsigned char *)b; 
    for (size_t i = 0; i < len; i++) {
        *(tmp + i) = c;
    }
    return tmp;
}
