#include "../inc/pathfinder.h"

void check_line_fromat(char *str, int counter) {
    while (mx_isalpha(*str)) {
        str++;
    }
    if (*(str++) == '-') {
        while (mx_isalpha(*str)) {
            str++;
        }
        if (*(str++) == ',') {
            while (mx_isdigit(*str)) {
                str++;
            }
            if (*str == '\0') {
                return;
            }
        }
    }
    mx_printerr("error: line ");
    mx_printerr(mx_itoa(counter + 1));
    mx_printerr(" is not valid\n");
    exit(EXIT_FAILURE);
}

void check_line_from_to_from(char *str, int counter) {
    char *first = NULL;
    char *second = NULL;
    char *temp = str;
    int k = 0;

    for (int i = 0; str[i] != '\0'; i++, k++) {
        if (str[i] == '-') {
            first = mx_strndup(temp, k);
            temp += k + 1;
            k = 0;
        }

        if (str[i] == ',') {
            second = mx_strndup(temp, k-1);
            temp += i - k + 1;
            k = 0;
        }
    }

    if (mx_strcmp(first, second) == 0) {
        mx_printerr("error: line ");
        mx_printerr(mx_itoa(counter + 1));
        mx_printerr(" is not valid\n");
        exit(EXIT_FAILURE);
    }
    else {
        return;
    }
    
}

void check_first_line (char *str) {
    while(mx_isdigit(*str)) {
        str++;
    }
    if (*str == '\0') {
        return;
    }

    mx_printerr("error: line 1 is not valid\n");
    exit(EXIT_FAILURE);
}

void check_duplicate_bridges(char **str_array) {
    for (int i = 1; str_array[i] != NULL; i++) {
        char *temp = NULL;
        char *temp2 = NULL;
        
        for (int k = 0; str_array[i][k] != '\0'; k++) {
            if (str_array[i][k] == ',') {
                temp = mx_strndup(str_array[i], k);
                break;
            }
        }
        
        for (int j = 1; str_array[j] != NULL; j++) {
            if (i == j) {
                continue;
            }
            for (int z = 0; str_array[j][z] != '\0'; z++) {
                if (str_array[j][z] == ',') {
                    temp2 = mx_strndup(str_array[j], z);
                    break;
                }
            }
            if (mx_strcmp(temp, temp2) == 0) {
                mx_printerr("error: duplicate bridges\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

void check_sum_of_bridges(char **str_array) {
    int count_lines_in_file = 0;
    for (int i = 1; str_array[i] != NULL; i++) {
        count_lines_in_file++;
    } 

    int bridge_lengths[count_lines_in_file];
    int j = 0;
    for (int i = 1; str_array[i] != NULL; i++) {
        char *temp = NULL;
        char *temp_str = str_array[i];
        int z = 0;

        for (int k = 0; str_array[i][k] != '\0'; k++, z++) {
            if (str_array[i][k] == ',') {
                temp_str += z + 1;
                z = 0;
            }
            if (str_array[i][k+1] == '\0') {
                temp = mx_strndup(temp_str, z);
            }
        }

        bridge_lengths[j] = mx_atoi(temp);
        j++;
    }

    long long sum = 0;
    for (int i = 0; i < count_lines_in_file; i++) {
        sum += bridge_lengths[i];
        if (sum > INT_MAX) {
            mx_printerr("error: sum of bridges lengths is too big\n");
            exit(EXIT_FAILURE);
        }
    }
}

void check_number_of_island (char **str_array) {
    int count_lines_in_file = 0;
    for (int i = 0; str_array[i] != NULL; i++) {
        count_lines_in_file++;
    }   

    t_list *list_with_names = NULL;
    int island_amount = mx_atoi(str_array[0]);

    for (int p = 1; p < count_lines_in_file; p++) {
        char *temp = str_array[p];
        int k = 0;

        char *first = NULL;
        char *second = NULL;

        bool check1 = true;
        bool check2 = true;

        for (int i = 0; str_array[p][i] != '\0'; i++, k++) {
            if (str_array[p][i] == '-') {
                for (t_list *current = list_with_names; current != NULL; current = current->next) {
                    if (mx_strcmp(mx_strndup(temp, k), (char*)current->data) == 0) {
                        check1 = false;
                    } 
                }
                first = mx_strndup(temp, k);
                temp += k + 1;
                k = 0;
            }

            if (str_array[p][i] == ',') {
                for (t_list *current = list_with_names; current != NULL; current = current->next) {
                    if (mx_strcmp(mx_strndup(temp, k-1), (char*)current->data) == 0) {
                        check2 = false;
                    } 
                }
                second = mx_strndup(temp, k-1);
                temp += i - k + 1;
                k = 0;
            }
        }

        if (check1 && check2) {
            mx_push_back(&list_with_names, first);
            mx_push_back(&list_with_names, second);
            continue;
        }
        if (check1 && !check2) {
            mx_push_back(&list_with_names, first);
            continue;
        }
        if (!check1 && check2) {
            mx_push_back(&list_with_names, second);
            continue;
        }
        if (!check1 && !check2) {
            continue;
        }
    }

    if (mx_list_size(list_with_names) != island_amount) {
        mx_printerr("error: invalid number of islands\n");
        exit(EXIT_FAILURE);      
    }
}

void error_handle(int argc, char **argv) {
    //Checking usage: ./pathfinder [filename] if there is an invalid number of command-line arguments 
    if (argc != 2) {
        mx_printerr("usage: ./pathfinder [filename]\n");
        exit(EXIT_FAILURE);
    }

    //Checking error: file [filename] does not exist if the file does not exist
    int source = open(argv[1], O_RDONLY);
    if (source < 0) {
        mx_printerr("error: file ");
        mx_printerr(argv[1]);
        mx_printerr(" does not exist\n");
        exit(EXIT_FAILURE);
    }
    close(source);

    //Checking error: file [filename] is empty if the file is empty
    char *line = mx_file_to_str(argv[1]);
    if (!mx_strlen(line)) {
        mx_printerr("error: file ");
        mx_printerr(argv[1]);
        mx_printerr(" is empty\n");
        exit(EXIT_FAILURE);
    }

    char **line_arr = mx_strsplit(line, '\n');

    //Checking error: line 1 is not valid if the first line contains something other than digits or
    //has a non-positive value
    check_first_line (line_arr[0]);
    if (mx_atoi(line_arr[0]) == 0) {
        mx_printerr("error: line 1 is not valid\n");
        exit(EXIT_FAILURE);
    }

    //Checking error: line [line_number] is not valid if one of the remaining lines does not match
    // the format above
    int o = 1;
    for (o = 1; line_arr[o] != NULL; o++) {
        check_line_fromat(line_arr[o], o);
    }   

    if (line[mx_strlen(line) - 1] != '\n') {
        mx_printerr("error: line ");
        mx_printerr(mx_itoa(o));
        mx_printerr(" is not valid\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; line_arr[i] != NULL; i++) {
        check_line_from_to_from(line_arr[i], i);
    }   


    //Checking error: invalid number of islands if the number received in the first line does not
    // match with the number of islands
    check_number_of_island(line_arr);

    //Checking error: duplicate bridges if there is more than one bridge between the islands
    check_duplicate_bridges(line_arr);

    //Checking error: sum of bridges lengths is too big if the sum of the lengths of all bridges in
    // the file exceeds INT_MAX
    check_sum_of_bridges(line_arr);
}
