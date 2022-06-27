#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <limits.h>
#include "../libmx/inc/libmx.h"

void print_result_with_lots_path(int **distances, t_list ***pathes, int island_amount, char **array_with_names);
void print_result_with_one_path(int **distances, t_list ***pathes, int island_amount, char **array_with_names);
void print_result(int **distances, t_list ***link, int island_amount, char **array_with_names);
t_list *get_path(int from, int to, t_list ***pathes);
void do_matching(char **array_with_names, int amount, int *counter, char *string);
void make_graph (char **array_with_names, int amount, char *string, int **bridges);
void read_map (char *filename, int *island_amount, int ***grap, char ***array_with_names);
t_list *get_distance(int **distances, t_list *path);
void error_handle(int argc, char **argv);
void floyd_algo_with_path(int **graph,  int island_amount, int **distances, char **array_with_names);

#endif
