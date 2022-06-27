#include "../inc/pathfinder.h"

bool cmp(void *a, void *b) {
    int *a_int_ptr = (int*)a;
    int *b_int_ptr = (int*)b;

    int a_value = *a_int_ptr;
    int b_value = *b_int_ptr;
    if (a_value < b_value) {
        return false;
    }
    else {
        return true;
    }
}

void floyd_algo_with_path(int **graph,  int island_amount, int **distances, char **array_with_names) {
    distances = (int**)malloc(island_amount*sizeof(int*));
    for (int i = 0; i < island_amount; i++) {
		distances[i] = (int*) malloc(island_amount * sizeof(int));
	}

    t_list ***link;
    link = (t_list ***)malloc(island_amount * sizeof(t_list**));
    for (int i = 0; i < island_amount; i++) {
		link[i] = (t_list **) malloc(island_amount * sizeof(t_list*));
	}
    
    for (int i = 0; i < island_amount; i++) {
        for (int j = 0; j < island_amount; j++) {
            distances[i][j] = graph[i][j];
            
            if (graph[i][j] == 999999) {
                int *ptr = (int*) malloc(sizeof(int));
                *ptr = -1; 
                mx_push_back(&link[i][j], ptr);
            }
            else {
                int *ptr = (int*) malloc(sizeof(int));
                *ptr = j; 
                mx_push_back(&link[i][j], ptr);
            }
        }
    }

    for (int k = 0; k < island_amount; k++) {
        for (int i = 0; i < island_amount; i++) {
            for (int j = 0; j < island_amount; j++) {
                if (distances[i][k] == 999999 && distances[k][j] == 999999) {
                    continue;
                }
                if (distances[i][j] > distances[i][k] + distances[k][j]) {
                    distances[i][j] = distances[i][k] + distances[k][j];
                    mx_clear_list(&link[i][j]);
                    int *ptr = (int*) malloc(sizeof(int));
                    *ptr = k;
                    mx_push_back(&link[i][j], ptr);
                }
                else if (distances[i][j] == distances[i][k] + distances[k][j] && distances[i][j] < 999999 && k != j && k != i) {
                    int *ptr = (int*) malloc(sizeof(int));
                    *ptr = k;                
                    mx_push_back(&link[i][j], ptr);
                }
            }
        }
    }

    for(int i = 0; i < island_amount; i++){   
        for(int j = 0; j < island_amount; j++){
            mx_sort_list(link[i][j], cmp);
        }
    }
    
    for (int i = 0; i < island_amount; i++) {
        free(graph[i]); 
        graph[i] = NULL;
    } 
    free(graph);
    graph = NULL;

    print_result(distances, link, island_amount, array_with_names);
}

void print_result(int **distances, t_list ***link, int island_amount, char **array_with_names) {
    bool check = false;
    for(int i = 0; i < island_amount; i++){   
        for(int j = 0; j < island_amount; j++){
            if (mx_list_size(link[i][j]) > 1) {
                check = true;
            }
        }
    }

    if (!check) {
        print_result_with_one_path(distances, link, island_amount, array_with_names);
    }
    if (check) {
        print_result_with_lots_path(distances, link, island_amount, array_with_names);
    }

    for (int i = 0; i < island_amount; i++) {
        free(distances[i]); 
        distances[i] = NULL;
    } 
    free(distances);
    distances = NULL;

    for (int i = 0; i < island_amount; i++) {
        free(link[i]); 
        link[i] = NULL;
    } 
    free(link);
    link = NULL;

    for (int i = 0; i < island_amount; i++) {
        free(array_with_names[i]); 
        array_with_names[i] = NULL;
    } 
    free(array_with_names);
    array_with_names = NULL;
}

void print_first_part (char **array_with_names, int i, int j) {
    mx_printstr("========================================\n");
    char *path_string = mx_strjoin ("Path: ", mx_strjoin (array_with_names[i], mx_strjoin (" -> ", mx_strjoin (array_with_names[j], "\n"))));
    mx_printstr(path_string);
    mx_printstr("Route: ");
}

void print_second_part (t_list *path, int **distances) {
    mx_printstr("Distance: ");
    t_list *distance_list = NULL;
    int sum = 0;
    distance_list = get_distance(distances, path);
    if (mx_list_size(distance_list) == 1) {
        mx_printint(*(int*)distance_list->data);
    }
    else {
        while (distance_list != NULL) {
            sum += *(int*)distance_list->data;
            mx_printint(*(int*)distance_list->data);
            if(distance_list->next != NULL) {
                mx_printstr(" + ");
            }                         
            distance_list = distance_list->next;
        }
        mx_printstr(" = ");
        mx_printint(sum);
    }
    mx_printstr("\n========================================\n");
}

