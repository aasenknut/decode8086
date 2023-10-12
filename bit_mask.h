#ifndef bit_mask_h_
#define bit_mask_h_

#include <stdint.h>
#include <stdbool.h>

// --------
// 1st byte
// --------

// Masks for OP codes
typedef struct {
    uint8_t mask;
    char* op_code;
} bit_mask_op_code;

// OP Code
#define OP_CODE_BYTE_IDX 0;
extern const uint8_t op_code_field_bit_mask;
extern const bit_mask_op_code op_code_masks[1];


// D 
#define D_BYTE_IDX 0;
// If D==0: REG is not dst.
// If D==1: REG is dst.
extern const uint8_t d_field_bit_mask;

// W
#define W_BYTE_IDX 0;
extern const uint8_t w_field_bit_mask;

// --------
// 2nd byte
// --------

// MOD field
#define MOD_BYTE_IDX 1;
extern const uint8_t mod_field_bit_mask;
extern const uint8_t mod_mem_mode;
extern const uint8_t mod_eight_bit_displacement;
extern const uint8_t mod_sixteen_bit_displacement;
extern const uint8_t mod_reg_mode;

// Masks for registers in, e.g.,
// mov ax, bx
typedef struct {
    uint8_t mask;
    char* reg;
} bit_mask_register;

// REG field
#define REG_BYTE_IDX 1;
extern const uint8_t reg_field_bit_mask;

extern const bit_mask_register reg_non_wide_masks[8];
extern const bit_mask_register reg_wide_masks[8];


// RM field
#define RM_BYTE_IDX 1;
extern const uint8_t rm_field_bit_mask;

extern const bit_mask_register rm_non_wide_masks[8];
extern const bit_mask_register rm_wide_masks[8];

// 3rd byte
#define DL_BYTE_IDX 2;

// 4th byte
#define DH_BYTE_IDX 3;


#endif
