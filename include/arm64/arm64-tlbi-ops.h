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

#ifndef __LIBARCH_ARM64_TLBI_OPS_H__
#define __LIBARCH_ARM64_TLBI_OPS_H__

#include <stdlib.h>
#include <stdint.h>
#include "libarch.h"

LIBARCH_API int
get_tlbi (unsigned op1, unsigned CRn, unsigned CRm, unsigned op2);

/**
 *  \brief  AArch64 TLBI Operation names, indexed by the `arm64_tlbi_op_t` values.
 *  
 */
static const char *A64_TLBI_OPS_STR[] =
{
    "vmalle1is", "vae1is", "aside1is", "vaae1is", "vale1is", "vaale1is",
    "vmalle1", "vae1", "aside1", "vaae1", "vale1", "vaale1", "ipas2e1is", 
    "ipas2le1is", "alle2is", "vae2is", "alle1is", "vale2is", "vmalls12e1is", 
    "ipas2e1", "ipas2le1", "alle2", "vae2", "alle1", "vale2", "vmalls12e1", 
    "alle3is", "vae3is", "vale3is", "alle3", "vae3", "vale3", "vmalle1os",
    "vae1os", "aside1os", "vaae1os", "vale1os", "vaale1os", "alle2os", "vae2os",
    "alle1os", "vale2os", "vmalls12e1os", "ipas2e1os", "ipas2le1os", "alle3os", 
    "vae3os", "vale3os", "rvae1is", "rvaae1is", "rvale1is", "rvaale1is", "rvae1os",
    "rvaae1os", "rvale1os", "rvaale1os", "rvae1", "rvaae1", "rvale1", "rvaale1",
    "ripas2e1is", "ripas2le1is", "rvae2is", "rvale2is", "ripas2e1", "ripas2e1os", 
    "ripas2le1", "ripas2le1os", "rvae2os", "rvale2os", "rvae2", "rvale2", "rvae3is",
    "rvale3is", "rvae3os", "rvale3os", "rvae3", "rvale3", "vmalle1osnxs", "vae1osnxs",
    "aside1osnxs", "vaae1osnxs", "vale1osnxs", "vaale1osnxs", "rvae1isnxs", "rvaae1isnxs",
    "rvale1isnxs","rvaale1isnxs","vmalle1isnxs","vae1isnxs","aside1isnxs","vaae1isnxs",
    "vale1isnxs", "vaale1isnxs", "rvae1osnxs", "rvaae1osnxs", "rvale1osnxs", "rvaale1osnxs",
    "rvae1nxs", "rvaae1nxs", "rvale1nxs", "rvaale1nxs", "vmalle1nxs", "vae1nxs",
    "aside1nxs", "vaae1nxs", "vale1nxs", "vaale1nxs", "ipas2e1isnxs", "ripas2e1isnxs",
    "ipas2le1isnxs", "ripas2le1isnxs", "alle2osnxs", "vae2osnxs", "alle1osnxs", "vale2osnxs",
    "vmalls12e1osnxs", "rvae2isnxs", "rvale2isnxs", "alle2isnxs", "vae2isnxs", "alle1isnxs",
    "vale2isnxs", "vmalls12e1isnxs", "ipas2e1osnxs", "ipas2e1nxs", "ripas2e1nxs", "ripas2e1osnxs",
    "ipas2le1osnxs", "ipas2le1nxs", "ripas2le1nxs", "ripas2le1osnxs", "rvae2osnxs",
    "rvale2osnxs", "rvae2nxs", "rvale2nxs", "alle2nxs", "vae2nxs", "alle1nxs",
    "vale2nxs", "vmalls12e1nxs", "alle3osnxs", "vae3osnxs", "vale3osnxs", "rvae3isnxs",
    "rvale3isnxs", "alle3isnxs", "vae3isnxs", "vale3isnxs", "rvae3osnxs", "rvale3osnxs",
    "rvae3nxs", "rvale3nxs", "alle3nxs", "vae3nxs", "vale3nxs", "unknown",
};

/**
 *  \brief  Length of the A64_TLBI_OPS_STR array containing all the supported TLBI
 *          Operations.
 * 
*/
static uint64_t A64_TLBI_OPS_STR_LEN = sizeof (A64_TLBI_OPS_STR) / sizeof (*A64_TLBI_OPS_STR);

/**
 *  \brief  AArch64 TLBI Operation values, with corresponding strings in the A64_TLBI_OPS_STR
 *          array.
 *  
 */
