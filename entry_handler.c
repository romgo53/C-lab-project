#include "project.h"

entry *entry_head = NULL;

void append_entry(char *label, int line_number) {
    entry *new_entry = NULL;

    if (!check_entry(label)) {
        append_error("Label already exists", line_number);
        return;
    }

    new_entry = malloc(sizeof(entry));
    check_allocation(new_entry);
    new_entry->label = malloc(sizeof(char) * MAX_LINE_SIZE);
    strcpy(new_entry->label, label);
    new_entry->address = 0;
    new_entry->has_address = FALSE;
    new_entry->line = line_number;
    new_entry->next = NULL;

    /* add to the end of the list */
    if (!entry_head) {
        entry_head = new_entry;
    } else {
        entry *ptr = entry_head;
        while (ptr->next) {
            ptr = ptr->next;
        }
        ptr->next = new_entry;
    }
}


int check_entry(char *label) {
    entry *ptr = entry_head;
    while (ptr) {
        if (!strcmp(ptr->label, label)) {
            return 0;
        }
        ptr = ptr->next;
    }
    return 1;
}


void free_entry() {
    entry *ptr = entry_head;
    if (!ptr) {
        return;
    }
    while (ptr) {
        entry *tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
    entry_head = NULL;
}


entry *pop_entry() {
    entry *ptr = entry_head;
    while (ptr) {
        if (!ptr->has_address) {
            return ptr;
        }
        ptr = ptr->next;
    }

    return NULL;
}


entry *get_head_entry() {
    entry *ptr = entry_head;
    return ptr;
}