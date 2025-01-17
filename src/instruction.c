//===----------------------------------------------------------------------===//
//
//                       === Libarch Disassembler ===
//
//  This  document  is the property of "Is This On?" It is considered to be
//  confidential and proprietary and may not be, in any form, reproduced or
//  transmitted, in whole or in part, without express permission of Is This
//  On?.
//
//  Copyright (C) 2023, Harry Moulton - Is This On? Holdings Ltd
//
//  Harry Moulton <me@h3adsh0tzz.com>
//
//===----------------------------------------------------------------------===//

#include <assert.h>

#include "instruction.h"
#include "decoder/branch.h"
#include "decoder/load-and-store.h"
#include "decoder/data-processing.h"
#include "decoder/data-processing-register.h"

/**
 *  \brief  Allocate / Reallocated memory in the operands array for a new element.
 * 
 *  \param      instr   Instruction to modify the operands array of.
 * 
 *  \return Result code.
*/
LIBARCH_PRIVATE LIBARCH_API
libarch_return_t 
_libarch_instruction_realloc_operand(instruction_t **instr) {
    /* Alloc / Realloc the operands array */
    operand_t *new_operands = NULL;

    if ((*instr)->operands_len == 0) {
        new_operands = malloc(sizeof(operand_t));
    } else {
        new_operands = realloc((*instr)->operands, sizeof(operand_t) * ((*instr)->operands_len + 1));
    }

    if (new_operands == NULL) {
        return LIBARCH_RETURN_FAILURE;
    }

    (*instr)->operands = new_operands;
    (*instr)->operands_len++;

    assert((*instr)->operands_len != 0);
    return LIBARCH_RETURN_SUCCESS;
}

///////////////////////////////////////////////////////////////////////////////

LIBARCH_API
instruction_t *
libarch_instruction_create (uint32_t opcode, uint64_t addr)
{
    instruction_t *instr = calloc (1, sizeof (instruction_t));
    instr->opcode = opcode;
    instr->addr = addr;

    /* default extra values */
    instr->cond = -1;
    instr->spec = -1;

    return instr;
}


LIBARCH_API
libarch_return_t
libarch_instruction_add_operand_immediate (instruction_t **instr, uint64_t bits, uint8_t type, uint32_t opts)
{
    _libarch_instruction_realloc_operand (instr);

    /* Add the new operand */
    (*instr)->operands[(*instr)->operands_len - 1].op_type = ARM64_OPERAND_TYPE_IMMEDIATE;
    (*instr)->operands[(*instr)->operands_len - 1].imm_bits = bits;
    (*instr)->operands[(*instr)->operands_len - 1].imm_type = type;
    (*instr)->operands[(*instr)->operands_len - 1].imm_opts = opts;

    /* Nullify unused prefix, suffix and suffix_extra when not used */
    (*instr)->operands[(*instr)->operands_len - 1].prefix = 0;
    (*instr)->operands[(*instr)->operands_len - 1].suffix = 0;
    (*instr)->operands[(*instr)->operands_len - 1].suffix_extra = 0;

    return LIBARCH_RETURN_SUCCESS;
}

LIBARCH_API
libarch_return_t
libarch_instruction_add_operand_immediate_with_fix_extra (instruction_t **instr, uint64_t bits, uint8_t type, char prefix, char suffix)
{
    _libarch_instruction_realloc_operand (instr);

    /* Add the new operand */
    (*instr)->operands[(*instr)->operands_len - 1].op_type = ARM64_OPERAND_TYPE_IMMEDIATE;
    (*instr)->operands[(*instr)->operands_len - 1].imm_bits = bits;
    (*instr)->operands[(*instr)->operands_len - 1].imm_type = type;
    (*instr)->operands[(*instr)->operands_len - 1].imm_opts |= ARM64_IMMEDIATE_OPERAND_OPT_PREFER_DECIMAL;

    /* Immediate prefix/suffix, e.g. [12] has a prefix '[' and suffix ']' */
    (*instr)->operands[(*instr)->operands_len - 1].prefix = prefix;
    (*instr)->operands[(*instr)->operands_len - 1].suffix = suffix;
    (*instr)->operands[(*instr)->operands_len - 1].suffix_extra = '!';

    return LIBARCH_RETURN_SUCCESS;
}

