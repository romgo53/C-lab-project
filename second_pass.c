#include "project.h"

void assembler_second_pass(int IC) {
    wordNode *tmp_word = NULL;
    entry *tmp_entry = NULL;
    symbol *tmp_symbol = NULL;

    if ((count_words() + count_data()) > 1000) {
        append_error("Exceeded memory limit", -1);
        return;
    }
    /*Loop that gets every label which is missing an address*/
    while ((tmp_word = get_word_with_missing_label())) {
        tmp_symbol = search_symbol(tmp_word->missing_label);
        /*If no such symbol was found, add an error*/
        if (!tmp_symbol) {
            char *tmp_string;
            tmp_string = malloc(sizeof(char) * MAX_LINE_SIZE);
            strcpy(tmp_string, "Label \"");
            strcat(tmp_string, tmp_word->missing_label);
            strcat(tmp_string, "\" was not declared");
            append_error(tmp_string, tmp_word->line);
        }
            /*If the symbol was found*/
        else {
            /*If it's external, change the word accordingly*/
            if (tmp_symbol->external) {
                printf("address is %d\n", tmp_word->address);
                tmp_word->holder.immediate.are = 1;
                tmp_word->holder.immediate.number = 0;
                tmp_word->is_external = TRUE;
                tmp_word->external_label = tmp_symbol->label;
            } else {
                /* Not external */
                tmp_word->holder.immediate.are = 2;
                tmp_word->holder.immediate.number = tmp_symbol->address;
            }
        }
        tmp_word->missing_label = NULL;
    }
    /*Go through the entry list*/
    while ((tmp_entry = pop_entry())) {
        /* Search for symbols with the same label */
        tmp_symbol = search_symbol(tmp_entry->label);
        /*If there is no such symbol, add an error*/
        if (!tmp_symbol) {
            char *tmp_string;
            tmp_string = malloc(sizeof(char) * MAX_LINE_SIZE);
            strcpy(tmp_string, "Label \"");
            strcat(tmp_string, tmp_entry->label);
            strcat(tmp_string, "\" was not declared");
            append_error(tmp_string, tmp_entry->line);
            tmp_entry->has_address = TRUE;
        }
            /*If a symbol was found, assign its address to the entry node*/
        else {
            tmp_entry->address = tmp_symbol->address;
            tmp_entry->has_address = TRUE;
        }
    }

}