/*
 *  @author: dwclake
 */

#include <stdio.h>
#include <stdlib.h>
#include "compiler.h"

/* Creates a new compiler process
 * @param in_filename The file to compile
 * @param out_filename The name for the output file
 * @param flags Flags involving in file compilation
 * @return A new Compiler pointer or NULL
 */
struct Compiler* create_compiler(
        const char* in_filename, 
        const char* out_filename, 
        int flags
) {
    FILE* file = fopen(in_filename, "r");

    if (!file) return NULL;

    FILE* out_file = NULL;
    if (out_filename) {
        out_file = fopen(out_filename, "w");
        if (!out_file) return NULL;
    }

    struct Compiler* process = calloc(1, sizeof(struct Compiler));

    process->flags = flags;
    process->in_file.fp = file;
    process->in_file.path = in_filename;
    process->out_file.fp = out_file;
    process->out_file.path = out_filename;

    return process;
}


/* Free's the compiler from memory
 * @param process The compiler process to be freed
 * @return void
 */
void free_compiler(struct Compiler* process) {
    fclose(process->in_file.fp);
    if (process->out_file.fp) {
        fclose(process->out_file.fp);
    }
    free(process);
}