LIBARCH_API
libarch_return_t
libarch_instruction_add_operand_immediate_with_fix (instruction_t **instr, uint64_t bits, uint8_t type, char prefix, char suffix)
{
    _libarch_instruction_realloc_operand (instr);

    /* Add the new operand */
    (*instr)->operands[(*instr)->operands_len - 1].op_type = ARM64_OPERAND_TYPE_IMMEDIATE;
    (*instr)->operands[(*instr)->operands_len - 1].imm_bits = bits;
    (*instr)->operands[(*instr)->operands_len - 1].imm_type = type;
    (*instr)->operands[(*instr)->operands_len - 1].imm_opts = ARM64_IMMEDIATE_OPERAND_OPT_PREFER_DECIMAL;

    /* Immediate prefix/suffix, e.g. [12] has a prefix '[' and suffix ']' */
    (*instr)->operands[(*instr)->operands_len - 1].prefix = prefix;
    (*instr)->operands[(*instr)->operands_len - 1].suffix = suffix;
    (*instr)->operands[(*instr)->operands_len - 1].suffix_extra = 0;

    return LIBARCH_RETURN_SUCCESS;
}


LIBARCH_API
libarch_return_t
libarch_instruction_add_operand_shift (instruction_t **instr, uint32_t shift, uint8_t type)
{
    _libarch_instruction_realloc_operand (instr);

    /* Add the new operand */
    (*instr)->operands[(*instr)->operands_len - 1].op_type = ARM64_OPERAND_TYPE_SHIFT;
    (*instr)->operands[(*instr)->operands_len - 1].shift = shift;
    (*instr)->operands[(*instr)->operands_len - 1].shift_type = type;

    /* Nullify unused prefix, suffix and suffix_extra when not used */
    (*instr)->operands[(*instr)->operands_len - 1].prefix = 0;
    (*instr)->operands[(*instr)->operands_len - 1].suffix = 0;
    (*instr)->operands[(*instr)->operands_len - 1].suffix_extra = 0;

    return LIBARCH_RETURN_SUCCESS;
}


LIBARCH_API
libarch_return_t
libarch_instruction_add_operand_shift_with_fix (instruction_t **instr, uint32_t shift, uint8_t type, char prefix, char suffix)
{
    _libarch_instruction_realloc_operand (instr);

    /* Add the new operand */
    (*instr)->operands[(*instr)->operands_len - 1].op_type = ARM64_OPERAND_TYPE_SHIFT;
    (*instr)->operands[(*instr)->operands_len - 1].shift = shift;
    (*instr)->operands[(*instr)->operands_len - 1].shift_type = type;

    /* Shift prefix/suffix, e.g. [lsl #2] has a prefix '[' and suffix ']' */
    (*instr)->operands[(*instr)->operands_len - 1].prefix = prefix;
    (*instr)->operands[(*instr)->operands_len - 1].suffix = suffix;
    (*instr)->operands[(*instr)->operands_len - 1].suffix_extra = 0;

    return LIBARCH_RETURN_SUCCESS;
}


