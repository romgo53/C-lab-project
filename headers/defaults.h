#ifndef DEFAULTS_H
#define DEFAULTS_H

/*This file contains enumerations and defines of constants*/

/*boolean enum*/

/*Directive enum - used during the first pass to determine which directive has been received.
NONE means no directive has been received and ERROR means that the string was recognized as a directive but the syntax was wrong*/
enum directive {
    DIRECTIVE_NONE = 0, DIRECTIVE_DATA = 1, DIRECTIVE_STRING, DIRECTIVE_ENTRY, DIRECTIVE_EXTERN, DIRECTIVE_ERROR
};

/*Addressing method enum - NONE means first word*/
enum ADDRESSING_METHOD {
    NONE = -1,
    IMMEDIATE = 1,
    DIRECT = 3,
    REGISTER = 5
};

enum ARE {
    ABSOLUTE = 0,
    EXTERNAL = 1,
    RELOCATABLE = 2
};


/*Directive string constants, to be compared with input*/
#define STR_DIRECTIVE_DATA ".data"
#define STR_DIRECTIVE_STRING ".string"
#define STR_DIRECTIVE_ENTRY ".entry"
#define STR_DIRECTIVE_EXTERN ".extern"

#define WORD_SIZE 12
#define BASE64_SIZE 6

/*Maximum line buffer size*/
#define MAX_LINE_SIZE 80

/*Maximum filename size*/
#define MAX_FILENAME_SIZE 50

/*Number of registers*/
#define NUM_OF_REGISTERS 8

/*Maximum and minimum values that can be stored in 13 bits*/
#define MAX_NUMBER_DATA 4095
#define MIN_NUMBER_DATA -4096
#define MAX_NUMBER_IMMEDIATE 1023
#define MIN_NUMBER_IMMEDIATE -1024


/*Amoount of opcodes*/
#define OPCODES_AMOUNT 16

/*Extrnsions for files*/
#define AS_EXTENSION ".as"
#define TXT_EXTENSION ".txt"
#define OB_EXTENSION ".ob"
#define ENT_EXTENSION ".ent"
#define EXT_EXTENSION ".ext"

/* Values */
#define STEP 1
#define EXIT 1
#define TRUE 1
#define FALSE 0
#define START 1
#define MIN_ARGUMENTS 2
#define LOOP_START 1
#define MACRO "mcro"
#define END_MACRO "endmcro"

/* Bits */
#define OPERAND_BITS_DEST 3
#define OPERAND_BITS_SRC 3
#define ARE_BITS 2
#define OPCODE_BITS 4
#define IMMEDIATE_BITS 10
#define REGISTER_BITS 5

/* Directives */
#define DATA_DIRECTIVE_STR ".data"
#define STRING_DIRECTIVE_STR ".string"
#define ENTRY_DIRECTIVE_STR ".entry"
#define EXTERN_DIRECTIVE_STR ".extern"


/*Opcodes*/
#define MOV 0
#define CMP 1
#define ADD 2
#define SUB 3
#define NOT 4
#define CLR 5
#define LEA 6
#define INC 7
#define DEC 8
#define JMP 9
#define BNE 10
#define RED 11
#define PRN 12
#define JSR 13
#define RTS 14
#define STOP 15

#endif