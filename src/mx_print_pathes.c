#include "../inc/header.h"

static void print_distance(int *route, int **grid) {
    int i = 0;

    mx_printstr("Distance: ");
    for (i = 0; i < route[1] - 2; i++) {
        mx_printint(grid[route[i + 2]][route[i + 3]]);
        mx_printstr(" + ");
    }
    if (route[1] > 2) {
        mx_printint(grid[route[i + 2]][route[i + 3]]);
        mx_printstr(" = ");
    }
    mx_printint(route[0]);
    mx_printstr("\n");
}

static void print_route(int *route, char **names) {
    int i = 0;

    mx_printstr("Route: ");
    for (i = 0; i < route[1] - 1; i++) {
        mx_printstr(names[route[i + 2]]);
        mx_printstr(" -> ");
    }
    mx_printstr(names[route[i + 2]]);
    mx_printstr("\n");
}

static void print_path(t_list *pathes, char **names, int **grid) {
    int len = -1;

    while (pathes) {
        len = *((int*)(pathes->data) + 1);
        mx_printstr("========================================\nPath: ");
        mx_printstr(names[*((int*)(pathes->data) + 2)]);
        mx_printstr(" -> ");
        mx_printstr(names[*((int*)(pathes->data) + len + 1)]);
        mx_printstr("\n");
        print_route(pathes->data, names);
        print_distance(pathes->data, grid);
        mx_printstr("========================================\n");
        pathes = pathes->next;
    }
}

void mx_print_pathes(t_list **pathes, char **names, int **grid, int count) {
    for (int i = 0; i < count; i++) {
        print_path(pathes[i], names, grid);
    }
}

