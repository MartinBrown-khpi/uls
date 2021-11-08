int mx_strlen(const char *s) {
    if (!s) {
        return -1;
    }
    int counter = 0;
    while (*(s + counter) != '\0') {
        counter++;
    }
    return counter;
}
