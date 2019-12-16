#include "../inc/header.h"

void mx_fill_bridge(int **grid, t_bridge brg, char *s) {
    grid[brg.wi1][brg.wi2] = mx_atoi(s + mx_strlen(s) + 1);
    grid[brg.wi2][brg.wi1] = grid[brg.wi1][brg.wi2];
}