LIBARCH_API
libarch_return_t
libarch_instruction_add_operand_register (instruction_t **instr, arm64_reg_t a64reg, uint8_t size, uint8_t type, uint32_t opts)
{
    _libarch_instruction_realloc_operand (instr);

    if (a64reg == 31 && (size == 64 || size == 32))
        if (opts == ARM64_REGISTER_OPERAND_OPT_PREFER_ZERO) a64reg = (size == 64) ? ARM64_REG_XZR : ARM64_32_REG_WZR;
        else a64reg = (size == 64) ? ARM64_REG_SP : ARM64_32_REG_SP;

    /* Prevent overflows with vector registers */
    if (a64reg > 31 && size > 64) a64reg = (a64reg - 32);

    /* Add the new operand */
    (*instr)->operands[(*instr)->operands_len - 1].op_type = ARM64_OPERAND_TYPE_REGISTER;
    (*instr)->operands[(*instr)->operands_len - 1].reg = a64reg;
    (*instr)->operands[(*instr)->operands_len - 1].reg_size = size;
    (*instr)->operands[(*instr)->operands_len - 1].reg_type = type;

    (*instr)->operands[(*instr)->operands_len - 1].prefix = 0;
    (*instr)->operands[(*instr)->operands_len - 1].suffix = 0;
    (*instr)->operands[(*instr)->operands_len - 1].suffix_extra = 0;

    return LIBARCH_RETURN_SUCCESS;
}


LIBARCH_API
libarch_return_t
libarch_instruction_add_operand_register_with_fix (instruction_t **instr, arm64_reg_t a64reg, uint8_t size, uint8_t type, char prefix, char suffix)
{
    _libarch_instruction_realloc_operand (instr);

    /* Prevent overflows */
    if (a64reg > 31) a64reg = (a64reg - 32);

    /* Add the new operand */
    (*instr)->operands[(*instr)->operands_len - 1].op_type = ARM64_OPERAND_TYPE_REGISTER;
    (*instr)->operands[(*instr)->operands_len - 1].reg = a64reg;
    (*instr)->operands[(*instr)->operands_len - 1].reg_size = size;
    (*instr)->operands[(*instr)->operands_len - 1].reg_type = type;

    /* Register prefix/suffix, e.g. [x12] has a prefix '[' and suffix ']' */
    (*instr)->operands[(*instr)->operands_len - 1].prefix = prefix;
    (*instr)->operands[(*instr)->operands_len - 1].suffix = suffix;
    (*instr)->operands[(*instr)->operands_len - 1].suffix_extra = 0;

    return LIBARCH_RETURN_SUCCESS;
}


LIBARCH_API
libarch_return_t
libarch_instruction_add_operand_target (instruction_t **instr, char *target)
{
    _libarch_instruction_realloc_operand (instr);

    /* Add the new operand */
    (*instr)->operands[(*instr)->operands_len - 1].op_type = ARM64_OPERAND_TYPE_TARGET;
    (*instr)->operands[(*instr)->operands_len - 1].target = strdup (target);

    /* Nullify unused prefix, suffix and suffix_extra when not used */
    (*instr)->operands[(*instr)->operands_len - 1].prefix = 0;
    (*instr)->operands[(*instr)->operands_len - 1].suffix = 0;
    (*instr)->operands[(*instr)->operands_len - 1].suffix_extra = 0;

    return LIBARCH_RETURN_SUCCESS;
}


LIBARCH_API
libarch_return_t
libarch_instruction_add_operand_extra (instruction_t **instr, int type, int val)
{
    _libarch_instruction_realloc_operand (instr);

    /* Add the new operand */
    (*instr)->operands[(*instr)->operands_len - 1].op_type = type;
    (*instr)->operands[(*instr)->operands_len - 1].extra = val;

    /* Nullify unused prefix, suffix and suffix_extra when not used */
    (*instr)->operands[(*instr)->operands_len - 1].prefix = 0;
    (*instr)->operands[(*instr)->operands_len - 1].suffix = 0;
    (*instr)->operands[(*instr)->operands_len - 1].suffix_extra = 0;

    return LIBARCH_RETURN_SUCCESS;
}


