#include "../inc/libmx.h"

int mx_count_substr(const char *str, const char *sub) {
    int sublength = mx_strlen(sub);
    int count = 0;
    
    if (sublength == 0) {
        return 0; 
    }
    
    for (str = mx_strstr(str, sub); str; str = mx_strstr(str + sublength, sub)) {
        count++;
    }
    return count;
}
