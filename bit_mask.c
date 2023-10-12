#include <stdint.h>
#include "./bit_mask.h"

const uint8_t op_code_field_bit_mask = 0b11111100; // 1111 1100
const bit_mask_op_code op_code_masks[] = {
    {0b10001000, "mov"},
};

// If source is specified by REG field.
// 0: REG field = source
// 1: REG field = destination
const uint8_t d_field_bit_mask = 0b00000010; // 0000 0010
 
// If the instruction is "wide"; that is, if it operates on byte data or word data.
// 0: byte
// 1: word
const uint8_t w_field_bit_mask = 0b00000001; // 0000 0001

// MOD bit
const uint8_t mod_field_bit_mask = 0b11000000;
// MOD masks
const uint8_t mod_mem_mode = 0b00000000;
const uint8_t mod_eight_bit_displacement = 0b01000000;
const uint8_t mod_sixteen_bit_displacement = 0b10000000;
const uint8_t mod_reg_mode = 0b11000000;

// REG bit
const uint8_t reg_field_bit_mask = 0b00111000;
// REG masks
// Non-wide
const bit_mask_register reg_non_wide_masks[]= {
    {0b00000000, "al"},
    {0b00001000, "cl"},
    {0b00010000, "dl"},
    {0b00011000, "bl"},
    {0b00100000, "ah"},
    {0b00101000, "ch"},
    {0b00110000, "dh"},
    {0b00111000, "bh"},
};
// Wide
const bit_mask_register reg_wide_masks[]= {
    {0b00000000, "ax"},
    {0b00001000, "cx"},
    {0b00010000, "dx"},
    {0b00011000, "bx"},
    {0b00100000, "sp"},
    {0b00101000, "bp"},
    {0b00110000, "si"},
    {0b00111000, "di"},
};
// RM bit
const uint8_t rm_field_bit_mask = 0b00000111;
// Non-wide
const bit_mask_register rm_non_wide_masks[]= {
    {0b00000000, "al"},
    {0b00000001, "cl"},
    {0b00000010, "dl"},
    {0b00000011, "bl"},
    {0b00000100, "ah"},
    {0b00000101, "ch"},
    {0b00000110, "dh"},
    {0b00000111, "bh"},
};
// Wide
const bit_mask_register rm_wide_masks[]= {
    {0b00000000, "ax"},
    {0b00000001, "cx"},
    {0b00000010, "dx"},
    {0b00000011, "bx"},
    {0b00000100, "sp"},
    {0b00000101, "bp"},
    {0b00000110, "si"},
    {0b00000111, "di"},
};