LIBARCH_API
libarch_return_t
libarch_instruction_add_operand_extra_with_fix (instruction_t **instr, int type, int val, char prefix, char suffix)
{
    _libarch_instruction_realloc_operand (instr);

    /* Add the new operand */
    (*instr)->operands[(*instr)->operands_len - 1].op_type = type;
    (*instr)->operands[(*instr)->operands_len - 1].extra = val;

    /* Extra prefix/suffix, e.g. [x12] has a prefix '[' and suffix ']' */
    (*instr)->operands[(*instr)->operands_len - 1].prefix = prefix;
    (*instr)->operands[(*instr)->operands_len - 1].suffix = suffix;
    (*instr)->operands[(*instr)->operands_len - 1].suffix_extra = 0;
    

    return LIBARCH_RETURN_SUCCESS;
}


LIBARCH_API
libarch_return_t
libarch_instruction_add_field(instruction_t **instr, int field) {
    /* Alloc/Realloc fields array */
    uint64_t *new_fields = NULL;
    
    if ((*instr)->fields_len == 0) {
        new_fields = malloc(sizeof(uint64_t));
    } else {
        new_fields = realloc((*instr)->fields, sizeof(uint64_t) * ((*instr)->fields_len + 1));
    }
    
    if (new_fields == NULL) {
        return LIBARCH_RETURN_FAILURE;
    }
    
    (*instr)->fields = new_fields;
    (*instr)->fields[(*instr)->fields_len] = field;
    (*instr)->fields_len++;

    return LIBARCH_RETURN_SUCCESS;
}


LIBARCH_API
decode_status_t
libarch_disass (instruction_t **instr)
{
    /**
     *  ** AArch64 Instruction Set Encoding **
     * 
     *  Every instruction has some common bits to identify the Decode Group,
     *  these being op0 and op1.
     * 
     *   - op0[31]
     *      Not really relevant here. Section C4.1 of the Arm Reference Manual
     *      only really shows that bit 31 is `0` if the Decode Group is "Reserved".
     * 
     *   - op1[25:28]
     *      This is the important bit. These four bits tell us the decode group,
     *      essentially the type of instruction we're dealing with.
     * 
     */
    unsigned op0 = select_bits ((*instr)->opcode, 31, 31);
    unsigned op1 = select_bits ((*instr)->opcode, 25, 28);

    if (op0 == 0 && op1 == 0) {
        // Reserved
        (*instr)->group = ARM64_DECODE_GROUP_RESERVED;
    } else if (op0 == 1 && op1 == 0) {
        // SME
    } else if (op1 == 2) {
        // SVE
    } else if ((op1 >> 1) == 4) {
        // Data Processing - Immediate
        if (disass_data_processing_instruction (*instr) == LIBARCH_DECODE_STATUS_SUCCESS)
            (*instr)->group = ARM64_DECODE_GROUP_DATA_PROCESS_IMMEDIATE;
        
    } else if ((op1 >> 1) == 5) {
        // Branch, Exception, System Register
        if (disass_branch_exception_sys_instruction (*instr) == LIBARCH_DECODE_STATUS_SUCCESS)
            (*instr)->group = ARM64_DECODE_GROUP_BRANCH_EXCEPTION_SYSREG;
        
    } else if ((op1 & ~10) == 4) {
        // Load and Store
        if (disass_load_and_store_instruction (*instr) == LIBARCH_DECODE_STATUS_SUCCESS)
            (*instr)->group = ARM64_DECODE_GROUP_LOAD_AND_STORE;
        
    } else if ((op1 & ~8) == 5) {
        // Data Processing - Register
        if (disass_data_processing_register_instruction (*instr) == LIBARCH_DECODE_STATUS_SUCCESS)
            (*instr)->group = ARM64_DECODE_GROUP_DATA_PROCESS_REGISTER;
    } else if ((op1 & ~8) == 7) {
        // Data Processing - Floating
        (*instr)->group = ARM64_DECODE_GROUP_DATA_PROCESS_FLOATING;
    } else {
        // Unknown
        (*instr)->group = ARM64_DECODE_GROUP_UNKNOWN;
    }

    return ((*instr)->group != ARM64_DECODE_GROUP_UNKNOWN) ? LIBARCH_DECODE_STATUS_SUCCESS : LIBARCH_DECODE_STATUS_SOFT_FAIL;
}