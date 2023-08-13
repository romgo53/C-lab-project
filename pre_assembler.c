#include "project.h"


int macros_deployment(FILE *file_p, FILE *new_file_p) {

    char line[MAX_LINE_SIZE];
    int macro_flag = FALSE; /* flag to indicate if we are in a macro */
    int end_macro_flag = FALSE; /* flag to indicate if we are in the end of a macro */
    macro *macros = NULL; /* array of macros */
    int macro_counter = 0;
    macro *temp_macro;  /* Will be used to make sure the realloc didn't return a NULL */
    int word_in_line_counter = 0;
    char *words[MAX_LINE_SIZE]; /* array of words in a line */
    char line_copy[MAX_LINE_SIZE]; /* Will hold a copy of the current line */
    int macro_index; /* Will be used to iterate over the macros array */
    int inline_word_index = 0;
    char new_word[MAX_LINE_SIZE]; /* Will hold a word after removing spaces */

    /*
     1.  Opens a file
     2.  Gets his Macros
     3.  Copies the content to a new file and changes the macro contents
     */
    while (fgets(line, MAX_LINE_SIZE, file_p)) {
        strcpy(line_copy, line);
        /* separate the line into words separated by spaces and insert them into the array */
        convert_to_array(line, words);

        if (strcmp(words[0], MACRO) == 0) {
            end_macro_flag = FALSE;
            macro_counter++;
            if (macro_flag == FALSE) {
                macro_flag = TRUE;
                macros = (macro *) malloc(sizeof(macro));
                if (macros == NULL) {
                    puts("wasn't able to dynamically allocate en array, will stop the program from running");
                    return FALSE;
                }


                /* Inserting the macro's name into struct */
                strcpy((macros[macro_counter - STEP].name), words[1]);

                /*Adds lines until reaching the end of the macro */
                while (end_macro_flag == FALSE) {
                    fgets(line, MAX_LINE_SIZE, file_p);
                    word_in_line_counter = convert_to_array(line, words);
                    inline_word_index = 0;
                    remove_new_line(words[inline_word_index], new_word);

                    while ((strcmp(new_word, END_MACRO)) != 0 && inline_word_index < word_in_line_counter) {
                        strcat((macros[macro_counter - STEP].content), words[inline_word_index]);
                        inline_word_index++;
                        strcat(macros[macro_counter - STEP].content, " ");
                    }


                    if (strcmp(new_word, END_MACRO) == 0) {
                        end_macro_flag = TRUE;
                    } else {
                        strcat(macros[macro_counter - STEP].content, "\n");
                    }
                }
            } else {
                temp_macro = (macro *) realloc(macros, sizeof(macro) * macro_counter);
                if (temp_macro == NULL) {
                    puts("wasn't able to dynamically allocate en array, will stop the program from running");
                    return FALSE;
                }
                macros = temp_macro;
                strcpy((macros[macro_counter - STEP].name), words[1]);
            }

            while (end_macro_flag == FALSE) {
                fgets(line, MAX_LINE_SIZE, file_p);
                word_in_line_counter = convert_to_array(line, words);
                inline_word_index = 0;
                remove_new_line(words[inline_word_index], new_word);

                while (strcmp(new_word, END_MACRO) != 0 && inline_word_index < word_in_line_counter) {
                    strcat(macros[macro_counter - STEP].content, words[inline_word_index]);
                    inline_word_index++;
                    strcat(macros[macro_counter - STEP].content, " ");
                }

                if (strcmp(new_word, END_MACRO) == 0) {
                    end_macro_flag = TRUE;
                    macro_flag = TRUE;
                } else {
                    strcat(macros[macro_counter - STEP].content, "\n");
                }
            }
        } else {
            for (macro_index = 0; macro_index < macro_counter && macro_index >= 0; macro_index++) {
                if (strcmp(words[0], macros[macro_index].name) == 0) {
                    fputs(macros[macro_index].content, new_file_p);
                    macro_index = -2;
                }
            }
            if (macro_index >= 0)        /* Will enter if it is not a macro*/
            {
                fputs(line_copy, new_file_p); /* Will copy the line to the new file*/
            }

        }
    }
    if (macros)
        free(macros);
    return TRUE;
}