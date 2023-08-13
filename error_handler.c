#include "project.h"

/*pointer to error_head*/
static error *error_head = NULL;

/*This function adds an error to the errors list.
meant for internal use
HOW TO USE:
addError(err, line, str)
err - string which describes the error.
line - line number. a negative number means no line.
str - adds an error string (primarily for syntax errors)
*/
void append_error(char *err, int line_num) {
    error *tmp_err = malloc(sizeof(error));
    check_allocation(tmp_err);

    tmp_err->str_error = err;

    tmp_err->line = line_num;

    tmp_err->next = NULL;

    if (!error_head) {
        error_head = tmp_err;
    } else {
        error *p = error_head;
        while (p->next) {
            p = p->next;
        }
        p->next = tmp_err;
    }
}

int is_error() {
    if (error_head) {
        return TRUE;
    }
    return FALSE;
}

int get_max_line() {
    error *p = error_head;
    int max_line = 1;
    if (!p)
        return 0;
    while (p) {
        if (p->line > max_line)
            max_line = p->line;
        p = p->next;
    }
    return max_line;
}

void print_errors() {
    error *p = error_head;
    while (p) {
        printf("\nError in line %d: %s\n", p->line, p->str_error);
        p = p->next;
    }
}


void free_errors() {
    error *ptr = error_head;
    if (!ptr)
        return;

    while (ptr) {
        error *tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
    error_head = NULL;
}
