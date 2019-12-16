#include "../inc/header.h"
#define DEBUG 

static void init_used_isl_arr(int *arr, int len, int isl_index) {
    for (int i = 0; i < len; i++) {
        if (arr[i] < 0) {
            arr[i] = 0;
        }
    }
    arr[isl_index] = 1;
}

static int choose_isl(int *used_isl, int n) {
    if (!n) {
        return -1;
    }
    for (int i = 0; i < n; i++) {
        if (!used_isl[i]) {
            return i;
        }
    }
    return -1;
}

static void add_isls(t_isls *isls, t_cur_route *cur_route,
int *used_isl, int *isl_nums) {
    while((cur_route->j = choose_isl(used_isl + cur_route->pr_isl + 1,
            isls->count - cur_route->pr_isl - 1)) >= 0) {
        cur_route->j += cur_route->pr_isl + 1;
        while (isls->grid[cur_route->i][cur_route->j] < 0
                || used_isl[cur_route->j]) {
            if (++(cur_route->j) == isls->count) {
                break;
            }
        }
        if (cur_route->j == isls->count) {
            cur_route->fl = 1;  //flg means we have unused isls with no brdgs
            break;
        }
        mx_push_front(&(cur_route->list), &(isl_nums[cur_route->j]));
        cur_route->len += 1;
        cur_route->i = *((int*)((cur_route->list)->data));
        used_isl[cur_route->i] = 1;
        cur_route->pr_isl = -1;
    }
}

void mx_algo(t_list **shrt_path, t_isls isls, int *used_isl, int *isl_nums) {
    for (int i = 0; i < isls.count - 1; i++) { 
        t_cur_route cur_rou = mx_create_cur_route(i, isl_nums);

        init_used_isl_arr(used_isl, isls.count, i);
        while(cur_rou.list) {
            add_isls(&isls, &cur_rou, used_isl, isl_nums);
            while((cur_rou.j = choose_isl(used_isl + (cur_rou.pr_isl + 1),
                    isls.count - cur_rou.pr_isl - 1)) < 0 || cur_rou.fl) {
                cur_rou.j += cur_rou.pr_isl + 1;
                cur_rou.fl = 0;
                mx_save_route(cur_rou, shrt_path, i, isls);
                used_isl[cur_rou.i] = 0;
                cur_rou.pr_isl = cur_rou.i;
                mx_pop_front(&cur_rou.list);
                if (cur_rou.list)
                    cur_rou.i = *((int*)(cur_rou.list->data));
                cur_rou.len -= 1;
            }
        }
    }
}

