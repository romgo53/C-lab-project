#include "../lib/lib.h"

#ifndef C_LAB_PROJECT_FIRST_PASS_H
#define C_LAB_PROJECT_FIRST_PASS_H

/* Assembler first pass algo */
void assembler_first_pass(FILE *amFileP, int *IC, int *DC);

/* The function looks for a label
 * If there is a label, it returns the label
 * If there's an illegal label, it returns "!" for char error and "$" for saved word error
 * If there's no label, it returns NULL
 */
char *get_label(char *token);

int get_directive_type(char *token);

#endif