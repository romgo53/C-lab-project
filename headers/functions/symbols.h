

#ifndef C_LAB_PROJECT_SYMBOLS_H
#define C_LAB_PROJECT_SYMBOLS_H

/* Appends a symbol to the symbols list*/
void append_symbol(char *label, int address, int external, int operation, int line_number);

/* Update the symbol's addresses to match with the IC counter,
after the first pass */
void update_symbols(int IC);

/*This function cleans up the symbol list*/
void free_symbols();


/* Checks if a symbol with the same name exists */
void check_symbol(char *label, int line_number);

/* Returns a symbol with the same label as the string
entered as a parameter. if no such symbol was found, it will return NULL */
symbol *search_symbol(char *label);

#endif
