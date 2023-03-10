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

#ifndef __LIBARCH_INSTRUCTION_H__
#define __LIBARCH_INSTRUCTION_H__

#include <stdio.h>

#include "libarch.h"
#include "register.h"
#include "utils.h"

#include "arm64/arm64-instructions.h"
#include "arm64/arm64-registers.h"


#define ARM64_NONE                              0

/* Register type flags */
#define ARM64_REGISTER_TYPE_GENERAL             1
#define ARM64_REGISTER_TYPE_FLOATING_POINT      2
#define ARM64_REGISTER_TYPE_SYSTEM              3
#define ARM64_REGISTER_TYPE_ZERO                4

/* Shift type flags */
#define ARM64_SHIFT_TYPE_LSL                    4
#define ARM64_SHIFT_TYPE_LSR                    5
#define ARM64_SHIFT_TYPE_ASR                    6
#define ARM64_SHIFT_TYPE_ROR                    7
#define ARM64_SHIFT_TYPE_ROR                    8
#define ARM64_SHIFT_TYPE_MSL                    9

/* Immediate type flags */
#define ARM64_IMMEDIATE_TYPE_INT                10
#define ARM64_IMMEDIATE_TYPE_UINT               11
#define ARM64_IMMEDIATE_TYPE_LONG               12
#define ARM64_IMMEDIATE_TYPE_ULONG              13
#define ARM64_IMMEDIATE_TYPE_FLOAT              14

/* Operand type flags */
#define ARM64_OPERAND_TYPE_REGISTER             15
#define ARM64_OPERAND_TYPE_SHIFT                16
#define ARM64_OPERAND_TYPE_IMMEDIATE            17

typedef struct operand_t
{
    /* Operand type */
    uint8_t         op_type;

    /* op_type == ARM64_OPERAND_TYPE_REGISTER */
    arm64_reg_t     reg;
    uint8_t         reg_size;
    uint8_t         reg_type;

    /* op_type == ARM64_OPERAND_TYPE_SHIFT */
    uint32_t        shift;
    uint8_t         shift_type;

    /* op_type == ARM64_OPERAND_TYPE_IMMEDIATE */
    uint64_t        imm_bits; 
    uint8_t         imm_type;

} operand_t;

typedef struct instruction_t
{
    /* Fully decoded, parsed instruction */
    char               *parsed;
    uint32_t            opcode;
    uint64_t            addr;

    /* Decode Group and Instruction type */
    uint8_t             group;
    arm64_instr_t       type;

    /* Operands */
    operand_t          *operands;
    uint32_t            operands_len;

    /* Fields, left to right */
    uint64_t           *fields;
    uint32_t            fields_len;

        
} instruction_t;

extern libarch_return_t
libarch_instruction_add_operand_immediate (instruction_t **instr, uint64_t bits, uint8_t type);

extern libarch_return_t
libarch_instruction_add_operand_shift (instruction_t **instr, uint32_t shift, uint8_t type);

extern libarch_return_t
libarch_instruction_add_operand_register (instruction_t **instr, arm64_reg_t a64reg, uint8_t size, uint8_t type);


extern libarch_return_t
libarch_instruction_add_field (instruction_t **instr, int field);


extern instruction_t *
libarch_instruction_create (uint32_t opcode, uint64_t addr);

extern libarch_return_t
libarch_disass (instruction_t **instr);


#endif /* __libarch_disassembler_h__ */
