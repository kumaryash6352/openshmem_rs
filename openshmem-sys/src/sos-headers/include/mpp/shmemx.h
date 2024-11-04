/* -*- C -*-
 *
 * Copyright 2011 Sandia Corporation. Under the terms of Contract
 * DE-AC04-94AL85000 with Sandia Corporation, the U.S.  Government
 * retains certain rights in this software.
 *
 * Copyright (c) 2016 Intel Corporation. All rights reserved.
 * This software is available to you under the BSD license.
 *
 * This file is part of the Sandia OpenSHMEM software package. For license
 * information, see the LICENSE file in the top level directory of the
 * distribution.
 *
 */



#ifndef SHMEMX_H
#define SHMEMX_H

#include <stddef.h>
#include <stdint.h>
#include <shmem-def.h>
#include <shmemx-def.h>

#ifdef __cplusplus
extern "C" {
#endif


#ifndef SHMEM_FUNCTION_ATTRIBUTES
#  if SHMEM_HAVE_ATTRIBUTE_VISIBILITY == 1
#     define SHMEM_FUNCTION_ATTRIBUTES __attribute__((visibility("default")))
#  else
#     define SHMEM_FUNCTION_ATTRIBUTES
#  endif
#endif

SHMEM_FUNCTION_ATTRIBUTES double shmemx_wtime(void);
SHMEM_FUNCTION_ATTRIBUTES char* shmemx_nodename(void);

SHMEM_FUNCTION_ATTRIBUTES void shmemx_getmem_ct(shmemx_ct_t ct, void *target, const void *source, size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmemx_putmem_ct(shmemx_ct_t ct, void *target, const void *source, size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmemx_ct_create(shmemx_ct_t *ct);
SHMEM_FUNCTION_ATTRIBUTES void shmemx_ct_free(shmemx_ct_t *ct);
SHMEM_FUNCTION_ATTRIBUTES long shmemx_ct_get(shmemx_ct_t ct);
SHMEM_FUNCTION_ATTRIBUTES void shmemx_ct_set(shmemx_ct_t ct, long value);
SHMEM_FUNCTION_ATTRIBUTES void shmemx_ct_wait(shmemx_ct_t ct, long wait_for);

SHMEM_FUNCTION_ATTRIBUTES void shmemx_register_gettid(uint64_t (*gettid_fn)(void));

/* Performance Counter Query Routines */
SHMEM_FUNCTION_ATTRIBUTES void shmemx_pcntr_get_issued_write(shmem_ctx_t ctx, uint64_t *cntr_value);
SHMEM_FUNCTION_ATTRIBUTES void shmemx_pcntr_get_issued_read(shmem_ctx_t ctx, uint64_t *cntr_value);
SHMEM_FUNCTION_ATTRIBUTES void shmemx_pcntr_get_completed_write(shmem_ctx_t ctx, uint64_t *cntr_value);
SHMEM_FUNCTION_ATTRIBUTES void shmemx_pcntr_get_completed_read(shmem_ctx_t ctx, uint64_t *cntr_value);
SHMEM_FUNCTION_ATTRIBUTES void shmemx_pcntr_get_completed_target(uint64_t *cntr_value);
SHMEM_FUNCTION_ATTRIBUTES void shmemx_pcntr_get_all(shmem_ctx_t ctx, shmemx_pcntr_t *pcntr);

/* Option to enable bounce buffering on a given context */
#define SHMEMX_CTX_BOUNCE_BUFFER  (1l<<31)

/* SHMEMX constant(s) are included in MAX_HINTS value in shmem-def.h */
#define SHMEMX_MALLOC_NO_BARRIER (1l<<2)

/* C++ overloaded declarations */
#ifdef __cplusplus
} /* extern "C" */

/* C11 Generic Macros */
#elif (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L && !defined(SHMEM_INTERNAL_INCLUDE))

#endif /* C11 */

#endif /* SHMEMX_H */
