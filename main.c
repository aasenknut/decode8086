#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "./data.h"
#include "./decode.h"
#include "./bit_mask.h"

void print_binary(uint8_t byte) {
    for (int i = 7; i >= 0; i--) {
        if ((byte >> i) & 1) {
            printf("1");
        } else {
            printf("0");
        }
    }
}

int main() {

    input* bytes = read_file("./input/assembled_mov_instructions");

    for (size_t j = 0; j < bytes->len; j++) {
        printf("\nByte #%zu:\n", j);
        print_binary(bytes->bytes[j]);
    }

    printf("\n\n\nSTARTING: DECODE INSTRUCTIONS\n");
    decode_instructions(bytes);
}
