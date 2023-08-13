
#include "defaults.h"

#ifndef C_LAB_PROJECT_DEFINES_H
#define C_LAB_PROJECT_DEFINES_H

/*
 * This struct to save a macro and its contents
 */

typedef struct macro {
    char name[MAX_LINE_SIZE];
    char content[MAX_LINE_SIZE * MAX_LINE_SIZE];
} macro;

typedef struct firstWord {
    /* A.R.E bits */
    unsigned int are: ARE_BITS;

    /* Destination operand bits */
    unsigned int destination: OPERAND_BITS_DEST;

    /*Opcode bits*/
    unsigned int opcode: OPCODE_BITS;

    /*source operand bits*/
    unsigned int source: OPERAND_BITS_SRC;
} firstWord;

typedef struct immediateWord {
    /* A.R.E bits */
    unsigned int are: ARE_BITS;

    /*bits used to hold the value/address*/
    int number: IMMEDIATE_BITS;
} immediateWord;

typedef struct registerWord {
    /* A.R.E bits */
    unsigned int are: ARE_BITS;

    /*Destination register bits*/
    unsigned int destination: REGISTER_BITS;

    /*source register bits*/
    unsigned int source: REGISTER_BITS;
} registerWord;

/* Word holder union, used to hold all the words.
a union is used so that every type of word can be in a linked list together*/
typedef struct wordHolder {
    firstWord first;

    immediateWord immediate;

    registerWord reg;
} wordHolder;

/* wordNode is the type used in the word list. it contains a holder union type,
an address which is used when exporting files,
the method identifier which tells which type of word it holds,
the line number, the missing label string (if it refers to a label),
external label string (if it refers to an external variable),
an external flag, and a pointer to the next node */
typedef struct wordNode {
    /*The command itself*/
    struct wordHolder holder;
    /* The address assigned to it */
    int address;
    /* Addressing method */
    int method;
    /*Line number*/
    int line;
    /* Missing label */
    char *missing_label;
    /* Label of external */
    char *external_label;
    int is_external;
    /*Pointer to next*/
    struct wordNode *next;
} wordNode;

/*definition of opcode type
used to loop through all commands*/
typedef struct opcode {
    /*The operation string*/
    char *str;
    /*The opcode*/
    int code;
    /*The group*/
    int group;
} opcode;

/*definition of error type. used in the errors list*/
typedef struct error {
    /*The error itself*/
    char *str_error;
    /*The line where the error was found*/
    int line;
    /*Pointer to next*/
    struct error *next;
} error;

typedef struct symbol {
    /*Label of the symbol*/
    char *label;
    /*Address of the symbol*/
    int address;
    /*Is it external?*/
    int external;
    /*is it an operation?*/
    int operation;
    /*pointer to next*/
    struct symbol *next;
} symbol;

/* Definition of data type
contains an address and a value (which stores the number/char) */
typedef struct data {
    /*address of data word*/
    int address;
    /*Value*/
    short int value;
    /*pointer to next*/
    struct data *next;
} data;


/* Definition of entry type
Contains a label, an address, an address flag, a line value,
and a pointer to the next node */
typedef struct entry {
    /*Label of entry*/
    char *label;
    /*Address*/
    short int address;
    /*Does it have an address? (for internal use)*/
    int has_address;
    /*Line of entry*/
    int line;
    /*pointer to next*/
    struct entry *next;
} entry;


/*definition of opcode word type*/
static opcode op_codes[16] = {
        {"mov",  0,  0},
        {"cmp",  1,  0},
        {"add",  2,  0},
        {"sub",  3,  0},
        {"not",  4,  1},
        {"clr",  5,  1},
        {"lea",  6,  0},
        {"inc",  7,  1},
        {"dec",  8,  1},
        {"jmp",  9,  1},
        {"bne",  10, 1},
        {"red",  11, 1},
        {"prn",  12, 1},
        {"jsr",  13, 1},
        {"rts",  14, 2},
        {"stop", 15, 2}
};

static char *registers[8] = {
        "@r0",
        "@r1",
        "@r2",
        "@r3",
        "@r4",
        "@r5",
        "@r6",
        "@r7"
};

static char base64_table[64] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
        'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
        'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
        'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
        'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
        'w', 'x', 'y', 'z', '0', '1', '2', '3',
        '4', '5', '6', '7', '8', '9', '+', '/'
};


#endif
