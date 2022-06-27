#include "../inc/libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count) {
	int left, right, middle;

	left = 0;
	right = size - 1;

	while (left <= right) {
		middle = left + (right - left) / 2;
		(*count)++;
		
		if (mx_strcmp(arr[middle], s) == 0) {
			return middle;
		}
		else if (mx_strcmp(arr[middle], s) < 0) {
			left = middle + 1;
		}
		else {
			right = middle - 1;
		}
	}

	*count = 0;
	return -1;
}
