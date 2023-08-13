#include "project.h"


char *to_binary(int n, int len) {
    char *binary = (char *) malloc(sizeof(char) * len);
    int k = 0;
    unsigned int i;
    for (i = (1 << len - 1); i > 0; i = i / 2) {
        binary[k++] = (n & i) ? '1' : '0';
    }
    binary[k] = '\0';
    return binary;
}

char *to_base64(char *binary) {
    /* split to 2 parts */
    char *part1 = (char *) malloc(sizeof(char) * BASE64_SIZE + 1);
    char *part2 = (char *) malloc(sizeof(char) * BASE64_SIZE + 1);
    char *base64 = (char *) malloc(sizeof(char) * 3);
    memcpy(part1, binary, BASE64_SIZE);
    part1[BASE64_SIZE] = '\0';
    memcpy(part2, binary + BASE64_SIZE, BASE64_SIZE);
    part2[BASE64_SIZE] = '\0';
    /* convert the split parts to decimal */
    int decimal1 = (int) strtol(part1, NULL, 2);
    int decimal2 = (int) strtol(part2, NULL, 2);
    /* convert the decimal to base64 */
    base64[0] = base64_table[decimal1];
    base64[1] = base64_table[decimal2];
    base64[2] = '\0';
    return base64;
}

int convert_to_array(char line[MAX_LINE_SIZE], char **words) {
    int word_index = 0;
    char *word;

    word = strtok(line, " \t\n");
    while (word != NULL) {
        words[word_index] = word;
        word_index++;
        word = strtok(NULL, " \t\n");
    }
    return word_index;
}

void remove_new_line(char line[MAX_LINE_SIZE], char new_line[MAX_LINE_SIZE]) {
    int char_index = 0;
    while (line[char_index] != '\n' && line[char_index] != '\0') {
        new_line[char_index] = line[char_index];
        char_index++;
    }
    new_line[char_index] = '\0';
}

int is_comment(char *token) {
    if (*token == ';') {
        return TRUE;
    }
    return FALSE;
}

int is_opcode(char *token) {
    int i;
    for (i = 0; i < OPCODES_AMOUNT; i++) {
        if (!strcmp(token, op_codes[i].str)) {
            return TRUE;
        }
    }
    return FALSE;
}

int is_register(char *token) {
    int i;
    /* Check if the token is a register with @ and without */
    for (i = 0; i < NUM_OF_REGISTERS; i++) {
        if ((strcmp(token, registers[i]) == 0) || (strcmp(token, registers[i] + 1) == 0)) {
            return TRUE;
        }
    }


    return FALSE;
}

void check_allocation(void *ptr) {
    if (!ptr) {
        printf("The program has quit due to a memory allocation error.\n");
        exit(0);
    }
}

int is_number(char *token) {
    int i;
    char *ptr;
    ptr = token;
    if (token[0] == '-' || token[0] == '+') {
        ptr++;
    }
    for (i = 0; i < strlen(ptr); i++) {
        if (!isdigit(ptr[i])) {
            return FALSE;
        }
    }
    return TRUE;
}

