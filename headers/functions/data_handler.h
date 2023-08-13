#include "../global_defines.h"

#ifndef C_LAB_PROJECT_DATA_LIST_H
#define C_LAB_PROJECT_DATA_LIST_H

/* Takes a string as a parameter, and splits it into tokens of whole numbers.
if the string receives is null, it will add an error. otherwise, it will loop through the string's
tokens and send each one to the add_number function*/
void split_numbers(char *token, int line, int *DC);

/* Adds a number to the data list.
It will check if the string is a valid number, and if the number is within range.
It will convert the string to a long int and then store it in the data node*/
void add_number(char *number, int line, int *DC);

/*Adds an individual character to the symbols list.
Used when adding a string*/
void add_char(char chr);

/*Adds a string to the data list*/
void add_string(char *string, int line, int *DC);


/*Counts the number of nodes in the data list*/
int count_data();

/* Updates the data addresses AFTER we have all our operation words*/
void update_data_addresses(int IC);

/*Clear the data list*/
void free_data();

/*return pointer to head. used when exporting files*/
data *get_head_data();

#endif
