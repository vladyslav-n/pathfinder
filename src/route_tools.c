#include "../inc/header.h"
// #include <stdio.h>
#define DEBUG 

int mx_route_dist(t_list *cur_route, int len, int **grid) {
    int dist = 0;

    for (int i = 0; i < len - 1; i++) {
        dist += grid[*((int*)(cur_route->data))]
                    [*((int*)(cur_route->next->data))];
        cur_route = cur_route->next;
    }
    return dist;
}

int *mx_create_route(t_list *route, int len, int **grid) {
    int *new_route = (int*)malloc(sizeof(int) * (len + 2));
    int dist = 0;
    int i = 2;

    for (i = 0; i < len - 1; i++) {
        dist += grid[*((int*)(route->data))]
                    [*((int*)(route->next->data))];
        new_route[len + 1 - i] = *((int*)(route->data));
        route = route->next;
    }
    new_route[2] = *((int*)(route->data));
    new_route[0] = dist;
    new_route[1] = len;
    return new_route;
}

void mx_clear_list_routes(t_list **head) {
    if (!*head || !head) {
        return;
    }
    while (*head) {
        free((*head)->data);
        mx_pop_front(head);
    }
}

t_cur_route mx_create_cur_route(int i, int *isl_nums) {
    t_cur_route cur_route = {i, 1, 0, -1, -1, 0};

    cur_route.list = mx_create_node(&isl_nums[i]);
    return cur_route;
}

void mx_save_route(t_cur_route cur_route, t_list **shrt_path,
int i, t_isls isls) {
    if (cur_route.i > i) {
        int ri_tmp = MX_RI(i, cur_route.i, isls.count);

        if (!shrt_path[ri_tmp]) {
            mx_push_back(&shrt_path[ri_tmp], 
            mx_create_route(cur_route.list, cur_route.len, isls.grid));
        }
        else if (*((int*)(shrt_path[ri_tmp]->data))
                == mx_route_dist(cur_route.list, cur_route.len, isls.grid)) {
            mx_push_back(&shrt_path[ri_tmp], 
            mx_create_route(cur_route.list, cur_route.len, isls.grid));
        }
        else if (*((int*)(shrt_path[ri_tmp]->data))
                > mx_route_dist(cur_route.list, cur_route.len, isls.grid)) {
            mx_clear_list_routes(&shrt_path[ri_tmp]);
            mx_push_back(&shrt_path[ri_tmp], 
            mx_create_route(cur_route.list, cur_route.len, isls.grid));
        }
    }
}

