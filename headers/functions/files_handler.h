#include "../lib/lib.h"

#ifndef C_LAB_PROJECT_FILES_HANDLER_H
#define C_LAB_PROJECT_FILES_HANDLER_H

/* Opens a new file using the file's name, mode and extension.
 * Returns a pointer to the file.
 * If the file couldn't be opened, the function prints an error and exits the program.
 */
FILE *open_file(char *file_name, char *mode, char *extension);

/* Generates the files using the IC and DC counters
  and the data that was collected during first and second pass */
void generate_files(int IC, int DC, char *name);

#endif
