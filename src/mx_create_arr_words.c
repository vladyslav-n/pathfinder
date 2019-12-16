#include "../inc/header.h"

static void check_first_line(char *file) {
    int len = mx_get_char_index(file, '\n');

    if (len > 0) {
        for (int i = 0; i < len; i++) {
            if (!mx_isdigit(file[i])) {
                mx_print_errors(INV_FIRST_LINE, NULL);   
            }
        }
        return;
    }
    mx_print_errors(INV_FIRST_LINE, NULL);   
}

static void check_line(char *line, int num) {
    int hph_i = mx_get_char_index(line, '-');
    int coma_i = mx_get_char_index(line, ',');

    if (hph_i > 0 && coma_i > hph_i + 1 && coma_i < mx_strlen(line) - 1) {
        for (int i = 0; i < hph_i; i++) {
            if (!mx_isalpha(line[i])) {
                mx_print_errors(INV_LINE, mx_itoa(num));
            }
        }
        for (int i = hph_i + 1; i < coma_i; i++) {
            if (!mx_isalpha(line[i])) {
                mx_print_errors(INV_LINE, mx_itoa(num));
            }
        }
        for (int i = coma_i + 1; line[i]; i++) {
            if (!mx_isdigit(line[i]))
                mx_print_errors(INV_LINE, mx_itoa(num));
        }
        return;
    }
    mx_print_errors(INV_LINE, mx_itoa(num));
}

char ***mx_create_arr_words(char *file, int *lines_count,
int *isl_count) {
    char **file_lines = mx_strsplit_ncount(file, '\n', lines_count);
    int island_count = mx_atoi(file_lines[0]);
    *isl_count = island_count;
    char ***extra_isl_names = NULL;

    check_first_line(file);
    for (int i = 1; file_lines[i]; i++) {
        check_line(file_lines[i], i + 1);
    }
    extra_isl_names = (char***) malloc((*lines_count - 1) * sizeof(char**));
    for (int i = 0; i < *lines_count - 1; i++) {
        extra_isl_names[i] = mx_strsplit(file_lines[i + 1], '-');
    }
    for (int i = 0; i < *lines_count - 1; i++) {
        extra_isl_names[i][1][mx_get_char_index(extra_isl_names[i][1], ',')]
            = 0;
    }
    mx_del_strarr(&file_lines);
    return extra_isl_names;
}

