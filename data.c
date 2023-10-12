#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "./data.h"

input* read_file(char* f_path) {
    FILE *f = fopen(f_path, "r");
    if (f == NULL) {
        perror("err when reading file");
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    long f_size = ftell(f);
    rewind(f);
    if (f_size <= 0){
        fclose(f);
        perror("file_size <= 0");
        return NULL;
    }
    size_t bytes_to_read = (size_t)(f_size < INPUT_CAP ? f_size : INPUT_CAP);
    if (bytes_to_read == INPUT_CAP) {
        printf("\nRead until the input cap. Probably don't have all the bytes.\n");
    }

    input* data = (input*)malloc(sizeof(input));
    if (data == NULL) {
        fclose(f);
        perror("error allocating mem for input");
        return NULL;
    }

    size_t len_read = fread(data, sizeof(uint8_t), bytes_to_read, f);
    data->len = len_read;

    if (ferror(f)) {
        perror("");
    } else if (feof(f)) {
        printf("\nReached end of input file.\n");
    }

    // Initialise values
    data->current = 0;
    data->next = 0;

    return data;
}
