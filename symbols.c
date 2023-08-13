#include "project.h"

/* Symbols table */
symbol *symbol_head = NULL;

void append_symbol(char *label, int address, int external, int operation, int line_number) {
    symbol *new_symbol = malloc(sizeof(symbol));
    check_symbol(label, line_number);
    check_allocation(new_symbol);
    new_symbol->label = malloc(sizeof(char) * MAX_LINE_SIZE);
    check_allocation(new_symbol);
    strcpy(new_symbol->label, label);
    new_symbol->address = address;
    new_symbol->external = external;
    new_symbol->operation = operation;
    new_symbol->next = NULL;
    if (!symbol_head) {
        symbol_head = new_symbol;
        return;
    }
    symbol *ptr = symbol_head;
    while (ptr->next) {
        ptr = ptr->next;
    }
    ptr->next = new_symbol;
}

void update_symbols(int IC) {
    symbol *ptr = symbol_head;
    while (ptr) {
        if ((ptr->external == FALSE) && (ptr->operation == FALSE)) {
            ptr->address += IC;
        }
        ptr = ptr->next;
    }
}

void free_symbols() {
    symbol *ptr = symbol_head;
    while (ptr) {
        symbol *tmp = ptr;
        ptr = ptr->next;
        free(tmp->label);
        free(tmp);
    }
}

void check_symbol(char *label, int line_number) {
    symbol *ptr = symbol_head;
    while (ptr) {
        if (strcmp(ptr->label, label) == 0) {
            printf("Error: label %s already exists in line %d\n", label, line_number);
            return;
        }
        ptr = ptr->next;
    }
}

symbol *search_symbol(char *label) {
    symbol *ptr = symbol_head;
    while (ptr) {
        if (strcmp(ptr->label, label) == 0) {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}