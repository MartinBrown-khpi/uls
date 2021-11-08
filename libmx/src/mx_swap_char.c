void mx_swap_char(char *s1, char *s2) {
    if (!s1 || !s2) {
        return;
    }
    char tmp = s2[0];
    s2[0] = s1[0];
    s1[0] = tmp;
}
