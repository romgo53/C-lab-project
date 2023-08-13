#include "project.h"

data *data_head = NULL;


void split_numbers(char *token, int line_number, int *DC) {
    if (!(token = strtok(NULL, " ,\t\n"))) {
        append_error("You must specify numbers", line_number);
        return;
    }
    add_number(token, line_number, DC);
    while ((token = strtok(NULL, " ,\t\n"))) {
        add_number(token, line_number, DC);
    }
}


void add_number(char *number, int line_number, int *DC) {
    /* pointer for strtol error checking */
    char *p = NULL;
    data *new_data = NULL;
    long int tmp_num;
    tmp_num = strtol(number, &p, 10);
    /*if strtok returned an error*/
    if (*p != '\0') {
        append_error("Invalid number", line_number);
        return;
    }
    new_data = malloc(sizeof(data));
    check_allocation(new_data);
    new_data->value = (short int) tmp_num;
    new_data->next = NULL;
    /* add to the end of the list */
    if (!data_head) {
        data_head = new_data;
    } else {
        data *ptr = data_head;
        while (ptr->next) {
            ptr = ptr->next;
        }
        ptr->next = new_data;
    }
    (*DC)++;
}


void add_char(char c) {
    data *new_data = malloc(sizeof(data));
    new_data->value = c;
    new_data->next = NULL;

    /* add to the end of the list */
    if (!data_head) {
        data_head = new_data;
        return;
    }
    data *ptr = data_head;
    while (ptr->next) {
        ptr = ptr->next;
    }
    ptr->next = new_data;
}


void add_string(char *string, int line_number, int *DC) {
    if (!strcmp(string, "\"")) {
        append_error("Must specify a string", line_number);
        return;
    }
    /*Check if string is surrounded by quotation marks*/
    if (*string == '"' && string[strlen(string) - 1] == '"') {
        /*change right quotation marks to null terminator*/
        string[strlen(string) - 1] = '\0';
        /*point string to character after left quotation mark*/
        string++;
    } else {
        /*add error and return*/
        append_error("Strings must be surrounded by quotation marks", line_number);
        return;
    }
    /* Add each character to the data list */
    while (*string != '\0') {
        add_char(*string);
        string++;
        (*DC)++;
    }
    add_char('\0');
    (*DC)++;
}


int count_data() {
    int counter = 0;
    data *ptr = data_head;
    if (!ptr) {
        return counter;
    }
    while (ptr) {
        counter++;
        ptr = ptr->next;
    }
    return counter;
}


void update_data_addresses(int IC) {
    data *ptr = data_head;
    if (!ptr) {
        return;
    }
    while (ptr) {
        ptr->address = IC;
        IC++;
        ptr = ptr->next;
    }
}


void free_data() {
    data *ptr = data_head;
    if (!ptr) {
        return;
    }
    while (ptr) {
        data *tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
    data_head = NULL;
}


data *get_head_data() {
    data *ptr = data_head;
    return ptr;
}