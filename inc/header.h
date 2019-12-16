#pragma once
#include "../libmx/inc/libmx.h"
#define GRID_INIT_VAL -1
#define DEBUG
#ifdef DEBUG
    #include <stdio.h>
#endif

/* root number index */
#define MX_RI(i, j, n) i * (2 * n - 3 - i) / 2 + j - 1

enum errors {
    INV_ARGC,
    FILE_NOT_EXIST,
    FILE_EMPTY,
    INV_FIRST_LINE,
    INV_LINE,
    INV_NUM_OF_ISLS
};

typedef struct s_bridge {
    int wi1;
    int wi2;
} t_bridge;

typedef struct s_isls {
    int count;
    int **grid;
    char **names;
} t_isls;

typedef struct s_cur_route {
    int i;
    int len;
    t_list *list;
    int j;
    int pr_isl;
    char fl;

} t_cur_route;

void mx_print_pathes(t_list **pathes, char **names, int **grid, int count);
char *mx_invalid_file(int argc, char *argv[]);
t_isls mx_create_isls(int argc, char *argv[]);
void mx_print_errors(int err_num, char *text);
int mx_route_dist(t_list *cur_route, int len, int **grid);
int *mx_create_route(t_list *route, int len, int **grid);
void mx_clear_list_routes(t_list **head);
t_cur_route mx_create_cur_route(int i, int *isl_nums);
void mx_save_route(t_cur_route cur_route, t_list **shrt_path,
int i, t_isls isls);
void mx_algo(t_list **shrt_path, t_isls isls, int *used_isl, int *isl_nums);
char *mx_invalid_file(int argc, char *argv[]);
t_isls mx_create_isls(int argc, char *argv[]);
char ***mx_create_arr_words(char *file, int *lines_count,
int *isl_count);
void mx_fill_bridge(int **grid, t_bridge brg, char *s);

