#include "../inc/header.h"
#define DEBUG 

int main(int argc, char *argv[]) {
    t_isls isls = mx_create_isls(argc, argv);
    int routes_count = (isls.count * (isls.count - 1)) / 2;
    t_list **shrt_path
         = (t_list**)malloc(sizeof(t_list*) * routes_count);
    int *used_isl = (int*) malloc(sizeof(int) * isls.count);
    int *isl_nums = (int*) malloc(sizeof(int) * isls.count);

    for (int i = 0; i < isls.count; i++) {
        isl_nums[i] = i;
    }
    for (int i = 0; i < isls.count; i++) {
        used_isl[i] = -1;
    }
    for (int i = 0; i < routes_count; i++) {
        shrt_path[i] = NULL;
    }

    mx_algo(shrt_path, isls, used_isl, isl_nums);
    mx_print_pathes(shrt_path, isls.names, isls.grid, routes_count);
}