void get_many_paths(int from, int to, t_list ***pathes, t_list **exec_path, char **array_with_names, const int from_cst, const int to_cst, t_list **dist, int **distances) {
    t_list *temp = pathes[to][from];
    while (temp) {
        mx_push_front(exec_path, temp->data);
        if (to != *(int*)temp->data) {
            get_many_paths(from, *(int*)temp->data, pathes, exec_path, array_with_names, from_cst, to_cst, dist, distances);
            mx_pop_front(exec_path);
            temp = temp->next;
            continue;
        }
        else {
            int *ptr = (int*) malloc(sizeof(int));
            *ptr = from;
            mx_pop_front(exec_path);
            print_first_part(array_with_names, from_cst, to_cst);
            for (t_list *current = *exec_path; current != NULL; current = current->next) {
                mx_printstr(array_with_names[*(int*)current->data]);
                mx_push_back(dist, current->data);
                if(current->next != NULL) {
                    mx_printstr(" -> ");
                } 
                else  {
                    mx_printstr("\n");
                }
            }   
            print_second_part(*dist, distances);
            mx_clear_list(dist);
            break;
        }
    }
}

t_list *get_path(int from, int to, t_list ***pathes) {
    t_list *path = NULL;

    if (*(int*)pathes[from][to]->data == -1) {
        return path;
    }

    int list_size = 1;
    int from_temp = from;
    while (from_temp != to) {
        from_temp = *(int*)pathes[from_temp][to]->data;
        list_size++;
    }

    int *ptr = (int*) malloc(list_size * sizeof(int));
    
    *ptr = from;
    path = mx_create_node(ptr);
    ptr++;

    while (from != to) {
        from = *(int*)pathes[from][to]->data;
        *ptr = from;
        mx_push_back(&path, ptr);
        ptr++;
    }

    ptr -= mx_list_size(path);
    free(ptr);
    ptr = NULL;

    return path;
}

t_list *get_distance(int **distances, t_list *path) {
    t_list *distance = NULL;
    int list_size = mx_list_size(path);
    int *ptr = (int*) malloc(list_size * sizeof(int));

    int x = *(int*)path->data;
    int y = *(int*)path->next->data;
    *ptr = distances[x][y];
    distance = mx_create_node(ptr);
    ptr++;
    path = path->next;

    while (path->next != NULL) {
        x = *(int*)path->data;
        y = *(int*)path->next->data;
        *ptr = distances[x][y];
        mx_push_back(&distance, ptr);
        ptr++;
        path = path->next;
    }

    ptr -= mx_list_size(distance);
    free(ptr);
    ptr = NULL;
    return distance;
}

void print_result_with_lots_path(int **distances, t_list ***pathes, int island_amount, char **array_with_names) {
	for (int i = 0; i < island_amount; i++) {
        for (int j = 0; j < island_amount; j++) {
			if (distances[i][j] != 999999 && distances[i][j] != 0 && j > i) {
                t_list *path = NULL;
                t_list *dist = NULL;
                int *ptr = (int*) malloc(sizeof(int));
                *ptr = j;
                mx_push_front(&path, ptr);
                get_many_paths(i, j, pathes, &path, array_with_names, i, j, &dist, distances);
                free(ptr);
                ptr = NULL;
            }
			else {
                continue;
            }
		}
	}
}

void do_matching(char **array_with_names, int amount, int *counter, char *string) {
    char *temp = string;
    int k = 0;

    char *first = NULL;
    char *second = NULL;

    bool check1 = true;
    bool check2 = true;

    for (int i = 0; string[i] != '\0'; i++, k++) {
        if (string[i] == '-') {
            for (int z = 0; z < amount; z++) {
                if (mx_strcmp(mx_strndup(temp, k), array_with_names[z]) == 0) {
                    check1 = false;
                }
            }
            first = mx_strndup(temp, k);
            temp += k + 1;
            k = 0;
        }

        if (string[i] == ',') {
            for (int z = 0; z < amount; z++) {
                if (mx_strcmp(mx_strndup(temp, k-1), array_with_names[z]) == 0) {
                    check2 = false;
                }
            }
            second = mx_strndup(temp, k-1);
            temp += i - k + 1;
            k = 0;
        }
    }

    if (check1 && check2) {
        array_with_names[*counter] = first;
        (*counter)++;
        array_with_names[*counter] = second;
        (*counter)++;
        return;
    }
    if (check1 && !check2) {
        array_with_names[*counter] = first;
        (*counter)++;
        return;
    }
    if (!check1 && check2) {
        array_with_names[*counter] = second;
        (*counter)++;
        return;
    }
    if (!check1 && !check2) {
        return;
    }
}