typedef enum arm64_tlbi_op_t
{
    ARM64_TLBI_OP_VMALLE1IS = 0,
    ARM64_TLBI_OP_VAE1IS,
    ARM64_TLBI_OP_ASIDE1IS,
    ARM64_TLBI_OP_VAAE1IS,
    ARM64_TLBI_OP_VALE1IS,
    ARM64_TLBI_OP_VAALE1IS,
    ARM64_TLBI_OP_VMALLE1,
    ARM64_TLBI_OP_VAE1,
    ARM64_TLBI_OP_ASIDE1,
    ARM64_TLBI_OP_VAAE1,
    ARM64_TLBI_OP_VALE1,
    ARM64_TLBI_OP_VAALE1,
    ARM64_TLBI_OP_IPAS2E1IS,
    ARM64_TLBI_OP_IPAS2LE1IS,
    ARM64_TLBI_OP_ALLE2IS,
    ARM64_TLBI_OP_VAE2IS,

    ARM64_TLBI_OP_ALLE1IS,
    ARM64_TLBI_OP_VALE2IS,
    ARM64_TLBI_OP_VMALLS12E1IS,
    ARM64_TLBI_OP_IPAS2E1,
    ARM64_TLBI_OP_IPAS2LE1,
    ARM64_TLBI_OP_ALLE2,
    ARM64_TLBI_OP_VAE2,
    ARM64_TLBI_OP_ALLE1,
    ARM64_TLBI_OP_VALE2,
    ARM64_TLBI_OP_VMALLS12E1,
    ARM64_TLBI_OP_ALLE3IS,
    ARM64_TLBI_OP_VAE3IS,
    ARM64_TLBI_OP_VALE3IS,
    ARM64_TLBI_OP_ALLE3,
    ARM64_TLBI_OP_VAE3,
    ARM64_TLBI_OP_VALE3,
    ARM64_TLBI_OP_VMALLE1OS,
    ARM64_TLBI_OP_VAE1OS,
    ARM64_TLBI_OP_ASIDE1OS,
    ARM64_TLBI_OP_VAAE1OS,
    ARM64_TLBI_OP_VALE1OS,
    ARM64_TLBI_OP_VAALE1OS,
    ARM64_TLBI_OP_ALLE2OS,
    ARM64_TLBI_OP_VAE2OS,
    ARM64_TLBI_OP_ALLE1OS,
    ARM64_TLBI_OP_VALE2OS,
    ARM64_TLBI_OP_VMALLS12E1OS,
    ARM64_TLBI_OP_IPAS2E1OS,
    ARM64_TLBI_OP_IPAS2LE1OS,
    ARM64_TLBI_OP_ALLE3OS,
    ARM64_TLBI_OP_VAE3OS,
    ARM64_TLBI_OP_VALE3OS,
    ARM64_TLBI_OP_RVAE1IS,
    ARM64_TLBI_OP_RVAAE1IS,
    ARM64_TLBI_OP_RVALE1IS,
    ARM64_TLBI_OP_RVAALE1IS,
    ARM64_TLBI_OP_RVAE1OS,
    ARM64_TLBI_OP_RVAAE1OS,
    ARM64_TLBI_OP_RVALE1OS,
    ARM64_TLBI_OP_RVAALE1OS,
    ARM64_TLBI_OP_RVAE1,
    ARM64_TLBI_OP_RVAAE1,

    ARM64_TLBI_OP_RVALE1,
    ARM64_TLBI_OP_RVAALE1,
    ARM64_TLBI_OP_RIPAS2E1IS,
    ARM64_TLBI_OP_RIPAS2LE1IS,
    ARM64_TLBI_OP_RVAE2IS,
    ARM64_TLBI_OP_RVALE2IS,
    ARM64_TLBI_OP_RIPAS2E1,
    ARM64_TLBI_OP_RIPAS2E1OS,
    ARM64_TLBI_OP_RIPAS2LE1,
    ARM64_TLBI_OP_RIPAS2LE1OS,
    ARM64_TLBI_OP_RVAE2OS,
    ARM64_TLBI_OP_RVALE2OS,
    ARM64_TLBI_OP_RVAE2,
    ARM64_TLBI_OP_RVALE2,
    ARM64_TLBI_OP_RVAE3IS,
    ARM64_TLBI_OP_RVALE3IS,
    ARM64_TLBI_OP_RVAE3OS,
    ARM64_TLBI_OP_RVALE3OS,
    ARM64_TLBI_OP_RVAE3,
    ARM64_TLBI_OP_RVALE3,
    ARM64_TLBI_OP_VMALLE1OSNXS,
    ARM64_TLBI_OP_VAE1OSNXS,
    ARM64_TLBI_OP_ASIDE1OSNXS,
    ARM64_TLBI_OP_VAAE1OSNXS,
    ARM64_TLBI_OP_VALE1OSNXS,
    ARM64_TLBI_OP_VAALE1OSNXS,
    ARM64_TLBI_OP_RVAE1ISNXS,
    ARM64_TLBI_OP_RVAAE1ISNXS,
    ARM64_TLBI_OP_RVALE1ISNXS,
    ARM64_TLBI_OP_RVAALE1ISNXS,
    ARM64_TLBI_OP_VMALLE1ISNXS,
    ARM64_TLBI_OP_VAE1ISNXS,
    ARM64_TLBI_OP_ASIDE1ISNXS,
    ARM64_TLBI_OP_VAAE1ISNXS,
    ARM64_TLBI_OP_VALE1ISNXS,
    ARM64_TLBI_OP_VAALE1ISNXS,
    ARM64_TLBI_OP_RVAE1OSNXS,
    ARM64_TLBI_OP_RVAAE1OSNXS,
    ARM64_TLBI_OP_RVALE1OSNXS,
    ARM64_TLBI_OP_RVAALE1OSNXS,
    ARM64_TLBI_OP_RVAE1NXS,
    ARM64_TLBI_OP_RVAAE1NXS,
    ARM64_TLBI_OP_RVALE1NXS,

    ARM64_TLBI_OP_RVAALE1NXS,
    ARM64_TLBI_OP_VMALLE1NXS,
    ARM64_TLBI_OP_VAE1NXS,
    ARM64_TLBI_OP_ASIDE1NXS,
    ARM64_TLBI_OP_VAAE1NXS,
    ARM64_TLBI_OP_VALE1NXS,
    ARM64_TLBI_OP_VAALE1NXS,
    ARM64_TLBI_OP_IPAS2E1ISNXS,
    ARM64_TLBI_OP_RIPAS2E1ISNXS,
    ARM64_TLBI_OP_IPAS2LE1ISNXS,
    ARM64_TLBI_OP_RIPAS2LE1ISNXS,
    ARM64_TLBI_OP_ALLE2OSNXS,
    ARM64_TLBI_OP_VAE2OSNXS,
    ARM64_TLBI_OP_ALLE1OSNXS,
    ARM64_TLBI_OP_VALE2OSNXS,
    ARM64_TLBI_OP_VMALLS12E1OSNXS,
    ARM64_TLBI_OP_RVAE2ISNXS,
    ARM64_TLBI_OP_RVALE2ISNXS,
    ARM64_TLBI_OP_ALLE2ISNXS,
    ARM64_TLBI_OP_VAE2ISNXS,
    ARM64_TLBI_OP_ALLE1ISNXS,
    ARM64_TLBI_OP_VALE2ISNXS,
    ARM64_TLBI_OP_VMALLS12E1ISNXS,
    ARM64_TLBI_OP_IPAS2E1OSNXS,
    ARM64_TLBI_OP_IPAS2E1NXS,
    ARM64_TLBI_OP_RIPAS2E1NXS,
    ARM64_TLBI_OP_RIPAS2E1OSNXS,
    ARM64_TLBI_OP_IPAS2LE1OSNXS,
    ARM64_TLBI_OP_IPAS2LE1NXS,
    ARM64_TLBI_OP_RIPAS2LE1NXS,
    ARM64_TLBI_OP_RIPAS2LE1OSNXS,
    ARM64_TLBI_OP_RVAE2OSNXS,
    ARM64_TLBI_OP_RVALE2OSNXS,
    ARM64_TLBI_OP_RVAE2NXS,
    ARM64_TLBI_OP_RVALE2NXS,
    ARM64_TLBI_OP_ALLE2NXS,
    ARM64_TLBI_OP_VAE2NXS,
    ARM64_TLBI_OP_ALLE1NXS,
    ARM64_TLBI_OP_VALE2NXS,
    ARM64_TLBI_OP_VMALLS12E1NXS,
    ARM64_TLBI_OP_ALLE3OSNXS,
    ARM64_TLBI_OP_VAE3OSNXS,
    ARM64_TLBI_OP_VALE3OSNXS,
    ARM64_TLBI_OP_RVAE3ISNXS,

    ARM64_TLBI_OP_RVALE3ISNXS,
    ARM64_TLBI_OP_ALLE3ISNXS,
    ARM64_TLBI_OP_VAE3ISNXS,
    ARM64_TLBI_OP_VALE3ISNXS,
    ARM64_TLBI_OP_RVAE3OSNXS,
    ARM64_TLBI_OP_RVALE3OSNXS,
    ARM64_TLBI_OP_RVAE3NXS,
    ARM64_TLBI_OP_RVALE3NXS,
    ARM64_TLBI_OP_ALLE3NXS,
    ARM64_TLBI_OP_VAE3NXS,
    ARM64_TLBI_OP_VALE3NXS,

    ARM64_TLBI_OP_UNKNOWN,
} arm64_tlbi_op_t;

#endif /* __libarch_arm64_tlbi_ops_h__ */