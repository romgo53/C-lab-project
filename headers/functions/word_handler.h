#include "../global_defines.h"

#ifndef C_LAB_PROJECT_WORD_HANDLER_H
#define C_LAB_PROJECT_WORD_HANDLER_H

/* Add a word to the list */
void add_word(wordNode *node);

/* Updates all the words with their corresponding addresses*/
void update_word_list_addresses();

/* Returns the number of nodes in the list */
int count_words();

/* Cleans up the list */
void free_words();

/* Searches for a word with a missing label and return it.
if no such word was found, it will return NULL */
wordNode *get_word_with_missing_label();

/* Returns a pointer to the head of the list */
wordNode *get_head_word();

#endif
