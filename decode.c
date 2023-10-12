#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "./data.h"
#include "./bit_mask.h"

void test_print_binary(uint8_t byte) {
    for (int i = 7; i >= 0; i--) {
        if ((byte >> i) & 1) {
            printf("1");
        } else {
            printf("0");
        }
    }
}

uint8_t get_bit(uint8_t byte, uint8_t shift) {
    uint8_t mask =  1 << shift;
    uint8_t masked = byte & mask;
    uint8_t thebit = masked >> shift;
    return thebit;
}

// TODO: Remarkably poor naming here.
// Checks which bits are set in the field identified by the field_mask,
// and then these set bits are compared to a bit mask.
bool bit_mask_set(uint8_t byte, uint8_t bit_mask, uint8_t field_mask) {
    uint8_t set_bits = byte & field_mask;
    if (set_bits == bit_mask) {
        return true;
    }
    return false;
}

size_t extra_bytes(input* instrs) {
    size_t idx = (instrs->current)+MOD_BYTE_IDX;
    if(bit_mask_set(instrs->bytes[idx], mod_eight_bit_displacement, mod_field_bit_mask)) {
        return 1;
    } else if(bit_mask_set(instrs->bytes[idx], mod_sixteen_bit_displacement, mod_field_bit_mask)) {
        return 2;
    } 
    // missing special case for MOD==00 and R/M==110
    return 0;
}

// number of bytes used in instruction
size_t get_instr_len(input* instrs) {
    size_t idx = (instrs->current)+MOD_BYTE_IDX;
    uint8_t bit = bit_mask_set(instrs->bytes[idx], mod_field_bit_mask, mod_field_bit_mask);
    if (bit == 1) {
        return 4;
    }
    return 2;
}

bool w_is_set(input* instrs) {
    size_t byte_idx = W_BYTE_IDX;
    uint8_t byte = instrs->bytes[instrs->current+byte_idx];
    return bit_mask_set(byte, w_field_bit_mask, w_field_bit_mask);
}

bool reg_is_dst(input* instrs) {
    size_t byte_idx = D_BYTE_IDX;
    uint8_t byte = instrs->bytes[instrs->current+byte_idx];
    return bit_mask_set(byte, d_field_bit_mask, d_field_bit_mask);
}


char* decode_register_from_reg(input* instrs, bool w_set) {
    size_t byte_idx = REG_BYTE_IDX;
    const uint8_t src = instrs->bytes[instrs->current+byte_idx] & reg_field_bit_mask;
    if (w_set) {
        size_t len = sizeof(reg_wide_masks) / sizeof(reg_wide_masks[0]);
        for (size_t j = 0; j < len; j++) {
            if (bit_mask_set(src, reg_wide_masks[j].mask, reg_field_bit_mask)) {
                return reg_wide_masks[j].reg;
            }
        }
    } else {
        size_t len = sizeof(reg_non_wide_masks) / sizeof(reg_non_wide_masks[0]);
        for (size_t j = 0; j < len; j++) {
            if (bit_mask_set(src, reg_non_wide_masks[j].mask, reg_field_bit_mask)) {
                return reg_non_wide_masks[j].reg;
            }
        }
    }
    return "";
}

char* decode_register_from_rm(input* instrs, bool w_set) {
    size_t byte_idx = RM_BYTE_IDX;
    const uint8_t src = instrs->bytes[instrs->current+byte_idx] & rm_field_bit_mask;
    if (w_set) {
        size_t len = sizeof(rm_wide_masks) / sizeof(rm_wide_masks[0]);
        for (size_t j = 0; j < len; j++) {
            if (bit_mask_set(src, rm_wide_masks[j].mask, rm_field_bit_mask)) {
                return rm_wide_masks[j].reg;
            }
        }
    } else {
        size_t len = sizeof(rm_non_wide_masks) / sizeof(rm_non_wide_masks[0]);
        for (size_t j = 0; j < len; j++) {
            if (bit_mask_set(src, rm_non_wide_masks[j].mask, rm_field_bit_mask)) {
                return rm_non_wide_masks[j].reg;
            }
        }
    }
    return "";
}

char* decode_op_code(input* instrs) {
    size_t byte_idx = OP_CODE_BYTE_IDX;
    const uint8_t op_code = instrs->bytes[instrs->current+byte_idx] & op_code_field_bit_mask;
    size_t len = sizeof(op_code_masks) / sizeof(op_code_masks[0]);
    for (size_t j = 0; j < len; j++) {
        if (bit_mask_set(op_code, op_code_masks[j].mask, op_code_field_bit_mask)) {
            return op_code_masks[j].op_code;
        }
    }
    return "";
}

char* decode_dst(input* instrs, bool reg_dst, bool w_set) {
    if (reg_dst) {
        return decode_register_from_reg(instrs, w_set);
    } else {
        return decode_register_from_rm(instrs, w_set);
    }
    return "";
}

char* decode_src(input* instrs, bool reg_dst, bool w_set) {
    if (!reg_dst) {
        return decode_register_from_reg(instrs, w_set);
    } else {
        return decode_register_from_rm(instrs, w_set);
    }
    return "";
}

char* decode_instruction(input* instrs) {
    char* decoded_instr = (char*)malloc(DECODED_INSTRUCTIONS_CAP);
    size_t instr_len = get_instr_len(instrs);
    instrs->next = instrs->current + instr_len;
    bool w_set = w_is_set(instrs);
    bool reg_dst = reg_is_dst(instrs);

    char* op_code = decode_op_code(instrs);
    char* dst = decode_dst(instrs, reg_dst, w_set);
    char* src = decode_src(instrs, reg_dst, w_set);
    printf("\n\nDECODED INSTRCUTION:");
    printf("\n%s %s %s", op_code, dst, src);

    return decoded_instr;
}



char* decode_instructions(input* instrs) {
    char* decoded_instrs = (char*)malloc(DECODED_INSTRUCTIONS_CAP);
    size_t next = instrs->current + 2 + extra_bytes(instrs);
    while (next <= instrs->len) {
        decode_instruction(instrs);
        instrs->current = next;
        next = instrs->current + 2 + extra_bytes(instrs);
    }
    return decoded_instrs;
}

