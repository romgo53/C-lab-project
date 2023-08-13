#include "project.h"

int main(int argc, char *argv[]) {
    FILE *file_p;                    /* Will point to the given file */
    FILE *am_file_p;                /* Will point to a new file that will contain the program after placing macros */
    int current_file_index;      /* the current input fileName index */
    char current_file_name[MAX_FILENAME_SIZE];    /* Will contain the file name without the mime*/
    char am_file_name[MAX_FILENAME_SIZE];
    char ext_file_name[MAX_FILENAME_SIZE];
    char obj_file_name[MAX_FILENAME_SIZE];
    char ent_file_name[MAX_FILENAME_SIZE];
    char as_file_name[MAX_FILENAME_SIZE];    /* Will contain the file name with .as */


    int IC = 0;  /* instruction counter */
    int DC = 0;  /* data counter */

    if (argc == 1) {
        printf("Error: missing arguments\n");
        return EXIT;
    }
    for (current_file_index = LOOP_START; current_file_index < argc; current_file_index++) {

        strcpy(current_file_name, argv[current_file_index]);
        strcpy(am_file_name, current_file_name);
        strcpy(ext_file_name, argv[current_file_index]);
        strcpy(obj_file_name, argv[current_file_index]);
        strcpy(ent_file_name, argv[current_file_index]);
        strcpy(as_file_name, argv[current_file_index]);
        /* Open user file */

        file_p = fopen(strcat(as_file_name, ".as"), "r");
        /* Create .am file */
        am_file_p = fopen(strcat(am_file_name, ".am"), "w+");

        if (file_p == NULL) {
            printf("Error: file %s not found/unable to open moving to the next file\n", current_file_name);
            continue;
        }

        if (macros_deployment(file_p, am_file_p) == FALSE) {
            printf("Error: file %s not found/unable to open moving to the next file\n", current_file_name);
            continue;
        }
        fclose(am_file_p);
        am_file_p = fopen(am_file_name, "r");


        fclose(file_p);
        /* First pass */
        assembler_first_pass(am_file_p, &IC, &DC);

        /* Update symbols */
        update_symbols(IC);

        /* Update word list addresses */
        update_word_list_addresses();

        /* Update data list addresses */
        update_data_addresses(IC);
        /* Second pass */
        assembler_second_pass(IC);

        if (!is_error()) {
            generate_files(IC, DC, current_file_name);
        }
            /* If there were error, print them and don't create the output files */

        else {
            print_errors();
            free_errors();
        }
        /* Cleanups */
        free_data();
        free_symbols();
        free_entry();
        free_words();

    }

    return 0;
}

