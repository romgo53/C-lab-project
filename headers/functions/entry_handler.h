#ifndef C_LAB_PROJECT_ENTRY_HANDLER_H
#define C_LAB_PROJECT_ENTRY_HANDLER_H


/* Adds an entry to the list. it takes a label and a line, for error reporting*/
void append_entry(char *label, int line);


/* Checks if an entry with the same label already exists
If there is one, it will return 0. else, it will return 1; */
int check_entry(char *label);


/* Frees all the nodes in this list */
void free_entry();


/* Returns an entry without an address assigned to it.
   for use during the second pass */
entry *pop_entry();


/* Returns a pointer to the head */
entry *get_head_entry();


#endif
