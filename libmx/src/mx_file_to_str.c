#include "../inc/libmx.h"

char *mx_file_to_str(const char *file) {
    int fd = open(file, O_RDONLY);
    char c = 0;
    int len = 0;
    char *s = NULL;

    if (errno)
        return NULL;
    while ((c = read(fd, &c, 1))) {
        len++;
    }
    close(fd);
    s = mx_strnew(len);
    fd = open(file, O_RDONLY);
    for (int i = 0; i < len; i++) 
        read(fd, s + i, 1); 
    close(fd);
    if (!errno && *s)
        return s;
    return NULL;
}

