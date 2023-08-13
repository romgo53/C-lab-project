
#include "../global_defines.h"

#ifndef C_LAB_PROJECT_UTILS_H
#define C_LAB_PROJECT_UTILS_H

/* Divides the sentence into an array that contains the words of the sentence */
int convert_to_array(char line[MAX_LINE_SIZE], char **words);

/* Removes a new line from the end of the line */
void remove_new_line(char line[MAX_LINE_SIZE], char new_line[MAX_LINE_SIZE]);

/* Checks if the given line a comment */
int is_comment(char *token);

/* Check if the given token is a register */
int is_register(char *token);

/* Check if the given token is an opcode */
int is_opcode(char *token);

/* Checks if pointer is null */
void check_allocation(void *ptr);

/* Converts a number to binary string */
char *to_binary(int num, int len);

/* Converts a binary string to Base64 string  */
char *to_base64(char *binary);

/* Splits the input string to tokens and will analyze each token.
It will create the corresponding word nodes, add them to the word list,
and increment the IC as needed. */
void analyze_line(char *token, int line_number, int *IC, char *label);

#endif
