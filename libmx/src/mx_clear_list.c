#include "libmx.h"

void mx_clear_list(t_list **list) {
    if (*list == NULL || list == NULL) {
        return;
    }

    if ((*list)->next == NULL) {
        free(*list);
        *list = NULL;
        return;
    }

    t_list *temp_node = *list, *next; 

    while (temp_node != NULL) {
        next = temp_node->next;
        free(temp_node);
        temp_node = next;
    }

    *list = NULL;
}
