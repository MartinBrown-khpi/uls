#include "uls.h"
#include <stdio.h>
void mx_islink(long_data_t *long_data) {
    char buff[1024];
    char sec_buff[1024];
    int is_link = 0;
    int at_xattr = 0;


    is_link = listxattr(long_data->concat_name_path, buff, 1024,  XATTR_NOFOLLOW);
    at_xattr = getxattr(long_data->concat_name_path, buff, sec_buff, 1024, 0, 0);
    if (is_link > 0) {
        long_data->is_link = true; 
        long_data->at_link = mx_strdup(buff);
        long_data->xattr = at_xattr;
    }
    if ( S_ISLNK( long_data->f_mode )) {
        char *linkname = mx_strnew(long_data->f_size);
        readlink(long_data->concat_name_path, linkname, long_data->f_size );
        long_data->readlink = linkname;
    }

}

void mx_isplus(long_data_t *long_data) {
    acl_t acl;

    acl = acl_get_file(long_data->concat_name_path, ACL_TYPE_EXTENDED);
    if (acl != NULL) {
        long_data->is_plus = true;
    }

}
