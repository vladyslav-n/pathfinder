#include "../inc/header.h"

static int **create_grid(int row, int col, int val) {
    int i = 0;
    int j = 0;
    int **arr = (int **)malloc(row * sizeof(int *));

    for (i = 0; i < row; i++) 
        arr[i] = (int *)malloc(col * sizeof(int)); 
    for (i = 0; i <  row; i++) 
        for (j = 0; j < col; j++) 
            arr[i][j] = val;
    return arr;
}

static char **create_list_of_names(int count, const char *s) {
    char **names = (char**) malloc((count + 1) * sizeof(char*));

    names[count] = NULL;
    for (int i = 0; i < count; i++) {
        names[i] = (char*)s;
    }
    return names;
}

static int word_ind(char **arr, char *word) {
    for (int i = 0; arr[i]; i++) {
        if (!mx_strcmp(arr[i], word))
            return i;
    }
    return -1;
}

static void fill_grid(int lines_count, t_isls isls, 
char ***extra_isl_names) {
    int count = 0;
    t_bridge brg = {-2, -2};

    for (int i = 0; i < lines_count - 1; i++) {
        if ((brg.wi1 = word_ind(isls.names, extra_isl_names[i][0])) < 0) {
            mx_print_errors(count == isls.count ? INV_NUM_OF_ISLS : -1, "");
            isls.names[count] = mx_strdup(extra_isl_names[i][0]);
            brg.wi1 = count++;
        }
        if ((brg.wi2 = word_ind(isls.names, extra_isl_names[i][1])) < 0) {
            mx_print_errors(count == isls.count ? INV_NUM_OF_ISLS : -1, "");
            isls.names[count] = mx_strdup(extra_isl_names[i][1]);
            brg.wi2 = count++;
        }
    mx_fill_bridge(isls.grid, brg, extra_isl_names[i][1]);
    }
    if (count < isls.count) {
        mx_print_errors(INV_NUM_OF_ISLS, NULL);
    }
}

t_isls mx_create_isls(int argc, char *argv[]) {
    char *file = mx_invalid_file(argc, argv);
    int lines_count = 0;
    t_isls isls = {0};
    char ***extra_isl_names = mx_create_arr_words(file, 
    &lines_count, &isls.count);

    isls.grid = create_grid(isls.count, isls.count, GRID_INIT_VAL);
    isls.names = create_list_of_names(isls.count, "");
    fill_grid(lines_count, isls, extra_isl_names);
    free(file);
    for (int i = 0; i < lines_count - 1; i++) {
        mx_del_strarr(&extra_isl_names[i]);
    }
    free(extra_isl_names);
    extra_isl_names = NULL;
    return isls;
}