void analyze_line(char *token, int line_number, int *IC, char *label) {
    int i;
    int found_opcode_index = -1;
    /* Is opcode exists */
    int is_opcode = FALSE;
    /* IC increment calculation */
    int IC_increment = 0;
    /* pointer to word nodes */
    wordNode *first = NULL;
    wordNode *second = NULL;
    wordNode *third = NULL;
    /* Find opcode */
    for (i = 0; i < OPCODES_AMOUNT; i++) {
        if (strcmp(token, op_codes[i].str) == 0) {
            /* Create a new word object, initiate it and assign it with everything */
            is_opcode = TRUE;
            first = malloc(sizeof(wordNode));
            check_allocation(first);
            first->method = NONE;
            first->is_external = FALSE;
            first->missing_label = NULL;
            first->external_label = NULL;
            first->line = line_number;
            first->holder.first.opcode = op_codes[i].code;
            first->holder.first.source = 0;
            first->holder.first.destination = 0;
            first->holder.first.are = 0;
            first->next = NULL;
            /*Add one to the increment value*/
            IC_increment++;

            found_opcode_index = i;
        }
    }
    if (!is_opcode) {
        append_error("Unknown opcode", line_number);
        return;
    }
    /* Check parameters */
    if ((token = strtok(NULL, " ,\t\n"))) {

        if (op_codes[found_opcode_index].group == 0) {
            /* Check if the first parameter is a register */
            if (*token == '@' && is_register(token)) {
                puts(token);
                /* Check if command is 'lea', if so raise error */
                if (first->holder.first.opcode == LEA) {
                    append_error("This command can't take an immediate number as a first operand", line_number);
                    free(first);
                    return;
                }
                first->holder.first.source = REGISTER;
                second = malloc(sizeof(wordNode));
                second->method = REGISTER;
                second->is_external = FALSE;
                second->missing_label = NULL;
                second->external_label = NULL;
                second->line = line_number;
                second->holder.reg.source = (token[2] - '0');
                second->holder.reg.destination = 0;
                second->holder.reg.are = 0;
                second->next = NULL;
                /*Add one to the increment value*/
                IC_increment++;
            }
                /* check if token is a number */
            else if (is_number(token)) {
                int num;
                char *ptr;
                char *err_ptr;
                ptr = token;
                num = (int) strtol(ptr, &err_ptr, 10);
                if (first->holder.first.opcode == LEA) {
                    append_error("This command can't take an immediate number as a first operand", line_number);
                    free(first);
                    return;
                }
                if (*err_ptr != 0) {
                    append_error("Invalid number", line_number);
                    free(first);
                    return;
                }
                if (num > MAX_NUMBER_IMMEDIATE || num < MIN_NUMBER_IMMEDIATE) {
                    append_error("Number is out of range", line_number);
                    free(first);
                    return;
                }
                /* Syntax is correct */
                first->holder.first.source = IMMEDIATE;
                second = malloc(sizeof(wordNode));
                second->method = IMMEDIATE;
                second->is_external = FALSE;
                second->missing_label = NULL;
                second->external_label = NULL;
                second->line = line_number;
                second->holder.immediate.number = num;
                second->holder.immediate.are = 0;
                second->next = NULL;
                IC_increment++;
            }
                /* If the first parameter is not a register or a number, it must be a label */
            else {

                char *ptr;
                ptr = token;
                if (isalpha(*ptr)) {
                    while (*ptr != '\0') {
                        if ((!isdigit(*ptr)) && (!isalpha(*ptr))) {
                            append_error("Invalid character", line_number);
                            free(first);
                            return;
                        }
                        ptr++;
                    }

                    /* Syntax is correct */
                    first->holder.first.source = DIRECT;
                    second = malloc(sizeof(wordNode));
                    second->method = DIRECT;
                    second->is_external = FALSE;
                    second->missing_label = malloc(sizeof(char) * MAX_LINE_SIZE);
                    strcpy(second->missing_label, token);
                    second->external_label = NULL;
                    second->line = line_number;
                    second->holder.immediate.number = 0;
                    second->holder.immediate.are = 1;
                    second->next = NULL;
                    IC_increment++;
                } else {
                    append_error("Labels must start with a letter", line_number);
                    free(first);
                    return;
                }
            }
            if ((token = strtok(NULL, " ,\t\n"))) {
                /* Check if the second parameter is a register */
                if (*token == '@' && is_register(token)) {
                    puts(token);
                    first->holder.first.destination = REGISTER;
                    third = malloc(sizeof(wordNode));
                    third->method = REGISTER;
                    third->is_external = FALSE;
                    third->missing_label = NULL;
                    third->external_label = NULL;
                    third->line = line_number;
                    third->holder.reg.source = 0;
                    third->holder.reg.destination = (token[2] - '0');
                    third->holder.reg.are = 0;
                    third->next = NULL;
                    /*Add one to the increment value*/
                    IC_increment++;
                }
                    /* check if the second token is a number */
                else if (is_number(token)) {
                    int num;
                    char *ptr;
                    char *err_ptr;
                    ptr = token;
                    num = (int) strtol(ptr, &err_ptr, 10);
                    if (first->holder.first.opcode == CMP) {
                        append_error("This command can't take an immediate number as a second operand", line_number);
                        free(first);
                        free(second);
                        return;
                    }
                    if (*err_ptr != 0) {
                        append_error("Invalid number", line_number);
                        free(first);
                        free(second);
                        return;
                    }
                    if (num > MAX_NUMBER_IMMEDIATE || num < MIN_NUMBER_IMMEDIATE) {
                        append_error("Number is out of range", line_number);
                        free(first);
                        free(second);
                        return;
                    }
                    /* Syntax is correct */
                    first->holder.first.destination = IMMEDIATE;
                    third = malloc(sizeof(wordNode));
                    third->method = IMMEDIATE;
                    third->is_external = FALSE;
                    third->missing_label = NULL;
                    third->external_label = NULL;
                    third->line = line_number;
                    third->holder.immediate.number = num;
                    third->holder.immediate.are = 0;
                    third->next = NULL;
                    IC_increment++;
                }
                    /* If the second parameter is not a register or a number, it must be a label */
                else {
                    char *ptr;
                    ptr = token;
                    if (isalpha(*ptr)) {
                        while (*ptr != '\0') {
                            if ((!isdigit(*ptr)) && (!isalpha(*ptr))) {
                                append_error("Invalid character", line_number);
                                free(first);
                                free(second);
                                return;
                            }
                            ptr++;
                        }

                        /* Syntax is correct */
                        first->holder.first.destination = DIRECT;
                        third = malloc(sizeof(wordNode));
                        third->method = DIRECT;
                        third->is_external = FALSE;
                        third->missing_label = malloc(sizeof(char) * MAX_LINE_SIZE);
                        strcpy(third->missing_label, token);
                        third->external_label = NULL;
                        third->line = line_number;
                        third->holder.immediate.are = 1;
                        third->holder.immediate.number = 0;
                        third->next = NULL;
                    } else {
                        append_error("Labels must start with a letter", line_number);
                        free(first);
                        free(second);
                        return;
                    }

                }
                if ((token = strtok(NULL, " ,\t\n"))) {
                    append_error("Too many arguments", line_number);
                    free(first);
                    free(second);
                    free(third);
                    return;
                }
            } else {
                append_error("This command must take 2 parameters", line_number);
                free(first);
                free(second);
                return;
            }
        }
            /* command if from group 1 */
        else if (op_codes[found_opcode_index].group == 1) {
            if (*token == '@' && is_register(token)) {
                if (first->holder.first.opcode == LEA) {
                    first->holder.first.destination = REGISTER;
                    second = malloc(sizeof(wordNode));
                    second->method = REGISTER;
                    second->is_external = FALSE;
                    second->missing_label = NULL;
                    second->external_label = NULL;
                    second->line = line_number;
                    second->holder.reg.source = (token[2] - '0');
                    second->holder.reg.destination = 0;
                    second->holder.reg.are = 0;
                    second->next = NULL;
                    IC_increment++;
                }
            } else if (is_number(token)) {
                int num;
                char *ptr;
                char *err_ptr;
                ptr = token;
                num = (int) strtol(ptr, &err_ptr, 10);
                if (first->holder.first.opcode != PRN) {
                    append_error("This command can't take an immediate number as a first operand", line_number);
                    free(first);
                    return;
                }
                if (*err_ptr != 0) {
                    append_error("Invalid number", line_number);
                    free(first);
                    return;
                }
                if (num > MAX_NUMBER_IMMEDIATE || num < MIN_NUMBER_IMMEDIATE) {
                    append_error("Number is out of range", line_number);
                    free(first);
                    return;
                }
                /* Syntax is correct */
                first->holder.first.destination = IMMEDIATE;
                second = malloc(sizeof(wordNode));
                second->method = IMMEDIATE;
                second->is_external = FALSE;
                second->missing_label = NULL;
                second->external_label = NULL;
                second->line = line_number;
                second->holder.immediate.number = num;
                second->holder.immediate.are = 0;
                second->next = NULL;
                IC_increment++;
            } else {
                char *ptr;
                ptr = token;
                if (isalpha(*ptr)) {
                    while (*ptr != '\0') {
                        if ((!isdigit(*ptr)) && (!isalpha(*ptr))) {
                            append_error("Invalid character", line_number);
                            free(first);
                            return;
                        }
                        ptr++;
                    }

                    /* Syntax is correct */
                    first->holder.first.destination = DIRECT;
                    second = malloc(sizeof(wordNode));
                    second->method = DIRECT;
                    second->is_external = FALSE;
                    second->missing_label = malloc(sizeof(char) * MAX_LINE_SIZE);
                    strcpy(second->missing_label, token);
                    second->external_label = NULL;
                    second->line = line_number;
                    second->holder.immediate.number = 0;
                    second->holder.immediate.are = 1;
                    second->next = NULL;
                    IC_increment++;
                } else {
                    append_error("Labels must start with a letter", line_number);
                    free(first);
                    return;
                }
            }
            if ((token = strtok(NULL, " ,\t\n"))) {
                append_error("Too many arguments", line_number);
                free(first);
                free(second);
                return;
            }
        }
            /* Opcode group is 2 */
        else {
            append_error("This command can't take any operands", line_number);
            free(first);
            return;
        }
    }
        /* Didn't receive any parameters after the command (Group 2)*/
    else {
        if (first->holder.first.opcode != STOP && first->holder.first.opcode != RTS) {
            append_error("Missing parameters", line_number);
            free(first);
            return;
        }
    }
    if (label) {
        append_symbol(label, *IC, FALSE, TRUE, line_number);
    }
    /*Add each word (as needed) to the words list*/
    add_word(first);
    if (second) {
        printf("second is not null\n");
        add_word(second);
    }
    if (third) {
        printf("Line of the third: %d", third->line);
        add_word(third);
    }
    *IC += IC_increment;
}

