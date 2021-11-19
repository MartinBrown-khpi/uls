int mx_get_first_file(int argc, char const *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            return i;
        }
    }
    return -1;
}
