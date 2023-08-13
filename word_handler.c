#include "project.h"

static wordNode *word_head = NULL;

void add_word(wordNode *node) {
    if (!word_head) {
        word_head = node;
        return;
    }
    wordNode *ptr = word_head;
    while (ptr->next) {
        ptr = ptr->next;
    }
    ptr->next = node;
}

/* TODO: check if this is needed */
void update_word_list_addresses() {
    wordNode *ptr = word_head;
    int address = 100;
    if (!ptr)
        return;
    while (ptr) {
        ptr->address = address;
        address += 1;
        ptr = ptr->next;
    }
}

int count_words() {
    wordNode *ptr = word_head;
    int count = 0;
    while (ptr) {
        count++;
        ptr = ptr->next;
    }
    return count;
}

void free_words() {
    wordNode *ptr = word_head;
    if (!ptr)
        return;
    while (ptr) {
        wordNode *tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
    word_head = NULL;
}

wordNode *get_word_with_missing_label() {
    wordNode *ptr = word_head;
    while (ptr) {
        if (ptr->missing_label) {
            return ptr;
        }
        ptr = ptr->next;
    }
    return NULL;
}

wordNode *get_head_word() {
    wordNode *ptr = word_head;
    return ptr;
}