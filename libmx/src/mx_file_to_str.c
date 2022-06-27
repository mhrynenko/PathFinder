#include "../inc/libmx.h"

char *mx_file_to_str(const char *filename) {
    int source = open(filename, O_RDONLY);

    if (source < 0) {
        return NULL;
    }

    int size;
    char buf = 0;
    int length = 0;

    while ((size = read(source, &buf, 1)) > 0) {
        length++;
    }

    if (close(source) < 0) {
        return NULL;
    }

    source = open(filename, O_RDONLY);

    char *string = mx_strnew(length);

    for (int i = 0; (size = read(source, &buf, 1)) > 0; i++) {
        string[i] = buf;
    }

    if (close(source) < 0) {
        return NULL;
    }

    return string;
}
