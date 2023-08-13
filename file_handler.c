#include "project.h"


FILE *open_file(char *file_name, char *mode, char *extension) {
    FILE *file = NULL;
    char file_name_with_extension[MAX_FILENAME_SIZE];
    strcpy(file_name_with_extension, file_name);
    strcat(file_name_with_extension, extension);
    file = fopen(file_name_with_extension, mode);
    if (file == NULL) {
        printf("Error opening file %s\n", file_name_with_extension);
        exit(1);
    }
    return file;
}

void generate_files(int IC, int DC, char *name) {
    /* File pointer */
    FILE *ext_file_p = NULL;
    FILE *ob_file_p = NULL;
    FILE *ent_file_p = NULL;
    /* Word var */
    firstWord *first_word = NULL;
    immediateWord *imm_word = NULL;
    registerWord *reg_word = NULL;
    /* extern flag */
    int extern_flag = FALSE;
    /* entry counter */
    int entry_counter = 0;

    wordNode *words_p = NULL;
    entry *entries_p = NULL;
    data *data_p = NULL;

    /* Create .ob file */
    ob_file_p = open_file(name, "w", OB_EXTENSION);

    words_p = get_head_word();

    /* Write word counter and data counter to .ob file (Base 10) */
    fprintf(ob_file_p, "%d %d\n", count_words(), count_data());

    while (words_p) {
        first_word = NULL;
        imm_word = NULL;
        reg_word = NULL;

        /* Assign word_to_print with corresponding word */
        switch (words_p->method) {
            case NONE:
                first_word = malloc(sizeof(firstWord));
                *first_word = words_p->holder.first;
            case IMMEDIATE:
                imm_word = malloc(sizeof(imm_word));
                *imm_word = words_p->holder.immediate;
            case DIRECT:
                imm_word = malloc(sizeof(imm_word));
                *imm_word = words_p->holder.immediate;
            case REGISTER:
                reg_word = malloc(sizeof(reg_word));
                *reg_word = words_p->holder.reg;
        }
        char word_binary[MAX_LINE_SIZE];
        /* convert word_binary to binary*/
        if (first_word) {
            char *source = to_binary(first_word->source, OPERAND_BITS_SRC);
            char *opcode = to_binary(first_word->opcode, OPCODE_BITS);
            char *destination = to_binary(first_word->destination, OPERAND_BITS_DEST);
            char *are = to_binary(first_word->are, ARE_BITS);
            strcpy(word_binary, source);
            strcat(word_binary, opcode);
            strcat(word_binary, destination);
            strcat(word_binary, are);
        } else if (imm_word) {
            char data[MAX_LINE_SIZE];
            if (imm_word->are == RELOCATABLE) {
                /* The address starts from 100 */
                strcpy(data, to_binary((imm_word->number + 101), IMMEDIATE_BITS));
            } else {
                strcpy(data, to_binary(imm_word->number, IMMEDIATE_BITS));
            }
            char *are = to_binary(imm_word->are, ARE_BITS);
            strcpy(word_binary, data);
            strcat(word_binary, are);
        } else if (reg_word) {
            char *source = to_binary(reg_word->source, REGISTER_BITS);
            char *destination = to_binary(reg_word->destination, REGISTER_BITS);
            char *are = to_binary(reg_word->are, ARE_BITS);
            strcpy(word_binary, source);
            strcat(word_binary, destination);
            strcat(word_binary, are);
        }
        printf("%s\n", word_binary);
        /* Write base64 to .ob file */
        fprintf(ob_file_p, "%s\n", to_base64(word_binary));

        /* Check if external was found */
        if (words_p->is_external == TRUE) {
            extern_flag = TRUE;
        }
        words_p = words_p->next;
    }
    /* Assign pointer with data list head */
    data_p = get_head_data();
    while (data_p) {
        /* Print the address and data in BASE64 */
        fprintf(ob_file_p, "%s\n", to_base64(to_binary(data_p->value, 12)));
        data_p = data_p->next;
    }
    /* Assign pointer with entry list head */
    entries_p = get_head_entry();

    if (entries_p) {
        /* Create .ent file */
        ent_file_p = open_file(name, "w", ENT_EXTENSION);

        while (entries_p) {
            /* Print the entry label and address in base 10 */
            fprintf(ent_file_p, "%s %d\n", entries_p->label, entries_p->address + 100);
            entries_p = entries_p->next;
            entry_counter++;
        }
    }

    if (extern_flag) {
        /* Create .ext file */
        ext_file_p = open_file(name, "w", EXT_EXTENSION);
        words_p = get_head_word();
        while (words_p) {
            if (words_p->is_external == TRUE) {
                /* Print the external label and address in base 10 */
                fprintf(ext_file_p, "%s %d\n", words_p->external_label, words_p->address);
            }
            words_p = words_p->next;
        }
    }

    /* Close files */
    if (ob_file_p)
        fclose(ob_file_p);
    if (ext_file_p)
        fclose(ext_file_p);
    if (ent_file_p)
        fclose(ent_file_p);
}