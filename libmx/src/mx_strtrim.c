#include "../inc/libmx.h"

char *mx_strtrim(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    int left_spaces = 0, right_spaces = 0, finish = mx_strlen(str) - 1;

    while (mx_isspace(str[left_spaces])) {
        left_spaces++;
    }

    while (mx_isspace(str[finish])) {
        right_spaces++;
        finish--;
    }

    char *temp_str = mx_strnew(mx_strlen(str) - left_spaces - right_spaces);
    char *result_str = mx_strncpy(temp_str, str + left_spaces, mx_strlen(str) - left_spaces - right_spaces);
    
    mx_strdel(&temp_str);

    return result_str;
}