void make_graph (char **array_with_names, int amount, char *string, int **bridges) {
    char *temp = string;
    int k = 0;
    int from = 0;
    int to = 0;
    for (int i = 0; string[i] != '\0'; i++, k++) {
        if (string[i] == '-') {
            for (int z = 0; z < amount; z++) {
                if (mx_strcmp(mx_strndup(temp, k), array_with_names[z]) == 0) {
                    from = z;
                    break;
                }
            }
            temp += k + 1;
            k = 0;
        }

        if (string[i] == ',') {
            for (int z = 0; z < amount; z++) {
                if (mx_strcmp(mx_strndup(temp, k-1), array_with_names[z]) == 0) {
                    to = z;
                    break;
                }
            }
            temp += mx_strlen(array_with_names[to]) + 1;
            k = 0;
        }

        if (string[i+1] == '\0') {
            bridges[from][to] = mx_atoi(mx_strdup(mx_strndup(temp, k)));
            bridges[to][from] = mx_atoi(mx_strdup(mx_strndup(temp, k)));
        }
    }

    for (int i = 0; i < amount; i++) {
        for(int j = 0; j < amount; j++) {
            if (i == j) {
                bridges[i][j] = 0;
            }
            if (bridges[i][j] == -1) {
                bridges[i][j] = 999999;
            }
        }
    }
    
}

void read_map (char *filename, int *island_amount, int ***graph, char ***array_with_names) {
    char *map = mx_file_to_str(filename);
    char **strings_arr;
    strings_arr = mx_strsplit(map, '\n');
    *island_amount = mx_atoi(strings_arr[0]);

    (*graph) = (int**)malloc(*island_amount*sizeof(int*));

    for (int i = 0; i < *island_amount; i++) {
		(*graph)[i] = (int*) malloc(*island_amount * sizeof(int));
	}

    for (int i = 0; i < *island_amount; i++) {
        for(int j = 0; j < *island_amount; j++) {
            (*graph)[i][j] = -1;
        }
    }

    (*array_with_names) = (char**)malloc(*island_amount * sizeof(char*));

    for (int i = 0; i < *island_amount; i++) {
        (*array_with_names)[i] = mx_itoa(i+1);
        (*array_with_names)[i] = mx_strjoin("o", mx_itoa(i+1));
    }

    int counter = 0;
    for (int i = 1; strings_arr[i] != NULL; i++) {
        do_matching((*array_with_names), *island_amount, &counter, strings_arr[i]);
    }

    for (int i = 1; strings_arr[i] != NULL; i++) {
        make_graph((*array_with_names), *island_amount, strings_arr[i], (*graph));
    }
}

void print_result_with_one_path(int **distances, t_list ***pathes, int island_amount, char **array_with_names) {
    for (int i = 0; i < island_amount; i++) {
        for (int j = 0; j < island_amount; j++) {
            if (distances[i][j] != 999999 && distances[i][j] != 0 && j > i) {
                mx_printstr("========================================\n");
                char *path_string = mx_strjoin ("Path: ", mx_strjoin (array_with_names[i], mx_strjoin (" -> ", mx_strjoin (array_with_names[j], "\n"))));
                mx_printstr(path_string);
                mx_printstr("Route: ");
                t_list *path_list = NULL;
                path_list = get_path(i, j, pathes);
                for (t_list *current = path_list; current != NULL; current = current->next) {
                    mx_printstr(array_with_names[*(int*)current->data]); 
                    if (current->next != NULL) {
                        mx_printstr(" -> ");
                    }
                }
                mx_printstr("\n");
                
                mx_printstr("Distance: ");
                t_list *distance_list = NULL;
                int sum = 0;
                distance_list = get_distance(distances, path_list);
                if (mx_list_size(distance_list) == 1) {
                    mx_printint(*(int*)distance_list->data);
                }
                else {
                    while (distance_list != NULL) {
                        sum += *(int*)distance_list->data;
                        mx_printint(*(int*)distance_list->data);
                        if(distance_list->next != NULL) {
                            mx_printstr(" + ");
                        }                         
                        distance_list = distance_list->next;
                    }
                    mx_printstr(" = ");
                    mx_printint(sum);
                }
                mx_printstr("\n");
            }
            else {
                continue;
            }
            mx_printstr("========================================\n");
        }
    }
}


int main(int argc, char *argv[]) {
    error_handle(argc, argv);
	int **graph = NULL, **distances = NULL;
    char **array_with_names = NULL;
    int island_amount = 0;
    read_map(argv[1], &island_amount, &graph, &array_with_names);
    floyd_algo_with_path(graph, island_amount, distances, array_with_names);
	return 0;
}
