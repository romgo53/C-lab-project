#include "project.h"

void assembler_first_pass(FILE *amFileP, int *IC, int *DC) {
    char line[MAX_LINE_SIZE];
    int line_counter = 0;

    while (fgets(line, MAX_LINE_SIZE, amFileP)) {

        /* Point to token */
        char *token = NULL;
        /* Point to label */
        char *label = NULL;
        /* Directive type */
        int directive = 0;
        line_counter++;
        printf("first pass line num: %d \n", line_counter);
        puts(line);
        token = strtok(line, " \t\n");

        if (!token) {
            continue;
        }
        if (is_comment(token)) {
            continue;
        }

        if ((label = get_label(token))) {
            if (!strcmp(label, "!")) {
                append_error("Illegal label", line_counter);
                label = NULL;
            } else if (!strcmp(label, "@")) {
                append_error("Label name is reserved", line_counter);
            }
            token = strtok(NULL, " \t\n");
            if (!token) {
                append_error("Must add something next to label", line_counter);
                continue;
            }
        }
        if ((directive = get_directive_type(token)) != DIRECTIVE_NONE) {
            /*if getDirective returned an error*/
            if (directive == DIRECTIVE_ERROR) {
                /*add error*/
                append_error("Invalid directive", line_counter);
                continue;
            }
                /* if the directive is a data directive */
            else if (directive == DIRECTIVE_DATA) {
                if (label) {
                    append_symbol(label, *DC, FALSE, FALSE, line_counter);
                    split_numbers(token, line_counter, DC);
                } else {
                    split_numbers(token, line_counter, DC);
                }
            } else if (directive == DIRECTIVE_STRING) {
                token = strtok(NULL, "\n");
                if (!token) {
                    append_error("String directive must have a string", line_counter);
                    continue;
                }
                if (label) {
                    /*add to symbols table*/
                    append_symbol(label, *DC, FALSE, FALSE, line_counter);
                    /*add to data table*/
                    add_string(token, line_counter, DC);
                    /* next line */
                    continue;
                } else {
                    add_string(token, line_counter, DC);
                    continue;
                }
            } else if (directive == DIRECTIVE_ENTRY) {

                if (!(token = strtok(NULL, " \t\n"))) {
                    append_error("Entry directive must have a label parameter", line_counter);
                    continue;
                }
                append_entry(token, line_counter);

                if ((token = strtok(NULL, " \t\n"))) {
                    append_error("Entry directive take only 1 parameter", line_counter);
                    continue;
                } else {
                    /* next line */
                    continue;
                }
            } else if (directive == DIRECTIVE_EXTERN) {
                if (!(token = strtok(NULL, " \t\n"))) {
                    append_error("Extern directive must have a label parameter", line_counter);
                    continue;
                }
                append_symbol(token, 0, TRUE, FALSE, line_counter);
                if ((token = strtok(NULL, " \t\n"))) {
                    append_error("Extern directive takes only 1 parameter", line_counter);
                    continue;
                } else {
                    /* next line */
                    continue;
                }
            }
        } else {
            analyze_line(token, line_counter, IC, label);
        }

    }
    if (line_counter == 0) {
        append_error("File is empty", line_counter);
    }
}

char *get_label(char *token) {
    char *ptr = token;
    /* If last char is ':' (Label) */
    if (token[strlen(token) - 1] == ':') {
        if (isalpha(*token)) {
            /* Remove ':' from label */
            token[strlen(token) - 1] = '\0';
            /* If there's a char which is not a digit or a letter, return an error flag */
            while (*ptr != '\0') {
                if (!isalpha(*ptr)) {
                    if (!isdigit(*ptr)) {
                        return "!";
                    }
                }
                ptr++;
            }

            /* check if label is a valid */
            if (is_opcode(token) || is_register(token)) {
                return "@";
            }
            return token;

        } else {
            return "!";
        }
    } else {
        return NULL;
    }
}

int get_directive_type(char *token) {
    if (*token == '.') {
        if (!strcmp(token, DATA_DIRECTIVE_STR)) {
            return DIRECTIVE_DATA;
        } else if (!strcmp(token, STRING_DIRECTIVE_STR)) {
            return DIRECTIVE_STRING;
        } else if (!strcmp(token, ENTRY_DIRECTIVE_STR)) {
            return DIRECTIVE_ENTRY;
        } else if (!strcmp(token, EXTERN_DIRECTIVE_STR)) {
            return DIRECTIVE_EXTERN;
        } else {
            return DIRECTIVE_ERROR;
        }
    } else {
        return DIRECTIVE_NONE;
    }
}