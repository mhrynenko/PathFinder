#include "../inc/libmx.h"

void mx_str_reverse(char *s) {
    char *start, *finish, temp;

    start = s;
    finish = s;
    for (int i = 0; i < mx_strlen(s) - 1; i++){
        finish++;
    }

    for (int i = 0; i < mx_strlen(s)/2; i++) {
        temp = *start;
        *start = *finish;
        *finish = temp;
        start++; 
        finish--;
    }
}
