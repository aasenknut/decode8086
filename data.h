#ifndef data_h_
#define data_h_

#include <stdlib.h>
#define INPUT_CAP 16384
#define DECODED_INSTRUCTIONS_CAP 16384
#define DECODED_INSTRUCTION_CAP 2048
#define INSTRUCTION_BYTE_CAP 6

typedef struct {
    uint8_t bytes[INPUT_CAP];
    size_t current;
    size_t next;
    size_t len;
} input;

input* read_file(char* f_path);

#endif
