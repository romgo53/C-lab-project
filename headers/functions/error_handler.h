#include "../lib/lib.h"

#ifndef C_LAB_PROJECT_ERROR_HANDLER_H
#define C_LAB_PROJECT_ERROR_HANDLER_H

/* The function adds an error to the errors list */
void append_error(char *error, int line_number);

/*This function will return 0 if there's no error, and another value if there was an error*/
int is_error();

/*This function returns the last line an error appears in.
used in the error printing loop*/
int get_max_line();

/* Prints all the errors to stdout */
void print_errors();

/*clean up the errors list*/
void free_errors();

#endif
