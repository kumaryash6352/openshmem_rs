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

/*
 * This is a generated file, do not edit directly.
 */



#ifndef SHMEM_H
#define SHMEM_H

#include <stddef.h>
#include <stdint.h>
#include <shmem-def.h>

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

#ifndef SHMEM_ATTRIBUTE_DEPRECATED
#   if SHMEM_HAVE_ATTRIBUTE_DEPRECATED == 1
#       define SHMEM_ATTRIBUTE_DEPRECATED __attribute__((deprecated))
#   else
#       define SHMEM_ATTRIBUTE_DEPRECATED
#   endif
#endif

/* Library Setup, Exit, and Query Routines */
SHMEM_FUNCTION_ATTRIBUTES void shmem_init(void);
SHMEM_FUNCTION_ATTRIBUTES int shmem_init_thread(int requested, int *provided);
SHMEM_FUNCTION_ATTRIBUTES void shmem_query_thread(int *provided);
SHMEM_FUNCTION_ATTRIBUTES void shmem_finalize(void);
SHMEM_FUNCTION_ATTRIBUTES int shmem_n_pes(void);
SHMEM_FUNCTION_ATTRIBUTES int shmem_my_pe(void);
#ifdef __cplusplus
#  if __cplusplus >= 201103L
[[noreturn]] void shmem_global_exit(int status) SHMEM_FUNCTION_ATTRIBUTES;
#  else
SHMEM_FUNCTION_ATTRIBUTES void shmem_global_exit(int status);
#  endif
#elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
SHMEM_FUNCTION_ATTRIBUTES _Noreturn void shmem_global_exit(int status);
#else
SHMEM_FUNCTION_ATTRIBUTES void shmem_global_exit(int status);
#endif

SHMEM_FUNCTION_ATTRIBUTES int shmem_pe_accessible(int pe);
SHMEM_FUNCTION_ATTRIBUTES int shmem_addr_accessible(const void *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES void *shmem_ptr(const void *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void *shmem_team_ptr(shmem_team_t team, const void *target, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_info_get_version(int *major, int *minor);
SHMEM_FUNCTION_ATTRIBUTES void shmem_info_get_name(char *name);

/* Memory Management Routines */
SHMEM_FUNCTION_ATTRIBUTES void *shmem_malloc(size_t size);
SHMEM_FUNCTION_ATTRIBUTES void *shmem_calloc(size_t count, size_t size);
SHMEM_FUNCTION_ATTRIBUTES void *shmem_align(size_t alignment, size_t size);
SHMEM_FUNCTION_ATTRIBUTES void *shmem_realloc(void *ptr, size_t size);
SHMEM_FUNCTION_ATTRIBUTES void shmem_free(void *ptr);

/* Communicatoin Management Routines */
SHMEM_FUNCTION_ATTRIBUTES int shmem_ctx_create(long options, shmem_ctx_t *ctx);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_destroy(shmem_ctx_t ctx);

/* RMA: Elemental Data Put Routines */
SHMEM_FUNCTION_ATTRIBUTES void shmem_float_p(float *addr, float value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_double_p(double *addr, double value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_longdouble_p(long double *addr, long double value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_char_p(char *addr, char value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_schar_p(signed char *addr, signed char value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_short_p(short *addr, short value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int_p(int *addr, int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_p(long *addr, long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_p(long long *addr, long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uchar_p(unsigned char *addr, unsigned char value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ushort_p(unsigned short *addr, unsigned short value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint_p(unsigned int *addr, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulong_p(unsigned long *addr, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulonglong_p(unsigned long long *addr, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int8_p(int8_t *addr, int8_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int16_p(int16_t *addr, int16_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int32_p(int32_t *addr, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int64_p(int64_t *addr, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint8_p(uint8_t *addr, uint8_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint16_p(uint16_t *addr, uint16_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint32_p(uint32_t *addr, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint64_p(uint64_t *addr, uint64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_size_p(size_t *addr, size_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ptrdiff_p(ptrdiff_t *addr, ptrdiff_t value, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_float_p(shmem_ctx_t ctx, float *addr, float value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_double_p(shmem_ctx_t ctx, double *addr, double value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_longdouble_p(shmem_ctx_t ctx, long double *addr, long double value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_char_p(shmem_ctx_t ctx, char *addr, char value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_schar_p(shmem_ctx_t ctx, signed char *addr, signed char value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_short_p(shmem_ctx_t ctx, short *addr, short value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int_p(shmem_ctx_t ctx, int *addr, int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_long_p(shmem_ctx_t ctx, long *addr, long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_longlong_p(shmem_ctx_t ctx, long long *addr, long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uchar_p(shmem_ctx_t ctx, unsigned char *addr, unsigned char value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ushort_p(shmem_ctx_t ctx, unsigned short *addr, unsigned short value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint_p(shmem_ctx_t ctx, unsigned int *addr, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulong_p(shmem_ctx_t ctx, unsigned long *addr, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulonglong_p(shmem_ctx_t ctx, unsigned long long *addr, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int8_p(shmem_ctx_t ctx, int8_t *addr, int8_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int16_p(shmem_ctx_t ctx, int16_t *addr, int16_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int32_p(shmem_ctx_t ctx, int32_t *addr, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int64_p(shmem_ctx_t ctx, int64_t *addr, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint8_p(shmem_ctx_t ctx, uint8_t *addr, uint8_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint16_p(shmem_ctx_t ctx, uint16_t *addr, uint16_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint32_p(shmem_ctx_t ctx, uint32_t *addr, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint64_p(shmem_ctx_t ctx, uint64_t *addr, uint64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_size_p(shmem_ctx_t ctx, size_t *addr, size_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ptrdiff_p(shmem_ctx_t ctx, ptrdiff_t *addr, ptrdiff_t value, int pe);

/* RMA: Contiguous Data Put Routines */
SHMEM_FUNCTION_ATTRIBUTES void shmem_float_put(float *target, const float *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_double_put(double *target, const double *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_longdouble_put(long double *target, const long double *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_char_put(char *target, const char *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_schar_put(signed char *target, const signed char *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_short_put(short *target, const short *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int_put(int *target, const int *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_put(long *target, const long *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_put(long long *target, const long long *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uchar_put(unsigned char *target, const unsigned char *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ushort_put(unsigned short *target, const unsigned short *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint_put(unsigned int *target, const unsigned int *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulong_put(unsigned long *target, const unsigned long *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulonglong_put(unsigned long long *target, const unsigned long long *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int8_put(int8_t *target, const int8_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int16_put(int16_t *target, const int16_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int32_put(int32_t *target, const int32_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int64_put(int64_t *target, const int64_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint8_put(uint8_t *target, const uint8_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint16_put(uint16_t *target, const uint16_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint32_put(uint32_t *target, const uint32_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint64_put(uint64_t *target, const uint64_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_size_put(size_t *target, const size_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ptrdiff_put(ptrdiff_t *target, const ptrdiff_t *source, size_t nelems, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_float_put(shmem_ctx_t ctx, float *target, const float *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_double_put(shmem_ctx_t ctx, double *target, const double *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_longdouble_put(shmem_ctx_t ctx, long double *target, const long double *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_char_put(shmem_ctx_t ctx, char *target, const char *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_schar_put(shmem_ctx_t ctx, signed char *target, const signed char *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_short_put(shmem_ctx_t ctx, short *target, const short *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int_put(shmem_ctx_t ctx, int *target, const int *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_long_put(shmem_ctx_t ctx, long *target, const long *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_longlong_put(shmem_ctx_t ctx, long long *target, const long long *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uchar_put(shmem_ctx_t ctx, unsigned char *target, const unsigned char *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ushort_put(shmem_ctx_t ctx, unsigned short *target, const unsigned short *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint_put(shmem_ctx_t ctx, unsigned int *target, const unsigned int *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulong_put(shmem_ctx_t ctx, unsigned long *target, const unsigned long *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulonglong_put(shmem_ctx_t ctx, unsigned long long *target, const unsigned long long *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int8_put(shmem_ctx_t ctx, int8_t *target, const int8_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int16_put(shmem_ctx_t ctx, int16_t *target, const int16_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int32_put(shmem_ctx_t ctx, int32_t *target, const int32_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int64_put(shmem_ctx_t ctx, int64_t *target, const int64_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint8_put(shmem_ctx_t ctx, uint8_t *target, const uint8_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint16_put(shmem_ctx_t ctx, uint16_t *target, const uint16_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint32_put(shmem_ctx_t ctx, uint32_t *target, const uint32_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint64_put(shmem_ctx_t ctx, uint64_t *target, const uint64_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_size_put(shmem_ctx_t ctx, size_t *target, const size_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ptrdiff_put(shmem_ctx_t ctx, ptrdiff_t *target, const ptrdiff_t *source, size_t nelems, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_put8(void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_put16(void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_put32(void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_put64(void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_put128(void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_putmem(void* target, const void *source, size_t nelems, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_put8(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_put16(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_put32(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_put64(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_put128(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_putmem(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, int pe);

/* Blocking put with signal */
SHMEM_FUNCTION_ATTRIBUTES void shmem_float_put_signal(float *target, const float *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_double_put_signal(double *target, const double *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_longdouble_put_signal(long double *target, const long double *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_char_put_signal(char *target, const char *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_schar_put_signal(signed char *target, const signed char *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_short_put_signal(short *target, const short *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int_put_signal(int *target, const int *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_put_signal(long *target, const long *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_put_signal(long long *target, const long long *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uchar_put_signal(unsigned char *target, const unsigned char *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ushort_put_signal(unsigned short *target, const unsigned short *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint_put_signal(unsigned int *target, const unsigned int *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulong_put_signal(unsigned long *target, const unsigned long *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulonglong_put_signal(unsigned long long *target, const unsigned long long *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int8_put_signal(int8_t *target, const int8_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int16_put_signal(int16_t *target, const int16_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int32_put_signal(int32_t *target, const int32_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int64_put_signal(int64_t *target, const int64_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint8_put_signal(uint8_t *target, const uint8_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint16_put_signal(uint16_t *target, const uint16_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint32_put_signal(uint32_t *target, const uint32_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint64_put_signal(uint64_t *target, const uint64_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_size_put_signal(size_t *target, const size_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ptrdiff_put_signal(ptrdiff_t *target, const ptrdiff_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_float_put_signal(shmem_ctx_t ctx, float *target, const float *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_double_put_signal(shmem_ctx_t ctx, double *target, const double *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_longdouble_put_signal(shmem_ctx_t ctx, long double *target, const long double *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_char_put_signal(shmem_ctx_t ctx, char *target, const char *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_schar_put_signal(shmem_ctx_t ctx, signed char *target, const signed char *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_short_put_signal(shmem_ctx_t ctx, short *target, const short *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int_put_signal(shmem_ctx_t ctx, int *target, const int *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_long_put_signal(shmem_ctx_t ctx, long *target, const long *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_longlong_put_signal(shmem_ctx_t ctx, long long *target, const long long *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uchar_put_signal(shmem_ctx_t ctx, unsigned char *target, const unsigned char *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ushort_put_signal(shmem_ctx_t ctx, unsigned short *target, const unsigned short *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint_put_signal(shmem_ctx_t ctx, unsigned int *target, const unsigned int *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulong_put_signal(shmem_ctx_t ctx, unsigned long *target, const unsigned long *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulonglong_put_signal(shmem_ctx_t ctx, unsigned long long *target, const unsigned long long *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int8_put_signal(shmem_ctx_t ctx, int8_t *target, const int8_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int16_put_signal(shmem_ctx_t ctx, int16_t *target, const int16_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int32_put_signal(shmem_ctx_t ctx, int32_t *target, const int32_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int64_put_signal(shmem_ctx_t ctx, int64_t *target, const int64_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint8_put_signal(shmem_ctx_t ctx, uint8_t *target, const uint8_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint16_put_signal(shmem_ctx_t ctx, uint16_t *target, const uint16_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint32_put_signal(shmem_ctx_t ctx, uint32_t *target, const uint32_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint64_put_signal(shmem_ctx_t ctx, uint64_t *target, const uint64_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_size_put_signal(shmem_ctx_t ctx, size_t *target, const size_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ptrdiff_put_signal(shmem_ctx_t ctx, ptrdiff_t *target, const ptrdiff_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_put8_signal(void* target, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_put16_signal(void* target, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_put32_signal(void* target, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_put64_signal(void* target, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_put128_signal(void* target, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_putmem_signal(void* target, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_put8_signal(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_put16_signal(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_put32_signal(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_put64_signal(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_put128_signal(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_putmem_signal(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);

/* Non-blocking put with signal */
SHMEM_FUNCTION_ATTRIBUTES void shmem_float_put_signal_nbi(float *target, const float *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_double_put_signal_nbi(double *target, const double *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_longdouble_put_signal_nbi(long double *target, const long double *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_char_put_signal_nbi(char *target, const char *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_schar_put_signal_nbi(signed char *target, const signed char *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_short_put_signal_nbi(short *target, const short *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int_put_signal_nbi(int *target, const int *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_put_signal_nbi(long *target, const long *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_put_signal_nbi(long long *target, const long long *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uchar_put_signal_nbi(unsigned char *target, const unsigned char *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ushort_put_signal_nbi(unsigned short *target, const unsigned short *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint_put_signal_nbi(unsigned int *target, const unsigned int *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulong_put_signal_nbi(unsigned long *target, const unsigned long *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulonglong_put_signal_nbi(unsigned long long *target, const unsigned long long *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int8_put_signal_nbi(int8_t *target, const int8_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int16_put_signal_nbi(int16_t *target, const int16_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int32_put_signal_nbi(int32_t *target, const int32_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int64_put_signal_nbi(int64_t *target, const int64_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint8_put_signal_nbi(uint8_t *target, const uint8_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint16_put_signal_nbi(uint16_t *target, const uint16_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint32_put_signal_nbi(uint32_t *target, const uint32_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint64_put_signal_nbi(uint64_t *target, const uint64_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_size_put_signal_nbi(size_t *target, const size_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ptrdiff_put_signal_nbi(ptrdiff_t *target, const ptrdiff_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_float_put_signal_nbi(shmem_ctx_t ctx, float *target, const float *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_double_put_signal_nbi(shmem_ctx_t ctx, double *target, const double *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_longdouble_put_signal_nbi(shmem_ctx_t ctx, long double *target, const long double *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_char_put_signal_nbi(shmem_ctx_t ctx, char *target, const char *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_schar_put_signal_nbi(shmem_ctx_t ctx, signed char *target, const signed char *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_short_put_signal_nbi(shmem_ctx_t ctx, short *target, const short *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int_put_signal_nbi(shmem_ctx_t ctx, int *target, const int *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_long_put_signal_nbi(shmem_ctx_t ctx, long *target, const long *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_longlong_put_signal_nbi(shmem_ctx_t ctx, long long *target, const long long *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uchar_put_signal_nbi(shmem_ctx_t ctx, unsigned char *target, const unsigned char *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ushort_put_signal_nbi(shmem_ctx_t ctx, unsigned short *target, const unsigned short *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint_put_signal_nbi(shmem_ctx_t ctx, unsigned int *target, const unsigned int *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulong_put_signal_nbi(shmem_ctx_t ctx, unsigned long *target, const unsigned long *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulonglong_put_signal_nbi(shmem_ctx_t ctx, unsigned long long *target, const unsigned long long *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int8_put_signal_nbi(shmem_ctx_t ctx, int8_t *target, const int8_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int16_put_signal_nbi(shmem_ctx_t ctx, int16_t *target, const int16_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int32_put_signal_nbi(shmem_ctx_t ctx, int32_t *target, const int32_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int64_put_signal_nbi(shmem_ctx_t ctx, int64_t *target, const int64_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint8_put_signal_nbi(shmem_ctx_t ctx, uint8_t *target, const uint8_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint16_put_signal_nbi(shmem_ctx_t ctx, uint16_t *target, const uint16_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint32_put_signal_nbi(shmem_ctx_t ctx, uint32_t *target, const uint32_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint64_put_signal_nbi(shmem_ctx_t ctx, uint64_t *target, const uint64_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_size_put_signal_nbi(shmem_ctx_t ctx, size_t *target, const size_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ptrdiff_put_signal_nbi(shmem_ctx_t ctx, ptrdiff_t *target, const ptrdiff_t *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_put8_signal_nbi(void* target, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_put16_signal_nbi(void* target, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_put32_signal_nbi(void* target, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_put64_signal_nbi(void* target, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_put128_signal_nbi(void* target, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_putmem_signal_nbi(void* target, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_put8_signal_nbi(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_put16_signal_nbi(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_put32_signal_nbi(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_put64_signal_nbi(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_put128_signal_nbi(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_putmem_signal_nbi(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe);

/* RMA: Strided Put Routines */
SHMEM_FUNCTION_ATTRIBUTES void shmem_float_iput(float *target, const float *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_double_iput(double *target, const double *source,
                       ptrdiff_t tst, ptrdiff_t sst,
                       size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_longdouble_iput(long double *target, const long double *source,
                           ptrdiff_t tst, ptrdiff_t sst,
                           size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_char_iput(char *target, const char *source,
                     ptrdiff_t tst, ptrdiff_t sst,
                     size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_schar_iput(signed char *target, const signed char *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_short_iput(short *target, const short *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int_iput(int *target, const int *source,
                    ptrdiff_t tst, ptrdiff_t sst,
                    size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_iput(long *target, const long *source,
                     ptrdiff_t tst, ptrdiff_t sst,
                     size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_iput(long long *target, const long long *source,
                         ptrdiff_t tst, ptrdiff_t sst,
                         size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uchar_iput(unsigned char *target, const unsigned char *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ushort_iput(unsigned short *target, const unsigned short *source,
                       ptrdiff_t tst, ptrdiff_t sst,
                       size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint_iput(unsigned int *target, const unsigned int *source,
                     ptrdiff_t tst, ptrdiff_t sst,
                     size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulong_iput(unsigned long *target, const unsigned long *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulonglong_iput(unsigned long long *target, const unsigned long long *source,
                          ptrdiff_t tst, ptrdiff_t sst,
                          size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int8_iput(int8_t *target, const int8_t *source,
                     ptrdiff_t tst, ptrdiff_t sst,
                     size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int16_iput(int16_t *target, const int16_t *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int32_iput(int32_t *target, const int32_t *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int64_iput(int64_t *target, const int64_t *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint8_iput(uint8_t *target, const uint8_t *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint16_iput(uint16_t *target, const uint16_t *source,
                       ptrdiff_t tst, ptrdiff_t sst,
                       size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint32_iput(uint32_t *target, const uint32_t *source,
                       ptrdiff_t tst, ptrdiff_t sst,
                       size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint64_iput(uint64_t *target, const uint64_t *source,
                       ptrdiff_t tst, ptrdiff_t sst,
                       size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_size_iput(size_t *target, const size_t *source,
                     ptrdiff_t tst, ptrdiff_t sst,
                     size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ptrdiff_iput(ptrdiff_t *target, const ptrdiff_t *source,
                        ptrdiff_t tst, ptrdiff_t sst,
                        size_t len, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_float_iput(shmem_ctx_t ctx, float *target, const float *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_double_iput(shmem_ctx_t ctx, double *target, const double *source,
                       ptrdiff_t tst, ptrdiff_t sst,
                       size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_longdouble_iput(shmem_ctx_t ctx, long double *target, const long double *source,
                           ptrdiff_t tst, ptrdiff_t sst,
                           size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_char_iput(shmem_ctx_t ctx, char *target, const char *source,
                     ptrdiff_t tst, ptrdiff_t sst,
                     size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_schar_iput(shmem_ctx_t ctx, signed char *target, const signed char *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_short_iput(shmem_ctx_t ctx, short *target, const short *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int_iput(shmem_ctx_t ctx, int *target, const int *source,
                    ptrdiff_t tst, ptrdiff_t sst,
                    size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_long_iput(shmem_ctx_t ctx, long *target, const long *source,
                     ptrdiff_t tst, ptrdiff_t sst,
                     size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_longlong_iput(shmem_ctx_t ctx, long long *target, const long long *source,
                         ptrdiff_t tst, ptrdiff_t sst,
                         size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uchar_iput(shmem_ctx_t ctx, unsigned char *target, const unsigned char *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ushort_iput(shmem_ctx_t ctx, unsigned short *target, const unsigned short *source,
                       ptrdiff_t tst, ptrdiff_t sst,
                       size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint_iput(shmem_ctx_t ctx, unsigned int *target, const unsigned int *source,
                     ptrdiff_t tst, ptrdiff_t sst,
                     size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulong_iput(shmem_ctx_t ctx, unsigned long *target, const unsigned long *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulonglong_iput(shmem_ctx_t ctx, unsigned long long *target, const unsigned long long *source,
                          ptrdiff_t tst, ptrdiff_t sst,
                          size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int8_iput(shmem_ctx_t ctx, int8_t *target, const int8_t *source,
                     ptrdiff_t tst, ptrdiff_t sst,
                     size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int16_iput(shmem_ctx_t ctx, int16_t *target, const int16_t *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int32_iput(shmem_ctx_t ctx, int32_t *target, const int32_t *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int64_iput(shmem_ctx_t ctx, int64_t *target, const int64_t *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint8_iput(shmem_ctx_t ctx, uint8_t *target, const uint8_t *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint16_iput(shmem_ctx_t ctx, uint16_t *target, const uint16_t *source,
                       ptrdiff_t tst, ptrdiff_t sst,
                       size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint32_iput(shmem_ctx_t ctx, uint32_t *target, const uint32_t *source,
                       ptrdiff_t tst, ptrdiff_t sst,
                       size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint64_iput(shmem_ctx_t ctx, uint64_t *target, const uint64_t *source,
                       ptrdiff_t tst, ptrdiff_t sst,
                       size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_size_iput(shmem_ctx_t ctx, size_t *target, const size_t *source,
                     ptrdiff_t tst, ptrdiff_t sst,
                     size_t len, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ptrdiff_iput(shmem_ctx_t ctx, ptrdiff_t *target, const ptrdiff_t *source,
                        ptrdiff_t tst, ptrdiff_t sst,
                        size_t len, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_iput8(void *target, const void *source,
                 ptrdiff_t tst, ptrdiff_t sst, size_t len,
                 int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_iput16(void *target, const void *source,
                  ptrdiff_t tst, ptrdiff_t sst, size_t len,
                  int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_iput32(void *target, const void *source,
                  ptrdiff_t tst, ptrdiff_t sst, size_t len,
                  int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_iput64(void *target, const void *source,
                  ptrdiff_t tst, ptrdiff_t sst, size_t len,
                  int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_iput128(void *target, const void *source,
                   ptrdiff_t tst, ptrdiff_t sst, size_t len,
                   int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_iput8(shmem_ctx_t ctx, void *target, const void *source,
                 ptrdiff_t tst, ptrdiff_t sst, size_t len,
                 int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_iput16(shmem_ctx_t ctx, void *target, const void *source,
                  ptrdiff_t tst, ptrdiff_t sst, size_t len,
                  int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_iput32(shmem_ctx_t ctx, void *target, const void *source,
                  ptrdiff_t tst, ptrdiff_t sst, size_t len,
                  int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_iput64(shmem_ctx_t ctx, void *target, const void *source,
                  ptrdiff_t tst, ptrdiff_t sst, size_t len,
                  int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_iput128(shmem_ctx_t ctx, void *target, const void *source,
                   ptrdiff_t tst, ptrdiff_t sst, size_t len,
                   int pe);

/* RMA: Elemental Data Get Routines */
SHMEM_FUNCTION_ATTRIBUTES float shmem_float_g(const float *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES double shmem_double_g(const double *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES long double shmem_longdouble_g(const long double *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES char shmem_char_g(const char *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES signed char shmem_schar_g(const signed char *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES short shmem_short_g(const short *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int_g(const int *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES long shmem_long_g(const long *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES long long shmem_longlong_g(const long long *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned char shmem_uchar_g(const unsigned char *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned short shmem_ushort_g(const unsigned short *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned int shmem_uint_g(const unsigned int *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long shmem_ulong_g(const unsigned long *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long long shmem_ulonglong_g(const unsigned long long *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES int8_t shmem_int8_g(const int8_t *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES int16_t shmem_int16_g(const int16_t *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES int32_t shmem_int32_g(const int32_t *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES int64_t shmem_int64_g(const int64_t *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint8_t shmem_uint8_g(const uint8_t *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint16_t shmem_uint16_g(const uint16_t *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint32_t shmem_uint32_g(const uint32_t *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint64_t shmem_uint64_g(const uint64_t *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_size_g(const size_t *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES ptrdiff_t shmem_ptrdiff_g(const ptrdiff_t *addr, int pe);

SHMEM_FUNCTION_ATTRIBUTES float shmem_ctx_float_g(shmem_ctx_t ctx, const float *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES double shmem_ctx_double_g(shmem_ctx_t ctx, const double *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES long double shmem_ctx_longdouble_g(shmem_ctx_t ctx, const long double *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES char shmem_ctx_char_g(shmem_ctx_t ctx, const char *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES signed char shmem_ctx_schar_g(shmem_ctx_t ctx, const signed char *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES short shmem_ctx_short_g(shmem_ctx_t ctx, const short *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ctx_int_g(shmem_ctx_t ctx, const int *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES long shmem_ctx_long_g(shmem_ctx_t ctx, const long *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES long long shmem_ctx_longlong_g(shmem_ctx_t ctx, const long long *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned char shmem_ctx_uchar_g(shmem_ctx_t ctx, const unsigned char *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned short shmem_ctx_ushort_g(shmem_ctx_t ctx, const unsigned short *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned int shmem_ctx_uint_g(shmem_ctx_t ctx, const unsigned int *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long shmem_ctx_ulong_g(shmem_ctx_t ctx, const unsigned long *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long long shmem_ctx_ulonglong_g(shmem_ctx_t ctx, const unsigned long long *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES int8_t shmem_ctx_int8_g(shmem_ctx_t ctx, const int8_t *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES int16_t shmem_ctx_int16_g(shmem_ctx_t ctx, const int16_t *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES int32_t shmem_ctx_int32_g(shmem_ctx_t ctx, const int32_t *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES int64_t shmem_ctx_int64_g(shmem_ctx_t ctx, const int64_t *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint8_t shmem_ctx_uint8_g(shmem_ctx_t ctx, const uint8_t *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint16_t shmem_ctx_uint16_g(shmem_ctx_t ctx, const uint16_t *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint32_t shmem_ctx_uint32_g(shmem_ctx_t ctx, const uint32_t *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint64_t shmem_ctx_uint64_g(shmem_ctx_t ctx, const uint64_t *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ctx_size_g(shmem_ctx_t ctx, const size_t *addr, int pe);
SHMEM_FUNCTION_ATTRIBUTES ptrdiff_t shmem_ctx_ptrdiff_g(shmem_ctx_t ctx, const ptrdiff_t *addr, int pe);

/* RMA: Contiguous Data Get Routines */
SHMEM_FUNCTION_ATTRIBUTES void shmem_float_get(float *target, const float *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_double_get(double *target, const double *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_longdouble_get(long double *target, const long double *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_char_get(char *target, const char *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_schar_get(signed char *target, const signed char *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_short_get(short *target, const short *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int_get(int *target, const int *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_get(long *target, const long *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_get(long long *target, const long long *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uchar_get(unsigned char *target, const unsigned char *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ushort_get(unsigned short *target, const unsigned short *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint_get(unsigned int *target, const unsigned int *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulong_get(unsigned long *target, const unsigned long *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulonglong_get(unsigned long long *target, const unsigned long long *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int8_get(int8_t *target, const int8_t *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int16_get(int16_t *target, const int16_t *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int32_get(int32_t *target, const int32_t *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int64_get(int64_t *target, const int64_t *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint8_get(uint8_t *target, const uint8_t *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint16_get(uint16_t *target, const uint16_t *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint32_get(uint32_t *target, const uint32_t *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint64_get(uint64_t *target, const uint64_t *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_size_get(size_t *target, const size_t *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ptrdiff_get(ptrdiff_t *target, const ptrdiff_t *source, size_t nelems,int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_float_get(shmem_ctx_t ctx, float *target, const float *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_double_get(shmem_ctx_t ctx, double *target, const double *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_longdouble_get(shmem_ctx_t ctx, long double *target, const long double *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_char_get(shmem_ctx_t ctx, char *target, const char *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_schar_get(shmem_ctx_t ctx, signed char *target, const signed char *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_short_get(shmem_ctx_t ctx, short *target, const short *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int_get(shmem_ctx_t ctx, int *target, const int *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_long_get(shmem_ctx_t ctx, long *target, const long *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_longlong_get(shmem_ctx_t ctx, long long *target, const long long *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uchar_get(shmem_ctx_t ctx, unsigned char *target, const unsigned char *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ushort_get(shmem_ctx_t ctx, unsigned short *target, const unsigned short *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint_get(shmem_ctx_t ctx, unsigned int *target, const unsigned int *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulong_get(shmem_ctx_t ctx, unsigned long *target, const unsigned long *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulonglong_get(shmem_ctx_t ctx, unsigned long long *target, const unsigned long long *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int8_get(shmem_ctx_t ctx, int8_t *target, const int8_t *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int16_get(shmem_ctx_t ctx, int16_t *target, const int16_t *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int32_get(shmem_ctx_t ctx, int32_t *target, const int32_t *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int64_get(shmem_ctx_t ctx, int64_t *target, const int64_t *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint8_get(shmem_ctx_t ctx, uint8_t *target, const uint8_t *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint16_get(shmem_ctx_t ctx, uint16_t *target, const uint16_t *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint32_get(shmem_ctx_t ctx, uint32_t *target, const uint32_t *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint64_get(shmem_ctx_t ctx, uint64_t *target, const uint64_t *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_size_get(shmem_ctx_t ctx, size_t *target, const size_t *source, size_t nelems,int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ptrdiff_get(shmem_ctx_t ctx, ptrdiff_t *target, const ptrdiff_t *source, size_t nelems,int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_get8(void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_get16(void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_get32(void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_get64(void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_get128(void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_getmem(void* target, const void *source, size_t nelems, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_get8(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_get16(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_get32(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_get64(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_get128(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_getmem(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, int pe);

/* RMA: Strided Get Routines */
SHMEM_FUNCTION_ATTRIBUTES void shmem_float_iget(float *target, const float *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_double_iget(double *target, const double *source,
                       ptrdiff_t tst, ptrdiff_t sst,
                       size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_longdouble_iget(long double *target, const long double *source,
                           ptrdiff_t tst, ptrdiff_t sst,
                           size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_char_iget(char *target, const char *source,
                     ptrdiff_t tst, ptrdiff_t sst,
                     size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_schar_iget(signed char *target, const signed char *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_short_iget(short *target, const short *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int_iget(int *target, const int *source,
                    ptrdiff_t tst, ptrdiff_t sst,
                    size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_iget(long *target, const long *source,
                     ptrdiff_t tst, ptrdiff_t sst,
                     size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_iget(long long *target, const long long *source,
                         ptrdiff_t tst, ptrdiff_t sst,
                         size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uchar_iget(unsigned char *target, const unsigned char *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ushort_iget(unsigned short *target, const unsigned short *source,
                       ptrdiff_t tst, ptrdiff_t sst,
                       size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint_iget(unsigned int *target, const unsigned int *source,
                     ptrdiff_t tst, ptrdiff_t sst,
                     size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulong_iget(unsigned long *target, const unsigned long *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulonglong_iget(unsigned long long *target, const unsigned long long *source,
                          ptrdiff_t tst, ptrdiff_t sst,
                          size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int8_iget(int8_t *target, const int8_t *source,
                     ptrdiff_t tst, ptrdiff_t sst,
                     size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int16_iget(int16_t *target, const int16_t *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int32_iget(int32_t *target, const int32_t *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int64_iget(int64_t *target, const int64_t *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint8_iget(uint8_t *target, const uint8_t *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint16_iget(uint16_t *target, const uint16_t *source,
                       ptrdiff_t tst, ptrdiff_t sst,
                       size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint32_iget(uint32_t *target, const uint32_t *source,
                       ptrdiff_t tst, ptrdiff_t sst,
                       size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint64_iget(uint64_t *target, const uint64_t *source,
                       ptrdiff_t tst, ptrdiff_t sst,
                       size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_size_iget(size_t *target, const size_t *source,
                     ptrdiff_t tst, ptrdiff_t sst,
                     size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ptrdiff_iget(ptrdiff_t *target, const ptrdiff_t *source,
                        ptrdiff_t tst, ptrdiff_t sst,
                        size_t nelems, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_float_iget(shmem_ctx_t ctx, float *target, const float *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_double_iget(shmem_ctx_t ctx, double *target, const double *source,
                       ptrdiff_t tst, ptrdiff_t sst,
                       size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_longdouble_iget(shmem_ctx_t ctx, long double *target, const long double *source,
                           ptrdiff_t tst, ptrdiff_t sst,
                           size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_char_iget(shmem_ctx_t ctx, char *target, const char *source,
                     ptrdiff_t tst, ptrdiff_t sst,
                     size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_schar_iget(shmem_ctx_t ctx, signed char *target, const signed char *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_short_iget(shmem_ctx_t ctx, short *target, const short *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int_iget(shmem_ctx_t ctx, int *target, const int *source,
                    ptrdiff_t tst, ptrdiff_t sst,
                    size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_long_iget(shmem_ctx_t ctx, long *target, const long *source,
                     ptrdiff_t tst, ptrdiff_t sst,
                     size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_longlong_iget(shmem_ctx_t ctx, long long *target, const long long *source,
                         ptrdiff_t tst, ptrdiff_t sst,
                         size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uchar_iget(shmem_ctx_t ctx, unsigned char *target, const unsigned char *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ushort_iget(shmem_ctx_t ctx, unsigned short *target, const unsigned short *source,
                       ptrdiff_t tst, ptrdiff_t sst,
                       size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint_iget(shmem_ctx_t ctx, unsigned int *target, const unsigned int *source,
                     ptrdiff_t tst, ptrdiff_t sst,
                     size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulong_iget(shmem_ctx_t ctx, unsigned long *target, const unsigned long *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulonglong_iget(shmem_ctx_t ctx, unsigned long long *target, const unsigned long long *source,
                          ptrdiff_t tst, ptrdiff_t sst,
                          size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int8_iget(shmem_ctx_t ctx, int8_t *target, const int8_t *source,
                     ptrdiff_t tst, ptrdiff_t sst,
                     size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int16_iget(shmem_ctx_t ctx, int16_t *target, const int16_t *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int32_iget(shmem_ctx_t ctx, int32_t *target, const int32_t *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int64_iget(shmem_ctx_t ctx, int64_t *target, const int64_t *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint8_iget(shmem_ctx_t ctx, uint8_t *target, const uint8_t *source,
                      ptrdiff_t tst, ptrdiff_t sst,
                      size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint16_iget(shmem_ctx_t ctx, uint16_t *target, const uint16_t *source,
                       ptrdiff_t tst, ptrdiff_t sst,
                       size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint32_iget(shmem_ctx_t ctx, uint32_t *target, const uint32_t *source,
                       ptrdiff_t tst, ptrdiff_t sst,
                       size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint64_iget(shmem_ctx_t ctx, uint64_t *target, const uint64_t *source,
                       ptrdiff_t tst, ptrdiff_t sst,
                       size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_size_iget(shmem_ctx_t ctx, size_t *target, const size_t *source,
                     ptrdiff_t tst, ptrdiff_t sst,
                     size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ptrdiff_iget(shmem_ctx_t ctx, ptrdiff_t *target, const ptrdiff_t *source,
                        ptrdiff_t tst, ptrdiff_t sst,
                        size_t nelems, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_iget8(void* target, const void *source,
                 ptrdiff_t tst, ptrdiff_t sst,
                 size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_iget16(void* target, const void *source,
                  ptrdiff_t tst, ptrdiff_t sst,
                  size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_iget32(void* target, const void *source,
                  ptrdiff_t tst, ptrdiff_t sst,
                  size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_iget64(void* target, const void *source,
                  ptrdiff_t tst, ptrdiff_t sst,
                  size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_iget128(void* target, const void *source,
                   ptrdiff_t tst, ptrdiff_t sst,
                   size_t nelems, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_iget8(shmem_ctx_t ctx, void* target, const void *source,
                 ptrdiff_t tst, ptrdiff_t sst,
                 size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_iget16(shmem_ctx_t ctx, void* target, const void *source,
                  ptrdiff_t tst, ptrdiff_t sst,
                  size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_iget32(shmem_ctx_t ctx, void* target, const void *source,
                  ptrdiff_t tst, ptrdiff_t sst,
                  size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_iget64(shmem_ctx_t ctx, void* target, const void *source,
                  ptrdiff_t tst, ptrdiff_t sst,
                  size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_iget128(shmem_ctx_t ctx, void* target, const void *source,
                   ptrdiff_t tst, ptrdiff_t sst,
                   size_t nelems, int pe);

/* RMA: Nonblocking Contiguous Data Put Routines */
SHMEM_FUNCTION_ATTRIBUTES void shmem_float_put_nbi(float *target, const float *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_double_put_nbi(double *target, const double *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_longdouble_put_nbi(long double *target, const long double *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_char_put_nbi(char *target, const char *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_schar_put_nbi(signed char *target, const signed char *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_short_put_nbi(short *target, const short *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int_put_nbi(int *target, const int *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_put_nbi(long *target, const long *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_put_nbi(long long *target, const long long *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uchar_put_nbi(unsigned char *target, const unsigned char *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ushort_put_nbi(unsigned short *target, const unsigned short *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint_put_nbi(unsigned int *target, const unsigned int *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulong_put_nbi(unsigned long *target, const unsigned long *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulonglong_put_nbi(unsigned long long *target, const unsigned long long *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int8_put_nbi(int8_t *target, const int8_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int16_put_nbi(int16_t *target, const int16_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int32_put_nbi(int32_t *target, const int32_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int64_put_nbi(int64_t *target, const int64_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint8_put_nbi(uint8_t *target, const uint8_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint16_put_nbi(uint16_t *target, const uint16_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint32_put_nbi(uint32_t *target, const uint32_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint64_put_nbi(uint64_t *target, const uint64_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_size_put_nbi(size_t *target, const size_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ptrdiff_put_nbi(ptrdiff_t *target, const ptrdiff_t *source, size_t nelems, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_float_put_nbi(shmem_ctx_t ctx, float *target, const float *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_double_put_nbi(shmem_ctx_t ctx, double *target, const double *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_longdouble_put_nbi(shmem_ctx_t ctx, long double *target, const long double *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_char_put_nbi(shmem_ctx_t ctx, char *target, const char *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_schar_put_nbi(shmem_ctx_t ctx, signed char *target, const signed char *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_short_put_nbi(shmem_ctx_t ctx, short *target, const short *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int_put_nbi(shmem_ctx_t ctx, int *target, const int *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_long_put_nbi(shmem_ctx_t ctx, long *target, const long *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_longlong_put_nbi(shmem_ctx_t ctx, long long *target, const long long *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uchar_put_nbi(shmem_ctx_t ctx, unsigned char *target, const unsigned char *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ushort_put_nbi(shmem_ctx_t ctx, unsigned short *target, const unsigned short *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint_put_nbi(shmem_ctx_t ctx, unsigned int *target, const unsigned int *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulong_put_nbi(shmem_ctx_t ctx, unsigned long *target, const unsigned long *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulonglong_put_nbi(shmem_ctx_t ctx, unsigned long long *target, const unsigned long long *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int8_put_nbi(shmem_ctx_t ctx, int8_t *target, const int8_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int16_put_nbi(shmem_ctx_t ctx, int16_t *target, const int16_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int32_put_nbi(shmem_ctx_t ctx, int32_t *target, const int32_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int64_put_nbi(shmem_ctx_t ctx, int64_t *target, const int64_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint8_put_nbi(shmem_ctx_t ctx, uint8_t *target, const uint8_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint16_put_nbi(shmem_ctx_t ctx, uint16_t *target, const uint16_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint32_put_nbi(shmem_ctx_t ctx, uint32_t *target, const uint32_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint64_put_nbi(shmem_ctx_t ctx, uint64_t *target, const uint64_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_size_put_nbi(shmem_ctx_t ctx, size_t *target, const size_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ptrdiff_put_nbi(shmem_ctx_t ctx, ptrdiff_t *target, const ptrdiff_t *source, size_t nelems, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_put8_nbi(void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_put16_nbi(void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_put32_nbi(void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_put64_nbi(void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_put128_nbi(void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_putmem_nbi(void* target, const void *source, size_t nelems, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_put8_nbi(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_put16_nbi(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_put32_nbi(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_put64_nbi(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_put128_nbi(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_putmem_nbi(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, int pe);

/* RMA: Nonblocking Contiguous Data Get Routines */
SHMEM_FUNCTION_ATTRIBUTES void shmem_float_get_nbi(float *target, const float *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_double_get_nbi(double *target, const double *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_longdouble_get_nbi(long double *target, const long double *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_char_get_nbi(char *target, const char *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_schar_get_nbi(signed char *target, const signed char *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_short_get_nbi(short *target, const short *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int_get_nbi(int *target, const int *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_get_nbi(long *target, const long *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_get_nbi(long long *target, const long long *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uchar_get_nbi(unsigned char *target, const unsigned char *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ushort_get_nbi(unsigned short *target, const unsigned short *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint_get_nbi(unsigned int *target, const unsigned int *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulong_get_nbi(unsigned long *target, const unsigned long *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulonglong_get_nbi(unsigned long long *target, const unsigned long long *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int8_get_nbi(int8_t *target, const int8_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int16_get_nbi(int16_t *target, const int16_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int32_get_nbi(int32_t *target, const int32_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int64_get_nbi(int64_t *target, const int64_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint8_get_nbi(uint8_t *target, const uint8_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint16_get_nbi(uint16_t *target, const uint16_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint32_get_nbi(uint32_t *target, const uint32_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint64_get_nbi(uint64_t *target, const uint64_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_size_get_nbi(size_t *target, const size_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ptrdiff_get_nbi(ptrdiff_t *target, const ptrdiff_t *source, size_t nelems, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_float_get_nbi(shmem_ctx_t ctx, float *target, const float *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_double_get_nbi(shmem_ctx_t ctx, double *target, const double *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_longdouble_get_nbi(shmem_ctx_t ctx, long double *target, const long double *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_char_get_nbi(shmem_ctx_t ctx, char *target, const char *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_schar_get_nbi(shmem_ctx_t ctx, signed char *target, const signed char *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_short_get_nbi(shmem_ctx_t ctx, short *target, const short *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int_get_nbi(shmem_ctx_t ctx, int *target, const int *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_long_get_nbi(shmem_ctx_t ctx, long *target, const long *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_longlong_get_nbi(shmem_ctx_t ctx, long long *target, const long long *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uchar_get_nbi(shmem_ctx_t ctx, unsigned char *target, const unsigned char *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ushort_get_nbi(shmem_ctx_t ctx, unsigned short *target, const unsigned short *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint_get_nbi(shmem_ctx_t ctx, unsigned int *target, const unsigned int *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulong_get_nbi(shmem_ctx_t ctx, unsigned long *target, const unsigned long *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulonglong_get_nbi(shmem_ctx_t ctx, unsigned long long *target, const unsigned long long *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int8_get_nbi(shmem_ctx_t ctx, int8_t *target, const int8_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int16_get_nbi(shmem_ctx_t ctx, int16_t *target, const int16_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int32_get_nbi(shmem_ctx_t ctx, int32_t *target, const int32_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int64_get_nbi(shmem_ctx_t ctx, int64_t *target, const int64_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint8_get_nbi(shmem_ctx_t ctx, uint8_t *target, const uint8_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint16_get_nbi(shmem_ctx_t ctx, uint16_t *target, const uint16_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint32_get_nbi(shmem_ctx_t ctx, uint32_t *target, const uint32_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint64_get_nbi(shmem_ctx_t ctx, uint64_t *target, const uint64_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_size_get_nbi(shmem_ctx_t ctx, size_t *target, const size_t *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ptrdiff_get_nbi(shmem_ctx_t ctx, ptrdiff_t *target, const ptrdiff_t *source, size_t nelems, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_get8_nbi(void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_get16_nbi(void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_get32_nbi(void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_get64_nbi(void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_get128_nbi(void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_getmem_nbi(void* target, const void *source, size_t nelems, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_get8_nbi(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_get16_nbi(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_get32_nbi(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_get64_nbi(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_get128_nbi(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_getmem_nbi(shmem_ctx_t ctx, void* target, const void *source, size_t nelems, int pe);

/* AMO: Atomic Swap Routines */
SHMEM_FUNCTION_ATTRIBUTES int shmem_int_swap(int *target, int value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES long shmem_long_swap(long *target, long value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES long long shmem_longlong_swap(long long *target, long long value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES unsigned int shmem_uint_swap(unsigned int *target, unsigned int value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES unsigned long shmem_ulong_swap(unsigned long *target, unsigned long value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES unsigned long long shmem_ulonglong_swap(unsigned long long *target, unsigned long long value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES int32_t shmem_int32_swap(int32_t *target, int32_t value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES int64_t shmem_int64_swap(int64_t *target, int64_t value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES uint32_t shmem_uint32_swap(uint32_t *target, uint32_t value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES uint64_t shmem_uint64_swap(uint64_t *target, uint64_t value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_size_swap(size_t *target, size_t value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES ptrdiff_t shmem_ptrdiff_swap(ptrdiff_t *target, ptrdiff_t value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES float shmem_float_swap(float *target, float value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES double shmem_double_swap(double *target, double value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;

SHMEM_FUNCTION_ATTRIBUTES int shmem_int_atomic_swap(int *target, int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES long shmem_long_atomic_swap(long *target, long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES long long shmem_longlong_atomic_swap(long long *target, long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned int shmem_uint_atomic_swap(unsigned int *target, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long shmem_ulong_atomic_swap(unsigned long *target, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long long shmem_ulonglong_atomic_swap(unsigned long long *target, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES int32_t shmem_int32_atomic_swap(int32_t *target, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES int64_t shmem_int64_atomic_swap(int64_t *target, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint32_t shmem_uint32_atomic_swap(uint32_t *target, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint64_t shmem_uint64_atomic_swap(uint64_t *target, uint64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_size_atomic_swap(size_t *target, size_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES ptrdiff_t shmem_ptrdiff_atomic_swap(ptrdiff_t *target, ptrdiff_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES float shmem_float_atomic_swap(float *target, float value, int pe);
SHMEM_FUNCTION_ATTRIBUTES double shmem_double_atomic_swap(double *target, double value, int pe);

SHMEM_FUNCTION_ATTRIBUTES int shmem_ctx_int_atomic_swap(shmem_ctx_t ctx, int *target, int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES long shmem_ctx_long_atomic_swap(shmem_ctx_t ctx, long *target, long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES long long shmem_ctx_longlong_atomic_swap(shmem_ctx_t ctx, long long *target, long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned int shmem_ctx_uint_atomic_swap(shmem_ctx_t ctx, unsigned int *target, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long shmem_ctx_ulong_atomic_swap(shmem_ctx_t ctx, unsigned long *target, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long long shmem_ctx_ulonglong_atomic_swap(shmem_ctx_t ctx, unsigned long long *target, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES int32_t shmem_ctx_int32_atomic_swap(shmem_ctx_t ctx, int32_t *target, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES int64_t shmem_ctx_int64_atomic_swap(shmem_ctx_t ctx, int64_t *target, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint32_t shmem_ctx_uint32_atomic_swap(shmem_ctx_t ctx, uint32_t *target, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint64_t shmem_ctx_uint64_atomic_swap(shmem_ctx_t ctx, uint64_t *target, uint64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ctx_size_atomic_swap(shmem_ctx_t ctx, size_t *target, size_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES ptrdiff_t shmem_ctx_ptrdiff_atomic_swap(shmem_ctx_t ctx, ptrdiff_t *target, ptrdiff_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES float shmem_ctx_float_atomic_swap(shmem_ctx_t ctx, float *target, float value, int pe);
SHMEM_FUNCTION_ATTRIBUTES double shmem_ctx_double_atomic_swap(shmem_ctx_t ctx, double *target, double value, int pe);

/* Special case, only enabled when C++ and C11 bindings are disabled */
#if ( !defined(__cplusplus) && \
      !(defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L) ) || \
    defined(SHMEM_INTERNAL_INCLUDE) || defined(SHMEM_DECLARE_SPECIAL_CASES)
SHMEM_FUNCTION_ATTRIBUTES long shmem_swap(long *target, long value, int pe);
#endif

/* AMO: Atomic Conditional Swap Routines */
SHMEM_FUNCTION_ATTRIBUTES int shmem_int_cswap(int *target, int cond, int value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES long shmem_long_cswap(long *target, long cond, long value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES long long shmem_longlong_cswap(long long *target, long long cond, long long value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES unsigned int shmem_uint_cswap(unsigned int *target, unsigned int cond, unsigned int value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES unsigned long shmem_ulong_cswap(unsigned long *target, unsigned long cond, unsigned long value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES unsigned long long shmem_ulonglong_cswap(unsigned long long *target, unsigned long long cond, unsigned long long value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES int32_t shmem_int32_cswap(int32_t *target, int32_t cond, int32_t value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES int64_t shmem_int64_cswap(int64_t *target, int64_t cond, int64_t value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES uint32_t shmem_uint32_cswap(uint32_t *target, uint32_t cond, uint32_t value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES uint64_t shmem_uint64_cswap(uint64_t *target, uint64_t cond, uint64_t value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_size_cswap(size_t *target, size_t cond, size_t value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES ptrdiff_t shmem_ptrdiff_cswap(ptrdiff_t *target, ptrdiff_t cond, ptrdiff_t value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;

SHMEM_FUNCTION_ATTRIBUTES int shmem_int_atomic_compare_swap(int *target, int cond, int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES long shmem_long_atomic_compare_swap(long *target, long cond, long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES long long shmem_longlong_atomic_compare_swap(long long *target, long long cond, long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned int shmem_uint_atomic_compare_swap(unsigned int *target, unsigned int cond, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long shmem_ulong_atomic_compare_swap(unsigned long *target, unsigned long cond, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long long shmem_ulonglong_atomic_compare_swap(unsigned long long *target, unsigned long long cond, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES int32_t shmem_int32_atomic_compare_swap(int32_t *target, int32_t cond, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES int64_t shmem_int64_atomic_compare_swap(int64_t *target, int64_t cond, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint32_t shmem_uint32_atomic_compare_swap(uint32_t *target, uint32_t cond, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint64_t shmem_uint64_atomic_compare_swap(uint64_t *target, uint64_t cond, uint64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_size_atomic_compare_swap(size_t *target, size_t cond, size_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES ptrdiff_t shmem_ptrdiff_atomic_compare_swap(ptrdiff_t *target, ptrdiff_t cond, ptrdiff_t value, int pe);

SHMEM_FUNCTION_ATTRIBUTES int shmem_ctx_int_atomic_compare_swap(shmem_ctx_t ctx, int *target, int cond, int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES long shmem_ctx_long_atomic_compare_swap(shmem_ctx_t ctx, long *target, long cond, long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES long long shmem_ctx_longlong_atomic_compare_swap(shmem_ctx_t ctx, long long *target, long long cond, long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned int shmem_ctx_uint_atomic_compare_swap(shmem_ctx_t ctx, unsigned int *target, unsigned int cond, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long shmem_ctx_ulong_atomic_compare_swap(shmem_ctx_t ctx, unsigned long *target, unsigned long cond, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long long shmem_ctx_ulonglong_atomic_compare_swap(shmem_ctx_t ctx, unsigned long long *target, unsigned long long cond, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES int32_t shmem_ctx_int32_atomic_compare_swap(shmem_ctx_t ctx, int32_t *target, int32_t cond, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES int64_t shmem_ctx_int64_atomic_compare_swap(shmem_ctx_t ctx, int64_t *target, int64_t cond, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint32_t shmem_ctx_uint32_atomic_compare_swap(shmem_ctx_t ctx, uint32_t *target, uint32_t cond, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint64_t shmem_ctx_uint64_atomic_compare_swap(shmem_ctx_t ctx, uint64_t *target, uint64_t cond, uint64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ctx_size_atomic_compare_swap(shmem_ctx_t ctx, size_t *target, size_t cond, size_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES ptrdiff_t shmem_ctx_ptrdiff_atomic_compare_swap(shmem_ctx_t ctx, ptrdiff_t *target, ptrdiff_t cond, ptrdiff_t value, int pe);

/* AMO: Atomic Fetch-and-Add Routines */
SHMEM_FUNCTION_ATTRIBUTES int shmem_int_fadd(int *target, int value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES long shmem_long_fadd(long *target, long value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES long long shmem_longlong_fadd(long long *target, long long value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES unsigned int shmem_uint_fadd(unsigned int *target, unsigned int value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES unsigned long shmem_ulong_fadd(unsigned long *target, unsigned long value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES unsigned long long shmem_ulonglong_fadd(unsigned long long *target, unsigned long long value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES int32_t shmem_int32_fadd(int32_t *target, int32_t value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES int64_t shmem_int64_fadd(int64_t *target, int64_t value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES uint32_t shmem_uint32_fadd(uint32_t *target, uint32_t value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES uint64_t shmem_uint64_fadd(uint64_t *target, uint64_t value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_size_fadd(size_t *target, size_t value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES ptrdiff_t shmem_ptrdiff_fadd(ptrdiff_t *target, ptrdiff_t value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;

SHMEM_FUNCTION_ATTRIBUTES int shmem_int_atomic_fetch_add(int *target, int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES long shmem_long_atomic_fetch_add(long *target, long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES long long shmem_longlong_atomic_fetch_add(long long *target, long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned int shmem_uint_atomic_fetch_add(unsigned int *target, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long shmem_ulong_atomic_fetch_add(unsigned long *target, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long long shmem_ulonglong_atomic_fetch_add(unsigned long long *target, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES int32_t shmem_int32_atomic_fetch_add(int32_t *target, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES int64_t shmem_int64_atomic_fetch_add(int64_t *target, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint32_t shmem_uint32_atomic_fetch_add(uint32_t *target, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint64_t shmem_uint64_atomic_fetch_add(uint64_t *target, uint64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_size_atomic_fetch_add(size_t *target, size_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES ptrdiff_t shmem_ptrdiff_atomic_fetch_add(ptrdiff_t *target, ptrdiff_t value, int pe);

SHMEM_FUNCTION_ATTRIBUTES int shmem_ctx_int_atomic_fetch_add(shmem_ctx_t ctx, int *target, int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES long shmem_ctx_long_atomic_fetch_add(shmem_ctx_t ctx, long *target, long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES long long shmem_ctx_longlong_atomic_fetch_add(shmem_ctx_t ctx, long long *target, long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned int shmem_ctx_uint_atomic_fetch_add(shmem_ctx_t ctx, unsigned int *target, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long shmem_ctx_ulong_atomic_fetch_add(shmem_ctx_t ctx, unsigned long *target, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long long shmem_ctx_ulonglong_atomic_fetch_add(shmem_ctx_t ctx, unsigned long long *target, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES int32_t shmem_ctx_int32_atomic_fetch_add(shmem_ctx_t ctx, int32_t *target, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES int64_t shmem_ctx_int64_atomic_fetch_add(shmem_ctx_t ctx, int64_t *target, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint32_t shmem_ctx_uint32_atomic_fetch_add(shmem_ctx_t ctx, uint32_t *target, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint64_t shmem_ctx_uint64_atomic_fetch_add(shmem_ctx_t ctx, uint64_t *target, uint64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ctx_size_atomic_fetch_add(shmem_ctx_t ctx, size_t *target, size_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES ptrdiff_t shmem_ctx_ptrdiff_atomic_fetch_add(shmem_ctx_t ctx, ptrdiff_t *target, ptrdiff_t value, int pe);

/* AMO: Atomic Fetch-and-Increment Routines */
SHMEM_FUNCTION_ATTRIBUTES int shmem_int_finc(int *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES long shmem_long_finc(long *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES long long shmem_longlong_finc(long long *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES unsigned int shmem_uint_finc(unsigned int *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES unsigned long shmem_ulong_finc(unsigned long *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES unsigned long long shmem_ulonglong_finc(unsigned long long *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES int32_t shmem_int32_finc(int32_t *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES int64_t shmem_int64_finc(int64_t *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES uint32_t shmem_uint32_finc(uint32_t *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES uint64_t shmem_uint64_finc(uint64_t *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_size_finc(size_t *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES ptrdiff_t shmem_ptrdiff_finc(ptrdiff_t *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;

SHMEM_FUNCTION_ATTRIBUTES int shmem_int_atomic_fetch_inc(int *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES long shmem_long_atomic_fetch_inc(long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES long long shmem_longlong_atomic_fetch_inc(long long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned int shmem_uint_atomic_fetch_inc(unsigned int *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long shmem_ulong_atomic_fetch_inc(unsigned long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long long shmem_ulonglong_atomic_fetch_inc(unsigned long long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES int32_t shmem_int32_atomic_fetch_inc(int32_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES int64_t shmem_int64_atomic_fetch_inc(int64_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint32_t shmem_uint32_atomic_fetch_inc(uint32_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint64_t shmem_uint64_atomic_fetch_inc(uint64_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_size_atomic_fetch_inc(size_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES ptrdiff_t shmem_ptrdiff_atomic_fetch_inc(ptrdiff_t *target, int pe);

SHMEM_FUNCTION_ATTRIBUTES int shmem_ctx_int_atomic_fetch_inc(shmem_ctx_t ctx, int *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES long shmem_ctx_long_atomic_fetch_inc(shmem_ctx_t ctx, long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES long long shmem_ctx_longlong_atomic_fetch_inc(shmem_ctx_t ctx, long long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned int shmem_ctx_uint_atomic_fetch_inc(shmem_ctx_t ctx, unsigned int *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long shmem_ctx_ulong_atomic_fetch_inc(shmem_ctx_t ctx, unsigned long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long long shmem_ctx_ulonglong_atomic_fetch_inc(shmem_ctx_t ctx, unsigned long long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES int32_t shmem_ctx_int32_atomic_fetch_inc(shmem_ctx_t ctx, int32_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES int64_t shmem_ctx_int64_atomic_fetch_inc(shmem_ctx_t ctx, int64_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint32_t shmem_ctx_uint32_atomic_fetch_inc(shmem_ctx_t ctx, uint32_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint64_t shmem_ctx_uint64_atomic_fetch_inc(shmem_ctx_t ctx, uint64_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ctx_size_atomic_fetch_inc(shmem_ctx_t ctx, size_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES ptrdiff_t shmem_ctx_ptrdiff_atomic_fetch_inc(shmem_ctx_t ctx, ptrdiff_t *target, int pe);

/* AMO: Atomic Add Routines */
SHMEM_FUNCTION_ATTRIBUTES void shmem_int_add(int *target, int value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_add(long *target, long value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_add(long long *target, long long value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint_add(unsigned int *target, unsigned int value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulong_add(unsigned long *target, unsigned long value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulonglong_add(unsigned long long *target, unsigned long long value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_int32_add(int32_t *target, int32_t value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_int64_add(int64_t *target, int64_t value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint32_add(uint32_t *target, uint32_t value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint64_add(uint64_t *target, uint64_t value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_size_add(size_t *target, size_t value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_ptrdiff_add(ptrdiff_t *target, ptrdiff_t value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;

SHMEM_FUNCTION_ATTRIBUTES void shmem_int_atomic_add(int *target, int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_atomic_add(long *target, long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_atomic_add(long long *target, long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint_atomic_add(unsigned int *target, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulong_atomic_add(unsigned long *target, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulonglong_atomic_add(unsigned long long *target, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int32_atomic_add(int32_t *target, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int64_atomic_add(int64_t *target, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint32_atomic_add(uint32_t *target, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint64_atomic_add(uint64_t *target, uint64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_size_atomic_add(size_t *target, size_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ptrdiff_atomic_add(ptrdiff_t *target, ptrdiff_t value, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int_atomic_add(shmem_ctx_t ctx, int *target, int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_long_atomic_add(shmem_ctx_t ctx, long *target, long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_longlong_atomic_add(shmem_ctx_t ctx, long long *target, long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint_atomic_add(shmem_ctx_t ctx, unsigned int *target, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulong_atomic_add(shmem_ctx_t ctx, unsigned long *target, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulonglong_atomic_add(shmem_ctx_t ctx, unsigned long long *target, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int32_atomic_add(shmem_ctx_t ctx, int32_t *target, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int64_atomic_add(shmem_ctx_t ctx, int64_t *target, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint32_atomic_add(shmem_ctx_t ctx, uint32_t *target, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint64_atomic_add(shmem_ctx_t ctx, uint64_t *target, uint64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_size_atomic_add(shmem_ctx_t ctx, size_t *target, size_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ptrdiff_atomic_add(shmem_ctx_t ctx, ptrdiff_t *target, ptrdiff_t value, int pe);

/* AMO: Atomic Increment Routines */
SHMEM_FUNCTION_ATTRIBUTES void shmem_int_inc(int *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_inc(long *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_inc(long long *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint_inc(unsigned int *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulong_inc(unsigned long *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulonglong_inc(unsigned long long *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_int32_inc(int32_t *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_int64_inc(int64_t *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint32_inc(uint32_t *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint64_inc(uint64_t *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_size_inc(size_t *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_ptrdiff_inc(ptrdiff_t *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;

SHMEM_FUNCTION_ATTRIBUTES void shmem_int_atomic_inc(int *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_atomic_inc(long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_atomic_inc(long long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint_atomic_inc(unsigned int *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulong_atomic_inc(unsigned long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulonglong_atomic_inc(unsigned long long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int32_atomic_inc(int32_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int64_atomic_inc(int64_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint32_atomic_inc(uint32_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint64_atomic_inc(uint64_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_size_atomic_inc(size_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ptrdiff_atomic_inc(ptrdiff_t *target, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int_atomic_inc(shmem_ctx_t ctx, int *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_long_atomic_inc(shmem_ctx_t ctx, long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_longlong_atomic_inc(shmem_ctx_t ctx, long long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint_atomic_inc(shmem_ctx_t ctx, unsigned int *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulong_atomic_inc(shmem_ctx_t ctx, unsigned long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulonglong_atomic_inc(shmem_ctx_t ctx, unsigned long long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int32_atomic_inc(shmem_ctx_t ctx, int32_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int64_atomic_inc(shmem_ctx_t ctx, int64_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint32_atomic_inc(shmem_ctx_t ctx, uint32_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint64_atomic_inc(shmem_ctx_t ctx, uint64_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_size_atomic_inc(shmem_ctx_t ctx, size_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ptrdiff_atomic_inc(shmem_ctx_t ctx, ptrdiff_t *target, int pe);

/* AMO: Atomic Fetch Routines */
SHMEM_FUNCTION_ATTRIBUTES int shmem_int_fetch(const int *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES long shmem_long_fetch(const long *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES long long shmem_longlong_fetch(const long long *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES unsigned int shmem_uint_fetch(const unsigned int *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES unsigned long shmem_ulong_fetch(const unsigned long *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES unsigned long long shmem_ulonglong_fetch(const unsigned long long *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES int32_t shmem_int32_fetch(const int32_t *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES int64_t shmem_int64_fetch(const int64_t *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES uint32_t shmem_uint32_fetch(const uint32_t *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES uint64_t shmem_uint64_fetch(const uint64_t *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_size_fetch(const size_t *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES ptrdiff_t shmem_ptrdiff_fetch(const ptrdiff_t *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES float shmem_float_fetch(const float *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES double shmem_double_fetch(const double *target, int pe) SHMEM_ATTRIBUTE_DEPRECATED;

SHMEM_FUNCTION_ATTRIBUTES int shmem_int_atomic_fetch(const int *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES long shmem_long_atomic_fetch(const long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES long long shmem_longlong_atomic_fetch(const long long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned int shmem_uint_atomic_fetch(const unsigned int *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long shmem_ulong_atomic_fetch(const unsigned long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long long shmem_ulonglong_atomic_fetch(const unsigned long long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES int32_t shmem_int32_atomic_fetch(const int32_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES int64_t shmem_int64_atomic_fetch(const int64_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint32_t shmem_uint32_atomic_fetch(const uint32_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint64_t shmem_uint64_atomic_fetch(const uint64_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_size_atomic_fetch(const size_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES ptrdiff_t shmem_ptrdiff_atomic_fetch(const ptrdiff_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES float shmem_float_atomic_fetch(const float *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES double shmem_double_atomic_fetch(const double *target, int pe);

SHMEM_FUNCTION_ATTRIBUTES int shmem_ctx_int_atomic_fetch(shmem_ctx_t ctx, const int *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES long shmem_ctx_long_atomic_fetch(shmem_ctx_t ctx, const long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES long long shmem_ctx_longlong_atomic_fetch(shmem_ctx_t ctx, const long long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned int shmem_ctx_uint_atomic_fetch(shmem_ctx_t ctx, const unsigned int *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long shmem_ctx_ulong_atomic_fetch(shmem_ctx_t ctx, const unsigned long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long long shmem_ctx_ulonglong_atomic_fetch(shmem_ctx_t ctx, const unsigned long long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES int32_t shmem_ctx_int32_atomic_fetch(shmem_ctx_t ctx, const int32_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES int64_t shmem_ctx_int64_atomic_fetch(shmem_ctx_t ctx, const int64_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint32_t shmem_ctx_uint32_atomic_fetch(shmem_ctx_t ctx, const uint32_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint64_t shmem_ctx_uint64_atomic_fetch(shmem_ctx_t ctx, const uint64_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ctx_size_atomic_fetch(shmem_ctx_t ctx, const size_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES ptrdiff_t shmem_ctx_ptrdiff_atomic_fetch(shmem_ctx_t ctx, const ptrdiff_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES float shmem_ctx_float_atomic_fetch(shmem_ctx_t ctx, const float *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES double shmem_ctx_double_atomic_fetch(shmem_ctx_t ctx, const double *target, int pe);

/* AMO: Atomic Set Routines */
SHMEM_FUNCTION_ATTRIBUTES void shmem_int_set(int *target, int value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_set(long *target, long value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_set(long long *target, long long value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint_set(unsigned int *target, unsigned int value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulong_set(unsigned long *target, unsigned long value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulonglong_set(unsigned long long *target, unsigned long long value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_int32_set(int32_t *target, int32_t value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_int64_set(int64_t *target, int64_t value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint32_set(uint32_t *target, uint32_t value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint64_set(uint64_t *target, uint64_t value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_size_set(size_t *target, size_t value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_ptrdiff_set(ptrdiff_t *target, ptrdiff_t value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_float_set(float *target, float value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_double_set(double *target, double value, int pe) SHMEM_ATTRIBUTE_DEPRECATED;

SHMEM_FUNCTION_ATTRIBUTES void shmem_int_atomic_set(int *target, int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_atomic_set(long *target, long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_atomic_set(long long *target, long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint_atomic_set(unsigned int *target, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulong_atomic_set(unsigned long *target, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulonglong_atomic_set(unsigned long long *target, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int32_atomic_set(int32_t *target, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int64_atomic_set(int64_t *target, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint32_atomic_set(uint32_t *target, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint64_atomic_set(uint64_t *target, uint64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_size_atomic_set(size_t *target, size_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ptrdiff_atomic_set(ptrdiff_t *target, ptrdiff_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_float_atomic_set(float *target, float value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_double_atomic_set(double *target, double value, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int_atomic_set(shmem_ctx_t ctx, int *target, int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_long_atomic_set(shmem_ctx_t ctx, long *target, long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_longlong_atomic_set(shmem_ctx_t ctx, long long *target, long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint_atomic_set(shmem_ctx_t ctx, unsigned int *target, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulong_atomic_set(shmem_ctx_t ctx, unsigned long *target, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulonglong_atomic_set(shmem_ctx_t ctx, unsigned long long *target, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int32_atomic_set(shmem_ctx_t ctx, int32_t *target, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int64_atomic_set(shmem_ctx_t ctx, int64_t *target, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint32_atomic_set(shmem_ctx_t ctx, uint32_t *target, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint64_atomic_set(shmem_ctx_t ctx, uint64_t *target, uint64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_size_atomic_set(shmem_ctx_t ctx, size_t *target, size_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ptrdiff_atomic_set(shmem_ctx_t ctx, ptrdiff_t *target, ptrdiff_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_float_atomic_set(shmem_ctx_t ctx, float *target, float value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_double_atomic_set(shmem_ctx_t ctx, double *target, double value, int pe);

/* AMO: Atomic Bitwise Routines */
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint_atomic_xor(unsigned int *target, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulong_atomic_xor(unsigned long *target, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulonglong_atomic_xor(unsigned long long *target, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int32_atomic_xor(int32_t *target, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int64_atomic_xor(int64_t *target, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint32_atomic_xor(uint32_t *target, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint64_atomic_xor(uint64_t *target, uint64_t value, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint_atomic_xor(shmem_ctx_t ctx, unsigned int *target, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulong_atomic_xor(shmem_ctx_t ctx, unsigned long *target, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulonglong_atomic_xor(shmem_ctx_t ctx, unsigned long long *target, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int32_atomic_xor(shmem_ctx_t ctx, int32_t *target, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int64_atomic_xor(shmem_ctx_t ctx, int64_t *target, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint32_atomic_xor(shmem_ctx_t ctx, uint32_t *target, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint64_atomic_xor(shmem_ctx_t ctx, uint64_t *target, uint64_t value, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_uint_atomic_and(unsigned int *target, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulong_atomic_and(unsigned long *target, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulonglong_atomic_and(unsigned long long *target, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int32_atomic_and(int32_t *target, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int64_atomic_and(int64_t *target, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint32_atomic_and(uint32_t *target, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint64_atomic_and(uint64_t *target, uint64_t value, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint_atomic_and(shmem_ctx_t ctx, unsigned int *target, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulong_atomic_and(shmem_ctx_t ctx, unsigned long *target, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulonglong_atomic_and(shmem_ctx_t ctx, unsigned long long *target, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int32_atomic_and(shmem_ctx_t ctx, int32_t *target, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int64_atomic_and(shmem_ctx_t ctx, int64_t *target, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint32_atomic_and(shmem_ctx_t ctx, uint32_t *target, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint64_atomic_and(shmem_ctx_t ctx, uint64_t *target, uint64_t value, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_uint_atomic_or(unsigned int *target, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulong_atomic_or(unsigned long *target, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulonglong_atomic_or(unsigned long long *target, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int32_atomic_or(int32_t *target, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int64_atomic_or(int64_t *target, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint32_atomic_or(uint32_t *target, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint64_atomic_or(uint64_t *target, uint64_t value, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint_atomic_or(shmem_ctx_t ctx, unsigned int *target, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulong_atomic_or(shmem_ctx_t ctx, unsigned long *target, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulonglong_atomic_or(shmem_ctx_t ctx, unsigned long long *target, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int32_atomic_or(shmem_ctx_t ctx, int32_t *target, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int64_atomic_or(shmem_ctx_t ctx, int64_t *target, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint32_atomic_or(shmem_ctx_t ctx, uint32_t *target, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint64_atomic_or(shmem_ctx_t ctx, uint64_t *target, uint64_t value, int pe);

/* AMO: Fetching atomic Bitwise Routines */
SHMEM_FUNCTION_ATTRIBUTES unsigned int shmem_uint_atomic_fetch_xor(unsigned int *target, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long shmem_ulong_atomic_fetch_xor(unsigned long *target, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long long shmem_ulonglong_atomic_fetch_xor(unsigned long long *target, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES int32_t shmem_int32_atomic_fetch_xor(int32_t *target, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES int64_t shmem_int64_atomic_fetch_xor(int64_t *target, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint32_t shmem_uint32_atomic_fetch_xor(uint32_t *target, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint64_t shmem_uint64_atomic_fetch_xor(uint64_t *target, uint64_t value, int pe);

SHMEM_FUNCTION_ATTRIBUTES unsigned int shmem_ctx_uint_atomic_fetch_xor(shmem_ctx_t ctx, unsigned int *target, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long shmem_ctx_ulong_atomic_fetch_xor(shmem_ctx_t ctx, unsigned long *target, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long long shmem_ctx_ulonglong_atomic_fetch_xor(shmem_ctx_t ctx, unsigned long long *target, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES int32_t shmem_ctx_int32_atomic_fetch_xor(shmem_ctx_t ctx, int32_t *target, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES int64_t shmem_ctx_int64_atomic_fetch_xor(shmem_ctx_t ctx, int64_t *target, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint32_t shmem_ctx_uint32_atomic_fetch_xor(shmem_ctx_t ctx, uint32_t *target, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint64_t shmem_ctx_uint64_atomic_fetch_xor(shmem_ctx_t ctx, uint64_t *target, uint64_t value, int pe);

SHMEM_FUNCTION_ATTRIBUTES unsigned int shmem_uint_atomic_fetch_and(unsigned int *target, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long shmem_ulong_atomic_fetch_and(unsigned long *target, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long long shmem_ulonglong_atomic_fetch_and(unsigned long long *target, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES int32_t shmem_int32_atomic_fetch_and(int32_t *target, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES int64_t shmem_int64_atomic_fetch_and(int64_t *target, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint32_t shmem_uint32_atomic_fetch_and(uint32_t *target, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint64_t shmem_uint64_atomic_fetch_and(uint64_t *target, uint64_t value, int pe);

SHMEM_FUNCTION_ATTRIBUTES unsigned int shmem_ctx_uint_atomic_fetch_and(shmem_ctx_t ctx, unsigned int *target, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long shmem_ctx_ulong_atomic_fetch_and(shmem_ctx_t ctx, unsigned long *target, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long long shmem_ctx_ulonglong_atomic_fetch_and(shmem_ctx_t ctx, unsigned long long *target, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES int32_t shmem_ctx_int32_atomic_fetch_and(shmem_ctx_t ctx, int32_t *target, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES int64_t shmem_ctx_int64_atomic_fetch_and(shmem_ctx_t ctx, int64_t *target, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint32_t shmem_ctx_uint32_atomic_fetch_and(shmem_ctx_t ctx, uint32_t *target, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint64_t shmem_ctx_uint64_atomic_fetch_and(shmem_ctx_t ctx, uint64_t *target, uint64_t value, int pe);

SHMEM_FUNCTION_ATTRIBUTES unsigned int shmem_uint_atomic_fetch_or(unsigned int *target, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long shmem_ulong_atomic_fetch_or(unsigned long *target, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long long shmem_ulonglong_atomic_fetch_or(unsigned long long *target, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES int32_t shmem_int32_atomic_fetch_or(int32_t *target, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES int64_t shmem_int64_atomic_fetch_or(int64_t *target, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint32_t shmem_uint32_atomic_fetch_or(uint32_t *target, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint64_t shmem_uint64_atomic_fetch_or(uint64_t *target, uint64_t value, int pe);

SHMEM_FUNCTION_ATTRIBUTES unsigned int shmem_ctx_uint_atomic_fetch_or(shmem_ctx_t ctx, unsigned int *target, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long shmem_ctx_ulong_atomic_fetch_or(shmem_ctx_t ctx, unsigned long *target, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES unsigned long long shmem_ctx_ulonglong_atomic_fetch_or(shmem_ctx_t ctx, unsigned long long *target, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES int32_t shmem_ctx_int32_atomic_fetch_or(shmem_ctx_t ctx, int32_t *target, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES int64_t shmem_ctx_int64_atomic_fetch_or(shmem_ctx_t ctx, int64_t *target, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint32_t shmem_ctx_uint32_atomic_fetch_or(shmem_ctx_t ctx, uint32_t *target, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES uint64_t shmem_ctx_uint64_atomic_fetch_or(shmem_ctx_t ctx, uint64_t *target, uint64_t value, int pe);

/* COLL: Barrier Synchronization Routines */
SHMEM_FUNCTION_ATTRIBUTES void shmem_barrier(int PE_start, int logPE_stride, int PE_size, long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_barrier_all(void);
SHMEM_FUNCTION_ATTRIBUTES void shmem_sync(int PE_start, int logPE_stride, int PE_size, long *pSync);
SHMEM_FUNCTION_ATTRIBUTES void shmem_sync_all(void);

/* COLL: Reduction Routines */
SHMEM_FUNCTION_ATTRIBUTES void shmem_short_and_to_all(short *target,
                            const short *source, int nreduce,
                            int PE_start, int logPE_stride,
                            int PE_size, short *pWrk,
                            long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_int_and_to_all(int *target,
                          const int *source, int nreduce,
                          int PE_start, int logPE_stride,
                          int PE_size, int *pWrk,
                          long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_and_to_all(long *target,
                           const long *source, int nreduce,
                           int PE_start, int logPE_stride,
                           int PE_size, long *pWrk,
                           long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_and_to_all(long long *target,
                               const long long *source, int nreduce,
                               int PE_start, int logPE_stride,
                               int PE_size, long long *pWrk,
                               long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;

SHMEM_FUNCTION_ATTRIBUTES void shmem_short_or_to_all(short *target,
                           const short *source, int nreduce,
                           int PE_start, int logPE_stride,
                           int PE_size, short *pWrk,
                           long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_int_or_to_all(int *target,
                         const int *source, int nreduce,
                         int PE_start, int logPE_stride,
                         int PE_size, int *pWrk,
                         long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_or_to_all(long *target,
                          const long *source, int nreduce,
                          int PE_start, int logPE_stride,
                          int PE_size, long *pWrk,
                          long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_or_to_all(long long *target,
                              const long long *source, int nreduce,
                              int PE_start, int logPE_stride,
                              int PE_size, long long *pWrk,
                              long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;

SHMEM_FUNCTION_ATTRIBUTES void shmem_short_xor_to_all(short *target,
                            const short *source, int nreduce,
                            int PE_start, int logPE_stride,
                            int PE_size, short *pWrk,
                            long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_int_xor_to_all(int *target,
                          const int *source, int nreduce,
                          int PE_start, int logPE_stride,
                          int PE_size, int *pWrk,
                          long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_xor_to_all(long *target,
                           const long *source, int nreduce,
                           int PE_start, int logPE_stride,
                           int PE_size, long *pWrk,
                           long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_xor_to_all(long long *target,
                               const long long *source, int nreduce,
                               int PE_start, int logPE_stride,
                               int PE_size, long long *pWrk,
                               long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;

SHMEM_FUNCTION_ATTRIBUTES void shmem_short_min_to_all(short *target,
                            const short *source, int nreduce,
                            int PE_start, int logPE_stride,
                            int PE_size, short *pWrk,
                            long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_int_min_to_all(int *target,
                          const int *source, int nreduce,
                          int PE_start, int logPE_stride,
                          int PE_size, int *pWrk,
                          long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_min_to_all(long *target,
                           const long *source, int nreduce,
                           int PE_start, int logPE_stride,
                           int PE_size, long *pWrk,
                           long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_min_to_all(long long *target,
                               const long long *source, int nreduce,
                               int PE_start, int logPE_stride,
                               int PE_size, long long *pWrk,
                               long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_float_min_to_all(float *target,
                            const float *source, int nreduce,
                            int PE_start, int logPE_stride,
                            int PE_size, float *pWrk,
                            long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_double_min_to_all(double *target,
                             const double *source, int nreduce,
                             int PE_start, int logPE_stride,
                             int PE_size, double *pWrk,
                             long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_longdouble_min_to_all(long double *target,
                                 const long double *source, int nreduce,
                                 int PE_start, int logPE_stride,
                                 int PE_size, long double *pWrk,
                                 long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;

SHMEM_FUNCTION_ATTRIBUTES void shmem_short_max_to_all(short *target,
                            const short *source, int nreduce,
                            int PE_start, int logPE_stride,
                            int PE_size, short *pWrk,
                            long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_int_max_to_all(int *target,
                          const int *source, int nreduce,
                          int PE_start, int logPE_stride,
                          int PE_size, int *pWrk,
                          long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_max_to_all(long *target,
                           const long *source, int nreduce,
                           int PE_start, int logPE_stride,
                           int PE_size, long *pWrk,
                           long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_max_to_all(long long *target,
                               const long long *source, int nreduce,
                               int PE_start, int logPE_stride,
                               int PE_size, long long *pWrk,
                               long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_float_max_to_all(float *target,
                            const float *source, int nreduce,
                            int PE_start, int logPE_stride,
                            int PE_size, float *pWrk,
                            long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_double_max_to_all(double *target,
                             const double *source, int nreduce,
                             int PE_start, int logPE_stride,
                             int PE_size, double *pWrk,
                             long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_longdouble_max_to_all(long double *target,
                                 const long double *source, int nreduce,
                                 int PE_start, int logPE_stride,
                                 int PE_size, long double *pWrk,
                                 long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;

SHMEM_FUNCTION_ATTRIBUTES void shmem_short_sum_to_all(short *target,
                            const short *source, int nreduce,
                            int PE_start, int logPE_stride,
                            int PE_size, short *pWrk,
                            long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_int_sum_to_all(int *target,
                          const int *source, int nreduce,
                          int PE_start, int logPE_stride,
                          int PE_size, int *pWrk,
                          long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_sum_to_all(long *target,
                           const long *source, int nreduce,
                           int PE_start, int logPE_stride,
                           int PE_size, long *pWrk,
                           long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_sum_to_all(long long *target,
                               const long long *source, int nreduce,
                               int PE_start, int logPE_stride,
                               int PE_size, long long *pWrk,
                               long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_float_sum_to_all(float *target,
                            const float *source, int nreduce,
                            int PE_start, int logPE_stride,
                            int PE_size, float *pWrk,
                            long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_double_sum_to_all(double *target,
                             const double *source, int nreduce,
                             int PE_start, int logPE_stride,
                             int PE_size, double *pWrk,
                             long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_longdouble_sum_to_all(long double *target,
                                 const long double *source, int nreduce,
                                 int PE_start, int logPE_stride,
                                 int PE_size, long double *pWrk,
                                 long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_complexf_sum_to_all(float _Complex *target,
                               const float _Complex *source, int nreduce,
                               int PE_start, int logPE_stride,
                               int PE_size, float _Complex *pWrk,
                               long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_complexd_sum_to_all(double _Complex *target,
                               const double _Complex *source, int nreduce,
                               int PE_start, int logPE_stride,
                               int PE_size, double _Complex *pWrk,
                               long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;

SHMEM_FUNCTION_ATTRIBUTES void shmem_short_prod_to_all(short *target,
                             const short *source, int nreduce,
                             int PE_start, int logPE_stride,
                             int PE_size, short *pWrk,
                             long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_int_prod_to_all(int *target,
                           const int *source, int nreduce,
                           int PE_start, int logPE_stride,
                           int PE_size, int *pWrk,
                           long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_prod_to_all(long *target,
                            const long *source, int nreduce,
                            int PE_start, int logPE_stride,
                            int PE_size, long *pWrk,
                            long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_prod_to_all(long long *target,
                                const long long *source, int nreduce,
                                int PE_start, int logPE_stride,
                                int PE_size, long long *pWrk,
                                long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_float_prod_to_all(float *target,
                             const float *source, int nreduce,
                             int PE_start, int logPE_stride,
                             int PE_size, float *pWrk,
                             long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_double_prod_to_all(double *target,
                              const double *source, int nreduce,
                              int PE_start, int logPE_stride,
                              int PE_size, double *pWrk,
                              long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_longdouble_prod_to_all(long double *target,
                                  const long double *source, int nreduce,
                                  int PE_start, int logPE_stride,
                                  int PE_size, long double *pWrk,
                                  long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_complexf_prod_to_all(float _Complex *target,
                                const float _Complex *source, int nreduce,
                                int PE_start, int logPE_stride,
                                int PE_size, float _Complex *pWrk,
                                long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_complexd_prod_to_all(double _Complex *target,
                                const double _Complex *source, int nreduce,
                                int PE_start, int logPE_stride,
                                int PE_size, double _Complex *pWrk,
                                long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;

/* COLL: Collect Routines */
SHMEM_FUNCTION_ATTRIBUTES void shmem_collect32(void *target, const void *source, size_t nlong,
                     int PE_start, int logPE_stride, int PE_size, long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_collect64(void *target, const void *source, size_t nlong,
                     int PE_start, int logPE_stride, int PE_size, long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_fcollect32(void *target, const void *source, size_t nlong,
                      int PE_start, int logPE_stride, int PE_size,
                      long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_fcollect64(void *target, const void *source, size_t nlong,
                      int PE_start, int logPE_stride, int PE_size,
                      long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;

/* COLL: Broadcast Routines */
SHMEM_FUNCTION_ATTRIBUTES void shmem_broadcast32(void *target, const void *source, size_t nlong,
                       int PE_root, int PE_start, int logPE_stride,
                       int PE_size, long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_broadcast64(void *target, const void *source, size_t nlong,
                       int PE_root, int PE_start, int logPE_stride,
                       int PE_size, long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;

/* COLL: All-to-All routines */
SHMEM_FUNCTION_ATTRIBUTES void shmem_alltoall32(void *dest, const void *source, size_t nelems, int PE_start,
                      int logPE_stride, int PE_size, long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_alltoall64(void *dest, const void *source, size_t nelems, int PE_start,
                      int logPE_stride, int PE_size, long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;

SHMEM_FUNCTION_ATTRIBUTES void shmem_alltoalls32(void *dest, const void *source, ptrdiff_t dst,
                       ptrdiff_t sst, size_t nelems, int PE_start,
                       int logPE_stride, int PE_size, long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_alltoalls64(void *dest, const void *source, ptrdiff_t dst,
                       ptrdiff_t sst, size_t nelems, int PE_start,
                       int logPE_stride, int PE_size, long *pSync) SHMEM_ATTRIBUTE_DEPRECATED;

/* Point-to-Point Synchronization Routines */
SHMEM_FUNCTION_ATTRIBUTES void shmem_wait(long *ivar, long cmp_value) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_short_wait(short *var, short value) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_int_wait(int *var, int value) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_wait(long *var, long value) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_wait(long long *var, long long value) SHMEM_ATTRIBUTE_DEPRECATED;

SHMEM_FUNCTION_ATTRIBUTES void shmem_short_wait_until(short *var, int cmp, short value);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int_wait_until(int *var, int cmp, int value);
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_wait_until(long *var, int cmp, long value);
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_wait_until(long long *var, int cmp, long long value);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ushort_wait_until(unsigned short *var, int cmp, unsigned short value);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint_wait_until(unsigned int *var, int cmp, unsigned int value);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulong_wait_until(unsigned long *var, int cmp, unsigned long value);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulonglong_wait_until(unsigned long long *var, int cmp, unsigned long long value);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int32_wait_until(int32_t *var, int cmp, int32_t value);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int64_wait_until(int64_t *var, int cmp, int64_t value);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint32_wait_until(uint32_t *var, int cmp, uint32_t value);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint64_wait_until(uint64_t *var, int cmp, uint64_t value);
SHMEM_FUNCTION_ATTRIBUTES void shmem_size_wait_until(size_t *var, int cmp, size_t value);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ptrdiff_wait_until(ptrdiff_t *var, int cmp, ptrdiff_t value);

/* Special case, only enabled when C++ and C11 bindings are disabled */
#if ( !defined(__cplusplus) && \
      !(defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L) ) || \
    defined(SHMEM_INTERNAL_INCLUDE) || defined(SHMEM_DECLARE_SPECIAL_CASES)
SHMEM_FUNCTION_ATTRIBUTES void shmem_wait_until(long *ivar, int cmp, long value);
#endif

SHMEM_FUNCTION_ATTRIBUTES void shmem_short_wait_until_all(short *vars, size_t nelems, const int *status, int cmp, short value);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int_wait_until_all(int *vars, size_t nelems, const int *status, int cmp, int value);
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_wait_until_all(long *vars, size_t nelems, const int *status, int cmp, long value);
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_wait_until_all(long long *vars, size_t nelems, const int *status, int cmp, long long value);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ushort_wait_until_all(unsigned short *vars, size_t nelems, const int *status, int cmp, unsigned short value);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint_wait_until_all(unsigned int *vars, size_t nelems, const int *status, int cmp, unsigned int value);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulong_wait_until_all(unsigned long *vars, size_t nelems, const int *status, int cmp, unsigned long value);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulonglong_wait_until_all(unsigned long long *vars, size_t nelems, const int *status, int cmp, unsigned long long value);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int32_wait_until_all(int32_t *vars, size_t nelems, const int *status, int cmp, int32_t value);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int64_wait_until_all(int64_t *vars, size_t nelems, const int *status, int cmp, int64_t value);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint32_wait_until_all(uint32_t *vars, size_t nelems, const int *status, int cmp, uint32_t value);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint64_wait_until_all(uint64_t *vars, size_t nelems, const int *status, int cmp, uint64_t value);
SHMEM_FUNCTION_ATTRIBUTES void shmem_size_wait_until_all(size_t *vars, size_t nelems, const int *status, int cmp, size_t value);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ptrdiff_wait_until_all(ptrdiff_t *vars, size_t nelems, const int *status, int cmp, ptrdiff_t value);

SHMEM_FUNCTION_ATTRIBUTES size_t shmem_short_wait_until_any(short *vars, size_t nelems, const int *status, int cmp, short value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_int_wait_until_any(int *vars, size_t nelems, const int *status, int cmp, int value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_long_wait_until_any(long *vars, size_t nelems, const int *status, int cmp, long value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_longlong_wait_until_any(long long *vars, size_t nelems, const int *status, int cmp, long long value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ushort_wait_until_any(unsigned short *vars, size_t nelems, const int *status, int cmp, unsigned short value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_uint_wait_until_any(unsigned int *vars, size_t nelems, const int *status, int cmp, unsigned int value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ulong_wait_until_any(unsigned long *vars, size_t nelems, const int *status, int cmp, unsigned long value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ulonglong_wait_until_any(unsigned long long *vars, size_t nelems, const int *status, int cmp, unsigned long long value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_int32_wait_until_any(int32_t *vars, size_t nelems, const int *status, int cmp, int32_t value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_int64_wait_until_any(int64_t *vars, size_t nelems, const int *status, int cmp, int64_t value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_uint32_wait_until_any(uint32_t *vars, size_t nelems, const int *status, int cmp, uint32_t value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_uint64_wait_until_any(uint64_t *vars, size_t nelems, const int *status, int cmp, uint64_t value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_size_wait_until_any(size_t *vars, size_t nelems, const int *status, int cmp, size_t value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ptrdiff_wait_until_any(ptrdiff_t *vars, size_t nelems, const int *status, int cmp, ptrdiff_t value);

SHMEM_FUNCTION_ATTRIBUTES size_t shmem_short_wait_until_some(short *vars, size_t nelems, size_t *indices, const int *status, int cmp, short value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_int_wait_until_some(int *vars, size_t nelems, size_t *indices, const int *status, int cmp, int value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_long_wait_until_some(long *vars, size_t nelems, size_t *indices, const int *status, int cmp, long value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_longlong_wait_until_some(long long *vars, size_t nelems, size_t *indices, const int *status, int cmp, long long value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ushort_wait_until_some(unsigned short *vars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned short value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_uint_wait_until_some(unsigned int *vars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned int value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ulong_wait_until_some(unsigned long *vars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned long value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ulonglong_wait_until_some(unsigned long long *vars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned long long value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_int32_wait_until_some(int32_t *vars, size_t nelems, size_t *indices, const int *status, int cmp, int32_t value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_int64_wait_until_some(int64_t *vars, size_t nelems, size_t *indices, const int *status, int cmp, int64_t value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_uint32_wait_until_some(uint32_t *vars, size_t nelems, size_t *indices, const int *status, int cmp, uint32_t value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_uint64_wait_until_some(uint64_t *vars, size_t nelems, size_t *indices, const int *status, int cmp, uint64_t value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_size_wait_until_some(size_t *vars, size_t nelems, size_t *indices, const int *status, int cmp, size_t value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ptrdiff_wait_until_some(ptrdiff_t *vars, size_t nelems, size_t *indices, const int *status, int cmp, ptrdiff_t value);

SHMEM_FUNCTION_ATTRIBUTES void shmem_short_wait_until_all_vector(short *vars, size_t nelems, const int *status, int cmp, short *values);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int_wait_until_all_vector(int *vars, size_t nelems, const int *status, int cmp, int *values);
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_wait_until_all_vector(long *vars, size_t nelems, const int *status, int cmp, long *values);
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_wait_until_all_vector(long long *vars, size_t nelems, const int *status, int cmp, long long *values);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ushort_wait_until_all_vector(unsigned short *vars, size_t nelems, const int *status, int cmp, unsigned short *values);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint_wait_until_all_vector(unsigned int *vars, size_t nelems, const int *status, int cmp, unsigned int *values);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulong_wait_until_all_vector(unsigned long *vars, size_t nelems, const int *status, int cmp, unsigned long *values);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulonglong_wait_until_all_vector(unsigned long long *vars, size_t nelems, const int *status, int cmp, unsigned long long *values);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int32_wait_until_all_vector(int32_t *vars, size_t nelems, const int *status, int cmp, int32_t *values);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int64_wait_until_all_vector(int64_t *vars, size_t nelems, const int *status, int cmp, int64_t *values);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint32_wait_until_all_vector(uint32_t *vars, size_t nelems, const int *status, int cmp, uint32_t *values);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint64_wait_until_all_vector(uint64_t *vars, size_t nelems, const int *status, int cmp, uint64_t *values);
SHMEM_FUNCTION_ATTRIBUTES void shmem_size_wait_until_all_vector(size_t *vars, size_t nelems, const int *status, int cmp, size_t *values);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ptrdiff_wait_until_all_vector(ptrdiff_t *vars, size_t nelems, const int *status, int cmp, ptrdiff_t *values);

SHMEM_FUNCTION_ATTRIBUTES size_t shmem_short_wait_until_any_vector(short *vars, size_t nelems, const int *status, int cmp, short *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_int_wait_until_any_vector(int *vars, size_t nelems, const int *status, int cmp, int *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_long_wait_until_any_vector(long *vars, size_t nelems, const int *status, int cmp, long *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_longlong_wait_until_any_vector(long long *vars, size_t nelems, const int *status, int cmp, long long *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ushort_wait_until_any_vector(unsigned short *vars, size_t nelems, const int *status, int cmp, unsigned short *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_uint_wait_until_any_vector(unsigned int *vars, size_t nelems, const int *status, int cmp, unsigned int *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ulong_wait_until_any_vector(unsigned long *vars, size_t nelems, const int *status, int cmp, unsigned long *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ulonglong_wait_until_any_vector(unsigned long long *vars, size_t nelems, const int *status, int cmp, unsigned long long *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_int32_wait_until_any_vector(int32_t *vars, size_t nelems, const int *status, int cmp, int32_t *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_int64_wait_until_any_vector(int64_t *vars, size_t nelems, const int *status, int cmp, int64_t *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_uint32_wait_until_any_vector(uint32_t *vars, size_t nelems, const int *status, int cmp, uint32_t *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_uint64_wait_until_any_vector(uint64_t *vars, size_t nelems, const int *status, int cmp, uint64_t *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_size_wait_until_any_vector(size_t *vars, size_t nelems, const int *status, int cmp, size_t *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ptrdiff_wait_until_any_vector(ptrdiff_t *vars, size_t nelems, const int *status, int cmp, ptrdiff_t *values);

SHMEM_FUNCTION_ATTRIBUTES size_t shmem_short_wait_until_some_vector(short *vars, size_t nelems, size_t *indices, const int *status, int cmp, short *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_int_wait_until_some_vector(int *vars, size_t nelems, size_t *indices, const int *status, int cmp, int *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_long_wait_until_some_vector(long *vars, size_t nelems, size_t *indices, const int *status, int cmp, long *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_longlong_wait_until_some_vector(long long *vars, size_t nelems, size_t *indices, const int *status, int cmp, long long *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ushort_wait_until_some_vector(unsigned short *vars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned short *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_uint_wait_until_some_vector(unsigned int *vars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned int *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ulong_wait_until_some_vector(unsigned long *vars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned long *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ulonglong_wait_until_some_vector(unsigned long long *vars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned long long *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_int32_wait_until_some_vector(int32_t *vars, size_t nelems, size_t *indices, const int *status, int cmp, int32_t *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_int64_wait_until_some_vector(int64_t *vars, size_t nelems, size_t *indices, const int *status, int cmp, int64_t *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_uint32_wait_until_some_vector(uint32_t *vars, size_t nelems, size_t *indices, const int *status, int cmp, uint32_t *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_uint64_wait_until_some_vector(uint64_t *vars, size_t nelems, size_t *indices, const int *status, int cmp, uint64_t *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_size_wait_until_some_vector(size_t *vars, size_t nelems, size_t *indices, const int *status, int cmp, size_t *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ptrdiff_wait_until_some_vector(ptrdiff_t *vars, size_t nelems, size_t *indices, const int *status, int cmp, ptrdiff_t *values);

SHMEM_FUNCTION_ATTRIBUTES int shmem_short_test(short *var, int cmp, short value);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int_test(int *var, int cmp, int value);
SHMEM_FUNCTION_ATTRIBUTES int shmem_long_test(long *var, int cmp, long value);
SHMEM_FUNCTION_ATTRIBUTES int shmem_longlong_test(long long *var, int cmp, long long value);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ushort_test(unsigned short *var, int cmp, unsigned short value);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint_test(unsigned int *var, int cmp, unsigned int value);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ulong_test(unsigned long *var, int cmp, unsigned long value);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ulonglong_test(unsigned long long *var, int cmp, unsigned long long value);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int32_test(int32_t *var, int cmp, int32_t value);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int64_test(int64_t *var, int cmp, int64_t value);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint32_test(uint32_t *var, int cmp, uint32_t value);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint64_test(uint64_t *var, int cmp, uint64_t value);
SHMEM_FUNCTION_ATTRIBUTES int shmem_size_test(size_t *var, int cmp, size_t value);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ptrdiff_test(ptrdiff_t *var, int cmp, ptrdiff_t value);

SHMEM_FUNCTION_ATTRIBUTES int shmem_short_test_all(short *vars, size_t nelems, const int *status, int cmp, short value);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int_test_all(int *vars, size_t nelems, const int *status, int cmp, int value);
SHMEM_FUNCTION_ATTRIBUTES int shmem_long_test_all(long *vars, size_t nelems, const int *status, int cmp, long value);
SHMEM_FUNCTION_ATTRIBUTES int shmem_longlong_test_all(long long *vars, size_t nelems, const int *status, int cmp, long long value);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ushort_test_all(unsigned short *vars, size_t nelems, const int *status, int cmp, unsigned short value);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint_test_all(unsigned int *vars, size_t nelems, const int *status, int cmp, unsigned int value);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ulong_test_all(unsigned long *vars, size_t nelems, const int *status, int cmp, unsigned long value);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ulonglong_test_all(unsigned long long *vars, size_t nelems, const int *status, int cmp, unsigned long long value);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int32_test_all(int32_t *vars, size_t nelems, const int *status, int cmp, int32_t value);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int64_test_all(int64_t *vars, size_t nelems, const int *status, int cmp, int64_t value);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint32_test_all(uint32_t *vars, size_t nelems, const int *status, int cmp, uint32_t value);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint64_test_all(uint64_t *vars, size_t nelems, const int *status, int cmp, uint64_t value);
SHMEM_FUNCTION_ATTRIBUTES int shmem_size_test_all(size_t *vars, size_t nelems, const int *status, int cmp, size_t value);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ptrdiff_test_all(ptrdiff_t *vars, size_t nelems, const int *status, int cmp, ptrdiff_t value);

SHMEM_FUNCTION_ATTRIBUTES size_t shmem_short_test_any(short *vars, size_t nelems, const int *status, int cmp, short value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_int_test_any(int *vars, size_t nelems, const int *status, int cmp, int value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_long_test_any(long *vars, size_t nelems, const int *status, int cmp, long value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_longlong_test_any(long long *vars, size_t nelems, const int *status, int cmp, long long value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ushort_test_any(unsigned short *vars, size_t nelems, const int *status, int cmp, unsigned short value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_uint_test_any(unsigned int *vars, size_t nelems, const int *status, int cmp, unsigned int value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ulong_test_any(unsigned long *vars, size_t nelems, const int *status, int cmp, unsigned long value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ulonglong_test_any(unsigned long long *vars, size_t nelems, const int *status, int cmp, unsigned long long value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_int32_test_any(int32_t *vars, size_t nelems, const int *status, int cmp, int32_t value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_int64_test_any(int64_t *vars, size_t nelems, const int *status, int cmp, int64_t value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_uint32_test_any(uint32_t *vars, size_t nelems, const int *status, int cmp, uint32_t value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_uint64_test_any(uint64_t *vars, size_t nelems, const int *status, int cmp, uint64_t value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_size_test_any(size_t *vars, size_t nelems, const int *status, int cmp, size_t value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ptrdiff_test_any(ptrdiff_t *vars, size_t nelems, const int *status, int cmp, ptrdiff_t value);

SHMEM_FUNCTION_ATTRIBUTES size_t shmem_short_test_some(short *vars, size_t nelems, size_t *indices, const int *status, int cmp, short value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_int_test_some(int *vars, size_t nelems, size_t *indices, const int *status, int cmp, int value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_long_test_some(long *vars, size_t nelems, size_t *indices, const int *status, int cmp, long value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_longlong_test_some(long long *vars, size_t nelems, size_t *indices, const int *status, int cmp, long long value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ushort_test_some(unsigned short *vars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned short value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_uint_test_some(unsigned int *vars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned int value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ulong_test_some(unsigned long *vars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned long value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ulonglong_test_some(unsigned long long *vars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned long long value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_int32_test_some(int32_t *vars, size_t nelems, size_t *indices, const int *status, int cmp, int32_t value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_int64_test_some(int64_t *vars, size_t nelems, size_t *indices, const int *status, int cmp, int64_t value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_uint32_test_some(uint32_t *vars, size_t nelems, size_t *indices, const int *status, int cmp, uint32_t value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_uint64_test_some(uint64_t *vars, size_t nelems, size_t *indices, const int *status, int cmp, uint64_t value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_size_test_some(size_t *vars, size_t nelems, size_t *indices, const int *status, int cmp, size_t value);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ptrdiff_test_some(ptrdiff_t *vars, size_t nelems, size_t *indices, const int *status, int cmp, ptrdiff_t value);

SHMEM_FUNCTION_ATTRIBUTES int shmem_short_test_all_vector(short *vars, size_t nelems, const int *status, int cmp, short *values);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int_test_all_vector(int *vars, size_t nelems, const int *status, int cmp, int *values);
SHMEM_FUNCTION_ATTRIBUTES int shmem_long_test_all_vector(long *vars, size_t nelems, const int *status, int cmp, long *values);
SHMEM_FUNCTION_ATTRIBUTES int shmem_longlong_test_all_vector(long long *vars, size_t nelems, const int *status, int cmp, long long *values);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ushort_test_all_vector(unsigned short *vars, size_t nelems, const int *status, int cmp, unsigned short *values);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint_test_all_vector(unsigned int *vars, size_t nelems, const int *status, int cmp, unsigned int *values);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ulong_test_all_vector(unsigned long *vars, size_t nelems, const int *status, int cmp, unsigned long *values);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ulonglong_test_all_vector(unsigned long long *vars, size_t nelems, const int *status, int cmp, unsigned long long *values);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int32_test_all_vector(int32_t *vars, size_t nelems, const int *status, int cmp, int32_t *values);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int64_test_all_vector(int64_t *vars, size_t nelems, const int *status, int cmp, int64_t *values);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint32_test_all_vector(uint32_t *vars, size_t nelems, const int *status, int cmp, uint32_t *values);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint64_test_all_vector(uint64_t *vars, size_t nelems, const int *status, int cmp, uint64_t *values);
SHMEM_FUNCTION_ATTRIBUTES int shmem_size_test_all_vector(size_t *vars, size_t nelems, const int *status, int cmp, size_t *values);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ptrdiff_test_all_vector(ptrdiff_t *vars, size_t nelems, const int *status, int cmp, ptrdiff_t *values);

SHMEM_FUNCTION_ATTRIBUTES size_t shmem_short_test_any_vector(short *vars, size_t nelems, const int *status, int cmp, short *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_int_test_any_vector(int *vars, size_t nelems, const int *status, int cmp, int *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_long_test_any_vector(long *vars, size_t nelems, const int *status, int cmp, long *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_longlong_test_any_vector(long long *vars, size_t nelems, const int *status, int cmp, long long *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ushort_test_any_vector(unsigned short *vars, size_t nelems, const int *status, int cmp, unsigned short *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_uint_test_any_vector(unsigned int *vars, size_t nelems, const int *status, int cmp, unsigned int *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ulong_test_any_vector(unsigned long *vars, size_t nelems, const int *status, int cmp, unsigned long *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ulonglong_test_any_vector(unsigned long long *vars, size_t nelems, const int *status, int cmp, unsigned long long *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_int32_test_any_vector(int32_t *vars, size_t nelems, const int *status, int cmp, int32_t *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_int64_test_any_vector(int64_t *vars, size_t nelems, const int *status, int cmp, int64_t *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_uint32_test_any_vector(uint32_t *vars, size_t nelems, const int *status, int cmp, uint32_t *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_uint64_test_any_vector(uint64_t *vars, size_t nelems, const int *status, int cmp, uint64_t *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_size_test_any_vector(size_t *vars, size_t nelems, const int *status, int cmp, size_t *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ptrdiff_test_any_vector(ptrdiff_t *vars, size_t nelems, const int *status, int cmp, ptrdiff_t *values);

SHMEM_FUNCTION_ATTRIBUTES size_t shmem_short_test_some_vector(short *vars, size_t nelems, size_t *indices, const int *status, int cmp, short *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_int_test_some_vector(int *vars, size_t nelems, size_t *indices, const int *status, int cmp, int *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_long_test_some_vector(long *vars, size_t nelems, size_t *indices, const int *status, int cmp, long *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_longlong_test_some_vector(long long *vars, size_t nelems, size_t *indices, const int *status, int cmp, long long *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ushort_test_some_vector(unsigned short *vars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned short *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_uint_test_some_vector(unsigned int *vars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned int *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ulong_test_some_vector(unsigned long *vars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned long *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ulonglong_test_some_vector(unsigned long long *vars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned long long *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_int32_test_some_vector(int32_t *vars, size_t nelems, size_t *indices, const int *status, int cmp, int32_t *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_int64_test_some_vector(int64_t *vars, size_t nelems, size_t *indices, const int *status, int cmp, int64_t *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_uint32_test_some_vector(uint32_t *vars, size_t nelems, size_t *indices, const int *status, int cmp, uint32_t *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_uint64_test_some_vector(uint64_t *vars, size_t nelems, size_t *indices, const int *status, int cmp, uint64_t *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_size_test_some_vector(size_t *vars, size_t nelems, size_t *indices, const int *status, int cmp, size_t *values);
SHMEM_FUNCTION_ATTRIBUTES size_t shmem_ptrdiff_test_some_vector(ptrdiff_t *vars, size_t nelems, size_t *indices, const int *status, int cmp, ptrdiff_t *values);

SHMEM_FUNCTION_ATTRIBUTES uint64_t shmem_signal_wait_until(uint64_t *sig_addr, int cmp, uint64_t cmp_value);

/* Memory Ordering Routines */
SHMEM_FUNCTION_ATTRIBUTES void shmem_quiet(void);
SHMEM_FUNCTION_ATTRIBUTES void shmem_fence(void);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_quiet(shmem_ctx_t ctx);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_fence(shmem_ctx_t ctx);

/* Distributed Locking Routines */
SHMEM_FUNCTION_ATTRIBUTES void shmem_set_lock(long *lock);
SHMEM_FUNCTION_ATTRIBUTES void shmem_clear_lock(long *lock);
SHMEM_FUNCTION_ATTRIBUTES int shmem_test_lock(long *lock);

/* Cache Management Routines (deprecated) */
SHMEM_FUNCTION_ATTRIBUTES void shmem_set_cache_inv(void) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_set_cache_line_inv(void *target) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_clear_cache_inv(void) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_clear_cache_line_inv(void *target) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_udcflush(void) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shmem_udcflush_line(void *target) SHMEM_ATTRIBUTE_DEPRECATED;

/* Deprecated API */
SHMEM_FUNCTION_ATTRIBUTES int _num_pes(void) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES int _my_pe(void) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void *shmalloc(size_t size) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void *shmemalign(size_t alignment, size_t size) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void *shrealloc(void *ptr, size_t size) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void shfree(void *ptr) SHMEM_ATTRIBUTE_DEPRECATED;
SHMEM_FUNCTION_ATTRIBUTES void start_pes(int npes) SHMEM_ATTRIBUTE_DEPRECATED;

/* Memory Management Routines */
SHMEM_FUNCTION_ATTRIBUTES void *shmem_malloc_with_hints(size_t size, long hints);

/* Nonblocking swap operations */
SHMEM_FUNCTION_ATTRIBUTES void shmem_int_atomic_swap_nbi(int *fetch, int *dest, int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_atomic_swap_nbi(long *fetch, long *dest, long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_atomic_swap_nbi(long long *fetch, long long *dest, long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint_atomic_swap_nbi(unsigned int *fetch, unsigned int *dest, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulong_atomic_swap_nbi(unsigned long *fetch, unsigned long *dest, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulonglong_atomic_swap_nbi(unsigned long long *fetch, unsigned long long *dest, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int32_atomic_swap_nbi(int32_t *fetch, int32_t *dest, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int64_atomic_swap_nbi(int64_t *fetch, int64_t *dest, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint32_atomic_swap_nbi(uint32_t *fetch, uint32_t *dest, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint64_atomic_swap_nbi(uint64_t *fetch, uint64_t *dest, uint64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_size_atomic_swap_nbi(size_t *fetch, size_t *dest, size_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ptrdiff_atomic_swap_nbi(ptrdiff_t *fetch, ptrdiff_t *dest, ptrdiff_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_float_atomic_swap_nbi(float *fetch, float *dest, float value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_double_atomic_swap_nbi(double *fetch, double *dest, double value, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int_atomic_swap_nbi(shmem_ctx_t ctx, int *fetch, int *dest, int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_long_atomic_swap_nbi(shmem_ctx_t ctx, long *fetch, long *dest, long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_longlong_atomic_swap_nbi(shmem_ctx_t ctx, long long *fetch, long long *dest, long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint_atomic_swap_nbi(shmem_ctx_t ctx, unsigned int *fetch, unsigned int *dest, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulong_atomic_swap_nbi(shmem_ctx_t ctx, unsigned long *fetch, unsigned long *dest, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulonglong_atomic_swap_nbi(shmem_ctx_t ctx, unsigned long long *fetch, unsigned long long *dest, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int32_atomic_swap_nbi(shmem_ctx_t ctx, int32_t *fetch, int32_t *dest, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int64_atomic_swap_nbi(shmem_ctx_t ctx, int64_t *fetch, int64_t *dest, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint32_atomic_swap_nbi(shmem_ctx_t ctx, uint32_t *fetch, uint32_t *dest, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint64_atomic_swap_nbi(shmem_ctx_t ctx, uint64_t *fetch, uint64_t *dest, uint64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_size_atomic_swap_nbi(shmem_ctx_t ctx, size_t *fetch, size_t *dest, size_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ptrdiff_atomic_swap_nbi(shmem_ctx_t ctx, ptrdiff_t *fetch, ptrdiff_t *dest, ptrdiff_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_float_atomic_swap_nbi(shmem_ctx_t ctx, float *fetch, float *dest, float value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_double_atomic_swap_nbi(shmem_ctx_t ctx, double *fetch, double *dest, double value, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_int_atomic_compare_swap_nbi(int *fetch, int *dest, int cond, int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_atomic_compare_swap_nbi(long *fetch, long *dest, long cond, long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_atomic_compare_swap_nbi(long long *fetch, long long *dest, long long cond, long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint_atomic_compare_swap_nbi(unsigned int *fetch, unsigned int *dest, unsigned int cond, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulong_atomic_compare_swap_nbi(unsigned long *fetch, unsigned long *dest, unsigned long cond, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulonglong_atomic_compare_swap_nbi(unsigned long long *fetch, unsigned long long *dest, unsigned long long cond, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int32_atomic_compare_swap_nbi(int32_t *fetch, int32_t *dest, int32_t cond, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int64_atomic_compare_swap_nbi(int64_t *fetch, int64_t *dest, int64_t cond, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint32_atomic_compare_swap_nbi(uint32_t *fetch, uint32_t *dest, uint32_t cond, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint64_atomic_compare_swap_nbi(uint64_t *fetch, uint64_t *dest, uint64_t cond, uint64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_size_atomic_compare_swap_nbi(size_t *fetch, size_t *dest, size_t cond, size_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ptrdiff_atomic_compare_swap_nbi(ptrdiff_t *fetch, ptrdiff_t *dest, ptrdiff_t cond, ptrdiff_t value, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int_atomic_compare_swap_nbi(shmem_ctx_t ctx, int *fetch, int *dest, int cond, int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_long_atomic_compare_swap_nbi(shmem_ctx_t ctx, long *fetch, long *dest, long cond, long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_longlong_atomic_compare_swap_nbi(shmem_ctx_t ctx, long long *fetch, long long *dest, long long cond, long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint_atomic_compare_swap_nbi(shmem_ctx_t ctx, unsigned int *fetch, unsigned int *dest, unsigned int cond, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulong_atomic_compare_swap_nbi(shmem_ctx_t ctx, unsigned long *fetch, unsigned long *dest, unsigned long cond, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulonglong_atomic_compare_swap_nbi(shmem_ctx_t ctx, unsigned long long *fetch, unsigned long long *dest, unsigned long long cond, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int32_atomic_compare_swap_nbi(shmem_ctx_t ctx, int32_t *fetch, int32_t *dest, int32_t cond, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int64_atomic_compare_swap_nbi(shmem_ctx_t ctx, int64_t *fetch, int64_t *dest, int64_t cond, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint32_atomic_compare_swap_nbi(shmem_ctx_t ctx, uint32_t *fetch, uint32_t *dest, uint32_t cond, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint64_atomic_compare_swap_nbi(shmem_ctx_t ctx, uint64_t *fetch, uint64_t *dest, uint64_t cond, uint64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_size_atomic_compare_swap_nbi(shmem_ctx_t ctx, size_t *fetch, size_t *dest, size_t cond, size_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ptrdiff_atomic_compare_swap_nbi(shmem_ctx_t ctx, ptrdiff_t *fetch, ptrdiff_t *dest, ptrdiff_t cond, ptrdiff_t value, int pe);

/* Nonblocking fetching AMOs */
SHMEM_FUNCTION_ATTRIBUTES void shmem_int_atomic_fetch_nbi(int *fetch, const int *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_atomic_fetch_nbi(long *fetch, const long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_atomic_fetch_nbi(long long *fetch, const long long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint_atomic_fetch_nbi(unsigned int *fetch, const unsigned int *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulong_atomic_fetch_nbi(unsigned long *fetch, const unsigned long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulonglong_atomic_fetch_nbi(unsigned long long *fetch, const unsigned long long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int32_atomic_fetch_nbi(int32_t *fetch, const int32_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int64_atomic_fetch_nbi(int64_t *fetch, const int64_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint32_atomic_fetch_nbi(uint32_t *fetch, const uint32_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint64_atomic_fetch_nbi(uint64_t *fetch, const uint64_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_size_atomic_fetch_nbi(size_t *fetch, const size_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ptrdiff_atomic_fetch_nbi(ptrdiff_t *fetch, const ptrdiff_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_float_atomic_fetch_nbi(float *fetch, const float *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_double_atomic_fetch_nbi(double *fetch, const double *target, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int_atomic_fetch_nbi(shmem_ctx_t ctx, int *fetch, const int *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_long_atomic_fetch_nbi(shmem_ctx_t ctx, long *fetch, const long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_longlong_atomic_fetch_nbi(shmem_ctx_t ctx, long long *fetch, const long long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint_atomic_fetch_nbi(shmem_ctx_t ctx, unsigned int *fetch, const unsigned int *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulong_atomic_fetch_nbi(shmem_ctx_t ctx, unsigned long *fetch, const unsigned long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulonglong_atomic_fetch_nbi(shmem_ctx_t ctx, unsigned long long *fetch, const unsigned long long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int32_atomic_fetch_nbi(shmem_ctx_t ctx, int32_t *fetch, const int32_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int64_atomic_fetch_nbi(shmem_ctx_t ctx, int64_t *fetch, const int64_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint32_atomic_fetch_nbi(shmem_ctx_t ctx, uint32_t *fetch, const uint32_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint64_atomic_fetch_nbi(shmem_ctx_t ctx, uint64_t *fetch, const uint64_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_size_atomic_fetch_nbi(shmem_ctx_t ctx, size_t *fetch, const size_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ptrdiff_atomic_fetch_nbi(shmem_ctx_t ctx, ptrdiff_t *fetch, const ptrdiff_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_float_atomic_fetch_nbi(shmem_ctx_t ctx, float *fetch, const float *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_double_atomic_fetch_nbi(shmem_ctx_t ctx, double *fetch, const double *target, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_int_atomic_fetch_inc_nbi(int *fetch, int *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_atomic_fetch_inc_nbi(long *fetch, long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_atomic_fetch_inc_nbi(long long *fetch, long long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint_atomic_fetch_inc_nbi(unsigned int *fetch, unsigned int *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulong_atomic_fetch_inc_nbi(unsigned long *fetch, unsigned long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulonglong_atomic_fetch_inc_nbi(unsigned long long *fetch, unsigned long long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int32_atomic_fetch_inc_nbi(int32_t *fetch, int32_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int64_atomic_fetch_inc_nbi(int64_t *fetch, int64_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint32_atomic_fetch_inc_nbi(uint32_t *fetch, uint32_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint64_atomic_fetch_inc_nbi(uint64_t *fetch, uint64_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_size_atomic_fetch_inc_nbi(size_t *fetch, size_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ptrdiff_atomic_fetch_inc_nbi(ptrdiff_t *fetch, ptrdiff_t *target, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int_atomic_fetch_inc_nbi(shmem_ctx_t ctx, int *fetch, int *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_long_atomic_fetch_inc_nbi(shmem_ctx_t ctx, long *fetch, long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_longlong_atomic_fetch_inc_nbi(shmem_ctx_t ctx, long long *fetch, long long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint_atomic_fetch_inc_nbi(shmem_ctx_t ctx, unsigned int *fetch, unsigned int *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulong_atomic_fetch_inc_nbi(shmem_ctx_t ctx, unsigned long *fetch, unsigned long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulonglong_atomic_fetch_inc_nbi(shmem_ctx_t ctx, unsigned long long *fetch, unsigned long long *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int32_atomic_fetch_inc_nbi(shmem_ctx_t ctx, int32_t *fetch, int32_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int64_atomic_fetch_inc_nbi(shmem_ctx_t ctx, int64_t *fetch, int64_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint32_atomic_fetch_inc_nbi(shmem_ctx_t ctx, uint32_t *fetch, uint32_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint64_atomic_fetch_inc_nbi(shmem_ctx_t ctx, uint64_t *fetch, uint64_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_size_atomic_fetch_inc_nbi(shmem_ctx_t ctx, size_t *fetch, size_t *target, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ptrdiff_atomic_fetch_inc_nbi(shmem_ctx_t ctx, ptrdiff_t *fetch, ptrdiff_t *target, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_int_atomic_fetch_add_nbi(int *fetch, int *target, int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_long_atomic_fetch_add_nbi(long *fetch, long *target, long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_longlong_atomic_fetch_add_nbi(long long *fetch, long long *target, long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint_atomic_fetch_add_nbi(unsigned int *fetch, unsigned int *target, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulong_atomic_fetch_add_nbi(unsigned long *fetch, unsigned long *target, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulonglong_atomic_fetch_add_nbi(unsigned long long *fetch, unsigned long long *target, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int32_atomic_fetch_add_nbi(int32_t *fetch, int32_t *target, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int64_atomic_fetch_add_nbi(int64_t *fetch, int64_t *target, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint32_atomic_fetch_add_nbi(uint32_t *fetch, uint32_t *target, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint64_atomic_fetch_add_nbi(uint64_t *fetch, uint64_t *target, uint64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_size_atomic_fetch_add_nbi(size_t *fetch, size_t *target, size_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ptrdiff_atomic_fetch_add_nbi(ptrdiff_t *fetch, ptrdiff_t *target, ptrdiff_t value, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int_atomic_fetch_add_nbi(shmem_ctx_t ctx, int *fetch, int *target, int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_long_atomic_fetch_add_nbi(shmem_ctx_t ctx, long *fetch, long *target, long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_longlong_atomic_fetch_add_nbi(shmem_ctx_t ctx, long long *fetch, long long *target, long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint_atomic_fetch_add_nbi(shmem_ctx_t ctx, unsigned int *fetch, unsigned int *target, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulong_atomic_fetch_add_nbi(shmem_ctx_t ctx, unsigned long *fetch, unsigned long *target, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulonglong_atomic_fetch_add_nbi(shmem_ctx_t ctx, unsigned long long *fetch, unsigned long long *target, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int32_atomic_fetch_add_nbi(shmem_ctx_t ctx, int32_t *fetch, int32_t *target, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int64_atomic_fetch_add_nbi(shmem_ctx_t ctx, int64_t *fetch, int64_t *target, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint32_atomic_fetch_add_nbi(shmem_ctx_t ctx, uint32_t *fetch, uint32_t *target, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint64_atomic_fetch_add_nbi(shmem_ctx_t ctx, uint64_t *fetch, uint64_t *target, uint64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_size_atomic_fetch_add_nbi(shmem_ctx_t ctx, size_t *fetch, size_t *target, size_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ptrdiff_atomic_fetch_add_nbi(shmem_ctx_t ctx, ptrdiff_t *fetch, ptrdiff_t *target, ptrdiff_t value, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_uint_atomic_fetch_xor_nbi(unsigned int *fetch, unsigned int *target, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulong_atomic_fetch_xor_nbi(unsigned long *fetch, unsigned long *target, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulonglong_atomic_fetch_xor_nbi(unsigned long long *fetch, unsigned long long *target, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int32_atomic_fetch_xor_nbi(int32_t *fetch, int32_t *target, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int64_atomic_fetch_xor_nbi(int64_t *fetch, int64_t *target, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint32_atomic_fetch_xor_nbi(uint32_t *fetch, uint32_t *target, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint64_atomic_fetch_xor_nbi(uint64_t *fetch, uint64_t *target, uint64_t value, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint_atomic_fetch_xor_nbi(shmem_ctx_t ctx, unsigned int *fetch, unsigned int *target, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulong_atomic_fetch_xor_nbi(shmem_ctx_t ctx, unsigned long *fetch, unsigned long *target, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulonglong_atomic_fetch_xor_nbi(shmem_ctx_t ctx, unsigned long long *fetch, unsigned long long *target, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int32_atomic_fetch_xor_nbi(shmem_ctx_t ctx, int32_t *fetch, int32_t *target, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int64_atomic_fetch_xor_nbi(shmem_ctx_t ctx, int64_t *fetch, int64_t *target, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint32_atomic_fetch_xor_nbi(shmem_ctx_t ctx, uint32_t *fetch, uint32_t *target, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint64_atomic_fetch_xor_nbi(shmem_ctx_t ctx, uint64_t *fetch, uint64_t *target, uint64_t value, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_uint_atomic_fetch_and_nbi(unsigned int *fetch, unsigned int *target, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulong_atomic_fetch_and_nbi(unsigned long *fetch, unsigned long *target, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulonglong_atomic_fetch_and_nbi(unsigned long long *fetch, unsigned long long *target, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int32_atomic_fetch_and_nbi(int32_t *fetch, int32_t *target, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int64_atomic_fetch_and_nbi(int64_t *fetch, int64_t *target, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint32_atomic_fetch_and_nbi(uint32_t *fetch, uint32_t *target, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint64_atomic_fetch_and_nbi(uint64_t *fetch, uint64_t *target, uint64_t value, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint_atomic_fetch_and_nbi(shmem_ctx_t ctx, unsigned int *fetch, unsigned int *target, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulong_atomic_fetch_and_nbi(shmem_ctx_t ctx, unsigned long *fetch, unsigned long *target, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulonglong_atomic_fetch_and_nbi(shmem_ctx_t ctx, unsigned long long *fetch, unsigned long long *target, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int32_atomic_fetch_and_nbi(shmem_ctx_t ctx, int32_t *fetch, int32_t *target, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int64_atomic_fetch_and_nbi(shmem_ctx_t ctx, int64_t *fetch, int64_t *target, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint32_atomic_fetch_and_nbi(shmem_ctx_t ctx, uint32_t *fetch, uint32_t *target, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint64_atomic_fetch_and_nbi(shmem_ctx_t ctx, uint64_t *fetch, uint64_t *target, uint64_t value, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_uint_atomic_fetch_or_nbi(unsigned int *fetch, unsigned int *target, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulong_atomic_fetch_or_nbi(unsigned long *fetch, unsigned long *target, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ulonglong_atomic_fetch_or_nbi(unsigned long long *fetch, unsigned long long *target, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int32_atomic_fetch_or_nbi(int32_t *fetch, int32_t *target, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_int64_atomic_fetch_or_nbi(int64_t *fetch, int64_t *target, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint32_atomic_fetch_or_nbi(uint32_t *fetch, uint32_t *target, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_uint64_atomic_fetch_or_nbi(uint64_t *fetch, uint64_t *target, uint64_t value, int pe);

SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint_atomic_fetch_or_nbi(shmem_ctx_t ctx, unsigned int *fetch, unsigned int *target, unsigned int value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulong_atomic_fetch_or_nbi(shmem_ctx_t ctx, unsigned long *fetch, unsigned long *target, unsigned long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_ulonglong_atomic_fetch_or_nbi(shmem_ctx_t ctx, unsigned long long *fetch, unsigned long long *target, unsigned long long value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int32_atomic_fetch_or_nbi(shmem_ctx_t ctx, int32_t *fetch, int32_t *target, int32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_int64_atomic_fetch_or_nbi(shmem_ctx_t ctx, int64_t *fetch, int64_t *target, int64_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint32_atomic_fetch_or_nbi(shmem_ctx_t ctx, uint32_t *fetch, uint32_t *target, uint32_t value, int pe);
SHMEM_FUNCTION_ATTRIBUTES void shmem_ctx_uint64_atomic_fetch_or_nbi(shmem_ctx_t ctx, uint64_t *fetch, uint64_t *target, uint64_t value, int pe);

/* Team Management Routines */
SHMEM_FUNCTION_ATTRIBUTES int shmem_team_my_pe(shmem_team_t team);

SHMEM_FUNCTION_ATTRIBUTES int shmem_team_translate_pe(shmem_team_t src_team, int src_pe, shmem_team_t dest_team);

SHMEM_FUNCTION_ATTRIBUTES int shmem_team_n_pes(shmem_team_t team);

SHMEM_FUNCTION_ATTRIBUTES int shmem_team_get_config(shmem_team_t team, long config_mask, shmem_team_config_t *config);

SHMEM_FUNCTION_ATTRIBUTES int shmem_team_split_strided(shmem_team_t parent_team, int PE_start, int PE_stride, int PE_size, const shmem_team_config_t *config, long config_mask, shmem_team_t *new_team);

SHMEM_FUNCTION_ATTRIBUTES int shmem_team_split_2d(shmem_team_t parent_team, int xrange, const shmem_team_config_t *xaxis_config, long xaxis_mask, shmem_team_t *xaxis_team, const shmem_team_config_t *yaxis_config, long yaxis_mask, shmem_team_t *yaxis_team);

SHMEM_FUNCTION_ATTRIBUTES int shmem_team_destroy(shmem_team_t team);

SHMEM_FUNCTION_ATTRIBUTES int shmem_team_create_ctx(shmem_team_t team, long options, shmem_ctx_t *ctx);

SHMEM_FUNCTION_ATTRIBUTES int shmem_ctx_get_team(shmem_ctx_t ctx, shmem_team_t *team);

SHMEM_FUNCTION_ATTRIBUTES int shmem_team_sync(shmem_team_t team);

/* Team Collective Routines */
SHMEM_FUNCTION_ATTRIBUTES int shmem_float_alltoall(shmem_team_t team, float *dest, const float *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_double_alltoall(shmem_team_t team, double *dest, const double *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_longdouble_alltoall(shmem_team_t team, long double *dest, const long double *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_char_alltoall(shmem_team_t team, char *dest, const char *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_schar_alltoall(shmem_team_t team, signed char *dest, const signed char *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_short_alltoall(shmem_team_t team, short *dest, const short *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int_alltoall(shmem_team_t team, int *dest, const int *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_long_alltoall(shmem_team_t team, long *dest, const long *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_longlong_alltoall(shmem_team_t team, long long *dest, const long long *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uchar_alltoall(shmem_team_t team, unsigned char *dest, const unsigned char *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ushort_alltoall(shmem_team_t team, unsigned short *dest, const unsigned short *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint_alltoall(shmem_team_t team, unsigned int *dest, const unsigned int *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ulong_alltoall(shmem_team_t team, unsigned long *dest, const unsigned long *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ulonglong_alltoall(shmem_team_t team, unsigned long long *dest, const unsigned long long *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int8_alltoall(shmem_team_t team, int8_t *dest, const int8_t *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int16_alltoall(shmem_team_t team, int16_t *dest, const int16_t *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int32_alltoall(shmem_team_t team, int32_t *dest, const int32_t *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int64_alltoall(shmem_team_t team, int64_t *dest, const int64_t *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint8_alltoall(shmem_team_t team, uint8_t *dest, const uint8_t *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint16_alltoall(shmem_team_t team, uint16_t *dest, const uint16_t *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint32_alltoall(shmem_team_t team, uint32_t *dest, const uint32_t *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint64_alltoall(shmem_team_t team, uint64_t *dest, const uint64_t *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_size_alltoall(shmem_team_t team, size_t *dest, const size_t *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ptrdiff_alltoall(shmem_team_t team, ptrdiff_t *dest, const ptrdiff_t *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_alltoallmem(shmem_team_t team, void *dest, const void *source, size_t nelems);

SHMEM_FUNCTION_ATTRIBUTES int shmem_float_alltoalls(shmem_team_t team, float *dest, const float *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_double_alltoalls(shmem_team_t team, double *dest, const double *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_longdouble_alltoalls(shmem_team_t team, long double *dest, const long double *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_char_alltoalls(shmem_team_t team, char *dest, const char *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_schar_alltoalls(shmem_team_t team, signed char *dest, const signed char *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_short_alltoalls(shmem_team_t team, short *dest, const short *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int_alltoalls(shmem_team_t team, int *dest, const int *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_long_alltoalls(shmem_team_t team, long *dest, const long *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_longlong_alltoalls(shmem_team_t team, long long *dest, const long long *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uchar_alltoalls(shmem_team_t team, unsigned char *dest, const unsigned char *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ushort_alltoalls(shmem_team_t team, unsigned short *dest, const unsigned short *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint_alltoalls(shmem_team_t team, unsigned int *dest, const unsigned int *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ulong_alltoalls(shmem_team_t team, unsigned long *dest, const unsigned long *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ulonglong_alltoalls(shmem_team_t team, unsigned long long *dest, const unsigned long long *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int8_alltoalls(shmem_team_t team, int8_t *dest, const int8_t *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int16_alltoalls(shmem_team_t team, int16_t *dest, const int16_t *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int32_alltoalls(shmem_team_t team, int32_t *dest, const int32_t *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int64_alltoalls(shmem_team_t team, int64_t *dest, const int64_t *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint8_alltoalls(shmem_team_t team, uint8_t *dest, const uint8_t *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint16_alltoalls(shmem_team_t team, uint16_t *dest, const uint16_t *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint32_alltoalls(shmem_team_t team, uint32_t *dest, const uint32_t *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint64_alltoalls(shmem_team_t team, uint64_t *dest, const uint64_t *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_size_alltoalls(shmem_team_t team, size_t *dest, const size_t *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ptrdiff_alltoalls(shmem_team_t team, ptrdiff_t *dest, const ptrdiff_t *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_alltoallsmem(shmem_team_t team, void *dest, const void *source, ptrdiff_t dst, ptrdiff_t sst, size_t nelems);

SHMEM_FUNCTION_ATTRIBUTES int shmem_float_broadcast(shmem_team_t team, float *dest, const float *source, size_t nelems, int PE_root);
SHMEM_FUNCTION_ATTRIBUTES int shmem_double_broadcast(shmem_team_t team, double *dest, const double *source, size_t nelems, int PE_root);
SHMEM_FUNCTION_ATTRIBUTES int shmem_longdouble_broadcast(shmem_team_t team, long double *dest, const long double *source, size_t nelems, int PE_root);
SHMEM_FUNCTION_ATTRIBUTES int shmem_char_broadcast(shmem_team_t team, char *dest, const char *source, size_t nelems, int PE_root);
SHMEM_FUNCTION_ATTRIBUTES int shmem_schar_broadcast(shmem_team_t team, signed char *dest, const signed char *source, size_t nelems, int PE_root);
SHMEM_FUNCTION_ATTRIBUTES int shmem_short_broadcast(shmem_team_t team, short *dest, const short *source, size_t nelems, int PE_root);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int_broadcast(shmem_team_t team, int *dest, const int *source, size_t nelems, int PE_root);
SHMEM_FUNCTION_ATTRIBUTES int shmem_long_broadcast(shmem_team_t team, long *dest, const long *source, size_t nelems, int PE_root);
SHMEM_FUNCTION_ATTRIBUTES int shmem_longlong_broadcast(shmem_team_t team, long long *dest, const long long *source, size_t nelems, int PE_root);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uchar_broadcast(shmem_team_t team, unsigned char *dest, const unsigned char *source, size_t nelems, int PE_root);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ushort_broadcast(shmem_team_t team, unsigned short *dest, const unsigned short *source, size_t nelems, int PE_root);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint_broadcast(shmem_team_t team, unsigned int *dest, const unsigned int *source, size_t nelems, int PE_root);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ulong_broadcast(shmem_team_t team, unsigned long *dest, const unsigned long *source, size_t nelems, int PE_root);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ulonglong_broadcast(shmem_team_t team, unsigned long long *dest, const unsigned long long *source, size_t nelems, int PE_root);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int8_broadcast(shmem_team_t team, int8_t *dest, const int8_t *source, size_t nelems, int PE_root);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int16_broadcast(shmem_team_t team, int16_t *dest, const int16_t *source, size_t nelems, int PE_root);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int32_broadcast(shmem_team_t team, int32_t *dest, const int32_t *source, size_t nelems, int PE_root);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int64_broadcast(shmem_team_t team, int64_t *dest, const int64_t *source, size_t nelems, int PE_root);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint8_broadcast(shmem_team_t team, uint8_t *dest, const uint8_t *source, size_t nelems, int PE_root);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint16_broadcast(shmem_team_t team, uint16_t *dest, const uint16_t *source, size_t nelems, int PE_root);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint32_broadcast(shmem_team_t team, uint32_t *dest, const uint32_t *source, size_t nelems, int PE_root);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint64_broadcast(shmem_team_t team, uint64_t *dest, const uint64_t *source, size_t nelems, int PE_root);
SHMEM_FUNCTION_ATTRIBUTES int shmem_size_broadcast(shmem_team_t team, size_t *dest, const size_t *source, size_t nelems, int PE_root);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ptrdiff_broadcast(shmem_team_t team, ptrdiff_t *dest, const ptrdiff_t *source, size_t nelems, int PE_root);
SHMEM_FUNCTION_ATTRIBUTES int shmem_broadcastmem(shmem_team_t team, void *dest, const void *source, size_t nelems, int PE_root);

SHMEM_FUNCTION_ATTRIBUTES int shmem_float_collect(shmem_team_t team, float *dest, const float *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_double_collect(shmem_team_t team, double *dest, const double *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_longdouble_collect(shmem_team_t team, long double *dest, const long double *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_char_collect(shmem_team_t team, char *dest, const char *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_schar_collect(shmem_team_t team, signed char *dest, const signed char *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_short_collect(shmem_team_t team, short *dest, const short *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int_collect(shmem_team_t team, int *dest, const int *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_long_collect(shmem_team_t team, long *dest, const long *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_longlong_collect(shmem_team_t team, long long *dest, const long long *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uchar_collect(shmem_team_t team, unsigned char *dest, const unsigned char *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ushort_collect(shmem_team_t team, unsigned short *dest, const unsigned short *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint_collect(shmem_team_t team, unsigned int *dest, const unsigned int *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ulong_collect(shmem_team_t team, unsigned long *dest, const unsigned long *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ulonglong_collect(shmem_team_t team, unsigned long long *dest, const unsigned long long *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int8_collect(shmem_team_t team, int8_t *dest, const int8_t *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int16_collect(shmem_team_t team, int16_t *dest, const int16_t *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int32_collect(shmem_team_t team, int32_t *dest, const int32_t *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int64_collect(shmem_team_t team, int64_t *dest, const int64_t *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint8_collect(shmem_team_t team, uint8_t *dest, const uint8_t *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint16_collect(shmem_team_t team, uint16_t *dest, const uint16_t *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint32_collect(shmem_team_t team, uint32_t *dest, const uint32_t *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint64_collect(shmem_team_t team, uint64_t *dest, const uint64_t *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_size_collect(shmem_team_t team, size_t *dest, const size_t *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ptrdiff_collect(shmem_team_t team, ptrdiff_t *dest, const ptrdiff_t *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_collectmem(shmem_team_t team, void *dest, const void *source, size_t nelems);

SHMEM_FUNCTION_ATTRIBUTES int shmem_float_fcollect(shmem_team_t team, float *dest, const float *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_double_fcollect(shmem_team_t team, double *dest, const double *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_longdouble_fcollect(shmem_team_t team, long double *dest, const long double *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_char_fcollect(shmem_team_t team, char *dest, const char *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_schar_fcollect(shmem_team_t team, signed char *dest, const signed char *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_short_fcollect(shmem_team_t team, short *dest, const short *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int_fcollect(shmem_team_t team, int *dest, const int *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_long_fcollect(shmem_team_t team, long *dest, const long *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_longlong_fcollect(shmem_team_t team, long long *dest, const long long *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uchar_fcollect(shmem_team_t team, unsigned char *dest, const unsigned char *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ushort_fcollect(shmem_team_t team, unsigned short *dest, const unsigned short *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint_fcollect(shmem_team_t team, unsigned int *dest, const unsigned int *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ulong_fcollect(shmem_team_t team, unsigned long *dest, const unsigned long *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ulonglong_fcollect(shmem_team_t team, unsigned long long *dest, const unsigned long long *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int8_fcollect(shmem_team_t team, int8_t *dest, const int8_t *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int16_fcollect(shmem_team_t team, int16_t *dest, const int16_t *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int32_fcollect(shmem_team_t team, int32_t *dest, const int32_t *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int64_fcollect(shmem_team_t team, int64_t *dest, const int64_t *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint8_fcollect(shmem_team_t team, uint8_t *dest, const uint8_t *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint16_fcollect(shmem_team_t team, uint16_t *dest, const uint16_t *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint32_fcollect(shmem_team_t team, uint32_t *dest, const uint32_t *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint64_fcollect(shmem_team_t team, uint64_t *dest, const uint64_t *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_size_fcollect(shmem_team_t team, size_t *dest, const size_t *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ptrdiff_fcollect(shmem_team_t team, ptrdiff_t *dest, const ptrdiff_t *source, size_t nelems);
SHMEM_FUNCTION_ATTRIBUTES int shmem_fcollectmem(shmem_team_t team, void *dest, const void *source, size_t nelems);

SHMEM_FUNCTION_ATTRIBUTES int shmem_uchar_and_reduce(shmem_team_t team, unsigned char *dest, const unsigned char *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_short_and_reduce(shmem_team_t team, short *dest, const short *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ushort_and_reduce(shmem_team_t team, unsigned short *dest, const unsigned short *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int_and_reduce(shmem_team_t team, int *dest, const int *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint_and_reduce(shmem_team_t team, unsigned int *dest, const unsigned int *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_long_and_reduce(shmem_team_t team, long *dest, const long *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ulong_and_reduce(shmem_team_t team, unsigned long *dest, const unsigned long *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_longlong_and_reduce(shmem_team_t team, long long *dest, const long long *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ulonglong_and_reduce(shmem_team_t team, unsigned long long *dest, const unsigned long long *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int8_and_reduce(shmem_team_t team, int8_t *dest, const int8_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int16_and_reduce(shmem_team_t team, int16_t *dest, const int16_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int32_and_reduce(shmem_team_t team, int32_t *dest, const int32_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int64_and_reduce(shmem_team_t team, int64_t *dest, const int64_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint8_and_reduce(shmem_team_t team, uint8_t *dest, const uint8_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint16_and_reduce(shmem_team_t team, uint16_t *dest, const uint16_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint32_and_reduce(shmem_team_t team, uint32_t *dest, const uint32_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint64_and_reduce(shmem_team_t team, uint64_t *dest, const uint64_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_size_and_reduce(shmem_team_t team, size_t *dest, const size_t *source, size_t nreduce);

SHMEM_FUNCTION_ATTRIBUTES int shmem_uchar_or_reduce(shmem_team_t team, unsigned char *dest, const unsigned char *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_short_or_reduce(shmem_team_t team, short *dest, const short *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ushort_or_reduce(shmem_team_t team, unsigned short *dest, const unsigned short *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int_or_reduce(shmem_team_t team, int *dest, const int *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint_or_reduce(shmem_team_t team, unsigned int *dest, const unsigned int *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_long_or_reduce(shmem_team_t team, long *dest, const long *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ulong_or_reduce(shmem_team_t team, unsigned long *dest, const unsigned long *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_longlong_or_reduce(shmem_team_t team, long long *dest, const long long *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ulonglong_or_reduce(shmem_team_t team, unsigned long long *dest, const unsigned long long *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int8_or_reduce(shmem_team_t team, int8_t *dest, const int8_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int16_or_reduce(shmem_team_t team, int16_t *dest, const int16_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int32_or_reduce(shmem_team_t team, int32_t *dest, const int32_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int64_or_reduce(shmem_team_t team, int64_t *dest, const int64_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint8_or_reduce(shmem_team_t team, uint8_t *dest, const uint8_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint16_or_reduce(shmem_team_t team, uint16_t *dest, const uint16_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint32_or_reduce(shmem_team_t team, uint32_t *dest, const uint32_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint64_or_reduce(shmem_team_t team, uint64_t *dest, const uint64_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_size_or_reduce(shmem_team_t team, size_t *dest, const size_t *source, size_t nreduce);

SHMEM_FUNCTION_ATTRIBUTES int shmem_uchar_xor_reduce(shmem_team_t team, unsigned char *dest, const unsigned char *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_short_xor_reduce(shmem_team_t team, short *dest, const short *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ushort_xor_reduce(shmem_team_t team, unsigned short *dest, const unsigned short *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int_xor_reduce(shmem_team_t team, int *dest, const int *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint_xor_reduce(shmem_team_t team, unsigned int *dest, const unsigned int *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_long_xor_reduce(shmem_team_t team, long *dest, const long *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ulong_xor_reduce(shmem_team_t team, unsigned long *dest, const unsigned long *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_longlong_xor_reduce(shmem_team_t team, long long *dest, const long long *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ulonglong_xor_reduce(shmem_team_t team, unsigned long long *dest, const unsigned long long *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int8_xor_reduce(shmem_team_t team, int8_t *dest, const int8_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int16_xor_reduce(shmem_team_t team, int16_t *dest, const int16_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int32_xor_reduce(shmem_team_t team, int32_t *dest, const int32_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int64_xor_reduce(shmem_team_t team, int64_t *dest, const int64_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint8_xor_reduce(shmem_team_t team, uint8_t *dest, const uint8_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint16_xor_reduce(shmem_team_t team, uint16_t *dest, const uint16_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint32_xor_reduce(shmem_team_t team, uint32_t *dest, const uint32_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint64_xor_reduce(shmem_team_t team, uint64_t *dest, const uint64_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_size_xor_reduce(shmem_team_t team, size_t *dest, const size_t *source, size_t nreduce);

SHMEM_FUNCTION_ATTRIBUTES int shmem_char_min_reduce(shmem_team_t team, char *dest, const char *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_schar_min_reduce(shmem_team_t team, signed char *dest, const signed char *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_short_min_reduce(shmem_team_t team, short *dest, const short *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int_min_reduce(shmem_team_t team, int *dest, const int *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_long_min_reduce(shmem_team_t team, long *dest, const long *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_longlong_min_reduce(shmem_team_t team, long long *dest, const long long *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ptrdiff_min_reduce(shmem_team_t team, ptrdiff_t *dest, const ptrdiff_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uchar_min_reduce(shmem_team_t team, unsigned char *dest, const unsigned char *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ushort_min_reduce(shmem_team_t team, unsigned short *dest, const unsigned short *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint_min_reduce(shmem_team_t team, unsigned int *dest, const unsigned int *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ulong_min_reduce(shmem_team_t team, unsigned long *dest, const unsigned long *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ulonglong_min_reduce(shmem_team_t team, unsigned long long *dest, const unsigned long long *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int8_min_reduce(shmem_team_t team, int8_t *dest, const int8_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int16_min_reduce(shmem_team_t team, int16_t *dest, const int16_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int32_min_reduce(shmem_team_t team, int32_t *dest, const int32_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int64_min_reduce(shmem_team_t team, int64_t *dest, const int64_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint8_min_reduce(shmem_team_t team, uint8_t *dest, const uint8_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint16_min_reduce(shmem_team_t team, uint16_t *dest, const uint16_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint32_min_reduce(shmem_team_t team, uint32_t *dest, const uint32_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint64_min_reduce(shmem_team_t team, uint64_t *dest, const uint64_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_size_min_reduce(shmem_team_t team, size_t *dest, const size_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_float_min_reduce(shmem_team_t team, float *dest, const float *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_double_min_reduce(shmem_team_t team, double *dest, const double *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_longdouble_min_reduce(shmem_team_t team, long double *dest, const long double *source, size_t nreduce);

SHMEM_FUNCTION_ATTRIBUTES int shmem_char_max_reduce(shmem_team_t team, char *dest, const char *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_schar_max_reduce(shmem_team_t team, signed char *dest, const signed char *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_short_max_reduce(shmem_team_t team, short *dest, const short *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int_max_reduce(shmem_team_t team, int *dest, const int *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_long_max_reduce(shmem_team_t team, long *dest, const long *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_longlong_max_reduce(shmem_team_t team, long long *dest, const long long *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ptrdiff_max_reduce(shmem_team_t team, ptrdiff_t *dest, const ptrdiff_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uchar_max_reduce(shmem_team_t team, unsigned char *dest, const unsigned char *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ushort_max_reduce(shmem_team_t team, unsigned short *dest, const unsigned short *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint_max_reduce(shmem_team_t team, unsigned int *dest, const unsigned int *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ulong_max_reduce(shmem_team_t team, unsigned long *dest, const unsigned long *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ulonglong_max_reduce(shmem_team_t team, unsigned long long *dest, const unsigned long long *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int8_max_reduce(shmem_team_t team, int8_t *dest, const int8_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int16_max_reduce(shmem_team_t team, int16_t *dest, const int16_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int32_max_reduce(shmem_team_t team, int32_t *dest, const int32_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int64_max_reduce(shmem_team_t team, int64_t *dest, const int64_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint8_max_reduce(shmem_team_t team, uint8_t *dest, const uint8_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint16_max_reduce(shmem_team_t team, uint16_t *dest, const uint16_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint32_max_reduce(shmem_team_t team, uint32_t *dest, const uint32_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint64_max_reduce(shmem_team_t team, uint64_t *dest, const uint64_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_size_max_reduce(shmem_team_t team, size_t *dest, const size_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_float_max_reduce(shmem_team_t team, float *dest, const float *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_double_max_reduce(shmem_team_t team, double *dest, const double *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_longdouble_max_reduce(shmem_team_t team, long double *dest, const long double *source, size_t nreduce);

SHMEM_FUNCTION_ATTRIBUTES int shmem_char_sum_reduce(shmem_team_t team, char *dest, const char *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_schar_sum_reduce(shmem_team_t team, signed char *dest, const signed char *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_short_sum_reduce(shmem_team_t team, short *dest, const short *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int_sum_reduce(shmem_team_t team, int *dest, const int *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_long_sum_reduce(shmem_team_t team, long *dest, const long *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_longlong_sum_reduce(shmem_team_t team, long long *dest, const long long *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ptrdiff_sum_reduce(shmem_team_t team, ptrdiff_t *dest, const ptrdiff_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uchar_sum_reduce(shmem_team_t team, unsigned char *dest, const unsigned char *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ushort_sum_reduce(shmem_team_t team, unsigned short *dest, const unsigned short *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint_sum_reduce(shmem_team_t team, unsigned int *dest, const unsigned int *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ulong_sum_reduce(shmem_team_t team, unsigned long *dest, const unsigned long *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ulonglong_sum_reduce(shmem_team_t team, unsigned long long *dest, const unsigned long long *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int8_sum_reduce(shmem_team_t team, int8_t *dest, const int8_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int16_sum_reduce(shmem_team_t team, int16_t *dest, const int16_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int32_sum_reduce(shmem_team_t team, int32_t *dest, const int32_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int64_sum_reduce(shmem_team_t team, int64_t *dest, const int64_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint8_sum_reduce(shmem_team_t team, uint8_t *dest, const uint8_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint16_sum_reduce(shmem_team_t team, uint16_t *dest, const uint16_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint32_sum_reduce(shmem_team_t team, uint32_t *dest, const uint32_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint64_sum_reduce(shmem_team_t team, uint64_t *dest, const uint64_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_size_sum_reduce(shmem_team_t team, size_t *dest, const size_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_float_sum_reduce(shmem_team_t team, float *dest, const float *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_double_sum_reduce(shmem_team_t team, double *dest, const double *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_longdouble_sum_reduce(shmem_team_t team, long double *dest, const long double *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_complexd_sum_reduce(shmem_team_t team, double _Complex *dest, const double _Complex *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_complexf_sum_reduce(shmem_team_t team, float _Complex *dest, const float _Complex *source, size_t nreduce);

SHMEM_FUNCTION_ATTRIBUTES int shmem_char_prod_reduce(shmem_team_t team, char *dest, const char *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_schar_prod_reduce(shmem_team_t team, signed char *dest, const signed char *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_short_prod_reduce(shmem_team_t team, short *dest, const short *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int_prod_reduce(shmem_team_t team, int *dest, const int *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_long_prod_reduce(shmem_team_t team, long *dest, const long *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_longlong_prod_reduce(shmem_team_t team, long long *dest, const long long *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ptrdiff_prod_reduce(shmem_team_t team, ptrdiff_t *dest, const ptrdiff_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uchar_prod_reduce(shmem_team_t team, unsigned char *dest, const unsigned char *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ushort_prod_reduce(shmem_team_t team, unsigned short *dest, const unsigned short *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint_prod_reduce(shmem_team_t team, unsigned int *dest, const unsigned int *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ulong_prod_reduce(shmem_team_t team, unsigned long *dest, const unsigned long *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_ulonglong_prod_reduce(shmem_team_t team, unsigned long long *dest, const unsigned long long *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int8_prod_reduce(shmem_team_t team, int8_t *dest, const int8_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int16_prod_reduce(shmem_team_t team, int16_t *dest, const int16_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int32_prod_reduce(shmem_team_t team, int32_t *dest, const int32_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_int64_prod_reduce(shmem_team_t team, int64_t *dest, const int64_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint8_prod_reduce(shmem_team_t team, uint8_t *dest, const uint8_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint16_prod_reduce(shmem_team_t team, uint16_t *dest, const uint16_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint32_prod_reduce(shmem_team_t team, uint32_t *dest, const uint32_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_uint64_prod_reduce(shmem_team_t team, uint64_t *dest, const uint64_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_size_prod_reduce(shmem_team_t team, size_t *dest, const size_t *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_float_prod_reduce(shmem_team_t team, float *dest, const float *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_double_prod_reduce(shmem_team_t team, double *dest, const double *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_longdouble_prod_reduce(shmem_team_t team, long double *dest, const long double *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_complexd_prod_reduce(shmem_team_t team, double _Complex *dest, const double _Complex *source, size_t nreduce);
SHMEM_FUNCTION_ATTRIBUTES int shmem_complexf_prod_reduce(shmem_team_t team, float _Complex *dest, const float _Complex *source, size_t nreduce);

/* Signal Fetch */
SHMEM_FUNCTION_ATTRIBUTES uint64_t shmem_signal_fetch(const uint64_t *sig_addr);

SHMEM_FUNCTION_ATTRIBUTES void shmem_pcontrol(int level, ...);

/* C++ overloaded declarations */
#ifdef __cplusplus
} /* extern "C" */

#if __cplusplus >= 201402L
#define SHMEM_CXX_ATTRIBUTE_DEPRECATED [[deprecated]]
#else
#define SHMEM_CXX_ATTRIBUTE_DEPRECATED
#endif

/* Blocking block, scalar, and block-strided put */
SHMEM_BIND_CXX_RMA_EXTRAS(static inline void shmem_put(* dest, const * source,
                             size_t nelems, int pe) {
    shmem__put(dest, source, nelems, pe);
}
static inline void shmem_put(shmem_ctx_t ctx, * dest, const * source,
                             size_t nelems, int pe) {
    shmem_ctx__put(ctx, dest, source, nelems, pe);
},)static inline void shmem_put(float* dest, const float* source,
                             size_t nelems, int pe) {
    shmem_float_put(dest, source, nelems, pe);
}
static inline void shmem_put(shmem_ctx_t ctx, float* dest, const float* source,
                             size_t nelems, int pe) {
    shmem_ctx_float_put(ctx, dest, source, nelems, pe);
}
static inline void shmem_put(double* dest, const double* source,
                             size_t nelems, int pe) {
    shmem_double_put(dest, source, nelems, pe);
}
static inline void shmem_put(shmem_ctx_t ctx, double* dest, const double* source,
                             size_t nelems, int pe) {
    shmem_ctx_double_put(ctx, dest, source, nelems, pe);
}
static inline void shmem_put(long double* dest, const long double* source,
                             size_t nelems, int pe) {
    shmem_longdouble_put(dest, source, nelems, pe);
}
static inline void shmem_put(shmem_ctx_t ctx, long double* dest, const long double* source,
                             size_t nelems, int pe) {
    shmem_ctx_longdouble_put(ctx, dest, source, nelems, pe);
}
static inline void shmem_put(char* dest, const char* source,
                             size_t nelems, int pe) {
    shmem_char_put(dest, source, nelems, pe);
}
static inline void shmem_put(shmem_ctx_t ctx, char* dest, const char* source,
                             size_t nelems, int pe) {
    shmem_ctx_char_put(ctx, dest, source, nelems, pe);
}
static inline void shmem_put(signed char* dest, const signed char* source,
                             size_t nelems, int pe) {
    shmem_schar_put(dest, source, nelems, pe);
}
static inline void shmem_put(shmem_ctx_t ctx, signed char* dest, const signed char* source,
                             size_t nelems, int pe) {
    shmem_ctx_schar_put(ctx, dest, source, nelems, pe);
}
static inline void shmem_put(short* dest, const short* source,
                             size_t nelems, int pe) {
    shmem_short_put(dest, source, nelems, pe);
}
static inline void shmem_put(shmem_ctx_t ctx, short* dest, const short* source,
                             size_t nelems, int pe) {
    shmem_ctx_short_put(ctx, dest, source, nelems, pe);
}
static inline void shmem_put(int* dest, const int* source,
                             size_t nelems, int pe) {
    shmem_int_put(dest, source, nelems, pe);
}
static inline void shmem_put(shmem_ctx_t ctx, int* dest, const int* source,
                             size_t nelems, int pe) {
    shmem_ctx_int_put(ctx, dest, source, nelems, pe);
}
static inline void shmem_put(long* dest, const long* source,
                             size_t nelems, int pe) {
    shmem_long_put(dest, source, nelems, pe);
}
static inline void shmem_put(shmem_ctx_t ctx, long* dest, const long* source,
                             size_t nelems, int pe) {
    shmem_ctx_long_put(ctx, dest, source, nelems, pe);
}
static inline void shmem_put(long long* dest, const long long* source,
                             size_t nelems, int pe) {
    shmem_longlong_put(dest, source, nelems, pe);
}
static inline void shmem_put(shmem_ctx_t ctx, long long* dest, const long long* source,
                             size_t nelems, int pe) {
    shmem_ctx_longlong_put(ctx, dest, source, nelems, pe);
}
static inline void shmem_put(unsigned char* dest, const unsigned char* source,
                             size_t nelems, int pe) {
    shmem_uchar_put(dest, source, nelems, pe);
}
static inline void shmem_put(shmem_ctx_t ctx, unsigned char* dest, const unsigned char* source,
                             size_t nelems, int pe) {
    shmem_ctx_uchar_put(ctx, dest, source, nelems, pe);
}
static inline void shmem_put(unsigned short* dest, const unsigned short* source,
                             size_t nelems, int pe) {
    shmem_ushort_put(dest, source, nelems, pe);
}
static inline void shmem_put(shmem_ctx_t ctx, unsigned short* dest, const unsigned short* source,
                             size_t nelems, int pe) {
    shmem_ctx_ushort_put(ctx, dest, source, nelems, pe);
}
static inline void shmem_put(unsigned int* dest, const unsigned int* source,
                             size_t nelems, int pe) {
    shmem_uint_put(dest, source, nelems, pe);
}
static inline void shmem_put(shmem_ctx_t ctx, unsigned int* dest, const unsigned int* source,
                             size_t nelems, int pe) {
    shmem_ctx_uint_put(ctx, dest, source, nelems, pe);
}
static inline void shmem_put(unsigned long* dest, const unsigned long* source,
                             size_t nelems, int pe) {
    shmem_ulong_put(dest, source, nelems, pe);
}
static inline void shmem_put(shmem_ctx_t ctx, unsigned long* dest, const unsigned long* source,
                             size_t nelems, int pe) {
    shmem_ctx_ulong_put(ctx, dest, source, nelems, pe);
}
static inline void shmem_put(unsigned long long* dest, const unsigned long long* source,
                             size_t nelems, int pe) {
    shmem_ulonglong_put(dest, source, nelems, pe);
}
static inline void shmem_put(shmem_ctx_t ctx, unsigned long long* dest, const unsigned long long* source,
                             size_t nelems, int pe) {
    shmem_ctx_ulonglong_put(ctx, dest, source, nelems, pe);
}

SHMEM_BIND_CXX_RMA_EXTRAS(static inline void shmem_p(* dest,  value, int pe) {
    shmem__p(dest, value, pe);
}
static inline void shmem_p(shmem_ctx_t ctx, * dest,  value, int pe) {
    shmem_ctx__p(ctx, dest, value, pe);
},)static inline void shmem_p(float* dest, float value, int pe) {
    shmem_float_p(dest, value, pe);
}
static inline void shmem_p(shmem_ctx_t ctx, float* dest, float value, int pe) {
    shmem_ctx_float_p(ctx, dest, value, pe);
}
static inline void shmem_p(double* dest, double value, int pe) {
    shmem_double_p(dest, value, pe);
}
static inline void shmem_p(shmem_ctx_t ctx, double* dest, double value, int pe) {
    shmem_ctx_double_p(ctx, dest, value, pe);
}
static inline void shmem_p(long double* dest, long double value, int pe) {
    shmem_longdouble_p(dest, value, pe);
}
static inline void shmem_p(shmem_ctx_t ctx, long double* dest, long double value, int pe) {
    shmem_ctx_longdouble_p(ctx, dest, value, pe);
}
static inline void shmem_p(char* dest, char value, int pe) {
    shmem_char_p(dest, value, pe);
}
static inline void shmem_p(shmem_ctx_t ctx, char* dest, char value, int pe) {
    shmem_ctx_char_p(ctx, dest, value, pe);
}
static inline void shmem_p(signed char* dest, signed char value, int pe) {
    shmem_schar_p(dest, value, pe);
}
static inline void shmem_p(shmem_ctx_t ctx, signed char* dest, signed char value, int pe) {
    shmem_ctx_schar_p(ctx, dest, value, pe);
}
static inline void shmem_p(short* dest, short value, int pe) {
    shmem_short_p(dest, value, pe);
}
static inline void shmem_p(shmem_ctx_t ctx, short* dest, short value, int pe) {
    shmem_ctx_short_p(ctx, dest, value, pe);
}
static inline void shmem_p(int* dest, int value, int pe) {
    shmem_int_p(dest, value, pe);
}
static inline void shmem_p(shmem_ctx_t ctx, int* dest, int value, int pe) {
    shmem_ctx_int_p(ctx, dest, value, pe);
}
static inline void shmem_p(long* dest, long value, int pe) {
    shmem_long_p(dest, value, pe);
}
static inline void shmem_p(shmem_ctx_t ctx, long* dest, long value, int pe) {
    shmem_ctx_long_p(ctx, dest, value, pe);
}
static inline void shmem_p(long long* dest, long long value, int pe) {
    shmem_longlong_p(dest, value, pe);
}
static inline void shmem_p(shmem_ctx_t ctx, long long* dest, long long value, int pe) {
    shmem_ctx_longlong_p(ctx, dest, value, pe);
}
static inline void shmem_p(unsigned char* dest, unsigned char value, int pe) {
    shmem_uchar_p(dest, value, pe);
}
static inline void shmem_p(shmem_ctx_t ctx, unsigned char* dest, unsigned char value, int pe) {
    shmem_ctx_uchar_p(ctx, dest, value, pe);
}
static inline void shmem_p(unsigned short* dest, unsigned short value, int pe) {
    shmem_ushort_p(dest, value, pe);
}
static inline void shmem_p(shmem_ctx_t ctx, unsigned short* dest, unsigned short value, int pe) {
    shmem_ctx_ushort_p(ctx, dest, value, pe);
}
static inline void shmem_p(unsigned int* dest, unsigned int value, int pe) {
    shmem_uint_p(dest, value, pe);
}
static inline void shmem_p(shmem_ctx_t ctx, unsigned int* dest, unsigned int value, int pe) {
    shmem_ctx_uint_p(ctx, dest, value, pe);
}
static inline void shmem_p(unsigned long* dest, unsigned long value, int pe) {
    shmem_ulong_p(dest, value, pe);
}
static inline void shmem_p(shmem_ctx_t ctx, unsigned long* dest, unsigned long value, int pe) {
    shmem_ctx_ulong_p(ctx, dest, value, pe);
}
static inline void shmem_p(unsigned long long* dest, unsigned long long value, int pe) {
    shmem_ulonglong_p(dest, value, pe);
}
static inline void shmem_p(shmem_ctx_t ctx, unsigned long long* dest, unsigned long long value, int pe) {
    shmem_ctx_ulonglong_p(ctx, dest, value, pe);
}

SHMEM_BIND_CXX_RMA_EXTRAS(static inline void shmem_iput( *target, const  *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem__iput(target, source, tst, sst, len, pe);
}
static inline void shmem_iput(shmem_ctx_t ctx,  *target, const  *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ctx__iput(ctx, target, source, tst, sst, len, pe);
},)static inline void shmem_iput(float *target, const float *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_float_iput(target, source, tst, sst, len, pe);
}
static inline void shmem_iput(shmem_ctx_t ctx, float *target, const float *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ctx_float_iput(ctx, target, source, tst, sst, len, pe);
}
static inline void shmem_iput(double *target, const double *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_double_iput(target, source, tst, sst, len, pe);
}
static inline void shmem_iput(shmem_ctx_t ctx, double *target, const double *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ctx_double_iput(ctx, target, source, tst, sst, len, pe);
}
static inline void shmem_iput(long double *target, const long double *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_longdouble_iput(target, source, tst, sst, len, pe);
}
static inline void shmem_iput(shmem_ctx_t ctx, long double *target, const long double *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ctx_longdouble_iput(ctx, target, source, tst, sst, len, pe);
}
static inline void shmem_iput(char *target, const char *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_char_iput(target, source, tst, sst, len, pe);
}
static inline void shmem_iput(shmem_ctx_t ctx, char *target, const char *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ctx_char_iput(ctx, target, source, tst, sst, len, pe);
}
static inline void shmem_iput(signed char *target, const signed char *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_schar_iput(target, source, tst, sst, len, pe);
}
static inline void shmem_iput(shmem_ctx_t ctx, signed char *target, const signed char *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ctx_schar_iput(ctx, target, source, tst, sst, len, pe);
}
static inline void shmem_iput(short *target, const short *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_short_iput(target, source, tst, sst, len, pe);
}
static inline void shmem_iput(shmem_ctx_t ctx, short *target, const short *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ctx_short_iput(ctx, target, source, tst, sst, len, pe);
}
static inline void shmem_iput(int *target, const int *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_int_iput(target, source, tst, sst, len, pe);
}
static inline void shmem_iput(shmem_ctx_t ctx, int *target, const int *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ctx_int_iput(ctx, target, source, tst, sst, len, pe);
}
static inline void shmem_iput(long *target, const long *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_long_iput(target, source, tst, sst, len, pe);
}
static inline void shmem_iput(shmem_ctx_t ctx, long *target, const long *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ctx_long_iput(ctx, target, source, tst, sst, len, pe);
}
static inline void shmem_iput(long long *target, const long long *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_longlong_iput(target, source, tst, sst, len, pe);
}
static inline void shmem_iput(shmem_ctx_t ctx, long long *target, const long long *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ctx_longlong_iput(ctx, target, source, tst, sst, len, pe);
}
static inline void shmem_iput(unsigned char *target, const unsigned char *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_uchar_iput(target, source, tst, sst, len, pe);
}
static inline void shmem_iput(shmem_ctx_t ctx, unsigned char *target, const unsigned char *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ctx_uchar_iput(ctx, target, source, tst, sst, len, pe);
}
static inline void shmem_iput(unsigned short *target, const unsigned short *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ushort_iput(target, source, tst, sst, len, pe);
}
static inline void shmem_iput(shmem_ctx_t ctx, unsigned short *target, const unsigned short *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ctx_ushort_iput(ctx, target, source, tst, sst, len, pe);
}
static inline void shmem_iput(unsigned int *target, const unsigned int *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_uint_iput(target, source, tst, sst, len, pe);
}
static inline void shmem_iput(shmem_ctx_t ctx, unsigned int *target, const unsigned int *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ctx_uint_iput(ctx, target, source, tst, sst, len, pe);
}
static inline void shmem_iput(unsigned long *target, const unsigned long *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ulong_iput(target, source, tst, sst, len, pe);
}
static inline void shmem_iput(shmem_ctx_t ctx, unsigned long *target, const unsigned long *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ctx_ulong_iput(ctx, target, source, tst, sst, len, pe);
}
static inline void shmem_iput(unsigned long long *target, const unsigned long long *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ulonglong_iput(target, source, tst, sst, len, pe);
}
static inline void shmem_iput(shmem_ctx_t ctx, unsigned long long *target, const unsigned long long *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ctx_ulonglong_iput(ctx, target, source, tst, sst, len, pe);
}

/* Blocking block, scalar, and block-strided get */
SHMEM_BIND_CXX_RMA_EXTRAS(static inline void shmem_get(* dest, const * source,
                             size_t nelems, int pe) {
    shmem__get(dest, source, nelems, pe);
}
static inline void shmem_get(shmem_ctx_t ctx, * dest, const * source,
                             size_t nelems, int pe) {
    shmem_ctx__get(ctx, dest, source, nelems, pe);
},)static inline void shmem_get(float* dest, const float* source,
                             size_t nelems, int pe) {
    shmem_float_get(dest, source, nelems, pe);
}
static inline void shmem_get(shmem_ctx_t ctx, float* dest, const float* source,
                             size_t nelems, int pe) {
    shmem_ctx_float_get(ctx, dest, source, nelems, pe);
}
static inline void shmem_get(double* dest, const double* source,
                             size_t nelems, int pe) {
    shmem_double_get(dest, source, nelems, pe);
}
static inline void shmem_get(shmem_ctx_t ctx, double* dest, const double* source,
                             size_t nelems, int pe) {
    shmem_ctx_double_get(ctx, dest, source, nelems, pe);
}
static inline void shmem_get(long double* dest, const long double* source,
                             size_t nelems, int pe) {
    shmem_longdouble_get(dest, source, nelems, pe);
}
static inline void shmem_get(shmem_ctx_t ctx, long double* dest, const long double* source,
                             size_t nelems, int pe) {
    shmem_ctx_longdouble_get(ctx, dest, source, nelems, pe);
}
static inline void shmem_get(char* dest, const char* source,
                             size_t nelems, int pe) {
    shmem_char_get(dest, source, nelems, pe);
}
static inline void shmem_get(shmem_ctx_t ctx, char* dest, const char* source,
                             size_t nelems, int pe) {
    shmem_ctx_char_get(ctx, dest, source, nelems, pe);
}
static inline void shmem_get(signed char* dest, const signed char* source,
                             size_t nelems, int pe) {
    shmem_schar_get(dest, source, nelems, pe);
}
static inline void shmem_get(shmem_ctx_t ctx, signed char* dest, const signed char* source,
                             size_t nelems, int pe) {
    shmem_ctx_schar_get(ctx, dest, source, nelems, pe);
}
static inline void shmem_get(short* dest, const short* source,
                             size_t nelems, int pe) {
    shmem_short_get(dest, source, nelems, pe);
}
static inline void shmem_get(shmem_ctx_t ctx, short* dest, const short* source,
                             size_t nelems, int pe) {
    shmem_ctx_short_get(ctx, dest, source, nelems, pe);
}
static inline void shmem_get(int* dest, const int* source,
                             size_t nelems, int pe) {
    shmem_int_get(dest, source, nelems, pe);
}
static inline void shmem_get(shmem_ctx_t ctx, int* dest, const int* source,
                             size_t nelems, int pe) {
    shmem_ctx_int_get(ctx, dest, source, nelems, pe);
}
static inline void shmem_get(long* dest, const long* source,
                             size_t nelems, int pe) {
    shmem_long_get(dest, source, nelems, pe);
}
static inline void shmem_get(shmem_ctx_t ctx, long* dest, const long* source,
                             size_t nelems, int pe) {
    shmem_ctx_long_get(ctx, dest, source, nelems, pe);
}
static inline void shmem_get(long long* dest, const long long* source,
                             size_t nelems, int pe) {
    shmem_longlong_get(dest, source, nelems, pe);
}
static inline void shmem_get(shmem_ctx_t ctx, long long* dest, const long long* source,
                             size_t nelems, int pe) {
    shmem_ctx_longlong_get(ctx, dest, source, nelems, pe);
}
static inline void shmem_get(unsigned char* dest, const unsigned char* source,
                             size_t nelems, int pe) {
    shmem_uchar_get(dest, source, nelems, pe);
}
static inline void shmem_get(shmem_ctx_t ctx, unsigned char* dest, const unsigned char* source,
                             size_t nelems, int pe) {
    shmem_ctx_uchar_get(ctx, dest, source, nelems, pe);
}
static inline void shmem_get(unsigned short* dest, const unsigned short* source,
                             size_t nelems, int pe) {
    shmem_ushort_get(dest, source, nelems, pe);
}
static inline void shmem_get(shmem_ctx_t ctx, unsigned short* dest, const unsigned short* source,
                             size_t nelems, int pe) {
    shmem_ctx_ushort_get(ctx, dest, source, nelems, pe);
}
static inline void shmem_get(unsigned int* dest, const unsigned int* source,
                             size_t nelems, int pe) {
    shmem_uint_get(dest, source, nelems, pe);
}
static inline void shmem_get(shmem_ctx_t ctx, unsigned int* dest, const unsigned int* source,
                             size_t nelems, int pe) {
    shmem_ctx_uint_get(ctx, dest, source, nelems, pe);
}
static inline void shmem_get(unsigned long* dest, const unsigned long* source,
                             size_t nelems, int pe) {
    shmem_ulong_get(dest, source, nelems, pe);
}
static inline void shmem_get(shmem_ctx_t ctx, unsigned long* dest, const unsigned long* source,
                             size_t nelems, int pe) {
    shmem_ctx_ulong_get(ctx, dest, source, nelems, pe);
}
static inline void shmem_get(unsigned long long* dest, const unsigned long long* source,
                             size_t nelems, int pe) {
    shmem_ulonglong_get(dest, source, nelems, pe);
}
static inline void shmem_get(shmem_ctx_t ctx, unsigned long long* dest, const unsigned long long* source,
                             size_t nelems, int pe) {
    shmem_ctx_ulonglong_get(ctx, dest, source, nelems, pe);
}

SHMEM_BIND_CXX_RMA_EXTRAS(static inline  shmem_g(const * src, int pe) {
    return shmem__g(src, pe);
}
static inline  shmem_g(shmem_ctx_t ctx, const * src, int pe) {
    return shmem_ctx__g(ctx, src, pe);
},)static inline float shmem_g(const float* src, int pe) {
    return shmem_float_g(src, pe);
}
static inline float shmem_g(shmem_ctx_t ctx, const float* src, int pe) {
    return shmem_ctx_float_g(ctx, src, pe);
}
static inline double shmem_g(const double* src, int pe) {
    return shmem_double_g(src, pe);
}
static inline double shmem_g(shmem_ctx_t ctx, const double* src, int pe) {
    return shmem_ctx_double_g(ctx, src, pe);
}
static inline long double shmem_g(const long double* src, int pe) {
    return shmem_longdouble_g(src, pe);
}
static inline long double shmem_g(shmem_ctx_t ctx, const long double* src, int pe) {
    return shmem_ctx_longdouble_g(ctx, src, pe);
}
static inline char shmem_g(const char* src, int pe) {
    return shmem_char_g(src, pe);
}
static inline char shmem_g(shmem_ctx_t ctx, const char* src, int pe) {
    return shmem_ctx_char_g(ctx, src, pe);
}
static inline signed char shmem_g(const signed char* src, int pe) {
    return shmem_schar_g(src, pe);
}
static inline signed char shmem_g(shmem_ctx_t ctx, const signed char* src, int pe) {
    return shmem_ctx_schar_g(ctx, src, pe);
}
static inline short shmem_g(const short* src, int pe) {
    return shmem_short_g(src, pe);
}
static inline short shmem_g(shmem_ctx_t ctx, const short* src, int pe) {
    return shmem_ctx_short_g(ctx, src, pe);
}
static inline int shmem_g(const int* src, int pe) {
    return shmem_int_g(src, pe);
}
static inline int shmem_g(shmem_ctx_t ctx, const int* src, int pe) {
    return shmem_ctx_int_g(ctx, src, pe);
}
static inline long shmem_g(const long* src, int pe) {
    return shmem_long_g(src, pe);
}
static inline long shmem_g(shmem_ctx_t ctx, const long* src, int pe) {
    return shmem_ctx_long_g(ctx, src, pe);
}
static inline long long shmem_g(const long long* src, int pe) {
    return shmem_longlong_g(src, pe);
}
static inline long long shmem_g(shmem_ctx_t ctx, const long long* src, int pe) {
    return shmem_ctx_longlong_g(ctx, src, pe);
}
static inline unsigned char shmem_g(const unsigned char* src, int pe) {
    return shmem_uchar_g(src, pe);
}
static inline unsigned char shmem_g(shmem_ctx_t ctx, const unsigned char* src, int pe) {
    return shmem_ctx_uchar_g(ctx, src, pe);
}
static inline unsigned short shmem_g(const unsigned short* src, int pe) {
    return shmem_ushort_g(src, pe);
}
static inline unsigned short shmem_g(shmem_ctx_t ctx, const unsigned short* src, int pe) {
    return shmem_ctx_ushort_g(ctx, src, pe);
}
static inline unsigned int shmem_g(const unsigned int* src, int pe) {
    return shmem_uint_g(src, pe);
}
static inline unsigned int shmem_g(shmem_ctx_t ctx, const unsigned int* src, int pe) {
    return shmem_ctx_uint_g(ctx, src, pe);
}
static inline unsigned long shmem_g(const unsigned long* src, int pe) {
    return shmem_ulong_g(src, pe);
}
static inline unsigned long shmem_g(shmem_ctx_t ctx, const unsigned long* src, int pe) {
    return shmem_ctx_ulong_g(ctx, src, pe);
}
static inline unsigned long long shmem_g(const unsigned long long* src, int pe) {
    return shmem_ulonglong_g(src, pe);
}
static inline unsigned long long shmem_g(shmem_ctx_t ctx, const unsigned long long* src, int pe) {
    return shmem_ctx_ulonglong_g(ctx, src, pe);
}

SHMEM_BIND_CXX_RMA_EXTRAS(static inline void shmem_iget( *target, const  *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem__iget(target, source, tst, sst, len, pe);
}
static inline void shmem_iget(shmem_ctx_t ctx,  *target, const  *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ctx__iget(ctx, target, source, tst, sst, len, pe);
},)static inline void shmem_iget(float *target, const float *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_float_iget(target, source, tst, sst, len, pe);
}
static inline void shmem_iget(shmem_ctx_t ctx, float *target, const float *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ctx_float_iget(ctx, target, source, tst, sst, len, pe);
}
static inline void shmem_iget(double *target, const double *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_double_iget(target, source, tst, sst, len, pe);
}
static inline void shmem_iget(shmem_ctx_t ctx, double *target, const double *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ctx_double_iget(ctx, target, source, tst, sst, len, pe);
}
static inline void shmem_iget(long double *target, const long double *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_longdouble_iget(target, source, tst, sst, len, pe);
}
static inline void shmem_iget(shmem_ctx_t ctx, long double *target, const long double *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ctx_longdouble_iget(ctx, target, source, tst, sst, len, pe);
}
static inline void shmem_iget(char *target, const char *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_char_iget(target, source, tst, sst, len, pe);
}
static inline void shmem_iget(shmem_ctx_t ctx, char *target, const char *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ctx_char_iget(ctx, target, source, tst, sst, len, pe);
}
static inline void shmem_iget(signed char *target, const signed char *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_schar_iget(target, source, tst, sst, len, pe);
}
static inline void shmem_iget(shmem_ctx_t ctx, signed char *target, const signed char *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ctx_schar_iget(ctx, target, source, tst, sst, len, pe);
}
static inline void shmem_iget(short *target, const short *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_short_iget(target, source, tst, sst, len, pe);
}
static inline void shmem_iget(shmem_ctx_t ctx, short *target, const short *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ctx_short_iget(ctx, target, source, tst, sst, len, pe);
}
static inline void shmem_iget(int *target, const int *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_int_iget(target, source, tst, sst, len, pe);
}
static inline void shmem_iget(shmem_ctx_t ctx, int *target, const int *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ctx_int_iget(ctx, target, source, tst, sst, len, pe);
}
static inline void shmem_iget(long *target, const long *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_long_iget(target, source, tst, sst, len, pe);
}
static inline void shmem_iget(shmem_ctx_t ctx, long *target, const long *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ctx_long_iget(ctx, target, source, tst, sst, len, pe);
}
static inline void shmem_iget(long long *target, const long long *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_longlong_iget(target, source, tst, sst, len, pe);
}
static inline void shmem_iget(shmem_ctx_t ctx, long long *target, const long long *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ctx_longlong_iget(ctx, target, source, tst, sst, len, pe);
}
static inline void shmem_iget(unsigned char *target, const unsigned char *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_uchar_iget(target, source, tst, sst, len, pe);
}
static inline void shmem_iget(shmem_ctx_t ctx, unsigned char *target, const unsigned char *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ctx_uchar_iget(ctx, target, source, tst, sst, len, pe);
}
static inline void shmem_iget(unsigned short *target, const unsigned short *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ushort_iget(target, source, tst, sst, len, pe);
}
static inline void shmem_iget(shmem_ctx_t ctx, unsigned short *target, const unsigned short *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ctx_ushort_iget(ctx, target, source, tst, sst, len, pe);
}
static inline void shmem_iget(unsigned int *target, const unsigned int *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_uint_iget(target, source, tst, sst, len, pe);
}
static inline void shmem_iget(shmem_ctx_t ctx, unsigned int *target, const unsigned int *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ctx_uint_iget(ctx, target, source, tst, sst, len, pe);
}
static inline void shmem_iget(unsigned long *target, const unsigned long *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ulong_iget(target, source, tst, sst, len, pe);
}
static inline void shmem_iget(shmem_ctx_t ctx, unsigned long *target, const unsigned long *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ctx_ulong_iget(ctx, target, source, tst, sst, len, pe);
}
static inline void shmem_iget(unsigned long long *target, const unsigned long long *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ulonglong_iget(target, source, tst, sst, len, pe);
}
static inline void shmem_iget(shmem_ctx_t ctx, unsigned long long *target, const unsigned long long *source,
                              ptrdiff_t tst, ptrdiff_t sst,
                              size_t len, int pe) {
    shmem_ctx_ulonglong_iget(ctx, target, source, tst, sst, len, pe);
}

/* Nonblocking block put/get */
SHMEM_BIND_CXX_RMA_EXTRAS(static inline void shmem_put_nbi(* dest, const * source,
                                 size_t nelems, int pe) {
    shmem__put_nbi(dest, source, nelems, pe);
}
static inline void shmem_put_nbi(shmem_ctx_t ctx, * dest, const * source,
                                 size_t nelems, int pe) {
    shmem_ctx__put_nbi(ctx, dest, source, nelems, pe);
},)static inline void shmem_put_nbi(float* dest, const float* source,
                                 size_t nelems, int pe) {
    shmem_float_put_nbi(dest, source, nelems, pe);
}
static inline void shmem_put_nbi(shmem_ctx_t ctx, float* dest, const float* source,
                                 size_t nelems, int pe) {
    shmem_ctx_float_put_nbi(ctx, dest, source, nelems, pe);
}
static inline void shmem_put_nbi(double* dest, const double* source,
                                 size_t nelems, int pe) {
    shmem_double_put_nbi(dest, source, nelems, pe);
}
static inline void shmem_put_nbi(shmem_ctx_t ctx, double* dest, const double* source,
                                 size_t nelems, int pe) {
    shmem_ctx_double_put_nbi(ctx, dest, source, nelems, pe);
}
static inline void shmem_put_nbi(long double* dest, const long double* source,
                                 size_t nelems, int pe) {
    shmem_longdouble_put_nbi(dest, source, nelems, pe);
}
static inline void shmem_put_nbi(shmem_ctx_t ctx, long double* dest, const long double* source,
                                 size_t nelems, int pe) {
    shmem_ctx_longdouble_put_nbi(ctx, dest, source, nelems, pe);
}
static inline void shmem_put_nbi(char* dest, const char* source,
                                 size_t nelems, int pe) {
    shmem_char_put_nbi(dest, source, nelems, pe);
}
static inline void shmem_put_nbi(shmem_ctx_t ctx, char* dest, const char* source,
                                 size_t nelems, int pe) {
    shmem_ctx_char_put_nbi(ctx, dest, source, nelems, pe);
}
static inline void shmem_put_nbi(signed char* dest, const signed char* source,
                                 size_t nelems, int pe) {
    shmem_schar_put_nbi(dest, source, nelems, pe);
}
static inline void shmem_put_nbi(shmem_ctx_t ctx, signed char* dest, const signed char* source,
                                 size_t nelems, int pe) {
    shmem_ctx_schar_put_nbi(ctx, dest, source, nelems, pe);
}
static inline void shmem_put_nbi(short* dest, const short* source,
                                 size_t nelems, int pe) {
    shmem_short_put_nbi(dest, source, nelems, pe);
}
static inline void shmem_put_nbi(shmem_ctx_t ctx, short* dest, const short* source,
                                 size_t nelems, int pe) {
    shmem_ctx_short_put_nbi(ctx, dest, source, nelems, pe);
}
static inline void shmem_put_nbi(int* dest, const int* source,
                                 size_t nelems, int pe) {
    shmem_int_put_nbi(dest, source, nelems, pe);
}
static inline void shmem_put_nbi(shmem_ctx_t ctx, int* dest, const int* source,
                                 size_t nelems, int pe) {
    shmem_ctx_int_put_nbi(ctx, dest, source, nelems, pe);
}
static inline void shmem_put_nbi(long* dest, const long* source,
                                 size_t nelems, int pe) {
    shmem_long_put_nbi(dest, source, nelems, pe);
}
static inline void shmem_put_nbi(shmem_ctx_t ctx, long* dest, const long* source,
                                 size_t nelems, int pe) {
    shmem_ctx_long_put_nbi(ctx, dest, source, nelems, pe);
}
static inline void shmem_put_nbi(long long* dest, const long long* source,
                                 size_t nelems, int pe) {
    shmem_longlong_put_nbi(dest, source, nelems, pe);
}
static inline void shmem_put_nbi(shmem_ctx_t ctx, long long* dest, const long long* source,
                                 size_t nelems, int pe) {
    shmem_ctx_longlong_put_nbi(ctx, dest, source, nelems, pe);
}
static inline void shmem_put_nbi(unsigned char* dest, const unsigned char* source,
                                 size_t nelems, int pe) {
    shmem_uchar_put_nbi(dest, source, nelems, pe);
}
static inline void shmem_put_nbi(shmem_ctx_t ctx, unsigned char* dest, const unsigned char* source,
                                 size_t nelems, int pe) {
    shmem_ctx_uchar_put_nbi(ctx, dest, source, nelems, pe);
}
static inline void shmem_put_nbi(unsigned short* dest, const unsigned short* source,
                                 size_t nelems, int pe) {
    shmem_ushort_put_nbi(dest, source, nelems, pe);
}
static inline void shmem_put_nbi(shmem_ctx_t ctx, unsigned short* dest, const unsigned short* source,
                                 size_t nelems, int pe) {
    shmem_ctx_ushort_put_nbi(ctx, dest, source, nelems, pe);
}
static inline void shmem_put_nbi(unsigned int* dest, const unsigned int* source,
                                 size_t nelems, int pe) {
    shmem_uint_put_nbi(dest, source, nelems, pe);
}
static inline void shmem_put_nbi(shmem_ctx_t ctx, unsigned int* dest, const unsigned int* source,
                                 size_t nelems, int pe) {
    shmem_ctx_uint_put_nbi(ctx, dest, source, nelems, pe);
}
static inline void shmem_put_nbi(unsigned long* dest, const unsigned long* source,
                                 size_t nelems, int pe) {
    shmem_ulong_put_nbi(dest, source, nelems, pe);
}
static inline void shmem_put_nbi(shmem_ctx_t ctx, unsigned long* dest, const unsigned long* source,
                                 size_t nelems, int pe) {
    shmem_ctx_ulong_put_nbi(ctx, dest, source, nelems, pe);
}
static inline void shmem_put_nbi(unsigned long long* dest, const unsigned long long* source,
                                 size_t nelems, int pe) {
    shmem_ulonglong_put_nbi(dest, source, nelems, pe);
}
static inline void shmem_put_nbi(shmem_ctx_t ctx, unsigned long long* dest, const unsigned long long* source,
                                 size_t nelems, int pe) {
    shmem_ctx_ulonglong_put_nbi(ctx, dest, source, nelems, pe);
}

SHMEM_BIND_CXX_RMA_EXTRAS(static inline void shmem_get_nbi(* dest, const * source,
                                 size_t nelems, int pe) {
    shmem__get_nbi(dest, source, nelems, pe);
}
static inline void shmem_get_nbi(shmem_ctx_t ctx, * dest, const * source,
                                 size_t nelems, int pe) {
    shmem_ctx__get_nbi(ctx, dest, source, nelems, pe);
},)static inline void shmem_get_nbi(float* dest, const float* source,
                                 size_t nelems, int pe) {
    shmem_float_get_nbi(dest, source, nelems, pe);
}
static inline void shmem_get_nbi(shmem_ctx_t ctx, float* dest, const float* source,
                                 size_t nelems, int pe) {
    shmem_ctx_float_get_nbi(ctx, dest, source, nelems, pe);
}
static inline void shmem_get_nbi(double* dest, const double* source,
                                 size_t nelems, int pe) {
    shmem_double_get_nbi(dest, source, nelems, pe);
}
static inline void shmem_get_nbi(shmem_ctx_t ctx, double* dest, const double* source,
                                 size_t nelems, int pe) {
    shmem_ctx_double_get_nbi(ctx, dest, source, nelems, pe);
}
static inline void shmem_get_nbi(long double* dest, const long double* source,
                                 size_t nelems, int pe) {
    shmem_longdouble_get_nbi(dest, source, nelems, pe);
}
static inline void shmem_get_nbi(shmem_ctx_t ctx, long double* dest, const long double* source,
                                 size_t nelems, int pe) {
    shmem_ctx_longdouble_get_nbi(ctx, dest, source, nelems, pe);
}
static inline void shmem_get_nbi(char* dest, const char* source,
                                 size_t nelems, int pe) {
    shmem_char_get_nbi(dest, source, nelems, pe);
}
static inline void shmem_get_nbi(shmem_ctx_t ctx, char* dest, const char* source,
                                 size_t nelems, int pe) {
    shmem_ctx_char_get_nbi(ctx, dest, source, nelems, pe);
}
static inline void shmem_get_nbi(signed char* dest, const signed char* source,
                                 size_t nelems, int pe) {
    shmem_schar_get_nbi(dest, source, nelems, pe);
}
static inline void shmem_get_nbi(shmem_ctx_t ctx, signed char* dest, const signed char* source,
                                 size_t nelems, int pe) {
    shmem_ctx_schar_get_nbi(ctx, dest, source, nelems, pe);
}
static inline void shmem_get_nbi(short* dest, const short* source,
                                 size_t nelems, int pe) {
    shmem_short_get_nbi(dest, source, nelems, pe);
}
static inline void shmem_get_nbi(shmem_ctx_t ctx, short* dest, const short* source,
                                 size_t nelems, int pe) {
    shmem_ctx_short_get_nbi(ctx, dest, source, nelems, pe);
}
static inline void shmem_get_nbi(int* dest, const int* source,
                                 size_t nelems, int pe) {
    shmem_int_get_nbi(dest, source, nelems, pe);
}
static inline void shmem_get_nbi(shmem_ctx_t ctx, int* dest, const int* source,
                                 size_t nelems, int pe) {
    shmem_ctx_int_get_nbi(ctx, dest, source, nelems, pe);
}
static inline void shmem_get_nbi(long* dest, const long* source,
                                 size_t nelems, int pe) {
    shmem_long_get_nbi(dest, source, nelems, pe);
}
static inline void shmem_get_nbi(shmem_ctx_t ctx, long* dest, const long* source,
                                 size_t nelems, int pe) {
    shmem_ctx_long_get_nbi(ctx, dest, source, nelems, pe);
}
static inline void shmem_get_nbi(long long* dest, const long long* source,
                                 size_t nelems, int pe) {
    shmem_longlong_get_nbi(dest, source, nelems, pe);
}
static inline void shmem_get_nbi(shmem_ctx_t ctx, long long* dest, const long long* source,
                                 size_t nelems, int pe) {
    shmem_ctx_longlong_get_nbi(ctx, dest, source, nelems, pe);
}
static inline void shmem_get_nbi(unsigned char* dest, const unsigned char* source,
                                 size_t nelems, int pe) {
    shmem_uchar_get_nbi(dest, source, nelems, pe);
}
static inline void shmem_get_nbi(shmem_ctx_t ctx, unsigned char* dest, const unsigned char* source,
                                 size_t nelems, int pe) {
    shmem_ctx_uchar_get_nbi(ctx, dest, source, nelems, pe);
}
static inline void shmem_get_nbi(unsigned short* dest, const unsigned short* source,
                                 size_t nelems, int pe) {
    shmem_ushort_get_nbi(dest, source, nelems, pe);
}
static inline void shmem_get_nbi(shmem_ctx_t ctx, unsigned short* dest, const unsigned short* source,
                                 size_t nelems, int pe) {
    shmem_ctx_ushort_get_nbi(ctx, dest, source, nelems, pe);
}
static inline void shmem_get_nbi(unsigned int* dest, const unsigned int* source,
                                 size_t nelems, int pe) {
    shmem_uint_get_nbi(dest, source, nelems, pe);
}
static inline void shmem_get_nbi(shmem_ctx_t ctx, unsigned int* dest, const unsigned int* source,
                                 size_t nelems, int pe) {
    shmem_ctx_uint_get_nbi(ctx, dest, source, nelems, pe);
}
static inline void shmem_get_nbi(unsigned long* dest, const unsigned long* source,
                                 size_t nelems, int pe) {
    shmem_ulong_get_nbi(dest, source, nelems, pe);
}
static inline void shmem_get_nbi(shmem_ctx_t ctx, unsigned long* dest, const unsigned long* source,
                                 size_t nelems, int pe) {
    shmem_ctx_ulong_get_nbi(ctx, dest, source, nelems, pe);
}
static inline void shmem_get_nbi(unsigned long long* dest, const unsigned long long* source,
                                 size_t nelems, int pe) {
    shmem_ulonglong_get_nbi(dest, source, nelems, pe);
}
static inline void shmem_get_nbi(shmem_ctx_t ctx, unsigned long long* dest, const unsigned long long* source,
                                 size_t nelems, int pe) {
    shmem_ctx_ulonglong_get_nbi(ctx, dest, source, nelems, pe);
}

/* Nonblocking swap operations */
SHMEM_BIND_CXX_EXTENDED_AMO_EXTRAS(static inline void shmem_atomic_swap_nbi( *fetch,  *target,  value, int pe) {
    shmem__atomic_swap_nbi(fetch, target, value, pe);
}
static inline void shmem_atomic_swap_nbi(shmem_ctx_t ctx,  *fetch,  *target,  value, int pe) {
    shmem_ctx__atomic_swap_nbi(ctx, fetch, target, value, pe);
},)static inline void shmem_atomic_swap_nbi(int *fetch, int *target, int value, int pe) {
    shmem_int_atomic_swap_nbi(fetch, target, value, pe);
}
static inline void shmem_atomic_swap_nbi(shmem_ctx_t ctx, int *fetch, int *target, int value, int pe) {
    shmem_ctx_int_atomic_swap_nbi(ctx, fetch, target, value, pe);
}
static inline void shmem_atomic_swap_nbi(long *fetch, long *target, long value, int pe) {
    shmem_long_atomic_swap_nbi(fetch, target, value, pe);
}
static inline void shmem_atomic_swap_nbi(shmem_ctx_t ctx, long *fetch, long *target, long value, int pe) {
    shmem_ctx_long_atomic_swap_nbi(ctx, fetch, target, value, pe);
}
static inline void shmem_atomic_swap_nbi(long long *fetch, long long *target, long long value, int pe) {
    shmem_longlong_atomic_swap_nbi(fetch, target, value, pe);
}
static inline void shmem_atomic_swap_nbi(shmem_ctx_t ctx, long long *fetch, long long *target, long long value, int pe) {
    shmem_ctx_longlong_atomic_swap_nbi(ctx, fetch, target, value, pe);
}
static inline void shmem_atomic_swap_nbi(unsigned int *fetch, unsigned int *target, unsigned int value, int pe) {
    shmem_uint_atomic_swap_nbi(fetch, target, value, pe);
}
static inline void shmem_atomic_swap_nbi(shmem_ctx_t ctx, unsigned int *fetch, unsigned int *target, unsigned int value, int pe) {
    shmem_ctx_uint_atomic_swap_nbi(ctx, fetch, target, value, pe);
}
static inline void shmem_atomic_swap_nbi(unsigned long *fetch, unsigned long *target, unsigned long value, int pe) {
    shmem_ulong_atomic_swap_nbi(fetch, target, value, pe);
}
static inline void shmem_atomic_swap_nbi(shmem_ctx_t ctx, unsigned long *fetch, unsigned long *target, unsigned long value, int pe) {
    shmem_ctx_ulong_atomic_swap_nbi(ctx, fetch, target, value, pe);
}
static inline void shmem_atomic_swap_nbi(unsigned long long *fetch, unsigned long long *target, unsigned long long value, int pe) {
    shmem_ulonglong_atomic_swap_nbi(fetch, target, value, pe);
}
static inline void shmem_atomic_swap_nbi(shmem_ctx_t ctx, unsigned long long *fetch, unsigned long long *target, unsigned long long value, int pe) {
    shmem_ctx_ulonglong_atomic_swap_nbi(ctx, fetch, target, value, pe);
}
static inline void shmem_atomic_swap_nbi(float *fetch, float *target, float value, int pe) {
    shmem_float_atomic_swap_nbi(fetch, target, value, pe);
}
static inline void shmem_atomic_swap_nbi(shmem_ctx_t ctx, float *fetch, float *target, float value, int pe) {
    shmem_ctx_float_atomic_swap_nbi(ctx, fetch, target, value, pe);
}
static inline void shmem_atomic_swap_nbi(double *fetch, double *target, double value, int pe) {
    shmem_double_atomic_swap_nbi(fetch, target, value, pe);
}
static inline void shmem_atomic_swap_nbi(shmem_ctx_t ctx, double *fetch, double *target, double value, int pe) {
    shmem_ctx_double_atomic_swap_nbi(ctx, fetch, target, value, pe);
}

SHMEM_BIND_CXX_AMO_EXTRAS(static inline void shmem_atomic_compare_swap_nbi( *fetch,  *target,  cond,  value, int pe) {
    shmem__atomic_compare_swap_nbi(fetch, target, cond, value, pe);
}
static inline void shmem_atomic_compare_swap_nbi(shmem_ctx_t ctx,  *fetch,  *target,  cond,  value, int pe) {
    shmem_ctx__atomic_compare_swap_nbi(ctx, fetch, target, cond, value, pe);
},)static inline void shmem_atomic_compare_swap_nbi(int *fetch, int *target, int cond, int value, int pe) {
    shmem_int_atomic_compare_swap_nbi(fetch, target, cond, value, pe);
}
static inline void shmem_atomic_compare_swap_nbi(shmem_ctx_t ctx, int *fetch, int *target, int cond, int value, int pe) {
    shmem_ctx_int_atomic_compare_swap_nbi(ctx, fetch, target, cond, value, pe);
}
static inline void shmem_atomic_compare_swap_nbi(long *fetch, long *target, long cond, long value, int pe) {
    shmem_long_atomic_compare_swap_nbi(fetch, target, cond, value, pe);
}
static inline void shmem_atomic_compare_swap_nbi(shmem_ctx_t ctx, long *fetch, long *target, long cond, long value, int pe) {
    shmem_ctx_long_atomic_compare_swap_nbi(ctx, fetch, target, cond, value, pe);
}
static inline void shmem_atomic_compare_swap_nbi(long long *fetch, long long *target, long long cond, long long value, int pe) {
    shmem_longlong_atomic_compare_swap_nbi(fetch, target, cond, value, pe);
}
static inline void shmem_atomic_compare_swap_nbi(shmem_ctx_t ctx, long long *fetch, long long *target, long long cond, long long value, int pe) {
    shmem_ctx_longlong_atomic_compare_swap_nbi(ctx, fetch, target, cond, value, pe);
}
static inline void shmem_atomic_compare_swap_nbi(unsigned int *fetch, unsigned int *target, unsigned int cond, unsigned int value, int pe) {
    shmem_uint_atomic_compare_swap_nbi(fetch, target, cond, value, pe);
}
static inline void shmem_atomic_compare_swap_nbi(shmem_ctx_t ctx, unsigned int *fetch, unsigned int *target, unsigned int cond, unsigned int value, int pe) {
    shmem_ctx_uint_atomic_compare_swap_nbi(ctx, fetch, target, cond, value, pe);
}
static inline void shmem_atomic_compare_swap_nbi(unsigned long *fetch, unsigned long *target, unsigned long cond, unsigned long value, int pe) {
    shmem_ulong_atomic_compare_swap_nbi(fetch, target, cond, value, pe);
}
static inline void shmem_atomic_compare_swap_nbi(shmem_ctx_t ctx, unsigned long *fetch, unsigned long *target, unsigned long cond, unsigned long value, int pe) {
    shmem_ctx_ulong_atomic_compare_swap_nbi(ctx, fetch, target, cond, value, pe);
}
static inline void shmem_atomic_compare_swap_nbi(unsigned long long *fetch, unsigned long long *target, unsigned long long cond, unsigned long long value, int pe) {
    shmem_ulonglong_atomic_compare_swap_nbi(fetch, target, cond, value, pe);
}
static inline void shmem_atomic_compare_swap_nbi(shmem_ctx_t ctx, unsigned long long *fetch, unsigned long long *target, unsigned long long cond, unsigned long long value, int pe) {
    shmem_ctx_ulonglong_atomic_compare_swap_nbi(ctx, fetch, target, cond, value, pe);
}

/* Nonblocking fetching AMOs */
SHMEM_BIND_CXX_EXTENDED_AMO_EXTRAS(static inline void shmem_atomic_fetch_nbi( *fetch, const  *target, int pe) {
    shmem__atomic_fetch_nbi(fetch, target, pe);
}
static inline void shmem_atomic_fetch_nbi(shmem_ctx_t ctx,  *fetch, const  *target, int pe) {
    shmem_ctx__atomic_fetch_nbi(ctx, fetch, target, pe);
},)static inline void shmem_atomic_fetch_nbi(int *fetch, const int *target, int pe) {
    shmem_int_atomic_fetch_nbi(fetch, target, pe);
}
static inline void shmem_atomic_fetch_nbi(shmem_ctx_t ctx, int *fetch, const int *target, int pe) {
    shmem_ctx_int_atomic_fetch_nbi(ctx, fetch, target, pe);
}
static inline void shmem_atomic_fetch_nbi(long *fetch, const long *target, int pe) {
    shmem_long_atomic_fetch_nbi(fetch, target, pe);
}
static inline void shmem_atomic_fetch_nbi(shmem_ctx_t ctx, long *fetch, const long *target, int pe) {
    shmem_ctx_long_atomic_fetch_nbi(ctx, fetch, target, pe);
}
static inline void shmem_atomic_fetch_nbi(long long *fetch, const long long *target, int pe) {
    shmem_longlong_atomic_fetch_nbi(fetch, target, pe);
}
static inline void shmem_atomic_fetch_nbi(shmem_ctx_t ctx, long long *fetch, const long long *target, int pe) {
    shmem_ctx_longlong_atomic_fetch_nbi(ctx, fetch, target, pe);
}
static inline void shmem_atomic_fetch_nbi(unsigned int *fetch, const unsigned int *target, int pe) {
    shmem_uint_atomic_fetch_nbi(fetch, target, pe);
}
static inline void shmem_atomic_fetch_nbi(shmem_ctx_t ctx, unsigned int *fetch, const unsigned int *target, int pe) {
    shmem_ctx_uint_atomic_fetch_nbi(ctx, fetch, target, pe);
}
static inline void shmem_atomic_fetch_nbi(unsigned long *fetch, const unsigned long *target, int pe) {
    shmem_ulong_atomic_fetch_nbi(fetch, target, pe);
}
static inline void shmem_atomic_fetch_nbi(shmem_ctx_t ctx, unsigned long *fetch, const unsigned long *target, int pe) {
    shmem_ctx_ulong_atomic_fetch_nbi(ctx, fetch, target, pe);
}
static inline void shmem_atomic_fetch_nbi(unsigned long long *fetch, const unsigned long long *target, int pe) {
    shmem_ulonglong_atomic_fetch_nbi(fetch, target, pe);
}
static inline void shmem_atomic_fetch_nbi(shmem_ctx_t ctx, unsigned long long *fetch, const unsigned long long *target, int pe) {
    shmem_ctx_ulonglong_atomic_fetch_nbi(ctx, fetch, target, pe);
}
static inline void shmem_atomic_fetch_nbi(float *fetch, const float *target, int pe) {
    shmem_float_atomic_fetch_nbi(fetch, target, pe);
}
static inline void shmem_atomic_fetch_nbi(shmem_ctx_t ctx, float *fetch, const float *target, int pe) {
    shmem_ctx_float_atomic_fetch_nbi(ctx, fetch, target, pe);
}
static inline void shmem_atomic_fetch_nbi(double *fetch, const double *target, int pe) {
    shmem_double_atomic_fetch_nbi(fetch, target, pe);
}
static inline void shmem_atomic_fetch_nbi(shmem_ctx_t ctx, double *fetch, const double *target, int pe) {
    shmem_ctx_double_atomic_fetch_nbi(ctx, fetch, target, pe);
}

SHMEM_BIND_CXX_AMO_EXTRAS(static inline void shmem_atomic_fetch_inc_nbi( *fetch,  *target, int pe) {
    shmem__atomic_fetch_inc_nbi(fetch, target, pe);
}
static inline void shmem_atomic_fetch_inc_nbi(shmem_ctx_t ctx,  *fetch,  *target, int pe) {
    shmem_ctx__atomic_fetch_inc_nbi(ctx, fetch, target, pe);
},)static inline void shmem_atomic_fetch_inc_nbi(int *fetch, int *target, int pe) {
    shmem_int_atomic_fetch_inc_nbi(fetch, target, pe);
}
static inline void shmem_atomic_fetch_inc_nbi(shmem_ctx_t ctx, int *fetch, int *target, int pe) {
    shmem_ctx_int_atomic_fetch_inc_nbi(ctx, fetch, target, pe);
}
static inline void shmem_atomic_fetch_inc_nbi(long *fetch, long *target, int pe) {
    shmem_long_atomic_fetch_inc_nbi(fetch, target, pe);
}
static inline void shmem_atomic_fetch_inc_nbi(shmem_ctx_t ctx, long *fetch, long *target, int pe) {
    shmem_ctx_long_atomic_fetch_inc_nbi(ctx, fetch, target, pe);
}
static inline void shmem_atomic_fetch_inc_nbi(long long *fetch, long long *target, int pe) {
    shmem_longlong_atomic_fetch_inc_nbi(fetch, target, pe);
}
static inline void shmem_atomic_fetch_inc_nbi(shmem_ctx_t ctx, long long *fetch, long long *target, int pe) {
    shmem_ctx_longlong_atomic_fetch_inc_nbi(ctx, fetch, target, pe);
}
static inline void shmem_atomic_fetch_inc_nbi(unsigned int *fetch, unsigned int *target, int pe) {
    shmem_uint_atomic_fetch_inc_nbi(fetch, target, pe);
}
static inline void shmem_atomic_fetch_inc_nbi(shmem_ctx_t ctx, unsigned int *fetch, unsigned int *target, int pe) {
    shmem_ctx_uint_atomic_fetch_inc_nbi(ctx, fetch, target, pe);
}
static inline void shmem_atomic_fetch_inc_nbi(unsigned long *fetch, unsigned long *target, int pe) {
    shmem_ulong_atomic_fetch_inc_nbi(fetch, target, pe);
}
static inline void shmem_atomic_fetch_inc_nbi(shmem_ctx_t ctx, unsigned long *fetch, unsigned long *target, int pe) {
    shmem_ctx_ulong_atomic_fetch_inc_nbi(ctx, fetch, target, pe);
}
static inline void shmem_atomic_fetch_inc_nbi(unsigned long long *fetch, unsigned long long *target, int pe) {
    shmem_ulonglong_atomic_fetch_inc_nbi(fetch, target, pe);
}
static inline void shmem_atomic_fetch_inc_nbi(shmem_ctx_t ctx, unsigned long long *fetch, unsigned long long *target, int pe) {
    shmem_ctx_ulonglong_atomic_fetch_inc_nbi(ctx, fetch, target, pe);
}

SHMEM_BIND_CXX_AMO_EXTRAS(static inline void shmem_atomic_fetch_add_nbi( *fetch,  *target,  value, int pe) {
    shmem__atomic_fetch_add_nbi(fetch, target, value, pe);
}
static inline void shmem_atomic_fetch_add_nbi(shmem_ctx_t ctx,  *fetch,  *target,  value, int pe) {
    shmem_ctx__atomic_fetch_add_nbi(ctx, fetch, target, value, pe);
},)static inline void shmem_atomic_fetch_add_nbi(int *fetch, int *target, int value, int pe) {
    shmem_int_atomic_fetch_add_nbi(fetch, target, value, pe);
}
static inline void shmem_atomic_fetch_add_nbi(shmem_ctx_t ctx, int *fetch, int *target, int value, int pe) {
    shmem_ctx_int_atomic_fetch_add_nbi(ctx, fetch, target, value, pe);
}
static inline void shmem_atomic_fetch_add_nbi(long *fetch, long *target, long value, int pe) {
    shmem_long_atomic_fetch_add_nbi(fetch, target, value, pe);
}
static inline void shmem_atomic_fetch_add_nbi(shmem_ctx_t ctx, long *fetch, long *target, long value, int pe) {
    shmem_ctx_long_atomic_fetch_add_nbi(ctx, fetch, target, value, pe);
}
static inline void shmem_atomic_fetch_add_nbi(long long *fetch, long long *target, long long value, int pe) {
    shmem_longlong_atomic_fetch_add_nbi(fetch, target, value, pe);
}
static inline void shmem_atomic_fetch_add_nbi(shmem_ctx_t ctx, long long *fetch, long long *target, long long value, int pe) {
    shmem_ctx_longlong_atomic_fetch_add_nbi(ctx, fetch, target, value, pe);
}
static inline void shmem_atomic_fetch_add_nbi(unsigned int *fetch, unsigned int *target, unsigned int value, int pe) {
    shmem_uint_atomic_fetch_add_nbi(fetch, target, value, pe);
}
static inline void shmem_atomic_fetch_add_nbi(shmem_ctx_t ctx, unsigned int *fetch, unsigned int *target, unsigned int value, int pe) {
    shmem_ctx_uint_atomic_fetch_add_nbi(ctx, fetch, target, value, pe);
}
static inline void shmem_atomic_fetch_add_nbi(unsigned long *fetch, unsigned long *target, unsigned long value, int pe) {
    shmem_ulong_atomic_fetch_add_nbi(fetch, target, value, pe);
}
static inline void shmem_atomic_fetch_add_nbi(shmem_ctx_t ctx, unsigned long *fetch, unsigned long *target, unsigned long value, int pe) {
    shmem_ctx_ulong_atomic_fetch_add_nbi(ctx, fetch, target, value, pe);
}
static inline void shmem_atomic_fetch_add_nbi(unsigned long long *fetch, unsigned long long *target, unsigned long long value, int pe) {
    shmem_ulonglong_atomic_fetch_add_nbi(fetch, target, value, pe);
}
static inline void shmem_atomic_fetch_add_nbi(shmem_ctx_t ctx, unsigned long long *fetch, unsigned long long *target, unsigned long long value, int pe) {
    shmem_ctx_ulonglong_atomic_fetch_add_nbi(ctx, fetch, target, value, pe);
}

SHMEM_BIND_CXX_BITWISE_AMO_EXTRAS(static inline void shmem_atomic_fetch_and_nbi( *fetch,  *dest,  value, int pe) {
    shmem__atomic_fetch_and_nbi(fetch, dest, value, pe);
}
static inline void shmem_atomic_fetch_and_nbi(shmem_ctx_t ctx,  *fetch,  *dest,  value, int pe) {
    shmem_ctx__atomic_fetch_and_nbi(ctx, fetch, dest, value, pe);
},)static inline void shmem_atomic_fetch_and_nbi(int32_t *fetch, int32_t *dest, int32_t value, int pe) {
    shmem_int32_atomic_fetch_and_nbi(fetch, dest, value, pe);
}
static inline void shmem_atomic_fetch_and_nbi(shmem_ctx_t ctx, int32_t *fetch, int32_t *dest, int32_t value, int pe) {
    shmem_ctx_int32_atomic_fetch_and_nbi(ctx, fetch, dest, value, pe);
}
static inline void shmem_atomic_fetch_and_nbi(int64_t *fetch, int64_t *dest, int64_t value, int pe) {
    shmem_int64_atomic_fetch_and_nbi(fetch, dest, value, pe);
}
static inline void shmem_atomic_fetch_and_nbi(shmem_ctx_t ctx, int64_t *fetch, int64_t *dest, int64_t value, int pe) {
    shmem_ctx_int64_atomic_fetch_and_nbi(ctx, fetch, dest, value, pe);
}
static inline void shmem_atomic_fetch_and_nbi(unsigned int *fetch, unsigned int *dest, unsigned int value, int pe) {
    shmem_uint_atomic_fetch_and_nbi(fetch, dest, value, pe);
}
static inline void shmem_atomic_fetch_and_nbi(shmem_ctx_t ctx, unsigned int *fetch, unsigned int *dest, unsigned int value, int pe) {
    shmem_ctx_uint_atomic_fetch_and_nbi(ctx, fetch, dest, value, pe);
}
static inline void shmem_atomic_fetch_and_nbi(unsigned long *fetch, unsigned long *dest, unsigned long value, int pe) {
    shmem_ulong_atomic_fetch_and_nbi(fetch, dest, value, pe);
}
static inline void shmem_atomic_fetch_and_nbi(shmem_ctx_t ctx, unsigned long *fetch, unsigned long *dest, unsigned long value, int pe) {
    shmem_ctx_ulong_atomic_fetch_and_nbi(ctx, fetch, dest, value, pe);
}
static inline void shmem_atomic_fetch_and_nbi(unsigned long long *fetch, unsigned long long *dest, unsigned long long value, int pe) {
    shmem_ulonglong_atomic_fetch_and_nbi(fetch, dest, value, pe);
}
static inline void shmem_atomic_fetch_and_nbi(shmem_ctx_t ctx, unsigned long long *fetch, unsigned long long *dest, unsigned long long value, int pe) {
    shmem_ctx_ulonglong_atomic_fetch_and_nbi(ctx, fetch, dest, value, pe);
}

SHMEM_BIND_CXX_BITWISE_AMO_EXTRAS(static inline void shmem_atomic_fetch_or_nbi( *fetch,  *dest,  value, int pe) {
    shmem__atomic_fetch_or_nbi(fetch, dest, value, pe);
}
static inline void shmem_atomic_fetch_or_nbi(shmem_ctx_t ctx,  *fetch,  *dest,  value, int pe) {
    shmem_ctx__atomic_fetch_or_nbi(ctx, fetch, dest, value, pe);
},)static inline void shmem_atomic_fetch_or_nbi(int32_t *fetch, int32_t *dest, int32_t value, int pe) {
    shmem_int32_atomic_fetch_or_nbi(fetch, dest, value, pe);
}
static inline void shmem_atomic_fetch_or_nbi(shmem_ctx_t ctx, int32_t *fetch, int32_t *dest, int32_t value, int pe) {
    shmem_ctx_int32_atomic_fetch_or_nbi(ctx, fetch, dest, value, pe);
}
static inline void shmem_atomic_fetch_or_nbi(int64_t *fetch, int64_t *dest, int64_t value, int pe) {
    shmem_int64_atomic_fetch_or_nbi(fetch, dest, value, pe);
}
static inline void shmem_atomic_fetch_or_nbi(shmem_ctx_t ctx, int64_t *fetch, int64_t *dest, int64_t value, int pe) {
    shmem_ctx_int64_atomic_fetch_or_nbi(ctx, fetch, dest, value, pe);
}
static inline void shmem_atomic_fetch_or_nbi(unsigned int *fetch, unsigned int *dest, unsigned int value, int pe) {
    shmem_uint_atomic_fetch_or_nbi(fetch, dest, value, pe);
}
static inline void shmem_atomic_fetch_or_nbi(shmem_ctx_t ctx, unsigned int *fetch, unsigned int *dest, unsigned int value, int pe) {
    shmem_ctx_uint_atomic_fetch_or_nbi(ctx, fetch, dest, value, pe);
}
static inline void shmem_atomic_fetch_or_nbi(unsigned long *fetch, unsigned long *dest, unsigned long value, int pe) {
    shmem_ulong_atomic_fetch_or_nbi(fetch, dest, value, pe);
}
static inline void shmem_atomic_fetch_or_nbi(shmem_ctx_t ctx, unsigned long *fetch, unsigned long *dest, unsigned long value, int pe) {
    shmem_ctx_ulong_atomic_fetch_or_nbi(ctx, fetch, dest, value, pe);
}
static inline void shmem_atomic_fetch_or_nbi(unsigned long long *fetch, unsigned long long *dest, unsigned long long value, int pe) {
    shmem_ulonglong_atomic_fetch_or_nbi(fetch, dest, value, pe);
}
static inline void shmem_atomic_fetch_or_nbi(shmem_ctx_t ctx, unsigned long long *fetch, unsigned long long *dest, unsigned long long value, int pe) {
    shmem_ctx_ulonglong_atomic_fetch_or_nbi(ctx, fetch, dest, value, pe);
}

SHMEM_BIND_CXX_BITWISE_AMO_EXTRAS(static inline void shmem_atomic_fetch_xor_nbi( *fetch,  *dest,  value, int pe) {
    shmem__atomic_fetch_xor_nbi(fetch, dest, value, pe);
}
static inline void shmem_atomic_fetch_xor_nbi(shmem_ctx_t ctx,  *fetch,  *dest,  value, int pe) {
    shmem_ctx__atomic_fetch_xor_nbi(ctx, fetch, dest, value, pe);
},)static inline void shmem_atomic_fetch_xor_nbi(int32_t *fetch, int32_t *dest, int32_t value, int pe) {
    shmem_int32_atomic_fetch_xor_nbi(fetch, dest, value, pe);
}
static inline void shmem_atomic_fetch_xor_nbi(shmem_ctx_t ctx, int32_t *fetch, int32_t *dest, int32_t value, int pe) {
    shmem_ctx_int32_atomic_fetch_xor_nbi(ctx, fetch, dest, value, pe);
}
static inline void shmem_atomic_fetch_xor_nbi(int64_t *fetch, int64_t *dest, int64_t value, int pe) {
    shmem_int64_atomic_fetch_xor_nbi(fetch, dest, value, pe);
}
static inline void shmem_atomic_fetch_xor_nbi(shmem_ctx_t ctx, int64_t *fetch, int64_t *dest, int64_t value, int pe) {
    shmem_ctx_int64_atomic_fetch_xor_nbi(ctx, fetch, dest, value, pe);
}
static inline void shmem_atomic_fetch_xor_nbi(unsigned int *fetch, unsigned int *dest, unsigned int value, int pe) {
    shmem_uint_atomic_fetch_xor_nbi(fetch, dest, value, pe);
}
static inline void shmem_atomic_fetch_xor_nbi(shmem_ctx_t ctx, unsigned int *fetch, unsigned int *dest, unsigned int value, int pe) {
    shmem_ctx_uint_atomic_fetch_xor_nbi(ctx, fetch, dest, value, pe);
}
static inline void shmem_atomic_fetch_xor_nbi(unsigned long *fetch, unsigned long *dest, unsigned long value, int pe) {
    shmem_ulong_atomic_fetch_xor_nbi(fetch, dest, value, pe);
}
static inline void shmem_atomic_fetch_xor_nbi(shmem_ctx_t ctx, unsigned long *fetch, unsigned long *dest, unsigned long value, int pe) {
    shmem_ctx_ulong_atomic_fetch_xor_nbi(ctx, fetch, dest, value, pe);
}
static inline void shmem_atomic_fetch_xor_nbi(unsigned long long *fetch, unsigned long long *dest, unsigned long long value, int pe) {
    shmem_ulonglong_atomic_fetch_xor_nbi(fetch, dest, value, pe);
}
static inline void shmem_atomic_fetch_xor_nbi(shmem_ctx_t ctx, unsigned long long *fetch, unsigned long long *dest, unsigned long long value, int pe) {
    shmem_ctx_ulonglong_atomic_fetch_xor_nbi(ctx, fetch, dest, value, pe);
}

/* Team Collective Routines */
SHMEM_BIND_CXX_RMA_EXTRAS(static inline int shmem_alltoall(shmem_team_t team, * dest, const * source,
                                  size_t nelems) {
    return shmem__alltoall(team, dest, source, nelems);
},)static inline int shmem_alltoall(shmem_team_t team, float* dest, const float* source,
                                  size_t nelems) {
    return shmem_float_alltoall(team, dest, source, nelems);
}
static inline int shmem_alltoall(shmem_team_t team, double* dest, const double* source,
                                  size_t nelems) {
    return shmem_double_alltoall(team, dest, source, nelems);
}
static inline int shmem_alltoall(shmem_team_t team, long double* dest, const long double* source,
                                  size_t nelems) {
    return shmem_longdouble_alltoall(team, dest, source, nelems);
}
static inline int shmem_alltoall(shmem_team_t team, char* dest, const char* source,
                                  size_t nelems) {
    return shmem_char_alltoall(team, dest, source, nelems);
}
static inline int shmem_alltoall(shmem_team_t team, signed char* dest, const signed char* source,
                                  size_t nelems) {
    return shmem_schar_alltoall(team, dest, source, nelems);
}
static inline int shmem_alltoall(shmem_team_t team, short* dest, const short* source,
                                  size_t nelems) {
    return shmem_short_alltoall(team, dest, source, nelems);
}
static inline int shmem_alltoall(shmem_team_t team, int* dest, const int* source,
                                  size_t nelems) {
    return shmem_int_alltoall(team, dest, source, nelems);
}
static inline int shmem_alltoall(shmem_team_t team, long* dest, const long* source,
                                  size_t nelems) {
    return shmem_long_alltoall(team, dest, source, nelems);
}
static inline int shmem_alltoall(shmem_team_t team, long long* dest, const long long* source,
                                  size_t nelems) {
    return shmem_longlong_alltoall(team, dest, source, nelems);
}
static inline int shmem_alltoall(shmem_team_t team, unsigned char* dest, const unsigned char* source,
                                  size_t nelems) {
    return shmem_uchar_alltoall(team, dest, source, nelems);
}
static inline int shmem_alltoall(shmem_team_t team, unsigned short* dest, const unsigned short* source,
                                  size_t nelems) {
    return shmem_ushort_alltoall(team, dest, source, nelems);
}
static inline int shmem_alltoall(shmem_team_t team, unsigned int* dest, const unsigned int* source,
                                  size_t nelems) {
    return shmem_uint_alltoall(team, dest, source, nelems);
}
static inline int shmem_alltoall(shmem_team_t team, unsigned long* dest, const unsigned long* source,
                                  size_t nelems) {
    return shmem_ulong_alltoall(team, dest, source, nelems);
}
static inline int shmem_alltoall(shmem_team_t team, unsigned long long* dest, const unsigned long long* source,
                                  size_t nelems) {
    return shmem_ulonglong_alltoall(team, dest, source, nelems);
}

SHMEM_BIND_CXX_RMA_EXTRAS(static inline int shmem_alltoalls(shmem_team_t team, * dest, const * source,
                                   ptrdiff_t dst, ptrdiff_t sst, size_t nelems) {
    return shmem__alltoalls(team, dest, source, dst, sst, nelems);
},)static inline int shmem_alltoalls(shmem_team_t team, float* dest, const float* source,
                                   ptrdiff_t dst, ptrdiff_t sst, size_t nelems) {
    return shmem_float_alltoalls(team, dest, source, dst, sst, nelems);
}
static inline int shmem_alltoalls(shmem_team_t team, double* dest, const double* source,
                                   ptrdiff_t dst, ptrdiff_t sst, size_t nelems) {
    return shmem_double_alltoalls(team, dest, source, dst, sst, nelems);
}
static inline int shmem_alltoalls(shmem_team_t team, long double* dest, const long double* source,
                                   ptrdiff_t dst, ptrdiff_t sst, size_t nelems) {
    return shmem_longdouble_alltoalls(team, dest, source, dst, sst, nelems);
}
static inline int shmem_alltoalls(shmem_team_t team, char* dest, const char* source,
                                   ptrdiff_t dst, ptrdiff_t sst, size_t nelems) {
    return shmem_char_alltoalls(team, dest, source, dst, sst, nelems);
}
static inline int shmem_alltoalls(shmem_team_t team, signed char* dest, const signed char* source,
                                   ptrdiff_t dst, ptrdiff_t sst, size_t nelems) {
    return shmem_schar_alltoalls(team, dest, source, dst, sst, nelems);
}
static inline int shmem_alltoalls(shmem_team_t team, short* dest, const short* source,
                                   ptrdiff_t dst, ptrdiff_t sst, size_t nelems) {
    return shmem_short_alltoalls(team, dest, source, dst, sst, nelems);
}
static inline int shmem_alltoalls(shmem_team_t team, int* dest, const int* source,
                                   ptrdiff_t dst, ptrdiff_t sst, size_t nelems) {
    return shmem_int_alltoalls(team, dest, source, dst, sst, nelems);
}
static inline int shmem_alltoalls(shmem_team_t team, long* dest, const long* source,
                                   ptrdiff_t dst, ptrdiff_t sst, size_t nelems) {
    return shmem_long_alltoalls(team, dest, source, dst, sst, nelems);
}
static inline int shmem_alltoalls(shmem_team_t team, long long* dest, const long long* source,
                                   ptrdiff_t dst, ptrdiff_t sst, size_t nelems) {
    return shmem_longlong_alltoalls(team, dest, source, dst, sst, nelems);
}
static inline int shmem_alltoalls(shmem_team_t team, unsigned char* dest, const unsigned char* source,
                                   ptrdiff_t dst, ptrdiff_t sst, size_t nelems) {
    return shmem_uchar_alltoalls(team, dest, source, dst, sst, nelems);
}
static inline int shmem_alltoalls(shmem_team_t team, unsigned short* dest, const unsigned short* source,
                                   ptrdiff_t dst, ptrdiff_t sst, size_t nelems) {
    return shmem_ushort_alltoalls(team, dest, source, dst, sst, nelems);
}
static inline int shmem_alltoalls(shmem_team_t team, unsigned int* dest, const unsigned int* source,
                                   ptrdiff_t dst, ptrdiff_t sst, size_t nelems) {
    return shmem_uint_alltoalls(team, dest, source, dst, sst, nelems);
}
static inline int shmem_alltoalls(shmem_team_t team, unsigned long* dest, const unsigned long* source,
                                   ptrdiff_t dst, ptrdiff_t sst, size_t nelems) {
    return shmem_ulong_alltoalls(team, dest, source, dst, sst, nelems);
}
static inline int shmem_alltoalls(shmem_team_t team, unsigned long long* dest, const unsigned long long* source,
                                   ptrdiff_t dst, ptrdiff_t sst, size_t nelems) {
    return shmem_ulonglong_alltoalls(team, dest, source, dst, sst, nelems);
}

SHMEM_BIND_CXX_RMA_EXTRAS(static inline int shmem_broadcast(shmem_team_t team, * dest, const * source,
                                   size_t nelems, int PE_root) {
    return shmem__broadcast(team, dest, source, nelems, PE_root);
},)static inline int shmem_broadcast(shmem_team_t team, float* dest, const float* source,
                                   size_t nelems, int PE_root) {
    return shmem_float_broadcast(team, dest, source, nelems, PE_root);
}
static inline int shmem_broadcast(shmem_team_t team, double* dest, const double* source,
                                   size_t nelems, int PE_root) {
    return shmem_double_broadcast(team, dest, source, nelems, PE_root);
}
static inline int shmem_broadcast(shmem_team_t team, long double* dest, const long double* source,
                                   size_t nelems, int PE_root) {
    return shmem_longdouble_broadcast(team, dest, source, nelems, PE_root);
}
static inline int shmem_broadcast(shmem_team_t team, char* dest, const char* source,
                                   size_t nelems, int PE_root) {
    return shmem_char_broadcast(team, dest, source, nelems, PE_root);
}
static inline int shmem_broadcast(shmem_team_t team, signed char* dest, const signed char* source,
                                   size_t nelems, int PE_root) {
    return shmem_schar_broadcast(team, dest, source, nelems, PE_root);
}
static inline int shmem_broadcast(shmem_team_t team, short* dest, const short* source,
                                   size_t nelems, int PE_root) {
    return shmem_short_broadcast(team, dest, source, nelems, PE_root);
}
static inline int shmem_broadcast(shmem_team_t team, int* dest, const int* source,
                                   size_t nelems, int PE_root) {
    return shmem_int_broadcast(team, dest, source, nelems, PE_root);
}
static inline int shmem_broadcast(shmem_team_t team, long* dest, const long* source,
                                   size_t nelems, int PE_root) {
    return shmem_long_broadcast(team, dest, source, nelems, PE_root);
}
static inline int shmem_broadcast(shmem_team_t team, long long* dest, const long long* source,
                                   size_t nelems, int PE_root) {
    return shmem_longlong_broadcast(team, dest, source, nelems, PE_root);
}
static inline int shmem_broadcast(shmem_team_t team, unsigned char* dest, const unsigned char* source,
                                   size_t nelems, int PE_root) {
    return shmem_uchar_broadcast(team, dest, source, nelems, PE_root);
}
static inline int shmem_broadcast(shmem_team_t team, unsigned short* dest, const unsigned short* source,
                                   size_t nelems, int PE_root) {
    return shmem_ushort_broadcast(team, dest, source, nelems, PE_root);
}
static inline int shmem_broadcast(shmem_team_t team, unsigned int* dest, const unsigned int* source,
                                   size_t nelems, int PE_root) {
    return shmem_uint_broadcast(team, dest, source, nelems, PE_root);
}
static inline int shmem_broadcast(shmem_team_t team, unsigned long* dest, const unsigned long* source,
                                   size_t nelems, int PE_root) {
    return shmem_ulong_broadcast(team, dest, source, nelems, PE_root);
}
static inline int shmem_broadcast(shmem_team_t team, unsigned long long* dest, const unsigned long long* source,
                                   size_t nelems, int PE_root) {
    return shmem_ulonglong_broadcast(team, dest, source, nelems, PE_root);
}

SHMEM_BIND_CXX_RMA_EXTRAS(static inline int shmem_collect(shmem_team_t team, * dest, const * source,
                                 size_t nelems) {
    return shmem__collect(team, dest, source, nelems);
},)static inline int shmem_collect(shmem_team_t team, float* dest, const float* source,
                                 size_t nelems) {
    return shmem_float_collect(team, dest, source, nelems);
}
static inline int shmem_collect(shmem_team_t team, double* dest, const double* source,
                                 size_t nelems) {
    return shmem_double_collect(team, dest, source, nelems);
}
static inline int shmem_collect(shmem_team_t team, long double* dest, const long double* source,
                                 size_t nelems) {
    return shmem_longdouble_collect(team, dest, source, nelems);
}
static inline int shmem_collect(shmem_team_t team, char* dest, const char* source,
                                 size_t nelems) {
    return shmem_char_collect(team, dest, source, nelems);
}
static inline int shmem_collect(shmem_team_t team, signed char* dest, const signed char* source,
                                 size_t nelems) {
    return shmem_schar_collect(team, dest, source, nelems);
}
static inline int shmem_collect(shmem_team_t team, short* dest, const short* source,
                                 size_t nelems) {
    return shmem_short_collect(team, dest, source, nelems);
}
static inline int shmem_collect(shmem_team_t team, int* dest, const int* source,
                                 size_t nelems) {
    return shmem_int_collect(team, dest, source, nelems);
}
static inline int shmem_collect(shmem_team_t team, long* dest, const long* source,
                                 size_t nelems) {
    return shmem_long_collect(team, dest, source, nelems);
}
static inline int shmem_collect(shmem_team_t team, long long* dest, const long long* source,
                                 size_t nelems) {
    return shmem_longlong_collect(team, dest, source, nelems);
}
static inline int shmem_collect(shmem_team_t team, unsigned char* dest, const unsigned char* source,
                                 size_t nelems) {
    return shmem_uchar_collect(team, dest, source, nelems);
}
static inline int shmem_collect(shmem_team_t team, unsigned short* dest, const unsigned short* source,
                                 size_t nelems) {
    return shmem_ushort_collect(team, dest, source, nelems);
}
static inline int shmem_collect(shmem_team_t team, unsigned int* dest, const unsigned int* source,
                                 size_t nelems) {
    return shmem_uint_collect(team, dest, source, nelems);
}
static inline int shmem_collect(shmem_team_t team, unsigned long* dest, const unsigned long* source,
                                 size_t nelems) {
    return shmem_ulong_collect(team, dest, source, nelems);
}
static inline int shmem_collect(shmem_team_t team, unsigned long long* dest, const unsigned long long* source,
                                 size_t nelems) {
    return shmem_ulonglong_collect(team, dest, source, nelems);
}

SHMEM_BIND_CXX_RMA_EXTRAS(static inline int shmem_fcollect(shmem_team_t team, * dest, const * source,
                                  size_t nelems) {
    return shmem__fcollect(team, dest, source, nelems);
},)static inline int shmem_fcollect(shmem_team_t team, float* dest, const float* source,
                                  size_t nelems) {
    return shmem_float_fcollect(team, dest, source, nelems);
}
static inline int shmem_fcollect(shmem_team_t team, double* dest, const double* source,
                                  size_t nelems) {
    return shmem_double_fcollect(team, dest, source, nelems);
}
static inline int shmem_fcollect(shmem_team_t team, long double* dest, const long double* source,
                                  size_t nelems) {
    return shmem_longdouble_fcollect(team, dest, source, nelems);
}
static inline int shmem_fcollect(shmem_team_t team, char* dest, const char* source,
                                  size_t nelems) {
    return shmem_char_fcollect(team, dest, source, nelems);
}
static inline int shmem_fcollect(shmem_team_t team, signed char* dest, const signed char* source,
                                  size_t nelems) {
    return shmem_schar_fcollect(team, dest, source, nelems);
}
static inline int shmem_fcollect(shmem_team_t team, short* dest, const short* source,
                                  size_t nelems) {
    return shmem_short_fcollect(team, dest, source, nelems);
}
static inline int shmem_fcollect(shmem_team_t team, int* dest, const int* source,
                                  size_t nelems) {
    return shmem_int_fcollect(team, dest, source, nelems);
}
static inline int shmem_fcollect(shmem_team_t team, long* dest, const long* source,
                                  size_t nelems) {
    return shmem_long_fcollect(team, dest, source, nelems);
}
static inline int shmem_fcollect(shmem_team_t team, long long* dest, const long long* source,
                                  size_t nelems) {
    return shmem_longlong_fcollect(team, dest, source, nelems);
}
static inline int shmem_fcollect(shmem_team_t team, unsigned char* dest, const unsigned char* source,
                                  size_t nelems) {
    return shmem_uchar_fcollect(team, dest, source, nelems);
}
static inline int shmem_fcollect(shmem_team_t team, unsigned short* dest, const unsigned short* source,
                                  size_t nelems) {
    return shmem_ushort_fcollect(team, dest, source, nelems);
}
static inline int shmem_fcollect(shmem_team_t team, unsigned int* dest, const unsigned int* source,
                                  size_t nelems) {
    return shmem_uint_fcollect(team, dest, source, nelems);
}
static inline int shmem_fcollect(shmem_team_t team, unsigned long* dest, const unsigned long* source,
                                  size_t nelems) {
    return shmem_ulong_fcollect(team, dest, source, nelems);
}
static inline int shmem_fcollect(shmem_team_t team, unsigned long long* dest, const unsigned long long* source,
                                  size_t nelems) {
    return shmem_ulonglong_fcollect(team, dest, source, nelems);
}

static inline int shmem_and_reduce(shmem_team_t team, unsigned char* dest, const unsigned char* source,
                                    size_t nreduce) {
    return shmem_uchar_and_reduce(team, dest, source, nreduce);
}
static inline int shmem_and_reduce(shmem_team_t team, short* dest, const short* source,
                                    size_t nreduce) {
    return shmem_short_and_reduce(team, dest, source, nreduce);
}
static inline int shmem_and_reduce(shmem_team_t team, unsigned short* dest, const unsigned short* source,
                                    size_t nreduce) {
    return shmem_ushort_and_reduce(team, dest, source, nreduce);
}
static inline int shmem_and_reduce(shmem_team_t team, int* dest, const int* source,
                                    size_t nreduce) {
    return shmem_int_and_reduce(team, dest, source, nreduce);
}
static inline int shmem_and_reduce(shmem_team_t team, unsigned int* dest, const unsigned int* source,
                                    size_t nreduce) {
    return shmem_uint_and_reduce(team, dest, source, nreduce);
}
static inline int shmem_and_reduce(shmem_team_t team, long* dest, const long* source,
                                    size_t nreduce) {
    return shmem_long_and_reduce(team, dest, source, nreduce);
}
static inline int shmem_and_reduce(shmem_team_t team, unsigned long* dest, const unsigned long* source,
                                    size_t nreduce) {
    return shmem_ulong_and_reduce(team, dest, source, nreduce);
}
static inline int shmem_and_reduce(shmem_team_t team, long long* dest, const long long* source,
                                    size_t nreduce) {
    return shmem_longlong_and_reduce(team, dest, source, nreduce);
}
static inline int shmem_and_reduce(shmem_team_t team, unsigned long long* dest, const unsigned long long* source,
                                    size_t nreduce) {
    return shmem_ulonglong_and_reduce(team, dest, source, nreduce);
}

static inline int shmem_min_reduce(shmem_team_t team, short* dest, const short* source,
                                    size_t nreduce) {
    return shmem_short_min_reduce(team, dest, source, nreduce);
}
static inline int shmem_min_reduce(shmem_team_t team, unsigned short* dest, const unsigned short* source,
                                    size_t nreduce) {
    return shmem_ushort_min_reduce(team, dest, source, nreduce);
}
static inline int shmem_min_reduce(shmem_team_t team, int* dest, const int* source,
                                    size_t nreduce) {
    return shmem_int_min_reduce(team, dest, source, nreduce);
}
static inline int shmem_min_reduce(shmem_team_t team, unsigned int* dest, const unsigned int* source,
                                    size_t nreduce) {
    return shmem_uint_min_reduce(team, dest, source, nreduce);
}
static inline int shmem_min_reduce(shmem_team_t team, long* dest, const long* source,
                                    size_t nreduce) {
    return shmem_long_min_reduce(team, dest, source, nreduce);
}
static inline int shmem_min_reduce(shmem_team_t team, unsigned long* dest, const unsigned long* source,
                                    size_t nreduce) {
    return shmem_ulong_min_reduce(team, dest, source, nreduce);
}
static inline int shmem_min_reduce(shmem_team_t team, long long* dest, const long long* source,
                                    size_t nreduce) {
    return shmem_longlong_min_reduce(team, dest, source, nreduce);
}
static inline int shmem_min_reduce(shmem_team_t team, unsigned long long* dest, const unsigned long long* source,
                                    size_t nreduce) {
    return shmem_ulonglong_min_reduce(team, dest, source, nreduce);
}
static inline int shmem_min_reduce(shmem_team_t team, float* dest, const float* source,
                                    size_t nreduce) {
    return shmem_float_min_reduce(team, dest, source, nreduce);
}
static inline int shmem_min_reduce(shmem_team_t team, double* dest, const double* source,
                                    size_t nreduce) {
    return shmem_double_min_reduce(team, dest, source, nreduce);
}
static inline int shmem_min_reduce(shmem_team_t team, long double* dest, const long double* source,
                                    size_t nreduce) {
    return shmem_longdouble_min_reduce(team, dest, source, nreduce);
}

static inline int shmem_max_reduce(shmem_team_t team, short* dest, const short* source,
                                    size_t nreduce) {
    return shmem_short_max_reduce(team, dest, source, nreduce);
}
static inline int shmem_max_reduce(shmem_team_t team, unsigned short* dest, const unsigned short* source,
                                    size_t nreduce) {
    return shmem_ushort_max_reduce(team, dest, source, nreduce);
}
static inline int shmem_max_reduce(shmem_team_t team, int* dest, const int* source,
                                    size_t nreduce) {
    return shmem_int_max_reduce(team, dest, source, nreduce);
}
static inline int shmem_max_reduce(shmem_team_t team, unsigned int* dest, const unsigned int* source,
                                    size_t nreduce) {
    return shmem_uint_max_reduce(team, dest, source, nreduce);
}
static inline int shmem_max_reduce(shmem_team_t team, long* dest, const long* source,
                                    size_t nreduce) {
    return shmem_long_max_reduce(team, dest, source, nreduce);
}
static inline int shmem_max_reduce(shmem_team_t team, unsigned long* dest, const unsigned long* source,
                                    size_t nreduce) {
    return shmem_ulong_max_reduce(team, dest, source, nreduce);
}
static inline int shmem_max_reduce(shmem_team_t team, long long* dest, const long long* source,
                                    size_t nreduce) {
    return shmem_longlong_max_reduce(team, dest, source, nreduce);
}
static inline int shmem_max_reduce(shmem_team_t team, unsigned long long* dest, const unsigned long long* source,
                                    size_t nreduce) {
    return shmem_ulonglong_max_reduce(team, dest, source, nreduce);
}
static inline int shmem_max_reduce(shmem_team_t team, float* dest, const float* source,
                                    size_t nreduce) {
    return shmem_float_max_reduce(team, dest, source, nreduce);
}
static inline int shmem_max_reduce(shmem_team_t team, double* dest, const double* source,
                                    size_t nreduce) {
    return shmem_double_max_reduce(team, dest, source, nreduce);
}
static inline int shmem_max_reduce(shmem_team_t team, long double* dest, const long double* source,
                                    size_t nreduce) {
    return shmem_longdouble_max_reduce(team, dest, source, nreduce);
}

static inline int shmem_sum_reduce(shmem_team_t team, short* dest, const short* source,
                                    size_t nreduce) {
    return shmem_short_sum_reduce(team, dest, source, nreduce);
}
static inline int shmem_sum_reduce(shmem_team_t team, unsigned short* dest, const unsigned short* source,
                                    size_t nreduce) {
    return shmem_ushort_sum_reduce(team, dest, source, nreduce);
}
static inline int shmem_sum_reduce(shmem_team_t team, int* dest, const int* source,
                                    size_t nreduce) {
    return shmem_int_sum_reduce(team, dest, source, nreduce);
}
static inline int shmem_sum_reduce(shmem_team_t team, unsigned int* dest, const unsigned int* source,
                                    size_t nreduce) {
    return shmem_uint_sum_reduce(team, dest, source, nreduce);
}
static inline int shmem_sum_reduce(shmem_team_t team, long* dest, const long* source,
                                    size_t nreduce) {
    return shmem_long_sum_reduce(team, dest, source, nreduce);
}
static inline int shmem_sum_reduce(shmem_team_t team, unsigned long* dest, const unsigned long* source,
                                    size_t nreduce) {
    return shmem_ulong_sum_reduce(team, dest, source, nreduce);
}
static inline int shmem_sum_reduce(shmem_team_t team, long long* dest, const long long* source,
                                    size_t nreduce) {
    return shmem_longlong_sum_reduce(team, dest, source, nreduce);
}
static inline int shmem_sum_reduce(shmem_team_t team, unsigned long long* dest, const unsigned long long* source,
                                    size_t nreduce) {
    return shmem_ulonglong_sum_reduce(team, dest, source, nreduce);
}
static inline int shmem_sum_reduce(shmem_team_t team, float* dest, const float* source,
                                    size_t nreduce) {
    return shmem_float_sum_reduce(team, dest, source, nreduce);
}
static inline int shmem_sum_reduce(shmem_team_t team, double* dest, const double* source,
                                    size_t nreduce) {
    return shmem_double_sum_reduce(team, dest, source, nreduce);
}
static inline int shmem_sum_reduce(shmem_team_t team, long double* dest, const long double* source,
                                    size_t nreduce) {
    return shmem_longdouble_sum_reduce(team, dest, source, nreduce);
}
static inline int shmem_sum_reduce(shmem_team_t team, double _Complex* dest, const double _Complex* source,
                                    size_t nreduce) {
    return shmem_complexd_sum_reduce(team, dest, source, nreduce);
}
static inline int shmem_sum_reduce(shmem_team_t team, float _Complex* dest, const float _Complex* source,
                                    size_t nreduce) {
    return shmem_complexf_sum_reduce(team, dest, source, nreduce);
}

static inline int shmem_prod_reduce(shmem_team_t team, short* dest, const short* source,
                                     size_t nreduce) {
    return shmem_short_prod_reduce(team, dest, source, nreduce);
}
static inline int shmem_prod_reduce(shmem_team_t team, unsigned short* dest, const unsigned short* source,
                                     size_t nreduce) {
    return shmem_ushort_prod_reduce(team, dest, source, nreduce);
}
static inline int shmem_prod_reduce(shmem_team_t team, int* dest, const int* source,
                                     size_t nreduce) {
    return shmem_int_prod_reduce(team, dest, source, nreduce);
}
static inline int shmem_prod_reduce(shmem_team_t team, unsigned int* dest, const unsigned int* source,
                                     size_t nreduce) {
    return shmem_uint_prod_reduce(team, dest, source, nreduce);
}
static inline int shmem_prod_reduce(shmem_team_t team, long* dest, const long* source,
                                     size_t nreduce) {
    return shmem_long_prod_reduce(team, dest, source, nreduce);
}
static inline int shmem_prod_reduce(shmem_team_t team, unsigned long* dest, const unsigned long* source,
                                     size_t nreduce) {
    return shmem_ulong_prod_reduce(team, dest, source, nreduce);
}
static inline int shmem_prod_reduce(shmem_team_t team, long long* dest, const long long* source,
                                     size_t nreduce) {
    return shmem_longlong_prod_reduce(team, dest, source, nreduce);
}
static inline int shmem_prod_reduce(shmem_team_t team, unsigned long long* dest, const unsigned long long* source,
                                     size_t nreduce) {
    return shmem_ulonglong_prod_reduce(team, dest, source, nreduce);
}
static inline int shmem_prod_reduce(shmem_team_t team, float* dest, const float* source,
                                     size_t nreduce) {
    return shmem_float_prod_reduce(team, dest, source, nreduce);
}
static inline int shmem_prod_reduce(shmem_team_t team, double* dest, const double* source,
                                     size_t nreduce) {
    return shmem_double_prod_reduce(team, dest, source, nreduce);
}
static inline int shmem_prod_reduce(shmem_team_t team, long double* dest, const long double* source,
                                     size_t nreduce) {
    return shmem_longdouble_prod_reduce(team, dest, source, nreduce);
}
static inline int shmem_prod_reduce(shmem_team_t team, double _Complex* dest, const double _Complex* source,
                                     size_t nreduce) {
    return shmem_complexd_prod_reduce(team, dest, source, nreduce);
}
static inline int shmem_prod_reduce(shmem_team_t team, float _Complex* dest, const float _Complex* source,
                                     size_t nreduce) {
    return shmem_complexf_prod_reduce(team, dest, source, nreduce);
}

/* Blocking put with signal */
SHMEM_BIND_CXX_RMA_EXTRAS(static inline void shmem_put_signal(* dest, const * source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem__put_signal(dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal(shmem_ctx_t ctx, * dest, const * source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ctx__put_signal(ctx, dest, source, nelems, sig_addr, signal, sig_op, pe);
},)static inline void shmem_put_signal(float* dest, const float* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_float_put_signal(dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal(shmem_ctx_t ctx, float* dest, const float* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ctx_float_put_signal(ctx, dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal(double* dest, const double* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_double_put_signal(dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal(shmem_ctx_t ctx, double* dest, const double* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ctx_double_put_signal(ctx, dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal(long double* dest, const long double* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_longdouble_put_signal(dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal(shmem_ctx_t ctx, long double* dest, const long double* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ctx_longdouble_put_signal(ctx, dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal(char* dest, const char* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_char_put_signal(dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal(shmem_ctx_t ctx, char* dest, const char* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ctx_char_put_signal(ctx, dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal(signed char* dest, const signed char* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_schar_put_signal(dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal(shmem_ctx_t ctx, signed char* dest, const signed char* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ctx_schar_put_signal(ctx, dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal(short* dest, const short* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_short_put_signal(dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal(shmem_ctx_t ctx, short* dest, const short* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ctx_short_put_signal(ctx, dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal(int* dest, const int* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_int_put_signal(dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal(shmem_ctx_t ctx, int* dest, const int* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ctx_int_put_signal(ctx, dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal(long* dest, const long* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_long_put_signal(dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal(shmem_ctx_t ctx, long* dest, const long* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ctx_long_put_signal(ctx, dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal(long long* dest, const long long* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_longlong_put_signal(dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal(shmem_ctx_t ctx, long long* dest, const long long* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ctx_longlong_put_signal(ctx, dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal(unsigned char* dest, const unsigned char* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_uchar_put_signal(dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal(shmem_ctx_t ctx, unsigned char* dest, const unsigned char* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ctx_uchar_put_signal(ctx, dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal(unsigned short* dest, const unsigned short* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ushort_put_signal(dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal(shmem_ctx_t ctx, unsigned short* dest, const unsigned short* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ctx_ushort_put_signal(ctx, dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal(unsigned int* dest, const unsigned int* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_uint_put_signal(dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal(shmem_ctx_t ctx, unsigned int* dest, const unsigned int* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ctx_uint_put_signal(ctx, dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal(unsigned long* dest, const unsigned long* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ulong_put_signal(dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal(shmem_ctx_t ctx, unsigned long* dest, const unsigned long* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ctx_ulong_put_signal(ctx, dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal(unsigned long long* dest, const unsigned long long* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ulonglong_put_signal(dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal(shmem_ctx_t ctx, unsigned long long* dest, const unsigned long long* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ctx_ulonglong_put_signal(ctx, dest, source, nelems, sig_addr, signal, sig_op, pe);
}

/* Non-blocking put with signal */
SHMEM_BIND_CXX_RMA_EXTRAS(static inline void shmem_put_signal_nbi(* dest, const * source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem__put_signal_nbi(dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal_nbi(shmem_ctx_t ctx, * dest, const * source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ctx__put_signal_nbi(ctx, dest, source, nelems, sig_addr, signal, sig_op, pe);
},)static inline void shmem_put_signal_nbi(float* dest, const float* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_float_put_signal_nbi(dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal_nbi(shmem_ctx_t ctx, float* dest, const float* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ctx_float_put_signal_nbi(ctx, dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal_nbi(double* dest, const double* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_double_put_signal_nbi(dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal_nbi(shmem_ctx_t ctx, double* dest, const double* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ctx_double_put_signal_nbi(ctx, dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal_nbi(long double* dest, const long double* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_longdouble_put_signal_nbi(dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal_nbi(shmem_ctx_t ctx, long double* dest, const long double* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ctx_longdouble_put_signal_nbi(ctx, dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal_nbi(char* dest, const char* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_char_put_signal_nbi(dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal_nbi(shmem_ctx_t ctx, char* dest, const char* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ctx_char_put_signal_nbi(ctx, dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal_nbi(signed char* dest, const signed char* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_schar_put_signal_nbi(dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal_nbi(shmem_ctx_t ctx, signed char* dest, const signed char* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ctx_schar_put_signal_nbi(ctx, dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal_nbi(short* dest, const short* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_short_put_signal_nbi(dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal_nbi(shmem_ctx_t ctx, short* dest, const short* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ctx_short_put_signal_nbi(ctx, dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal_nbi(int* dest, const int* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_int_put_signal_nbi(dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal_nbi(shmem_ctx_t ctx, int* dest, const int* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ctx_int_put_signal_nbi(ctx, dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal_nbi(long* dest, const long* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_long_put_signal_nbi(dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal_nbi(shmem_ctx_t ctx, long* dest, const long* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ctx_long_put_signal_nbi(ctx, dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal_nbi(long long* dest, const long long* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_longlong_put_signal_nbi(dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal_nbi(shmem_ctx_t ctx, long long* dest, const long long* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ctx_longlong_put_signal_nbi(ctx, dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal_nbi(unsigned char* dest, const unsigned char* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_uchar_put_signal_nbi(dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal_nbi(shmem_ctx_t ctx, unsigned char* dest, const unsigned char* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ctx_uchar_put_signal_nbi(ctx, dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal_nbi(unsigned short* dest, const unsigned short* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ushort_put_signal_nbi(dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal_nbi(shmem_ctx_t ctx, unsigned short* dest, const unsigned short* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ctx_ushort_put_signal_nbi(ctx, dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal_nbi(unsigned int* dest, const unsigned int* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_uint_put_signal_nbi(dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal_nbi(shmem_ctx_t ctx, unsigned int* dest, const unsigned int* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ctx_uint_put_signal_nbi(ctx, dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal_nbi(unsigned long* dest, const unsigned long* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ulong_put_signal_nbi(dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal_nbi(shmem_ctx_t ctx, unsigned long* dest, const unsigned long* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ctx_ulong_put_signal_nbi(ctx, dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal_nbi(unsigned long long* dest, const unsigned long long* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ulonglong_put_signal_nbi(dest, source, nelems, sig_addr, signal, sig_op, pe);
}
static inline void shmem_put_signal_nbi(shmem_ctx_t ctx, unsigned long long* dest, const unsigned long long* source,
                             size_t nelems, uint64_t *sig_addr, uint64_t signal, int sig_op, int pe) {
    shmem_ctx_ulonglong_put_signal_nbi(ctx, dest, source, nelems, sig_addr, signal, sig_op, pe);
}

/* Atomics with standard AMO types */
SHMEM_BIND_CXX_AMO_EXTRAS(SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline void shmem_add( *target,  value, int pe) {
    shmem__atomic_add(target, value, pe);
},)SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline void shmem_add(int *target, int value, int pe) {
    shmem_int_atomic_add(target, value, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline void shmem_add(long *target, long value, int pe) {
    shmem_long_atomic_add(target, value, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline void shmem_add(long long *target, long long value, int pe) {
    shmem_longlong_atomic_add(target, value, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline void shmem_add(unsigned int *target, unsigned int value, int pe) {
    shmem_uint_atomic_add(target, value, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline void shmem_add(unsigned long *target, unsigned long value, int pe) {
    shmem_ulong_atomic_add(target, value, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline void shmem_add(unsigned long long *target, unsigned long long value, int pe) {
    shmem_ulonglong_atomic_add(target, value, pe);
}

SHMEM_BIND_CXX_AMO_EXTRAS(static inline void shmem_atomic_add( *target,  value, int pe) {
    shmem__atomic_add(target, value, pe);
}
static inline void shmem_atomic_add(shmem_ctx_t ctx,  *target,  value, int pe) {
    shmem_ctx__atomic_add(ctx, target, value, pe);
},)static inline void shmem_atomic_add(int *target, int value, int pe) {
    shmem_int_atomic_add(target, value, pe);
}
static inline void shmem_atomic_add(shmem_ctx_t ctx, int *target, int value, int pe) {
    shmem_ctx_int_atomic_add(ctx, target, value, pe);
}
static inline void shmem_atomic_add(long *target, long value, int pe) {
    shmem_long_atomic_add(target, value, pe);
}
static inline void shmem_atomic_add(shmem_ctx_t ctx, long *target, long value, int pe) {
    shmem_ctx_long_atomic_add(ctx, target, value, pe);
}
static inline void shmem_atomic_add(long long *target, long long value, int pe) {
    shmem_longlong_atomic_add(target, value, pe);
}
static inline void shmem_atomic_add(shmem_ctx_t ctx, long long *target, long long value, int pe) {
    shmem_ctx_longlong_atomic_add(ctx, target, value, pe);
}
static inline void shmem_atomic_add(unsigned int *target, unsigned int value, int pe) {
    shmem_uint_atomic_add(target, value, pe);
}
static inline void shmem_atomic_add(shmem_ctx_t ctx, unsigned int *target, unsigned int value, int pe) {
    shmem_ctx_uint_atomic_add(ctx, target, value, pe);
}
static inline void shmem_atomic_add(unsigned long *target, unsigned long value, int pe) {
    shmem_ulong_atomic_add(target, value, pe);
}
static inline void shmem_atomic_add(shmem_ctx_t ctx, unsigned long *target, unsigned long value, int pe) {
    shmem_ctx_ulong_atomic_add(ctx, target, value, pe);
}
static inline void shmem_atomic_add(unsigned long long *target, unsigned long long value, int pe) {
    shmem_ulonglong_atomic_add(target, value, pe);
}
static inline void shmem_atomic_add(shmem_ctx_t ctx, unsigned long long *target, unsigned long long value, int pe) {
    shmem_ctx_ulonglong_atomic_add(ctx, target, value, pe);
}

SHMEM_BIND_CXX_AMO_EXTRAS(SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline  shmem_cswap( *target,  cond,  value, int pe) {
    return shmem__atomic_compare_swap(target, cond, value, pe);
},)SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline int shmem_cswap(int *target, int cond, int value, int pe) {
    return shmem_int_atomic_compare_swap(target, cond, value, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline long shmem_cswap(long *target, long cond, long value, int pe) {
    return shmem_long_atomic_compare_swap(target, cond, value, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline long long shmem_cswap(long long *target, long long cond, long long value, int pe) {
    return shmem_longlong_atomic_compare_swap(target, cond, value, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline unsigned int shmem_cswap(unsigned int *target, unsigned int cond, unsigned int value, int pe) {
    return shmem_uint_atomic_compare_swap(target, cond, value, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline unsigned long shmem_cswap(unsigned long *target, unsigned long cond, unsigned long value, int pe) {
    return shmem_ulong_atomic_compare_swap(target, cond, value, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline unsigned long long shmem_cswap(unsigned long long *target, unsigned long long cond, unsigned long long value, int pe) {
    return shmem_ulonglong_atomic_compare_swap(target, cond, value, pe);
}

SHMEM_BIND_CXX_AMO_EXTRAS(static inline  shmem_atomic_compare_swap( *target,  cond,  value, int pe) {
    return shmem__atomic_compare_swap(target, cond, value, pe);
}
static inline  shmem_atomic_compare_swap(shmem_ctx_t ctx,  *target,  cond,  value, int pe) {
    return shmem_ctx__atomic_compare_swap(ctx, target, cond, value, pe);
},)static inline int shmem_atomic_compare_swap(int *target, int cond, int value, int pe) {
    return shmem_int_atomic_compare_swap(target, cond, value, pe);
}
static inline int shmem_atomic_compare_swap(shmem_ctx_t ctx, int *target, int cond, int value, int pe) {
    return shmem_ctx_int_atomic_compare_swap(ctx, target, cond, value, pe);
}
static inline long shmem_atomic_compare_swap(long *target, long cond, long value, int pe) {
    return shmem_long_atomic_compare_swap(target, cond, value, pe);
}
static inline long shmem_atomic_compare_swap(shmem_ctx_t ctx, long *target, long cond, long value, int pe) {
    return shmem_ctx_long_atomic_compare_swap(ctx, target, cond, value, pe);
}
static inline long long shmem_atomic_compare_swap(long long *target, long long cond, long long value, int pe) {
    return shmem_longlong_atomic_compare_swap(target, cond, value, pe);
}
static inline long long shmem_atomic_compare_swap(shmem_ctx_t ctx, long long *target, long long cond, long long value, int pe) {
    return shmem_ctx_longlong_atomic_compare_swap(ctx, target, cond, value, pe);
}
static inline unsigned int shmem_atomic_compare_swap(unsigned int *target, unsigned int cond, unsigned int value, int pe) {
    return shmem_uint_atomic_compare_swap(target, cond, value, pe);
}
static inline unsigned int shmem_atomic_compare_swap(shmem_ctx_t ctx, unsigned int *target, unsigned int cond, unsigned int value, int pe) {
    return shmem_ctx_uint_atomic_compare_swap(ctx, target, cond, value, pe);
}
static inline unsigned long shmem_atomic_compare_swap(unsigned long *target, unsigned long cond, unsigned long value, int pe) {
    return shmem_ulong_atomic_compare_swap(target, cond, value, pe);
}
static inline unsigned long shmem_atomic_compare_swap(shmem_ctx_t ctx, unsigned long *target, unsigned long cond, unsigned long value, int pe) {
    return shmem_ctx_ulong_atomic_compare_swap(ctx, target, cond, value, pe);
}
static inline unsigned long long shmem_atomic_compare_swap(unsigned long long *target, unsigned long long cond, unsigned long long value, int pe) {
    return shmem_ulonglong_atomic_compare_swap(target, cond, value, pe);
}
static inline unsigned long long shmem_atomic_compare_swap(shmem_ctx_t ctx, unsigned long long *target, unsigned long long cond, unsigned long long value, int pe) {
    return shmem_ctx_ulonglong_atomic_compare_swap(ctx, target, cond, value, pe);
}

SHMEM_BIND_CXX_AMO_EXTRAS(SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline  shmem_finc( *target, int pe) {
    return shmem__atomic_fetch_inc(target, pe);
},)SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline int shmem_finc(int *target, int pe) {
    return shmem_int_atomic_fetch_inc(target, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline long shmem_finc(long *target, int pe) {
    return shmem_long_atomic_fetch_inc(target, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline long long shmem_finc(long long *target, int pe) {
    return shmem_longlong_atomic_fetch_inc(target, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline unsigned int shmem_finc(unsigned int *target, int pe) {
    return shmem_uint_atomic_fetch_inc(target, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline unsigned long shmem_finc(unsigned long *target, int pe) {
    return shmem_ulong_atomic_fetch_inc(target, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline unsigned long long shmem_finc(unsigned long long *target, int pe) {
    return shmem_ulonglong_atomic_fetch_inc(target, pe);
}

SHMEM_BIND_CXX_AMO_EXTRAS(static inline  shmem_atomic_fetch_inc( *target, int pe) {
    return shmem__atomic_fetch_inc(target, pe);
}
static inline  shmem_atomic_fetch_inc(shmem_ctx_t ctx,  *target, int pe) {
    return shmem_ctx__atomic_fetch_inc(ctx, target, pe);
},)static inline int shmem_atomic_fetch_inc(int *target, int pe) {
    return shmem_int_atomic_fetch_inc(target, pe);
}
static inline int shmem_atomic_fetch_inc(shmem_ctx_t ctx, int *target, int pe) {
    return shmem_ctx_int_atomic_fetch_inc(ctx, target, pe);
}
static inline long shmem_atomic_fetch_inc(long *target, int pe) {
    return shmem_long_atomic_fetch_inc(target, pe);
}
static inline long shmem_atomic_fetch_inc(shmem_ctx_t ctx, long *target, int pe) {
    return shmem_ctx_long_atomic_fetch_inc(ctx, target, pe);
}
static inline long long shmem_atomic_fetch_inc(long long *target, int pe) {
    return shmem_longlong_atomic_fetch_inc(target, pe);
}
static inline long long shmem_atomic_fetch_inc(shmem_ctx_t ctx, long long *target, int pe) {
    return shmem_ctx_longlong_atomic_fetch_inc(ctx, target, pe);
}
static inline unsigned int shmem_atomic_fetch_inc(unsigned int *target, int pe) {
    return shmem_uint_atomic_fetch_inc(target, pe);
}
static inline unsigned int shmem_atomic_fetch_inc(shmem_ctx_t ctx, unsigned int *target, int pe) {
    return shmem_ctx_uint_atomic_fetch_inc(ctx, target, pe);
}
static inline unsigned long shmem_atomic_fetch_inc(unsigned long *target, int pe) {
    return shmem_ulong_atomic_fetch_inc(target, pe);
}
static inline unsigned long shmem_atomic_fetch_inc(shmem_ctx_t ctx, unsigned long *target, int pe) {
    return shmem_ctx_ulong_atomic_fetch_inc(ctx, target, pe);
}
static inline unsigned long long shmem_atomic_fetch_inc(unsigned long long *target, int pe) {
    return shmem_ulonglong_atomic_fetch_inc(target, pe);
}
static inline unsigned long long shmem_atomic_fetch_inc(shmem_ctx_t ctx, unsigned long long *target, int pe) {
    return shmem_ctx_ulonglong_atomic_fetch_inc(ctx, target, pe);
}

SHMEM_BIND_CXX_AMO_EXTRAS(SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline void shmem_inc( *target, int pe) {
    shmem__atomic_inc(target, pe);
},)SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline void shmem_inc(int *target, int pe) {
    shmem_int_atomic_inc(target, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline void shmem_inc(long *target, int pe) {
    shmem_long_atomic_inc(target, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline void shmem_inc(long long *target, int pe) {
    shmem_longlong_atomic_inc(target, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline void shmem_inc(unsigned int *target, int pe) {
    shmem_uint_atomic_inc(target, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline void shmem_inc(unsigned long *target, int pe) {
    shmem_ulong_atomic_inc(target, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline void shmem_inc(unsigned long long *target, int pe) {
    shmem_ulonglong_atomic_inc(target, pe);
}

SHMEM_BIND_CXX_AMO_EXTRAS(static inline void shmem_atomic_inc( *target, int pe) {
    shmem__atomic_inc(target, pe);
}
static inline void shmem_atomic_inc(shmem_ctx_t ctx,  *target, int pe) {
    shmem_ctx__atomic_inc(ctx, target, pe);
},)static inline void shmem_atomic_inc(int *target, int pe) {
    shmem_int_atomic_inc(target, pe);
}
static inline void shmem_atomic_inc(shmem_ctx_t ctx, int *target, int pe) {
    shmem_ctx_int_atomic_inc(ctx, target, pe);
}
static inline void shmem_atomic_inc(long *target, int pe) {
    shmem_long_atomic_inc(target, pe);
}
static inline void shmem_atomic_inc(shmem_ctx_t ctx, long *target, int pe) {
    shmem_ctx_long_atomic_inc(ctx, target, pe);
}
static inline void shmem_atomic_inc(long long *target, int pe) {
    shmem_longlong_atomic_inc(target, pe);
}
static inline void shmem_atomic_inc(shmem_ctx_t ctx, long long *target, int pe) {
    shmem_ctx_longlong_atomic_inc(ctx, target, pe);
}
static inline void shmem_atomic_inc(unsigned int *target, int pe) {
    shmem_uint_atomic_inc(target, pe);
}
static inline void shmem_atomic_inc(shmem_ctx_t ctx, unsigned int *target, int pe) {
    shmem_ctx_uint_atomic_inc(ctx, target, pe);
}
static inline void shmem_atomic_inc(unsigned long *target, int pe) {
    shmem_ulong_atomic_inc(target, pe);
}
static inline void shmem_atomic_inc(shmem_ctx_t ctx, unsigned long *target, int pe) {
    shmem_ctx_ulong_atomic_inc(ctx, target, pe);
}
static inline void shmem_atomic_inc(unsigned long long *target, int pe) {
    shmem_ulonglong_atomic_inc(target, pe);
}
static inline void shmem_atomic_inc(shmem_ctx_t ctx, unsigned long long *target, int pe) {
    shmem_ctx_ulonglong_atomic_inc(ctx, target, pe);
}

SHMEM_BIND_CXX_AMO_EXTRAS(SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline  shmem_fadd( *target,  value, int pe) {
    return shmem__atomic_fetch_add(target, value, pe);
},)SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline int shmem_fadd(int *target, int value, int pe) {
    return shmem_int_atomic_fetch_add(target, value, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline long shmem_fadd(long *target, long value, int pe) {
    return shmem_long_atomic_fetch_add(target, value, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline long long shmem_fadd(long long *target, long long value, int pe) {
    return shmem_longlong_atomic_fetch_add(target, value, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline unsigned int shmem_fadd(unsigned int *target, unsigned int value, int pe) {
    return shmem_uint_atomic_fetch_add(target, value, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline unsigned long shmem_fadd(unsigned long *target, unsigned long value, int pe) {
    return shmem_ulong_atomic_fetch_add(target, value, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline unsigned long long shmem_fadd(unsigned long long *target, unsigned long long value, int pe) {
    return shmem_ulonglong_atomic_fetch_add(target, value, pe);
}

SHMEM_BIND_CXX_AMO_EXTRAS(static inline  shmem_atomic_fetch_add( *target,  value, int pe) {
    return shmem__atomic_fetch_add(target, value, pe);
}
static inline  shmem_atomic_fetch_add(shmem_ctx_t ctx,  *target,  value, int pe) {
    return shmem_ctx__atomic_fetch_add(ctx, target, value, pe);
},)static inline int shmem_atomic_fetch_add(int *target, int value, int pe) {
    return shmem_int_atomic_fetch_add(target, value, pe);
}
static inline int shmem_atomic_fetch_add(shmem_ctx_t ctx, int *target, int value, int pe) {
    return shmem_ctx_int_atomic_fetch_add(ctx, target, value, pe);
}
static inline long shmem_atomic_fetch_add(long *target, long value, int pe) {
    return shmem_long_atomic_fetch_add(target, value, pe);
}
static inline long shmem_atomic_fetch_add(shmem_ctx_t ctx, long *target, long value, int pe) {
    return shmem_ctx_long_atomic_fetch_add(ctx, target, value, pe);
}
static inline long long shmem_atomic_fetch_add(long long *target, long long value, int pe) {
    return shmem_longlong_atomic_fetch_add(target, value, pe);
}
static inline long long shmem_atomic_fetch_add(shmem_ctx_t ctx, long long *target, long long value, int pe) {
    return shmem_ctx_longlong_atomic_fetch_add(ctx, target, value, pe);
}
static inline unsigned int shmem_atomic_fetch_add(unsigned int *target, unsigned int value, int pe) {
    return shmem_uint_atomic_fetch_add(target, value, pe);
}
static inline unsigned int shmem_atomic_fetch_add(shmem_ctx_t ctx, unsigned int *target, unsigned int value, int pe) {
    return shmem_ctx_uint_atomic_fetch_add(ctx, target, value, pe);
}
static inline unsigned long shmem_atomic_fetch_add(unsigned long *target, unsigned long value, int pe) {
    return shmem_ulong_atomic_fetch_add(target, value, pe);
}
static inline unsigned long shmem_atomic_fetch_add(shmem_ctx_t ctx, unsigned long *target, unsigned long value, int pe) {
    return shmem_ctx_ulong_atomic_fetch_add(ctx, target, value, pe);
}
static inline unsigned long long shmem_atomic_fetch_add(unsigned long long *target, unsigned long long value, int pe) {
    return shmem_ulonglong_atomic_fetch_add(target, value, pe);
}
static inline unsigned long long shmem_atomic_fetch_add(shmem_ctx_t ctx, unsigned long long *target, unsigned long long value, int pe) {
    return shmem_ctx_ulonglong_atomic_fetch_add(ctx, target, value, pe);
}

SHMEM_BIND_CXX_BITWISE_AMO_EXTRAS(static inline void shmem_atomic_and( *dest,  value, int pe) {
    shmem__atomic_and(dest, value, pe);
}
static inline void shmem_atomic_and(shmem_ctx_t ctx,  *dest,  value, int pe) {
    shmem_ctx__atomic_and(ctx, dest, value, pe);
},)static inline void shmem_atomic_and(int32_t *dest, int32_t value, int pe) {
    shmem_int32_atomic_and(dest, value, pe);
}
static inline void shmem_atomic_and(shmem_ctx_t ctx, int32_t *dest, int32_t value, int pe) {
    shmem_ctx_int32_atomic_and(ctx, dest, value, pe);
}
static inline void shmem_atomic_and(int64_t *dest, int64_t value, int pe) {
    shmem_int64_atomic_and(dest, value, pe);
}
static inline void shmem_atomic_and(shmem_ctx_t ctx, int64_t *dest, int64_t value, int pe) {
    shmem_ctx_int64_atomic_and(ctx, dest, value, pe);
}
static inline void shmem_atomic_and(unsigned int *dest, unsigned int value, int pe) {
    shmem_uint_atomic_and(dest, value, pe);
}
static inline void shmem_atomic_and(shmem_ctx_t ctx, unsigned int *dest, unsigned int value, int pe) {
    shmem_ctx_uint_atomic_and(ctx, dest, value, pe);
}
static inline void shmem_atomic_and(unsigned long *dest, unsigned long value, int pe) {
    shmem_ulong_atomic_and(dest, value, pe);
}
static inline void shmem_atomic_and(shmem_ctx_t ctx, unsigned long *dest, unsigned long value, int pe) {
    shmem_ctx_ulong_atomic_and(ctx, dest, value, pe);
}
static inline void shmem_atomic_and(unsigned long long *dest, unsigned long long value, int pe) {
    shmem_ulonglong_atomic_and(dest, value, pe);
}
static inline void shmem_atomic_and(shmem_ctx_t ctx, unsigned long long *dest, unsigned long long value, int pe) {
    shmem_ctx_ulonglong_atomic_and(ctx, dest, value, pe);
}

SHMEM_BIND_CXX_BITWISE_AMO_EXTRAS(static inline void shmem_atomic_or( *dest,  value, int pe) {
    shmem__atomic_or(dest, value, pe);
}
static inline void shmem_atomic_or(shmem_ctx_t ctx,  *dest,  value, int pe) {
    shmem_ctx__atomic_or(ctx, dest, value, pe);
},)static inline void shmem_atomic_or(int32_t *dest, int32_t value, int pe) {
    shmem_int32_atomic_or(dest, value, pe);
}
static inline void shmem_atomic_or(shmem_ctx_t ctx, int32_t *dest, int32_t value, int pe) {
    shmem_ctx_int32_atomic_or(ctx, dest, value, pe);
}
static inline void shmem_atomic_or(int64_t *dest, int64_t value, int pe) {
    shmem_int64_atomic_or(dest, value, pe);
}
static inline void shmem_atomic_or(shmem_ctx_t ctx, int64_t *dest, int64_t value, int pe) {
    shmem_ctx_int64_atomic_or(ctx, dest, value, pe);
}
static inline void shmem_atomic_or(unsigned int *dest, unsigned int value, int pe) {
    shmem_uint_atomic_or(dest, value, pe);
}
static inline void shmem_atomic_or(shmem_ctx_t ctx, unsigned int *dest, unsigned int value, int pe) {
    shmem_ctx_uint_atomic_or(ctx, dest, value, pe);
}
static inline void shmem_atomic_or(unsigned long *dest, unsigned long value, int pe) {
    shmem_ulong_atomic_or(dest, value, pe);
}
static inline void shmem_atomic_or(shmem_ctx_t ctx, unsigned long *dest, unsigned long value, int pe) {
    shmem_ctx_ulong_atomic_or(ctx, dest, value, pe);
}
static inline void shmem_atomic_or(unsigned long long *dest, unsigned long long value, int pe) {
    shmem_ulonglong_atomic_or(dest, value, pe);
}
static inline void shmem_atomic_or(shmem_ctx_t ctx, unsigned long long *dest, unsigned long long value, int pe) {
    shmem_ctx_ulonglong_atomic_or(ctx, dest, value, pe);
}

SHMEM_BIND_CXX_BITWISE_AMO_EXTRAS(static inline void shmem_atomic_xor( *dest,  value, int pe) {
    shmem__atomic_xor(dest, value, pe);
}
static inline void shmem_atomic_xor(shmem_ctx_t ctx,  *dest,  value, int pe) {
    shmem_ctx__atomic_xor(ctx, dest, value, pe);
},)static inline void shmem_atomic_xor(int32_t *dest, int32_t value, int pe) {
    shmem_int32_atomic_xor(dest, value, pe);
}
static inline void shmem_atomic_xor(shmem_ctx_t ctx, int32_t *dest, int32_t value, int pe) {
    shmem_ctx_int32_atomic_xor(ctx, dest, value, pe);
}
static inline void shmem_atomic_xor(int64_t *dest, int64_t value, int pe) {
    shmem_int64_atomic_xor(dest, value, pe);
}
static inline void shmem_atomic_xor(shmem_ctx_t ctx, int64_t *dest, int64_t value, int pe) {
    shmem_ctx_int64_atomic_xor(ctx, dest, value, pe);
}
static inline void shmem_atomic_xor(unsigned int *dest, unsigned int value, int pe) {
    shmem_uint_atomic_xor(dest, value, pe);
}
static inline void shmem_atomic_xor(shmem_ctx_t ctx, unsigned int *dest, unsigned int value, int pe) {
    shmem_ctx_uint_atomic_xor(ctx, dest, value, pe);
}
static inline void shmem_atomic_xor(unsigned long *dest, unsigned long value, int pe) {
    shmem_ulong_atomic_xor(dest, value, pe);
}
static inline void shmem_atomic_xor(shmem_ctx_t ctx, unsigned long *dest, unsigned long value, int pe) {
    shmem_ctx_ulong_atomic_xor(ctx, dest, value, pe);
}
static inline void shmem_atomic_xor(unsigned long long *dest, unsigned long long value, int pe) {
    shmem_ulonglong_atomic_xor(dest, value, pe);
}
static inline void shmem_atomic_xor(shmem_ctx_t ctx, unsigned long long *dest, unsigned long long value, int pe) {
    shmem_ctx_ulonglong_atomic_xor(ctx, dest, value, pe);
}

SHMEM_BIND_CXX_BITWISE_AMO_EXTRAS(static inline  shmem_atomic_fetch_and( *dest,  value, int pe) {
    return shmem__atomic_fetch_and(dest, value, pe);
}
static inline  shmem_atomic_fetch_and(shmem_ctx_t ctx,  *dest,  value, int pe) {
    return shmem_ctx__atomic_fetch_and(ctx, dest, value, pe);
},)static inline int32_t shmem_atomic_fetch_and(int32_t *dest, int32_t value, int pe) {
    return shmem_int32_atomic_fetch_and(dest, value, pe);
}
static inline int32_t shmem_atomic_fetch_and(shmem_ctx_t ctx, int32_t *dest, int32_t value, int pe) {
    return shmem_ctx_int32_atomic_fetch_and(ctx, dest, value, pe);
}
static inline int64_t shmem_atomic_fetch_and(int64_t *dest, int64_t value, int pe) {
    return shmem_int64_atomic_fetch_and(dest, value, pe);
}
static inline int64_t shmem_atomic_fetch_and(shmem_ctx_t ctx, int64_t *dest, int64_t value, int pe) {
    return shmem_ctx_int64_atomic_fetch_and(ctx, dest, value, pe);
}
static inline unsigned int shmem_atomic_fetch_and(unsigned int *dest, unsigned int value, int pe) {
    return shmem_uint_atomic_fetch_and(dest, value, pe);
}
static inline unsigned int shmem_atomic_fetch_and(shmem_ctx_t ctx, unsigned int *dest, unsigned int value, int pe) {
    return shmem_ctx_uint_atomic_fetch_and(ctx, dest, value, pe);
}
static inline unsigned long shmem_atomic_fetch_and(unsigned long *dest, unsigned long value, int pe) {
    return shmem_ulong_atomic_fetch_and(dest, value, pe);
}
static inline unsigned long shmem_atomic_fetch_and(shmem_ctx_t ctx, unsigned long *dest, unsigned long value, int pe) {
    return shmem_ctx_ulong_atomic_fetch_and(ctx, dest, value, pe);
}
static inline unsigned long long shmem_atomic_fetch_and(unsigned long long *dest, unsigned long long value, int pe) {
    return shmem_ulonglong_atomic_fetch_and(dest, value, pe);
}
static inline unsigned long long shmem_atomic_fetch_and(shmem_ctx_t ctx, unsigned long long *dest, unsigned long long value, int pe) {
    return shmem_ctx_ulonglong_atomic_fetch_and(ctx, dest, value, pe);
}

SHMEM_BIND_CXX_BITWISE_AMO_EXTRAS(static inline  shmem_atomic_fetch_or( *dest,  value, int pe) {
    return shmem__atomic_fetch_or(dest, value, pe);
}
static inline  shmem_atomic_fetch_or(shmem_ctx_t ctx,  *dest,  value, int pe) {
    return shmem_ctx__atomic_fetch_or(ctx, dest, value, pe);
},)static inline int32_t shmem_atomic_fetch_or(int32_t *dest, int32_t value, int pe) {
    return shmem_int32_atomic_fetch_or(dest, value, pe);
}
static inline int32_t shmem_atomic_fetch_or(shmem_ctx_t ctx, int32_t *dest, int32_t value, int pe) {
    return shmem_ctx_int32_atomic_fetch_or(ctx, dest, value, pe);
}
static inline int64_t shmem_atomic_fetch_or(int64_t *dest, int64_t value, int pe) {
    return shmem_int64_atomic_fetch_or(dest, value, pe);
}
static inline int64_t shmem_atomic_fetch_or(shmem_ctx_t ctx, int64_t *dest, int64_t value, int pe) {
    return shmem_ctx_int64_atomic_fetch_or(ctx, dest, value, pe);
}
static inline unsigned int shmem_atomic_fetch_or(unsigned int *dest, unsigned int value, int pe) {
    return shmem_uint_atomic_fetch_or(dest, value, pe);
}
static inline unsigned int shmem_atomic_fetch_or(shmem_ctx_t ctx, unsigned int *dest, unsigned int value, int pe) {
    return shmem_ctx_uint_atomic_fetch_or(ctx, dest, value, pe);
}
static inline unsigned long shmem_atomic_fetch_or(unsigned long *dest, unsigned long value, int pe) {
    return shmem_ulong_atomic_fetch_or(dest, value, pe);
}
static inline unsigned long shmem_atomic_fetch_or(shmem_ctx_t ctx, unsigned long *dest, unsigned long value, int pe) {
    return shmem_ctx_ulong_atomic_fetch_or(ctx, dest, value, pe);
}
static inline unsigned long long shmem_atomic_fetch_or(unsigned long long *dest, unsigned long long value, int pe) {
    return shmem_ulonglong_atomic_fetch_or(dest, value, pe);
}
static inline unsigned long long shmem_atomic_fetch_or(shmem_ctx_t ctx, unsigned long long *dest, unsigned long long value, int pe) {
    return shmem_ctx_ulonglong_atomic_fetch_or(ctx, dest, value, pe);
}

SHMEM_BIND_CXX_BITWISE_AMO_EXTRAS(static inline  shmem_atomic_fetch_xor( *dest,  value, int pe) {
    return shmem__atomic_fetch_xor(dest, value, pe);
}
static inline  shmem_atomic_fetch_xor(shmem_ctx_t ctx,  *dest,  value, int pe) {
    return shmem_ctx__atomic_fetch_xor(ctx, dest, value, pe);
},)static inline int32_t shmem_atomic_fetch_xor(int32_t *dest, int32_t value, int pe) {
    return shmem_int32_atomic_fetch_xor(dest, value, pe);
}
static inline int32_t shmem_atomic_fetch_xor(shmem_ctx_t ctx, int32_t *dest, int32_t value, int pe) {
    return shmem_ctx_int32_atomic_fetch_xor(ctx, dest, value, pe);
}
static inline int64_t shmem_atomic_fetch_xor(int64_t *dest, int64_t value, int pe) {
    return shmem_int64_atomic_fetch_xor(dest, value, pe);
}
static inline int64_t shmem_atomic_fetch_xor(shmem_ctx_t ctx, int64_t *dest, int64_t value, int pe) {
    return shmem_ctx_int64_atomic_fetch_xor(ctx, dest, value, pe);
}
static inline unsigned int shmem_atomic_fetch_xor(unsigned int *dest, unsigned int value, int pe) {
    return shmem_uint_atomic_fetch_xor(dest, value, pe);
}
static inline unsigned int shmem_atomic_fetch_xor(shmem_ctx_t ctx, unsigned int *dest, unsigned int value, int pe) {
    return shmem_ctx_uint_atomic_fetch_xor(ctx, dest, value, pe);
}
static inline unsigned long shmem_atomic_fetch_xor(unsigned long *dest, unsigned long value, int pe) {
    return shmem_ulong_atomic_fetch_xor(dest, value, pe);
}
static inline unsigned long shmem_atomic_fetch_xor(shmem_ctx_t ctx, unsigned long *dest, unsigned long value, int pe) {
    return shmem_ctx_ulong_atomic_fetch_xor(ctx, dest, value, pe);
}
static inline unsigned long long shmem_atomic_fetch_xor(unsigned long long *dest, unsigned long long value, int pe) {
    return shmem_ulonglong_atomic_fetch_xor(dest, value, pe);
}
static inline unsigned long long shmem_atomic_fetch_xor(shmem_ctx_t ctx, unsigned long long *dest, unsigned long long value, int pe) {
    return shmem_ctx_ulonglong_atomic_fetch_xor(ctx, dest, value, pe);
}

/* Atomics with extended AMO types */
SHMEM_BIND_CXX_EXTENDED_AMO_EXTRAS(SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline  shmem_swap( *target,  value, int pe) {
    return shmem__atomic_swap(target, value, pe);
},)SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline int shmem_swap(int *target, int value, int pe) {
    return shmem_int_atomic_swap(target, value, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline long shmem_swap(long *target, long value, int pe) {
    return shmem_long_atomic_swap(target, value, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline long long shmem_swap(long long *target, long long value, int pe) {
    return shmem_longlong_atomic_swap(target, value, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline unsigned int shmem_swap(unsigned int *target, unsigned int value, int pe) {
    return shmem_uint_atomic_swap(target, value, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline unsigned long shmem_swap(unsigned long *target, unsigned long value, int pe) {
    return shmem_ulong_atomic_swap(target, value, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline unsigned long long shmem_swap(unsigned long long *target, unsigned long long value, int pe) {
    return shmem_ulonglong_atomic_swap(target, value, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline float shmem_swap(float *target, float value, int pe) {
    return shmem_float_atomic_swap(target, value, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline double shmem_swap(double *target, double value, int pe) {
    return shmem_double_atomic_swap(target, value, pe);
}

SHMEM_BIND_CXX_EXTENDED_AMO_EXTRAS(static inline  shmem_atomic_swap( *target,  value, int pe) {
    return shmem__atomic_swap(target, value, pe);
}
static inline  shmem_atomic_swap(shmem_ctx_t ctx,  *target,  value, int pe) {
    return shmem_ctx__atomic_swap(ctx, target, value, pe);
},)static inline int shmem_atomic_swap(int *target, int value, int pe) {
    return shmem_int_atomic_swap(target, value, pe);
}
static inline int shmem_atomic_swap(shmem_ctx_t ctx, int *target, int value, int pe) {
    return shmem_ctx_int_atomic_swap(ctx, target, value, pe);
}
static inline long shmem_atomic_swap(long *target, long value, int pe) {
    return shmem_long_atomic_swap(target, value, pe);
}
static inline long shmem_atomic_swap(shmem_ctx_t ctx, long *target, long value, int pe) {
    return shmem_ctx_long_atomic_swap(ctx, target, value, pe);
}
static inline long long shmem_atomic_swap(long long *target, long long value, int pe) {
    return shmem_longlong_atomic_swap(target, value, pe);
}
static inline long long shmem_atomic_swap(shmem_ctx_t ctx, long long *target, long long value, int pe) {
    return shmem_ctx_longlong_atomic_swap(ctx, target, value, pe);
}
static inline unsigned int shmem_atomic_swap(unsigned int *target, unsigned int value, int pe) {
    return shmem_uint_atomic_swap(target, value, pe);
}
static inline unsigned int shmem_atomic_swap(shmem_ctx_t ctx, unsigned int *target, unsigned int value, int pe) {
    return shmem_ctx_uint_atomic_swap(ctx, target, value, pe);
}
static inline unsigned long shmem_atomic_swap(unsigned long *target, unsigned long value, int pe) {
    return shmem_ulong_atomic_swap(target, value, pe);
}
static inline unsigned long shmem_atomic_swap(shmem_ctx_t ctx, unsigned long *target, unsigned long value, int pe) {
    return shmem_ctx_ulong_atomic_swap(ctx, target, value, pe);
}
static inline unsigned long long shmem_atomic_swap(unsigned long long *target, unsigned long long value, int pe) {
    return shmem_ulonglong_atomic_swap(target, value, pe);
}
static inline unsigned long long shmem_atomic_swap(shmem_ctx_t ctx, unsigned long long *target, unsigned long long value, int pe) {
    return shmem_ctx_ulonglong_atomic_swap(ctx, target, value, pe);
}
static inline float shmem_atomic_swap(float *target, float value, int pe) {
    return shmem_float_atomic_swap(target, value, pe);
}
static inline float shmem_atomic_swap(shmem_ctx_t ctx, float *target, float value, int pe) {
    return shmem_ctx_float_atomic_swap(ctx, target, value, pe);
}
static inline double shmem_atomic_swap(double *target, double value, int pe) {
    return shmem_double_atomic_swap(target, value, pe);
}
static inline double shmem_atomic_swap(shmem_ctx_t ctx, double *target, double value, int pe) {
    return shmem_ctx_double_atomic_swap(ctx, target, value, pe);
}

SHMEM_BIND_CXX_EXTENDED_AMO_EXTRAS(SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline  shmem_fetch(const  *target, int pe) {
    return shmem__atomic_fetch(target, pe);
},)SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline int shmem_fetch(const int *target, int pe) {
    return shmem_int_atomic_fetch(target, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline long shmem_fetch(const long *target, int pe) {
    return shmem_long_atomic_fetch(target, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline long long shmem_fetch(const long long *target, int pe) {
    return shmem_longlong_atomic_fetch(target, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline unsigned int shmem_fetch(const unsigned int *target, int pe) {
    return shmem_uint_atomic_fetch(target, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline unsigned long shmem_fetch(const unsigned long *target, int pe) {
    return shmem_ulong_atomic_fetch(target, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline unsigned long long shmem_fetch(const unsigned long long *target, int pe) {
    return shmem_ulonglong_atomic_fetch(target, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline float shmem_fetch(const float *target, int pe) {
    return shmem_float_atomic_fetch(target, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline double shmem_fetch(const double *target, int pe) {
    return shmem_double_atomic_fetch(target, pe);
}

SHMEM_BIND_CXX_EXTENDED_AMO_EXTRAS(static inline  shmem_atomic_fetch(const  *target, int pe) {
    return shmem__atomic_fetch(target, pe);
}
static inline  shmem_atomic_fetch(shmem_ctx_t ctx, const  *target, int pe) {
    return shmem_ctx__atomic_fetch(ctx, target, pe);
},)static inline int shmem_atomic_fetch(const int *target, int pe) {
    return shmem_int_atomic_fetch(target, pe);
}
static inline int shmem_atomic_fetch(shmem_ctx_t ctx, const int *target, int pe) {
    return shmem_ctx_int_atomic_fetch(ctx, target, pe);
}
static inline long shmem_atomic_fetch(const long *target, int pe) {
    return shmem_long_atomic_fetch(target, pe);
}
static inline long shmem_atomic_fetch(shmem_ctx_t ctx, const long *target, int pe) {
    return shmem_ctx_long_atomic_fetch(ctx, target, pe);
}
static inline long long shmem_atomic_fetch(const long long *target, int pe) {
    return shmem_longlong_atomic_fetch(target, pe);
}
static inline long long shmem_atomic_fetch(shmem_ctx_t ctx, const long long *target, int pe) {
    return shmem_ctx_longlong_atomic_fetch(ctx, target, pe);
}
static inline unsigned int shmem_atomic_fetch(const unsigned int *target, int pe) {
    return shmem_uint_atomic_fetch(target, pe);
}
static inline unsigned int shmem_atomic_fetch(shmem_ctx_t ctx, const unsigned int *target, int pe) {
    return shmem_ctx_uint_atomic_fetch(ctx, target, pe);
}
static inline unsigned long shmem_atomic_fetch(const unsigned long *target, int pe) {
    return shmem_ulong_atomic_fetch(target, pe);
}
static inline unsigned long shmem_atomic_fetch(shmem_ctx_t ctx, const unsigned long *target, int pe) {
    return shmem_ctx_ulong_atomic_fetch(ctx, target, pe);
}
static inline unsigned long long shmem_atomic_fetch(const unsigned long long *target, int pe) {
    return shmem_ulonglong_atomic_fetch(target, pe);
}
static inline unsigned long long shmem_atomic_fetch(shmem_ctx_t ctx, const unsigned long long *target, int pe) {
    return shmem_ctx_ulonglong_atomic_fetch(ctx, target, pe);
}
static inline float shmem_atomic_fetch(const float *target, int pe) {
    return shmem_float_atomic_fetch(target, pe);
}
static inline float shmem_atomic_fetch(shmem_ctx_t ctx, const float *target, int pe) {
    return shmem_ctx_float_atomic_fetch(ctx, target, pe);
}
static inline double shmem_atomic_fetch(const double *target, int pe) {
    return shmem_double_atomic_fetch(target, pe);
}
static inline double shmem_atomic_fetch(shmem_ctx_t ctx, const double *target, int pe) {
    return shmem_ctx_double_atomic_fetch(ctx, target, pe);
}

SHMEM_BIND_CXX_EXTENDED_AMO_EXTRAS(SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline void shmem_set( *target,  value, int pe) {
    shmem__atomic_set(target, value, pe);
},)SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline void shmem_set(int *target, int value, int pe) {
    shmem_int_atomic_set(target, value, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline void shmem_set(long *target, long value, int pe) {
    shmem_long_atomic_set(target, value, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline void shmem_set(long long *target, long long value, int pe) {
    shmem_longlong_atomic_set(target, value, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline void shmem_set(unsigned int *target, unsigned int value, int pe) {
    shmem_uint_atomic_set(target, value, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline void shmem_set(unsigned long *target, unsigned long value, int pe) {
    shmem_ulong_atomic_set(target, value, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline void shmem_set(unsigned long long *target, unsigned long long value, int pe) {
    shmem_ulonglong_atomic_set(target, value, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline void shmem_set(float *target, float value, int pe) {
    shmem_float_atomic_set(target, value, pe);
}
SHMEM_CXX_ATTRIBUTE_DEPRECATED static inline void shmem_set(double *target, double value, int pe) {
    shmem_double_atomic_set(target, value, pe);
}

SHMEM_BIND_CXX_EXTENDED_AMO_EXTRAS(static inline void shmem_atomic_set( *target,  value, int pe) {
    shmem__atomic_set(target, value, pe);
}
static inline void shmem_atomic_set(shmem_ctx_t ctx,  *target,  value, int pe) {
    shmem_ctx__atomic_set(ctx, target, value, pe);
},)static inline void shmem_atomic_set(int *target, int value, int pe) {
    shmem_int_atomic_set(target, value, pe);
}
static inline void shmem_atomic_set(shmem_ctx_t ctx, int *target, int value, int pe) {
    shmem_ctx_int_atomic_set(ctx, target, value, pe);
}
static inline void shmem_atomic_set(long *target, long value, int pe) {
    shmem_long_atomic_set(target, value, pe);
}
static inline void shmem_atomic_set(shmem_ctx_t ctx, long *target, long value, int pe) {
    shmem_ctx_long_atomic_set(ctx, target, value, pe);
}
static inline void shmem_atomic_set(long long *target, long long value, int pe) {
    shmem_longlong_atomic_set(target, value, pe);
}
static inline void shmem_atomic_set(shmem_ctx_t ctx, long long *target, long long value, int pe) {
    shmem_ctx_longlong_atomic_set(ctx, target, value, pe);
}
static inline void shmem_atomic_set(unsigned int *target, unsigned int value, int pe) {
    shmem_uint_atomic_set(target, value, pe);
}
static inline void shmem_atomic_set(shmem_ctx_t ctx, unsigned int *target, unsigned int value, int pe) {
    shmem_ctx_uint_atomic_set(ctx, target, value, pe);
}
static inline void shmem_atomic_set(unsigned long *target, unsigned long value, int pe) {
    shmem_ulong_atomic_set(target, value, pe);
}
static inline void shmem_atomic_set(shmem_ctx_t ctx, unsigned long *target, unsigned long value, int pe) {
    shmem_ctx_ulong_atomic_set(ctx, target, value, pe);
}
static inline void shmem_atomic_set(unsigned long long *target, unsigned long long value, int pe) {
    shmem_ulonglong_atomic_set(target, value, pe);
}
static inline void shmem_atomic_set(shmem_ctx_t ctx, unsigned long long *target, unsigned long long value, int pe) {
    shmem_ctx_ulonglong_atomic_set(ctx, target, value, pe);
}
static inline void shmem_atomic_set(float *target, float value, int pe) {
    shmem_float_atomic_set(target, value, pe);
}
static inline void shmem_atomic_set(shmem_ctx_t ctx, float *target, float value, int pe) {
    shmem_ctx_float_atomic_set(ctx, target, value, pe);
}
static inline void shmem_atomic_set(double *target, double value, int pe) {
    shmem_double_atomic_set(target, value, pe);
}
static inline void shmem_atomic_set(shmem_ctx_t ctx, double *target, double value, int pe) {
    shmem_ctx_double_atomic_set(ctx, target, value, pe);
}

/* Point-to-point synchronization */

SHMEM_BIND_CXX_SYNC_EXTRAS(static inline void shmem_wait_until( *ivar, int cmp,  cmp_value) {
    shmem__wait_until(ivar, cmp, cmp_value);
},)static inline void shmem_wait_until(short *ivar, int cmp, short cmp_value) {
    shmem_short_wait_until(ivar, cmp, cmp_value);
}
static inline void shmem_wait_until(int *ivar, int cmp, int cmp_value) {
    shmem_int_wait_until(ivar, cmp, cmp_value);
}
static inline void shmem_wait_until(long *ivar, int cmp, long cmp_value) {
    shmem_long_wait_until(ivar, cmp, cmp_value);
}
static inline void shmem_wait_until(long long *ivar, int cmp, long long cmp_value) {
    shmem_longlong_wait_until(ivar, cmp, cmp_value);
}
static inline void shmem_wait_until(unsigned short *ivar, int cmp, unsigned short cmp_value) {
    shmem_ushort_wait_until(ivar, cmp, cmp_value);
}
static inline void shmem_wait_until(unsigned int *ivar, int cmp, unsigned int cmp_value) {
    shmem_uint_wait_until(ivar, cmp, cmp_value);
}
static inline void shmem_wait_until(unsigned long *ivar, int cmp, unsigned long cmp_value) {
    shmem_ulong_wait_until(ivar, cmp, cmp_value);
}
static inline void shmem_wait_until(unsigned long long *ivar, int cmp, unsigned long long cmp_value) {
    shmem_ulonglong_wait_until(ivar, cmp, cmp_value);
}

SHMEM_BIND_CXX_SYNC_EXTRAS(static inline void shmem_wait_until_all( *ivars, size_t nelems, const int *status, int cmp,  cmp_value) {
    shmem__wait_until_all(ivars, nelems, status, cmp, cmp_value);
},)static inline void shmem_wait_until_all(short *ivars, size_t nelems, const int *status, int cmp, short cmp_value) {
    shmem_short_wait_until_all(ivars, nelems, status, cmp, cmp_value);
}
static inline void shmem_wait_until_all(int *ivars, size_t nelems, const int *status, int cmp, int cmp_value) {
    shmem_int_wait_until_all(ivars, nelems, status, cmp, cmp_value);
}
static inline void shmem_wait_until_all(long *ivars, size_t nelems, const int *status, int cmp, long cmp_value) {
    shmem_long_wait_until_all(ivars, nelems, status, cmp, cmp_value);
}
static inline void shmem_wait_until_all(long long *ivars, size_t nelems, const int *status, int cmp, long long cmp_value) {
    shmem_longlong_wait_until_all(ivars, nelems, status, cmp, cmp_value);
}
static inline void shmem_wait_until_all(unsigned short *ivars, size_t nelems, const int *status, int cmp, unsigned short cmp_value) {
    shmem_ushort_wait_until_all(ivars, nelems, status, cmp, cmp_value);
}
static inline void shmem_wait_until_all(unsigned int *ivars, size_t nelems, const int *status, int cmp, unsigned int cmp_value) {
    shmem_uint_wait_until_all(ivars, nelems, status, cmp, cmp_value);
}
static inline void shmem_wait_until_all(unsigned long *ivars, size_t nelems, const int *status, int cmp, unsigned long cmp_value) {
    shmem_ulong_wait_until_all(ivars, nelems, status, cmp, cmp_value);
}
static inline void shmem_wait_until_all(unsigned long long *ivars, size_t nelems, const int *status, int cmp, unsigned long long cmp_value) {
    shmem_ulonglong_wait_until_all(ivars, nelems, status, cmp, cmp_value);
}

SHMEM_BIND_CXX_SYNC_EXTRAS(static inline void shmem_wait_until_all_vector( *ivars, size_t nelems, const int *status, int cmp,  *cmp_values) {
    shmem__wait_until_all_vector(ivars, nelems, status, cmp, cmp_values);
},)static inline void shmem_wait_until_all_vector(short *ivars, size_t nelems, const int *status, int cmp, short *cmp_values) {
    shmem_short_wait_until_all_vector(ivars, nelems, status, cmp, cmp_values);
}
static inline void shmem_wait_until_all_vector(int *ivars, size_t nelems, const int *status, int cmp, int *cmp_values) {
    shmem_int_wait_until_all_vector(ivars, nelems, status, cmp, cmp_values);
}
static inline void shmem_wait_until_all_vector(long *ivars, size_t nelems, const int *status, int cmp, long *cmp_values) {
    shmem_long_wait_until_all_vector(ivars, nelems, status, cmp, cmp_values);
}
static inline void shmem_wait_until_all_vector(long long *ivars, size_t nelems, const int *status, int cmp, long long *cmp_values) {
    shmem_longlong_wait_until_all_vector(ivars, nelems, status, cmp, cmp_values);
}
static inline void shmem_wait_until_all_vector(unsigned short *ivars, size_t nelems, const int *status, int cmp, unsigned short *cmp_values) {
    shmem_ushort_wait_until_all_vector(ivars, nelems, status, cmp, cmp_values);
}
static inline void shmem_wait_until_all_vector(unsigned int *ivars, size_t nelems, const int *status, int cmp, unsigned int *cmp_values) {
    shmem_uint_wait_until_all_vector(ivars, nelems, status, cmp, cmp_values);
}
static inline void shmem_wait_until_all_vector(unsigned long *ivars, size_t nelems, const int *status, int cmp, unsigned long *cmp_values) {
    shmem_ulong_wait_until_all_vector(ivars, nelems, status, cmp, cmp_values);
}
static inline void shmem_wait_until_all_vector(unsigned long long *ivars, size_t nelems, const int *status, int cmp, unsigned long long *cmp_values) {
    shmem_ulonglong_wait_until_all_vector(ivars, nelems, status, cmp, cmp_values);
}

SHMEM_BIND_CXX_SYNC_EXTRAS(static inline size_t shmem_wait_until_any( *ivars, size_t nelems, const int *status, int cmp,  cmp_value) {
    return shmem__wait_until_any(ivars, nelems, status, cmp, cmp_value);
},)static inline size_t shmem_wait_until_any(short *ivars, size_t nelems, const int *status, int cmp, short cmp_value) {
    return shmem_short_wait_until_any(ivars, nelems, status, cmp, cmp_value);
}
static inline size_t shmem_wait_until_any(int *ivars, size_t nelems, const int *status, int cmp, int cmp_value) {
    return shmem_int_wait_until_any(ivars, nelems, status, cmp, cmp_value);
}
static inline size_t shmem_wait_until_any(long *ivars, size_t nelems, const int *status, int cmp, long cmp_value) {
    return shmem_long_wait_until_any(ivars, nelems, status, cmp, cmp_value);
}
static inline size_t shmem_wait_until_any(long long *ivars, size_t nelems, const int *status, int cmp, long long cmp_value) {
    return shmem_longlong_wait_until_any(ivars, nelems, status, cmp, cmp_value);
}
static inline size_t shmem_wait_until_any(unsigned short *ivars, size_t nelems, const int *status, int cmp, unsigned short cmp_value) {
    return shmem_ushort_wait_until_any(ivars, nelems, status, cmp, cmp_value);
}
static inline size_t shmem_wait_until_any(unsigned int *ivars, size_t nelems, const int *status, int cmp, unsigned int cmp_value) {
    return shmem_uint_wait_until_any(ivars, nelems, status, cmp, cmp_value);
}
static inline size_t shmem_wait_until_any(unsigned long *ivars, size_t nelems, const int *status, int cmp, unsigned long cmp_value) {
    return shmem_ulong_wait_until_any(ivars, nelems, status, cmp, cmp_value);
}
static inline size_t shmem_wait_until_any(unsigned long long *ivars, size_t nelems, const int *status, int cmp, unsigned long long cmp_value) {
    return shmem_ulonglong_wait_until_any(ivars, nelems, status, cmp, cmp_value);
}

SHMEM_BIND_CXX_SYNC_EXTRAS(static inline size_t shmem_wait_until_any_vector( *ivars, size_t nelems, const int *status, int cmp,  *cmp_values) {
    return shmem__wait_until_any_vector(ivars, nelems, status, cmp, cmp_values);
},)static inline size_t shmem_wait_until_any_vector(short *ivars, size_t nelems, const int *status, int cmp, short *cmp_values) {
    return shmem_short_wait_until_any_vector(ivars, nelems, status, cmp, cmp_values);
}
static inline size_t shmem_wait_until_any_vector(int *ivars, size_t nelems, const int *status, int cmp, int *cmp_values) {
    return shmem_int_wait_until_any_vector(ivars, nelems, status, cmp, cmp_values);
}
static inline size_t shmem_wait_until_any_vector(long *ivars, size_t nelems, const int *status, int cmp, long *cmp_values) {
    return shmem_long_wait_until_any_vector(ivars, nelems, status, cmp, cmp_values);
}
static inline size_t shmem_wait_until_any_vector(long long *ivars, size_t nelems, const int *status, int cmp, long long *cmp_values) {
    return shmem_longlong_wait_until_any_vector(ivars, nelems, status, cmp, cmp_values);
}
static inline size_t shmem_wait_until_any_vector(unsigned short *ivars, size_t nelems, const int *status, int cmp, unsigned short *cmp_values) {
    return shmem_ushort_wait_until_any_vector(ivars, nelems, status, cmp, cmp_values);
}
static inline size_t shmem_wait_until_any_vector(unsigned int *ivars, size_t nelems, const int *status, int cmp, unsigned int *cmp_values) {
    return shmem_uint_wait_until_any_vector(ivars, nelems, status, cmp, cmp_values);
}
static inline size_t shmem_wait_until_any_vector(unsigned long *ivars, size_t nelems, const int *status, int cmp, unsigned long *cmp_values) {
    return shmem_ulong_wait_until_any_vector(ivars, nelems, status, cmp, cmp_values);
}
static inline size_t shmem_wait_until_any_vector(unsigned long long *ivars, size_t nelems, const int *status, int cmp, unsigned long long *cmp_values) {
    return shmem_ulonglong_wait_until_any_vector(ivars, nelems, status, cmp, cmp_values);
}

SHMEM_BIND_CXX_SYNC_EXTRAS(static inline size_t shmem_wait_until_some( *ivars, size_t nelems, size_t *indices, const int *status, int cmp,  cmp_value) {
    return shmem__wait_until_some(ivars, nelems, indices, status, cmp, cmp_value);
},)static inline size_t shmem_wait_until_some(short *ivars, size_t nelems, size_t *indices, const int *status, int cmp, short cmp_value) {
    return shmem_short_wait_until_some(ivars, nelems, indices, status, cmp, cmp_value);
}
static inline size_t shmem_wait_until_some(int *ivars, size_t nelems, size_t *indices, const int *status, int cmp, int cmp_value) {
    return shmem_int_wait_until_some(ivars, nelems, indices, status, cmp, cmp_value);
}
static inline size_t shmem_wait_until_some(long *ivars, size_t nelems, size_t *indices, const int *status, int cmp, long cmp_value) {
    return shmem_long_wait_until_some(ivars, nelems, indices, status, cmp, cmp_value);
}
static inline size_t shmem_wait_until_some(long long *ivars, size_t nelems, size_t *indices, const int *status, int cmp, long long cmp_value) {
    return shmem_longlong_wait_until_some(ivars, nelems, indices, status, cmp, cmp_value);
}
static inline size_t shmem_wait_until_some(unsigned short *ivars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned short cmp_value) {
    return shmem_ushort_wait_until_some(ivars, nelems, indices, status, cmp, cmp_value);
}
static inline size_t shmem_wait_until_some(unsigned int *ivars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned int cmp_value) {
    return shmem_uint_wait_until_some(ivars, nelems, indices, status, cmp, cmp_value);
}
static inline size_t shmem_wait_until_some(unsigned long *ivars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned long cmp_value) {
    return shmem_ulong_wait_until_some(ivars, nelems, indices, status, cmp, cmp_value);
}
static inline size_t shmem_wait_until_some(unsigned long long *ivars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned long long cmp_value) {
    return shmem_ulonglong_wait_until_some(ivars, nelems, indices, status, cmp, cmp_value);
}

SHMEM_BIND_CXX_SYNC_EXTRAS(static inline size_t shmem_wait_until_some_vector( *ivars, size_t nelems, size_t *indices, const int *status, int cmp,  *cmp_values) {
    return shmem__wait_until_some_vector(ivars, nelems, indices, status, cmp, cmp_values);
},)static inline size_t shmem_wait_until_some_vector(short *ivars, size_t nelems, size_t *indices, const int *status, int cmp, short *cmp_values) {
    return shmem_short_wait_until_some_vector(ivars, nelems, indices, status, cmp, cmp_values);
}
static inline size_t shmem_wait_until_some_vector(int *ivars, size_t nelems, size_t *indices, const int *status, int cmp, int *cmp_values) {
    return shmem_int_wait_until_some_vector(ivars, nelems, indices, status, cmp, cmp_values);
}
static inline size_t shmem_wait_until_some_vector(long *ivars, size_t nelems, size_t *indices, const int *status, int cmp, long *cmp_values) {
    return shmem_long_wait_until_some_vector(ivars, nelems, indices, status, cmp, cmp_values);
}
static inline size_t shmem_wait_until_some_vector(long long *ivars, size_t nelems, size_t *indices, const int *status, int cmp, long long *cmp_values) {
    return shmem_longlong_wait_until_some_vector(ivars, nelems, indices, status, cmp, cmp_values);
}
static inline size_t shmem_wait_until_some_vector(unsigned short *ivars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned short *cmp_values) {
    return shmem_ushort_wait_until_some_vector(ivars, nelems, indices, status, cmp, cmp_values);
}
static inline size_t shmem_wait_until_some_vector(unsigned int *ivars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned int *cmp_values) {
    return shmem_uint_wait_until_some_vector(ivars, nelems, indices, status, cmp, cmp_values);
}
static inline size_t shmem_wait_until_some_vector(unsigned long *ivars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned long *cmp_values) {
    return shmem_ulong_wait_until_some_vector(ivars, nelems, indices, status, cmp, cmp_values);
}
static inline size_t shmem_wait_until_some_vector(unsigned long long *ivars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned long long *cmp_values) {
    return shmem_ulonglong_wait_until_some_vector(ivars, nelems, indices, status, cmp, cmp_values);
}

SHMEM_BIND_CXX_SYNC_EXTRAS(static inline int shmem_test( *ivar, int cmp,  cmp_value) {
    return shmem__test(ivar, cmp, cmp_value);
},)static inline int shmem_test(short *ivar, int cmp, short cmp_value) {
    return shmem_short_test(ivar, cmp, cmp_value);
}
static inline int shmem_test(int *ivar, int cmp, int cmp_value) {
    return shmem_int_test(ivar, cmp, cmp_value);
}
static inline int shmem_test(long *ivar, int cmp, long cmp_value) {
    return shmem_long_test(ivar, cmp, cmp_value);
}
static inline int shmem_test(long long *ivar, int cmp, long long cmp_value) {
    return shmem_longlong_test(ivar, cmp, cmp_value);
}
static inline int shmem_test(unsigned short *ivar, int cmp, unsigned short cmp_value) {
    return shmem_ushort_test(ivar, cmp, cmp_value);
}
static inline int shmem_test(unsigned int *ivar, int cmp, unsigned int cmp_value) {
    return shmem_uint_test(ivar, cmp, cmp_value);
}
static inline int shmem_test(unsigned long *ivar, int cmp, unsigned long cmp_value) {
    return shmem_ulong_test(ivar, cmp, cmp_value);
}
static inline int shmem_test(unsigned long long *ivar, int cmp, unsigned long long cmp_value) {
    return shmem_ulonglong_test(ivar, cmp, cmp_value);
}

SHMEM_BIND_CXX_SYNC_EXTRAS(static inline int shmem_test_all( *ivars, size_t nelems, const int *status, int cmp,  cmp_value) {
    return shmem__test_all(ivars, nelems, status, cmp, cmp_value);
},)static inline int shmem_test_all(short *ivars, size_t nelems, const int *status, int cmp, short cmp_value) {
    return shmem_short_test_all(ivars, nelems, status, cmp, cmp_value);
}
static inline int shmem_test_all(int *ivars, size_t nelems, const int *status, int cmp, int cmp_value) {
    return shmem_int_test_all(ivars, nelems, status, cmp, cmp_value);
}
static inline int shmem_test_all(long *ivars, size_t nelems, const int *status, int cmp, long cmp_value) {
    return shmem_long_test_all(ivars, nelems, status, cmp, cmp_value);
}
static inline int shmem_test_all(long long *ivars, size_t nelems, const int *status, int cmp, long long cmp_value) {
    return shmem_longlong_test_all(ivars, nelems, status, cmp, cmp_value);
}
static inline int shmem_test_all(unsigned short *ivars, size_t nelems, const int *status, int cmp, unsigned short cmp_value) {
    return shmem_ushort_test_all(ivars, nelems, status, cmp, cmp_value);
}
static inline int shmem_test_all(unsigned int *ivars, size_t nelems, const int *status, int cmp, unsigned int cmp_value) {
    return shmem_uint_test_all(ivars, nelems, status, cmp, cmp_value);
}
static inline int shmem_test_all(unsigned long *ivars, size_t nelems, const int *status, int cmp, unsigned long cmp_value) {
    return shmem_ulong_test_all(ivars, nelems, status, cmp, cmp_value);
}
static inline int shmem_test_all(unsigned long long *ivars, size_t nelems, const int *status, int cmp, unsigned long long cmp_value) {
    return shmem_ulonglong_test_all(ivars, nelems, status, cmp, cmp_value);
}

SHMEM_BIND_CXX_SYNC_EXTRAS(static inline int shmem_test_all_vector( *ivars, size_t nelems, const int *status, int cmp,  *cmp_values) {
    return shmem__test_all_vector(ivars, nelems, status, cmp, cmp_values);
},)static inline int shmem_test_all_vector(short *ivars, size_t nelems, const int *status, int cmp, short *cmp_values) {
    return shmem_short_test_all_vector(ivars, nelems, status, cmp, cmp_values);
}
static inline int shmem_test_all_vector(int *ivars, size_t nelems, const int *status, int cmp, int *cmp_values) {
    return shmem_int_test_all_vector(ivars, nelems, status, cmp, cmp_values);
}
static inline int shmem_test_all_vector(long *ivars, size_t nelems, const int *status, int cmp, long *cmp_values) {
    return shmem_long_test_all_vector(ivars, nelems, status, cmp, cmp_values);
}
static inline int shmem_test_all_vector(long long *ivars, size_t nelems, const int *status, int cmp, long long *cmp_values) {
    return shmem_longlong_test_all_vector(ivars, nelems, status, cmp, cmp_values);
}
static inline int shmem_test_all_vector(unsigned short *ivars, size_t nelems, const int *status, int cmp, unsigned short *cmp_values) {
    return shmem_ushort_test_all_vector(ivars, nelems, status, cmp, cmp_values);
}
static inline int shmem_test_all_vector(unsigned int *ivars, size_t nelems, const int *status, int cmp, unsigned int *cmp_values) {
    return shmem_uint_test_all_vector(ivars, nelems, status, cmp, cmp_values);
}
static inline int shmem_test_all_vector(unsigned long *ivars, size_t nelems, const int *status, int cmp, unsigned long *cmp_values) {
    return shmem_ulong_test_all_vector(ivars, nelems, status, cmp, cmp_values);
}
static inline int shmem_test_all_vector(unsigned long long *ivars, size_t nelems, const int *status, int cmp, unsigned long long *cmp_values) {
    return shmem_ulonglong_test_all_vector(ivars, nelems, status, cmp, cmp_values);
}

SHMEM_BIND_CXX_SYNC_EXTRAS(static inline size_t shmem_test_any( *ivars, size_t nelems, const int *status, int cmp,  cmp_value) {
    return shmem__test_any(ivars, nelems, status, cmp, cmp_value);
},)static inline size_t shmem_test_any(short *ivars, size_t nelems, const int *status, int cmp, short cmp_value) {
    return shmem_short_test_any(ivars, nelems, status, cmp, cmp_value);
}
static inline size_t shmem_test_any(int *ivars, size_t nelems, const int *status, int cmp, int cmp_value) {
    return shmem_int_test_any(ivars, nelems, status, cmp, cmp_value);
}
static inline size_t shmem_test_any(long *ivars, size_t nelems, const int *status, int cmp, long cmp_value) {
    return shmem_long_test_any(ivars, nelems, status, cmp, cmp_value);
}
static inline size_t shmem_test_any(long long *ivars, size_t nelems, const int *status, int cmp, long long cmp_value) {
    return shmem_longlong_test_any(ivars, nelems, status, cmp, cmp_value);
}
static inline size_t shmem_test_any(unsigned short *ivars, size_t nelems, const int *status, int cmp, unsigned short cmp_value) {
    return shmem_ushort_test_any(ivars, nelems, status, cmp, cmp_value);
}
static inline size_t shmem_test_any(unsigned int *ivars, size_t nelems, const int *status, int cmp, unsigned int cmp_value) {
    return shmem_uint_test_any(ivars, nelems, status, cmp, cmp_value);
}
static inline size_t shmem_test_any(unsigned long *ivars, size_t nelems, const int *status, int cmp, unsigned long cmp_value) {
    return shmem_ulong_test_any(ivars, nelems, status, cmp, cmp_value);
}
static inline size_t shmem_test_any(unsigned long long *ivars, size_t nelems, const int *status, int cmp, unsigned long long cmp_value) {
    return shmem_ulonglong_test_any(ivars, nelems, status, cmp, cmp_value);
}

SHMEM_BIND_CXX_SYNC_EXTRAS(static inline size_t shmem_test_any_vector( *ivars, size_t nelems, const int *status, int cmp,  *cmp_values) {
    return shmem__test_any_vector(ivars, nelems, status, cmp, cmp_values);
},)static inline size_t shmem_test_any_vector(short *ivars, size_t nelems, const int *status, int cmp, short *cmp_values) {
    return shmem_short_test_any_vector(ivars, nelems, status, cmp, cmp_values);
}
static inline size_t shmem_test_any_vector(int *ivars, size_t nelems, const int *status, int cmp, int *cmp_values) {
    return shmem_int_test_any_vector(ivars, nelems, status, cmp, cmp_values);
}
static inline size_t shmem_test_any_vector(long *ivars, size_t nelems, const int *status, int cmp, long *cmp_values) {
    return shmem_long_test_any_vector(ivars, nelems, status, cmp, cmp_values);
}
static inline size_t shmem_test_any_vector(long long *ivars, size_t nelems, const int *status, int cmp, long long *cmp_values) {
    return shmem_longlong_test_any_vector(ivars, nelems, status, cmp, cmp_values);
}
static inline size_t shmem_test_any_vector(unsigned short *ivars, size_t nelems, const int *status, int cmp, unsigned short *cmp_values) {
    return shmem_ushort_test_any_vector(ivars, nelems, status, cmp, cmp_values);
}
static inline size_t shmem_test_any_vector(unsigned int *ivars, size_t nelems, const int *status, int cmp, unsigned int *cmp_values) {
    return shmem_uint_test_any_vector(ivars, nelems, status, cmp, cmp_values);
}
static inline size_t shmem_test_any_vector(unsigned long *ivars, size_t nelems, const int *status, int cmp, unsigned long *cmp_values) {
    return shmem_ulong_test_any_vector(ivars, nelems, status, cmp, cmp_values);
}
static inline size_t shmem_test_any_vector(unsigned long long *ivars, size_t nelems, const int *status, int cmp, unsigned long long *cmp_values) {
    return shmem_ulonglong_test_any_vector(ivars, nelems, status, cmp, cmp_values);
}

SHMEM_BIND_CXX_SYNC_EXTRAS(static inline size_t shmem_test_some( *ivars, size_t nelems, size_t *indices, const int *status, int cmp,  cmp_value) {
    return shmem__test_some(ivars, nelems, indices, status, cmp, cmp_value);
},)static inline size_t shmem_test_some(short *ivars, size_t nelems, size_t *indices, const int *status, int cmp, short cmp_value) {
    return shmem_short_test_some(ivars, nelems, indices, status, cmp, cmp_value);
}
static inline size_t shmem_test_some(int *ivars, size_t nelems, size_t *indices, const int *status, int cmp, int cmp_value) {
    return shmem_int_test_some(ivars, nelems, indices, status, cmp, cmp_value);
}
static inline size_t shmem_test_some(long *ivars, size_t nelems, size_t *indices, const int *status, int cmp, long cmp_value) {
    return shmem_long_test_some(ivars, nelems, indices, status, cmp, cmp_value);
}
static inline size_t shmem_test_some(long long *ivars, size_t nelems, size_t *indices, const int *status, int cmp, long long cmp_value) {
    return shmem_longlong_test_some(ivars, nelems, indices, status, cmp, cmp_value);
}
static inline size_t shmem_test_some(unsigned short *ivars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned short cmp_value) {
    return shmem_ushort_test_some(ivars, nelems, indices, status, cmp, cmp_value);
}
static inline size_t shmem_test_some(unsigned int *ivars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned int cmp_value) {
    return shmem_uint_test_some(ivars, nelems, indices, status, cmp, cmp_value);
}
static inline size_t shmem_test_some(unsigned long *ivars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned long cmp_value) {
    return shmem_ulong_test_some(ivars, nelems, indices, status, cmp, cmp_value);
}
static inline size_t shmem_test_some(unsigned long long *ivars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned long long cmp_value) {
    return shmem_ulonglong_test_some(ivars, nelems, indices, status, cmp, cmp_value);
}

SHMEM_BIND_CXX_SYNC_EXTRAS(static inline size_t shmem_test_some_vector( *ivars, size_t nelems, size_t *indices, const int *status, int cmp,  *cmp_values) {
    return shmem__test_some_vector(ivars, nelems, indices, status, cmp, cmp_values);
},)static inline size_t shmem_test_some_vector(short *ivars, size_t nelems, size_t *indices, const int *status, int cmp, short *cmp_values) {
    return shmem_short_test_some_vector(ivars, nelems, indices, status, cmp, cmp_values);
}
static inline size_t shmem_test_some_vector(int *ivars, size_t nelems, size_t *indices, const int *status, int cmp, int *cmp_values) {
    return shmem_int_test_some_vector(ivars, nelems, indices, status, cmp, cmp_values);
}
static inline size_t shmem_test_some_vector(long *ivars, size_t nelems, size_t *indices, const int *status, int cmp, long *cmp_values) {
    return shmem_long_test_some_vector(ivars, nelems, indices, status, cmp, cmp_values);
}
static inline size_t shmem_test_some_vector(long long *ivars, size_t nelems, size_t *indices, const int *status, int cmp, long long *cmp_values) {
    return shmem_longlong_test_some_vector(ivars, nelems, indices, status, cmp, cmp_values);
}
static inline size_t shmem_test_some_vector(unsigned short *ivars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned short *cmp_values) {
    return shmem_ushort_test_some_vector(ivars, nelems, indices, status, cmp, cmp_values);
}
static inline size_t shmem_test_some_vector(unsigned int *ivars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned int *cmp_values) {
    return shmem_uint_test_some_vector(ivars, nelems, indices, status, cmp, cmp_values);
}
static inline size_t shmem_test_some_vector(unsigned long *ivars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned long *cmp_values) {
    return shmem_ulong_test_some_vector(ivars, nelems, indices, status, cmp, cmp_values);
}
static inline size_t shmem_test_some_vector(unsigned long long *ivars, size_t nelems, size_t *indices, const int *status, int cmp, unsigned long long *cmp_values) {
    return shmem_ulonglong_test_some_vector(ivars, nelems, indices, status, cmp, cmp_values);
}


/* C11 Generic Macros */
#elif (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L && !defined(SHMEM_INTERNAL_INCLUDE))

/* These expressions have no effect, but cause the compiler to perform type
 * processing on the argument, e.g. to process int[5] down to int *.  EVAL_PTR
 * works with pointer types, including void*.  EVAL_PTR_OR_SCALAR works if the
 * argument is either a pointer (but not void*) or a scalar. */

#define SHMEM_C11_TYPE_EVAL_PTR(arg) &*(arg)
#define SHMEM_C11_TYPE_EVAL_PTR_OR_SCALAR(arg) (arg)+0

/* Helper routines to pick off specific arguments from a varags list. */
#define SHMEM_C11_ARG0(...) SHMEM_C11_ARG0_HELPER(__VA_ARGS__, sentinel)
#define SHMEM_C11_ARG0_HELPER(first, ...) first

#define SHMEM_C11_ARG1(first, ...) SHMEM_C11_ARG1_HELPER(__VA_ARGS__, sentinel)
#define SHMEM_C11_ARG1_HELPER(second, ...) second

/* This routine is intentionally incompatible with any of the generic OpenSHMEM
 * routines, so that if it is matched, it will cause a compile-time error. */

static inline void shmem_ctx_c11_generic_selection_failed(void) { }

/* Blocking block, scalar, and block-strided put */
#define shmem_put(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_RMA_EXTRAS(            *: shmem_ctx__put,, \)            float*: shmem_ctx_float_put, \
            double*: shmem_ctx_double_put, \
            long double*: shmem_ctx_longdouble_put, \
            char*: shmem_ctx_char_put, \
            signed char*: shmem_ctx_schar_put, \
            short*: shmem_ctx_short_put, \
            int*: shmem_ctx_int_put, \
            long*: shmem_ctx_long_put, \
            long long*: shmem_ctx_longlong_put, \
            unsigned char*: shmem_ctx_uchar_put, \
            unsigned short*: shmem_ctx_ushort_put, \
            unsigned int*: shmem_ctx_uint_put, \
            unsigned long*: shmem_ctx_ulong_put, \
            unsigned long long*: shmem_ctx_ulonglong_put \
        ), \
SHMEM_BIND_C11_RMA_EXTRAS(        *: shmem__put,, \)        float*: shmem_float_put, \
        double*: shmem_double_put, \
        long double*: shmem_longdouble_put, \
        char*: shmem_char_put, \
        signed char*: shmem_schar_put, \
        short*: shmem_short_put, \
        int*: shmem_int_put, \
        long*: shmem_long_put, \
        long long*: shmem_longlong_put, \
        unsigned char*: shmem_uchar_put, \
        unsigned short*: shmem_ushort_put, \
        unsigned int*: shmem_uint_put, \
        unsigned long*: shmem_ulong_put, \
        unsigned long long*: shmem_ulonglong_put \
    )(__VA_ARGS__)

#define shmem_p(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR_OR_SCALAR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_RMA_EXTRAS(            *: shmem_ctx__p,, \)            float*: shmem_ctx_float_p, \
            double*: shmem_ctx_double_p, \
            long double*: shmem_ctx_longdouble_p, \
            char*: shmem_ctx_char_p, \
            signed char*: shmem_ctx_schar_p, \
            short*: shmem_ctx_short_p, \
            int*: shmem_ctx_int_p, \
            long*: shmem_ctx_long_p, \
            long long*: shmem_ctx_longlong_p, \
            unsigned char*: shmem_ctx_uchar_p, \
            unsigned short*: shmem_ctx_ushort_p, \
            unsigned int*: shmem_ctx_uint_p, \
            unsigned long*: shmem_ctx_ulong_p, \
            unsigned long long*: shmem_ctx_ulonglong_p, \
            default: shmem_ctx_c11_generic_selection_failed \
        ), \
SHMEM_BIND_C11_RMA_EXTRAS(        *: shmem__p,, \)        float*: shmem_float_p, \
        double*: shmem_double_p, \
        long double*: shmem_longdouble_p, \
        char*: shmem_char_p, \
        signed char*: shmem_schar_p, \
        short*: shmem_short_p, \
        int*: shmem_int_p, \
        long*: shmem_long_p, \
        long long*: shmem_longlong_p, \
        unsigned char*: shmem_uchar_p, \
        unsigned short*: shmem_ushort_p, \
        unsigned int*: shmem_uint_p, \
        unsigned long*: shmem_ulong_p, \
        unsigned long long*: shmem_ulonglong_p \
    )(__VA_ARGS__)

#define shmem_iput(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_RMA_EXTRAS(            *: shmem_ctx__iput,, \)            float*: shmem_ctx_float_iput, \
            double*: shmem_ctx_double_iput, \
            long double*: shmem_ctx_longdouble_iput, \
            char*: shmem_ctx_char_iput, \
            signed char*: shmem_ctx_schar_iput, \
            short*: shmem_ctx_short_iput, \
            int*: shmem_ctx_int_iput, \
            long*: shmem_ctx_long_iput, \
            long long*: shmem_ctx_longlong_iput, \
            unsigned char*: shmem_ctx_uchar_iput, \
            unsigned short*: shmem_ctx_ushort_iput, \
            unsigned int*: shmem_ctx_uint_iput, \
            unsigned long*: shmem_ctx_ulong_iput, \
            unsigned long long*: shmem_ctx_ulonglong_iput \
        ), \
SHMEM_BIND_C11_RMA_EXTRAS(        *: shmem__iput,, \)        float*: shmem_float_iput, \
        double*: shmem_double_iput, \
        long double*: shmem_longdouble_iput, \
        char*: shmem_char_iput, \
        signed char*: shmem_schar_iput, \
        short*: shmem_short_iput, \
        int*: shmem_int_iput, \
        long*: shmem_long_iput, \
        long long*: shmem_longlong_iput, \
        unsigned char*: shmem_uchar_iput, \
        unsigned short*: shmem_ushort_iput, \
        unsigned int*: shmem_uint_iput, \
        unsigned long*: shmem_ulong_iput, \
        unsigned long long*: shmem_ulonglong_iput \
    )(__VA_ARGS__)

/* Blocking block, scalar, and block-strided get */
#define shmem_get(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_RMA_EXTRAS(            *: shmem_ctx__get,, \)            float*: shmem_ctx_float_get, \
            double*: shmem_ctx_double_get, \
            long double*: shmem_ctx_longdouble_get, \
            char*: shmem_ctx_char_get, \
            signed char*: shmem_ctx_schar_get, \
            short*: shmem_ctx_short_get, \
            int*: shmem_ctx_int_get, \
            long*: shmem_ctx_long_get, \
            long long*: shmem_ctx_longlong_get, \
            unsigned char*: shmem_ctx_uchar_get, \
            unsigned short*: shmem_ctx_ushort_get, \
            unsigned int*: shmem_ctx_uint_get, \
            unsigned long*: shmem_ctx_ulong_get, \
            unsigned long long*: shmem_ctx_ulonglong_get \
        ), \
SHMEM_BIND_C11_RMA_EXTRAS(        *: shmem__get,, \)        float*: shmem_float_get, \
        double*: shmem_double_get, \
        long double*: shmem_longdouble_get, \
        char*: shmem_char_get, \
        signed char*: shmem_schar_get, \
        short*: shmem_short_get, \
        int*: shmem_int_get, \
        long*: shmem_long_get, \
        long long*: shmem_longlong_get, \
        unsigned char*: shmem_uchar_get, \
        unsigned short*: shmem_ushort_get, \
        unsigned int*: shmem_uint_get, \
        unsigned long*: shmem_ulong_get, \
        unsigned long long*: shmem_ulonglong_get \
    )(__VA_ARGS__)

#define shmem_g(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR_OR_SCALAR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_RMA_EXTRAS(            *: shmem_ctx__g,, \)            float*: shmem_ctx_float_g, \
            double*: shmem_ctx_double_g, \
            long double*: shmem_ctx_longdouble_g, \
            char*: shmem_ctx_char_g, \
            signed char*: shmem_ctx_schar_g, \
            short*: shmem_ctx_short_g, \
            int*: shmem_ctx_int_g, \
            long*: shmem_ctx_long_g, \
            long long*: shmem_ctx_longlong_g, \
            unsigned char*: shmem_ctx_uchar_g, \
            unsigned short*: shmem_ctx_ushort_g, \
            unsigned int*: shmem_ctx_uint_g, \
            unsigned long*: shmem_ctx_ulong_g, \
            unsigned long long*: shmem_ctx_ulonglong_g, \
            default: shmem_ctx_c11_generic_selection_failed \
        ), \
SHMEM_BIND_C11_RMA_EXTRAS(        *: shmem__g,, \)        float*: shmem_float_g, \
        double*: shmem_double_g, \
        long double*: shmem_longdouble_g, \
        char*: shmem_char_g, \
        signed char*: shmem_schar_g, \
        short*: shmem_short_g, \
        int*: shmem_int_g, \
        long*: shmem_long_g, \
        long long*: shmem_longlong_g, \
        unsigned char*: shmem_uchar_g, \
        unsigned short*: shmem_ushort_g, \
        unsigned int*: shmem_uint_g, \
        unsigned long*: shmem_ulong_g, \
        unsigned long long*: shmem_ulonglong_g \
    )(__VA_ARGS__)

#define shmem_iget(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_RMA_EXTRAS(            *: shmem_ctx__iget,, \)            float*: shmem_ctx_float_iget, \
            double*: shmem_ctx_double_iget, \
            long double*: shmem_ctx_longdouble_iget, \
            char*: shmem_ctx_char_iget, \
            signed char*: shmem_ctx_schar_iget, \
            short*: shmem_ctx_short_iget, \
            int*: shmem_ctx_int_iget, \
            long*: shmem_ctx_long_iget, \
            long long*: shmem_ctx_longlong_iget, \
            unsigned char*: shmem_ctx_uchar_iget, \
            unsigned short*: shmem_ctx_ushort_iget, \
            unsigned int*: shmem_ctx_uint_iget, \
            unsigned long*: shmem_ctx_ulong_iget, \
            unsigned long long*: shmem_ctx_ulonglong_iget \
        ), \
SHMEM_BIND_C11_RMA_EXTRAS(        *: shmem__iget,, \)        float*: shmem_float_iget, \
        double*: shmem_double_iget, \
        long double*: shmem_longdouble_iget, \
        char*: shmem_char_iget, \
        signed char*: shmem_schar_iget, \
        short*: shmem_short_iget, \
        int*: shmem_int_iget, \
        long*: shmem_long_iget, \
        long long*: shmem_longlong_iget, \
        unsigned char*: shmem_uchar_iget, \
        unsigned short*: shmem_ushort_iget, \
        unsigned int*: shmem_uint_iget, \
        unsigned long*: shmem_ulong_iget, \
        unsigned long long*: shmem_ulonglong_iget \
    )(__VA_ARGS__)

/* Nonblocking block put/get */
#define shmem_put_nbi(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_RMA_EXTRAS(            *: shmem_ctx__put_nbi,, \)            float*: shmem_ctx_float_put_nbi, \
            double*: shmem_ctx_double_put_nbi, \
            long double*: shmem_ctx_longdouble_put_nbi, \
            char*: shmem_ctx_char_put_nbi, \
            signed char*: shmem_ctx_schar_put_nbi, \
            short*: shmem_ctx_short_put_nbi, \
            int*: shmem_ctx_int_put_nbi, \
            long*: shmem_ctx_long_put_nbi, \
            long long*: shmem_ctx_longlong_put_nbi, \
            unsigned char*: shmem_ctx_uchar_put_nbi, \
            unsigned short*: shmem_ctx_ushort_put_nbi, \
            unsigned int*: shmem_ctx_uint_put_nbi, \
            unsigned long*: shmem_ctx_ulong_put_nbi, \
            unsigned long long*: shmem_ctx_ulonglong_put_nbi \
        ), \
SHMEM_BIND_C11_RMA_EXTRAS(        *: shmem__put_nbi,, \)        float*: shmem_float_put_nbi, \
        double*: shmem_double_put_nbi, \
        long double*: shmem_longdouble_put_nbi, \
        char*: shmem_char_put_nbi, \
        signed char*: shmem_schar_put_nbi, \
        short*: shmem_short_put_nbi, \
        int*: shmem_int_put_nbi, \
        long*: shmem_long_put_nbi, \
        long long*: shmem_longlong_put_nbi, \
        unsigned char*: shmem_uchar_put_nbi, \
        unsigned short*: shmem_ushort_put_nbi, \
        unsigned int*: shmem_uint_put_nbi, \
        unsigned long*: shmem_ulong_put_nbi, \
        unsigned long long*: shmem_ulonglong_put_nbi \
    )(__VA_ARGS__)

#define shmem_get_nbi(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_RMA_EXTRAS(            *: shmem_ctx__get_nbi,, \)            float*: shmem_ctx_float_get_nbi, \
            double*: shmem_ctx_double_get_nbi, \
            long double*: shmem_ctx_longdouble_get_nbi, \
            char*: shmem_ctx_char_get_nbi, \
            signed char*: shmem_ctx_schar_get_nbi, \
            short*: shmem_ctx_short_get_nbi, \
            int*: shmem_ctx_int_get_nbi, \
            long*: shmem_ctx_long_get_nbi, \
            long long*: shmem_ctx_longlong_get_nbi, \
            unsigned char*: shmem_ctx_uchar_get_nbi, \
            unsigned short*: shmem_ctx_ushort_get_nbi, \
            unsigned int*: shmem_ctx_uint_get_nbi, \
            unsigned long*: shmem_ctx_ulong_get_nbi, \
            unsigned long long*: shmem_ctx_ulonglong_get_nbi \
        ), \
SHMEM_BIND_C11_RMA_EXTRAS(        *: shmem__get_nbi,, \)        float*: shmem_float_get_nbi, \
        double*: shmem_double_get_nbi, \
        long double*: shmem_longdouble_get_nbi, \
        char*: shmem_char_get_nbi, \
        signed char*: shmem_schar_get_nbi, \
        short*: shmem_short_get_nbi, \
        int*: shmem_int_get_nbi, \
        long*: shmem_long_get_nbi, \
        long long*: shmem_longlong_get_nbi, \
        unsigned char*: shmem_uchar_get_nbi, \
        unsigned short*: shmem_ushort_get_nbi, \
        unsigned int*: shmem_uint_get_nbi, \
        unsigned long*: shmem_ulong_get_nbi, \
        unsigned long long*: shmem_ulonglong_get_nbi \
    )(__VA_ARGS__)

/* Atomics with standard AMO types */
#define shmem_add(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
SHMEM_BIND_C11_AMO_EXTRAS(        *: shmem__add,, \)        int*: shmem_int_add, \
        long*: shmem_long_add, \
        long long*: shmem_longlong_add, \
        unsigned int*: shmem_uint_add, \
        unsigned long*: shmem_ulong_add, \
        unsigned long long*: shmem_ulonglong_add \
    )(__VA_ARGS__)

#define shmem_atomic_add(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR_OR_SCALAR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_AMO_EXTRAS(            *: shmem_ctx__atomic_add,, \)            int*: shmem_ctx_int_atomic_add, \
            long*: shmem_ctx_long_atomic_add, \
            long long*: shmem_ctx_longlong_atomic_add, \
            unsigned int*: shmem_ctx_uint_atomic_add, \
            unsigned long*: shmem_ctx_ulong_atomic_add, \
            unsigned long long*: shmem_ctx_ulonglong_atomic_add, \
            default: shmem_ctx_c11_generic_selection_failed \
        ), \
SHMEM_BIND_C11_AMO_EXTRAS(        *: shmem__atomic_add,, \)        int*: shmem_int_atomic_add, \
        long*: shmem_long_atomic_add, \
        long long*: shmem_longlong_atomic_add, \
        unsigned int*: shmem_uint_atomic_add, \
        unsigned long*: shmem_ulong_atomic_add, \
        unsigned long long*: shmem_ulonglong_atomic_add \
    )(__VA_ARGS__)

#define shmem_cswap(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
SHMEM_BIND_C11_AMO_EXTRAS(        *: shmem__cswap,, \)        int*: shmem_int_cswap, \
        long*: shmem_long_cswap, \
        long long*: shmem_longlong_cswap, \
        unsigned int*: shmem_uint_cswap, \
        unsigned long*: shmem_ulong_cswap, \
        unsigned long long*: shmem_ulonglong_cswap \
    )(__VA_ARGS__)

#define shmem_atomic_compare_swap(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR_OR_SCALAR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_AMO_EXTRAS(            *: shmem_ctx__atomic_compare_swap,, \)            int*: shmem_ctx_int_atomic_compare_swap, \
            long*: shmem_ctx_long_atomic_compare_swap, \
            long long*: shmem_ctx_longlong_atomic_compare_swap, \
            unsigned int*: shmem_ctx_uint_atomic_compare_swap, \
            unsigned long*: shmem_ctx_ulong_atomic_compare_swap, \
            unsigned long long*: shmem_ctx_ulonglong_atomic_compare_swap, \
            default: shmem_ctx_c11_generic_selection_failed \
        ), \
SHMEM_BIND_C11_AMO_EXTRAS(        *: shmem__atomic_compare_swap,, \)        int*: shmem_int_atomic_compare_swap, \
        long*: shmem_long_atomic_compare_swap, \
        long long*: shmem_longlong_atomic_compare_swap, \
        unsigned int*: shmem_uint_atomic_compare_swap, \
        unsigned long*: shmem_ulong_atomic_compare_swap, \
        unsigned long long*: shmem_ulonglong_atomic_compare_swap \
    )(__VA_ARGS__)


#define shmem_finc(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
SHMEM_BIND_C11_AMO_EXTRAS(        *: shmem__finc,, \)        int*: shmem_int_finc, \
        long*: shmem_long_finc, \
        long long*: shmem_longlong_finc, \
        unsigned int*: shmem_uint_finc, \
        unsigned long*: shmem_ulong_finc, \
        unsigned long long*: shmem_ulonglong_finc \
    )(__VA_ARGS__)

#define shmem_atomic_fetch_inc(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR_OR_SCALAR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_AMO_EXTRAS(            *: shmem_ctx__atomic_fetch_inc,, \)            int*: shmem_ctx_int_atomic_fetch_inc, \
            long*: shmem_ctx_long_atomic_fetch_inc, \
            long long*: shmem_ctx_longlong_atomic_fetch_inc, \
            unsigned int*: shmem_ctx_uint_atomic_fetch_inc, \
            unsigned long*: shmem_ctx_ulong_atomic_fetch_inc, \
            unsigned long long*: shmem_ctx_ulonglong_atomic_fetch_inc, \
            default: shmem_ctx_c11_generic_selection_failed \
        ), \
SHMEM_BIND_C11_AMO_EXTRAS(        *: shmem__atomic_fetch_inc,, \)        int*: shmem_int_atomic_fetch_inc, \
        long*: shmem_long_atomic_fetch_inc, \
        long long*: shmem_longlong_atomic_fetch_inc, \
        unsigned int*: shmem_uint_atomic_fetch_inc, \
        unsigned long*: shmem_ulong_atomic_fetch_inc, \
        unsigned long long*: shmem_ulonglong_atomic_fetch_inc \
    )(__VA_ARGS__)

#define shmem_inc(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
SHMEM_BIND_C11_AMO_EXTRAS(        *: shmem__inc,, \)        int*: shmem_int_inc, \
        long*: shmem_long_inc, \
        long long*: shmem_longlong_inc, \
        unsigned int*: shmem_uint_inc, \
        unsigned long*: shmem_ulong_inc, \
        unsigned long long*: shmem_ulonglong_inc \
    )(__VA_ARGS__)

#define shmem_atomic_inc(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR_OR_SCALAR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_AMO_EXTRAS(            *: shmem_ctx__atomic_inc,, \)            int*: shmem_ctx_int_atomic_inc, \
            long*: shmem_ctx_long_atomic_inc, \
            long long*: shmem_ctx_longlong_atomic_inc, \
            unsigned int*: shmem_ctx_uint_atomic_inc, \
            unsigned long*: shmem_ctx_ulong_atomic_inc, \
            unsigned long long*: shmem_ctx_ulonglong_atomic_inc, \
            default: shmem_ctx_c11_generic_selection_failed \
        ), \
SHMEM_BIND_C11_AMO_EXTRAS(        *: shmem__atomic_inc,, \)        int*: shmem_int_atomic_inc, \
        long*: shmem_long_atomic_inc, \
        long long*: shmem_longlong_atomic_inc, \
        unsigned int*: shmem_uint_atomic_inc, \
        unsigned long*: shmem_ulong_atomic_inc, \
        unsigned long long*: shmem_ulonglong_atomic_inc \
    )(__VA_ARGS__)

#define shmem_fadd(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
SHMEM_BIND_C11_AMO_EXTRAS(        *: shmem__fadd,, \)        int*: shmem_int_fadd, \
        long*: shmem_long_fadd, \
        long long*: shmem_longlong_fadd, \
        unsigned int*: shmem_uint_fadd, \
        unsigned long*: shmem_ulong_fadd, \
        unsigned long long*: shmem_ulonglong_fadd \
    )(__VA_ARGS__)

#define shmem_atomic_fetch_add(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR_OR_SCALAR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_AMO_EXTRAS(            *: shmem_ctx__atomic_fetch_add,, \)            int*: shmem_ctx_int_atomic_fetch_add, \
            long*: shmem_ctx_long_atomic_fetch_add, \
            long long*: shmem_ctx_longlong_atomic_fetch_add, \
            unsigned int*: shmem_ctx_uint_atomic_fetch_add, \
            unsigned long*: shmem_ctx_ulong_atomic_fetch_add, \
            unsigned long long*: shmem_ctx_ulonglong_atomic_fetch_add, \
            default: shmem_ctx_c11_generic_selection_failed \
        ), \
SHMEM_BIND_C11_AMO_EXTRAS(        *: shmem__atomic_fetch_add,, \)        int*: shmem_int_atomic_fetch_add, \
        long*: shmem_long_atomic_fetch_add, \
        long long*: shmem_longlong_atomic_fetch_add, \
        unsigned int*: shmem_uint_atomic_fetch_add, \
        unsigned long*: shmem_ulong_atomic_fetch_add, \
        unsigned long long*: shmem_ulonglong_atomic_fetch_add \
    )(__VA_ARGS__)

/* Blocking put with signal */
#define shmem_put_signal(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_RMA_EXTRAS(            *: shmem_ctx__put_signal,, \)            float*: shmem_ctx_float_put_signal, \
            double*: shmem_ctx_double_put_signal, \
            long double*: shmem_ctx_longdouble_put_signal, \
            char*: shmem_ctx_char_put_signal, \
            signed char*: shmem_ctx_schar_put_signal, \
            short*: shmem_ctx_short_put_signal, \
            int*: shmem_ctx_int_put_signal, \
            long*: shmem_ctx_long_put_signal, \
            long long*: shmem_ctx_longlong_put_signal, \
            unsigned char*: shmem_ctx_uchar_put_signal, \
            unsigned short*: shmem_ctx_ushort_put_signal, \
            unsigned int*: shmem_ctx_uint_put_signal, \
            unsigned long*: shmem_ctx_ulong_put_signal, \
            unsigned long long*: shmem_ctx_ulonglong_put_signal, \
            default: shmem_ctx_c11_generic_selection_failed \
        ), \
SHMEM_BIND_C11_RMA_EXTRAS(        *: shmem__put_signal,, \)        float*: shmem_float_put_signal, \
        double*: shmem_double_put_signal, \
        long double*: shmem_longdouble_put_signal, \
        char*: shmem_char_put_signal, \
        signed char*: shmem_schar_put_signal, \
        short*: shmem_short_put_signal, \
        int*: shmem_int_put_signal, \
        long*: shmem_long_put_signal, \
        long long*: shmem_longlong_put_signal, \
        unsigned char*: shmem_uchar_put_signal, \
        unsigned short*: shmem_ushort_put_signal, \
        unsigned int*: shmem_uint_put_signal, \
        unsigned long*: shmem_ulong_put_signal, \
        unsigned long long*: shmem_ulonglong_put_signal \
    )(__VA_ARGS__)

/* Non-blocking put with signal */
#define shmem_put_signal_nbi(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_RMA_EXTRAS(            *: shmem_ctx__put_signal_nbi,, \)            float*: shmem_ctx_float_put_signal_nbi, \
            double*: shmem_ctx_double_put_signal_nbi, \
            long double*: shmem_ctx_longdouble_put_signal_nbi, \
            char*: shmem_ctx_char_put_signal_nbi, \
            signed char*: shmem_ctx_schar_put_signal_nbi, \
            short*: shmem_ctx_short_put_signal_nbi, \
            int*: shmem_ctx_int_put_signal_nbi, \
            long*: shmem_ctx_long_put_signal_nbi, \
            long long*: shmem_ctx_longlong_put_signal_nbi, \
            unsigned char*: shmem_ctx_uchar_put_signal_nbi, \
            unsigned short*: shmem_ctx_ushort_put_signal_nbi, \
            unsigned int*: shmem_ctx_uint_put_signal_nbi, \
            unsigned long*: shmem_ctx_ulong_put_signal_nbi, \
            unsigned long long*: shmem_ctx_ulonglong_put_signal_nbi, \
            default: shmem_ctx_c11_generic_selection_failed \
        ), \
SHMEM_BIND_C11_RMA_EXTRAS(        *: shmem__put_signal_nbi,, \)        float*: shmem_float_put_signal_nbi, \
        double*: shmem_double_put_signal_nbi, \
        long double*: shmem_longdouble_put_signal_nbi, \
        char*: shmem_char_put_signal_nbi, \
        signed char*: shmem_schar_put_signal_nbi, \
        short*: shmem_short_put_signal_nbi, \
        int*: shmem_int_put_signal_nbi, \
        long*: shmem_long_put_signal_nbi, \
        long long*: shmem_longlong_put_signal_nbi, \
        unsigned char*: shmem_uchar_put_signal_nbi, \
        unsigned short*: shmem_ushort_put_signal_nbi, \
        unsigned int*: shmem_uint_put_signal_nbi, \
        unsigned long*: shmem_ulong_put_signal_nbi, \
        unsigned long long*: shmem_ulonglong_put_signal_nbi \
    )(__VA_ARGS__)

/* Nonblocking swap opeartions */
#define shmem_atomic_swap_nbi(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR_OR_SCALAR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_EXTENDED_AMO_EXTRAS(            *: shmem_ctx__atomic_swap_nbi,, \)            int*: shmem_ctx_int_atomic_swap_nbi, \
            long*: shmem_ctx_long_atomic_swap_nbi, \
            long long*: shmem_ctx_longlong_atomic_swap_nbi, \
            unsigned int*: shmem_ctx_uint_atomic_swap_nbi, \
            unsigned long*: shmem_ctx_ulong_atomic_swap_nbi, \
            unsigned long long*: shmem_ctx_ulonglong_atomic_swap_nbi, \
            float*: shmem_ctx_float_atomic_swap_nbi, \
            double*: shmem_ctx_double_atomic_swap_nbi, \
            default: shmem_ctx_c11_generic_selection_failed \
        ), \
SHMEM_BIND_C11_EXTENDED_AMO_EXTRAS(        *: shmem__atomic_swap_nbi,, \)        int*: shmem_int_atomic_swap_nbi, \
        long*: shmem_long_atomic_swap_nbi, \
        long long*: shmem_longlong_atomic_swap_nbi, \
        unsigned int*: shmem_uint_atomic_swap_nbi, \
        unsigned long*: shmem_ulong_atomic_swap_nbi, \
        unsigned long long*: shmem_ulonglong_atomic_swap_nbi, \
        float*: shmem_float_atomic_swap_nbi, \
        double*: shmem_double_atomic_swap_nbi \
    )(__VA_ARGS__)

#define shmem_atomic_compare_swap_nbi(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR_OR_SCALAR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_AMO_EXTRAS(            *: shmem_ctx__atomic_compare_swap_nbi,, \)            int*: shmem_ctx_int_atomic_compare_swap_nbi, \
            long*: shmem_ctx_long_atomic_compare_swap_nbi, \
            long long*: shmem_ctx_longlong_atomic_compare_swap_nbi, \
            unsigned int*: shmem_ctx_uint_atomic_compare_swap_nbi, \
            unsigned long*: shmem_ctx_ulong_atomic_compare_swap_nbi, \
            unsigned long long*: shmem_ctx_ulonglong_atomic_compare_swap_nbi, \
            default: shmem_ctx_c11_generic_selection_failed \
        ), \
SHMEM_BIND_C11_AMO_EXTRAS(        *: shmem__atomic_compare_swap_nbi,, \)        int*: shmem_int_atomic_compare_swap_nbi, \
        long*: shmem_long_atomic_compare_swap_nbi, \
        long long*: shmem_longlong_atomic_compare_swap_nbi, \
        unsigned int*: shmem_uint_atomic_compare_swap_nbi, \
        unsigned long*: shmem_ulong_atomic_compare_swap_nbi, \
        unsigned long long*: shmem_ulonglong_atomic_compare_swap_nbi \
    )(__VA_ARGS__)

/* Nonblocking fetching AMOs */
#define shmem_atomic_fetch_nbi(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR_OR_SCALAR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_EXTENDED_AMO_EXTRAS(            *: shmem_ctx__atomic_fetch_nbi,, \)            int*: shmem_ctx_int_atomic_fetch_nbi, \
            long*: shmem_ctx_long_atomic_fetch_nbi, \
            long long*: shmem_ctx_longlong_atomic_fetch_nbi, \
            unsigned int*: shmem_ctx_uint_atomic_fetch_nbi, \
            unsigned long*: shmem_ctx_ulong_atomic_fetch_nbi, \
            unsigned long long*: shmem_ctx_ulonglong_atomic_fetch_nbi, \
            float*: shmem_ctx_float_atomic_fetch_nbi, \
            double*: shmem_ctx_double_atomic_fetch_nbi, \
SHMEM_BIND_C11_EXTENDED_AMO_EXTRAS(            const *: shmem_ctx__atomic_fetch_nbi,, \)            const int*: shmem_ctx_int_atomic_fetch_nbi, \
            const long*: shmem_ctx_long_atomic_fetch_nbi, \
            const long long*: shmem_ctx_longlong_atomic_fetch_nbi, \
            const unsigned int*: shmem_ctx_uint_atomic_fetch_nbi, \
            const unsigned long*: shmem_ctx_ulong_atomic_fetch_nbi, \
            const unsigned long long*: shmem_ctx_ulonglong_atomic_fetch_nbi, \
            const float*: shmem_ctx_float_atomic_fetch_nbi, \
            const double*: shmem_ctx_double_atomic_fetch_nbi, \
            default: shmem_ctx_c11_generic_selection_failed \
        ), \
SHMEM_BIND_C11_EXTENDED_AMO_EXTRAS(        *: shmem__atomic_fetch_nbi,, \)        int*: shmem_int_atomic_fetch_nbi, \
        long*: shmem_long_atomic_fetch_nbi, \
        long long*: shmem_longlong_atomic_fetch_nbi, \
        unsigned int*: shmem_uint_atomic_fetch_nbi, \
        unsigned long*: shmem_ulong_atomic_fetch_nbi, \
        unsigned long long*: shmem_ulonglong_atomic_fetch_nbi, \
        float*: shmem_float_atomic_fetch_nbi, \
        double*: shmem_double_atomic_fetch_nbi, \
SHMEM_BIND_C11_EXTENDED_AMO_EXTRAS(        const *: shmem__atomic_fetch_nbi,, \)        const int*: shmem_int_atomic_fetch_nbi, \
        const long*: shmem_long_atomic_fetch_nbi, \
        const long long*: shmem_longlong_atomic_fetch_nbi, \
        const unsigned int*: shmem_uint_atomic_fetch_nbi, \
        const unsigned long*: shmem_ulong_atomic_fetch_nbi, \
        const unsigned long long*: shmem_ulonglong_atomic_fetch_nbi, \
        const float*: shmem_float_atomic_fetch_nbi, \
        const double*: shmem_double_atomic_fetch_nbi \
    )(__VA_ARGS__)

#define shmem_atomic_fetch_inc_nbi(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR_OR_SCALAR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_AMO_EXTRAS(            *: shmem_ctx__atomic_fetch_inc_nbi,, \)            int*: shmem_ctx_int_atomic_fetch_inc_nbi, \
            long*: shmem_ctx_long_atomic_fetch_inc_nbi, \
            long long*: shmem_ctx_longlong_atomic_fetch_inc_nbi, \
            unsigned int*: shmem_ctx_uint_atomic_fetch_inc_nbi, \
            unsigned long*: shmem_ctx_ulong_atomic_fetch_inc_nbi, \
            unsigned long long*: shmem_ctx_ulonglong_atomic_fetch_inc_nbi, \
            default: shmem_ctx_c11_generic_selection_failed \
        ), \
SHMEM_BIND_C11_AMO_EXTRAS(        *: shmem__atomic_fetch_inc_nbi,, \)        int*: shmem_int_atomic_fetch_inc_nbi, \
        long*: shmem_long_atomic_fetch_inc_nbi, \
        long long*: shmem_longlong_atomic_fetch_inc_nbi, \
        unsigned int*: shmem_uint_atomic_fetch_inc_nbi, \
        unsigned long*: shmem_ulong_atomic_fetch_inc_nbi, \
        unsigned long long*: shmem_ulonglong_atomic_fetch_inc_nbi \
    )(__VA_ARGS__)

#define shmem_atomic_fetch_add_nbi(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR_OR_SCALAR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_AMO_EXTRAS(            *: shmem_ctx__atomic_fetch_add_nbi,, \)            int*: shmem_ctx_int_atomic_fetch_add_nbi, \
            long*: shmem_ctx_long_atomic_fetch_add_nbi, \
            long long*: shmem_ctx_longlong_atomic_fetch_add_nbi, \
            unsigned int*: shmem_ctx_uint_atomic_fetch_add_nbi, \
            unsigned long*: shmem_ctx_ulong_atomic_fetch_add_nbi, \
            unsigned long long*: shmem_ctx_ulonglong_atomic_fetch_add_nbi, \
            default: shmem_ctx_c11_generic_selection_failed \
        ), \
SHMEM_BIND_C11_AMO_EXTRAS(        *: shmem__atomic_fetch_add_nbi,, \)        int*: shmem_int_atomic_fetch_add_nbi, \
        long*: shmem_long_atomic_fetch_add_nbi, \
        long long*: shmem_longlong_atomic_fetch_add_nbi, \
        unsigned int*: shmem_uint_atomic_fetch_add_nbi, \
        unsigned long*: shmem_ulong_atomic_fetch_add_nbi, \
        unsigned long long*: shmem_ulonglong_atomic_fetch_add_nbi \
    )(__VA_ARGS__)

#define shmem_atomic_fetch_and_nbi(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR_OR_SCALAR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_BITWISE_AMO_EXTRAS(            *: shmem_ctx__atomic_fetch_and_nbi,, \)            int32_t*: shmem_ctx_int32_atomic_fetch_and_nbi, \
            int64_t*: shmem_ctx_int64_atomic_fetch_and_nbi, \
            unsigned int*: shmem_ctx_uint_atomic_fetch_and_nbi, \
            unsigned long*: shmem_ctx_ulong_atomic_fetch_and_nbi, \
            unsigned long long*: shmem_ctx_ulonglong_atomic_fetch_and_nbi, \
            default: shmem_ctx_c11_generic_selection_failed \
        ), \
SHMEM_BIND_C11_BITWISE_AMO_EXTRAS(        *: shmem__atomic_fetch_and_nbi,, \)        int32_t*: shmem_int32_atomic_fetch_and_nbi, \
        int64_t*: shmem_int64_atomic_fetch_and_nbi, \
        unsigned int*: shmem_uint_atomic_fetch_and_nbi, \
        unsigned long*: shmem_ulong_atomic_fetch_and_nbi, \
        unsigned long long*: shmem_ulonglong_atomic_fetch_and_nbi \
    )(__VA_ARGS__)

#define shmem_atomic_fetch_or_nbi(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR_OR_SCALAR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_BITWISE_AMO_EXTRAS(            *: shmem_ctx__atomic_fetch_or_nbi,, \)            int32_t*: shmem_ctx_int32_atomic_fetch_or_nbi, \
            int64_t*: shmem_ctx_int64_atomic_fetch_or_nbi, \
            unsigned int*: shmem_ctx_uint_atomic_fetch_or_nbi, \
            unsigned long*: shmem_ctx_ulong_atomic_fetch_or_nbi, \
            unsigned long long*: shmem_ctx_ulonglong_atomic_fetch_or_nbi, \
            default: shmem_ctx_c11_generic_selection_failed \
        ), \
SHMEM_BIND_C11_BITWISE_AMO_EXTRAS(        *: shmem__atomic_fetch_or_nbi,, \)        int32_t*: shmem_int32_atomic_fetch_or_nbi, \
        int64_t*: shmem_int64_atomic_fetch_or_nbi, \
        unsigned int*: shmem_uint_atomic_fetch_or_nbi, \
        unsigned long*: shmem_ulong_atomic_fetch_or_nbi, \
        unsigned long long*: shmem_ulonglong_atomic_fetch_or_nbi \
    )(__VA_ARGS__)

#define shmem_atomic_fetch_xor_nbi(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR_OR_SCALAR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_BITWISE_AMO_EXTRAS(            *: shmem_ctx__atomic_fetch_xor_nbi,, \)            int32_t*: shmem_ctx_int32_atomic_fetch_xor_nbi, \
            int64_t*: shmem_ctx_int64_atomic_fetch_xor_nbi, \
            unsigned int*: shmem_ctx_uint_atomic_fetch_xor_nbi, \
            unsigned long*: shmem_ctx_ulong_atomic_fetch_xor_nbi, \
            unsigned long long*: shmem_ctx_ulonglong_atomic_fetch_xor_nbi, \
            default: shmem_ctx_c11_generic_selection_failed \
        ), \
SHMEM_BIND_C11_BITWISE_AMO_EXTRAS(        *: shmem__atomic_fetch_xor_nbi,, \)        int32_t*: shmem_int32_atomic_fetch_xor_nbi, \
        int64_t*: shmem_int64_atomic_fetch_xor_nbi, \
        unsigned int*: shmem_uint_atomic_fetch_xor_nbi, \
        unsigned long*: shmem_ulong_atomic_fetch_xor_nbi, \
        unsigned long long*: shmem_ulonglong_atomic_fetch_xor_nbi \
    )(__VA_ARGS__)

/* Team Collective Routines */
#define shmem_alltoall(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_RMA_EXTRAS(        *: shmem__alltoall,, \)        float*: shmem_float_alltoall, \
        double*: shmem_double_alltoall, \
        long double*: shmem_longdouble_alltoall, \
        char*: shmem_char_alltoall, \
        signed char*: shmem_schar_alltoall, \
        short*: shmem_short_alltoall, \
        int*: shmem_int_alltoall, \
        long*: shmem_long_alltoall, \
        long long*: shmem_longlong_alltoall, \
        unsigned char*: shmem_uchar_alltoall, \
        unsigned short*: shmem_ushort_alltoall, \
        unsigned int*: shmem_uint_alltoall, \
        unsigned long*: shmem_ulong_alltoall, \
        unsigned long long*: shmem_ulonglong_alltoall \
    )(__VA_ARGS__)

#define shmem_alltoalls(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_RMA_EXTRAS(        *: shmem__alltoalls,, \)        float*: shmem_float_alltoalls, \
        double*: shmem_double_alltoalls, \
        long double*: shmem_longdouble_alltoalls, \
        char*: shmem_char_alltoalls, \
        signed char*: shmem_schar_alltoalls, \
        short*: shmem_short_alltoalls, \
        int*: shmem_int_alltoalls, \
        long*: shmem_long_alltoalls, \
        long long*: shmem_longlong_alltoalls, \
        unsigned char*: shmem_uchar_alltoalls, \
        unsigned short*: shmem_ushort_alltoalls, \
        unsigned int*: shmem_uint_alltoalls, \
        unsigned long*: shmem_ulong_alltoalls, \
        unsigned long long*: shmem_ulonglong_alltoalls \
    )(__VA_ARGS__)

#define shmem_broadcast(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_RMA_EXTRAS(        *: shmem__broadcast,, \)        float*: shmem_float_broadcast, \
        double*: shmem_double_broadcast, \
        long double*: shmem_longdouble_broadcast, \
        char*: shmem_char_broadcast, \
        signed char*: shmem_schar_broadcast, \
        short*: shmem_short_broadcast, \
        int*: shmem_int_broadcast, \
        long*: shmem_long_broadcast, \
        long long*: shmem_longlong_broadcast, \
        unsigned char*: shmem_uchar_broadcast, \
        unsigned short*: shmem_ushort_broadcast, \
        unsigned int*: shmem_uint_broadcast, \
        unsigned long*: shmem_ulong_broadcast, \
        unsigned long long*: shmem_ulonglong_broadcast \
    )(__VA_ARGS__)

#define shmem_collect(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_RMA_EXTRAS(        *: shmem__collect,, \)        float*: shmem_float_collect, \
        double*: shmem_double_collect, \
        long double*: shmem_longdouble_collect, \
        char*: shmem_char_collect, \
        signed char*: shmem_schar_collect, \
        short*: shmem_short_collect, \
        int*: shmem_int_collect, \
        long*: shmem_long_collect, \
        long long*: shmem_longlong_collect, \
        unsigned char*: shmem_uchar_collect, \
        unsigned short*: shmem_ushort_collect, \
        unsigned int*: shmem_uint_collect, \
        unsigned long*: shmem_ulong_collect, \
        unsigned long long*: shmem_ulonglong_collect \
    )(__VA_ARGS__)

#define shmem_fcollect(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_RMA_EXTRAS(        *: shmem__fcollect,, \)        float*: shmem_float_fcollect, \
        double*: shmem_double_fcollect, \
        long double*: shmem_longdouble_fcollect, \
        char*: shmem_char_fcollect, \
        signed char*: shmem_schar_fcollect, \
        short*: shmem_short_fcollect, \
        int*: shmem_int_fcollect, \
        long*: shmem_long_fcollect, \
        long long*: shmem_longlong_fcollect, \
        unsigned char*: shmem_uchar_fcollect, \
        unsigned short*: shmem_ushort_fcollect, \
        unsigned int*: shmem_uint_fcollect, \
        unsigned long*: shmem_ulong_fcollect, \
        unsigned long long*: shmem_ulonglong_fcollect \
    )(__VA_ARGS__)

#define shmem_and_reduce(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_COLL_AND_OR_XOR_EXTRAS(        *: shmem__and_reduce,, \)        unsigned char*: shmem_uchar_and_reduce, \
        unsigned short*: shmem_ushort_and_reduce, \
        unsigned int*: shmem_uint_and_reduce, \
        unsigned long*: shmem_ulong_and_reduce, \
        unsigned long long*: shmem_ulonglong_and_reduce \
    )(__VA_ARGS__)

#define shmem_or_reduce(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_COLL_AND_OR_XOR_EXTRAS(        *: shmem__or_reduce,, \)        unsigned char*: shmem_uchar_or_reduce, \
        unsigned short*: shmem_ushort_or_reduce, \
        unsigned int*: shmem_uint_or_reduce, \
        unsigned long*: shmem_ulong_or_reduce, \
        unsigned long long*: shmem_ulonglong_or_reduce \
    )(__VA_ARGS__)

#define shmem_xor_reduce(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_COLL_AND_OR_XOR_EXTRAS(        *: shmem__xor_reduce,, \)        unsigned char*: shmem_uchar_xor_reduce, \
        unsigned short*: shmem_ushort_xor_reduce, \
        unsigned int*: shmem_uint_xor_reduce, \
        unsigned long*: shmem_ulong_xor_reduce, \
        unsigned long long*: shmem_ulonglong_xor_reduce \
    )(__VA_ARGS__)

#define shmem_min_reduce(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_COLL_EXTRAS(        *: shmem__min_reduce,, \)        char*: shmem_char_min_reduce, \
        signed char*: shmem_schar_min_reduce, \
        short*: shmem_short_min_reduce, \
        int*: shmem_int_min_reduce, \
        long*: shmem_long_min_reduce, \
        long long*: shmem_longlong_min_reduce, \
        unsigned char*: shmem_uchar_min_reduce, \
        unsigned short*: shmem_ushort_min_reduce, \
        unsigned int*: shmem_uint_min_reduce, \
        unsigned long*: shmem_ulong_min_reduce, \
        unsigned long long*: shmem_ulonglong_min_reduce, \
        float*: shmem_float_min_reduce, \
        double*: shmem_double_min_reduce, \
        long double*: shmem_longdouble_min_reduce \
    )(__VA_ARGS__)

#define shmem_max_reduce(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_COLL_EXTRAS(        *: shmem__max_reduce,, \)        char*: shmem_char_max_reduce, \
        signed char*: shmem_schar_max_reduce, \
        short*: shmem_short_max_reduce, \
        int*: shmem_int_max_reduce, \
        long*: shmem_long_max_reduce, \
        long long*: shmem_longlong_max_reduce, \
        unsigned char*: shmem_uchar_max_reduce, \
        unsigned short*: shmem_ushort_max_reduce, \
        unsigned int*: shmem_uint_max_reduce, \
        unsigned long*: shmem_ulong_max_reduce, \
        unsigned long long*: shmem_ulonglong_max_reduce, \
        float*: shmem_float_max_reduce, \
        double*: shmem_double_max_reduce, \
        long double*: shmem_longdouble_max_reduce \
    )(__VA_ARGS__)

#define shmem_sum_reduce(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_COLL_EXTRAS(        *: shmem__sum_reduce,, \)        char*: shmem_char_sum_reduce, \
        signed char*: shmem_schar_sum_reduce, \
        short*: shmem_short_sum_reduce, \
        int*: shmem_int_sum_reduce, \
        long*: shmem_long_sum_reduce, \
        long long*: shmem_longlong_sum_reduce, \
        unsigned char*: shmem_uchar_sum_reduce, \
        unsigned short*: shmem_ushort_sum_reduce, \
        unsigned int*: shmem_uint_sum_reduce, \
        unsigned long*: shmem_ulong_sum_reduce, \
        unsigned long long*: shmem_ulonglong_sum_reduce, \
        float*: shmem_float_sum_reduce, \
        double*: shmem_double_sum_reduce, \
        long double*: shmem_longdouble_sum_reduce, \
        double _Complex*: shmem_complexd_sum_reduce, \
        float _Complex*: shmem_complexf_sum_reduce \
    )(__VA_ARGS__)

#define shmem_prod_reduce(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_COLL_EXTRAS(        *: shmem__prod_reduce,, \)        char*: shmem_char_prod_reduce, \
        signed char*: shmem_schar_prod_reduce, \
        short*: shmem_short_prod_reduce, \
        int*: shmem_int_prod_reduce, \
        long*: shmem_long_prod_reduce, \
        long long*: shmem_longlong_prod_reduce, \
        unsigned char*: shmem_uchar_prod_reduce, \
        unsigned short*: shmem_ushort_prod_reduce, \
        unsigned int*: shmem_uint_prod_reduce, \
        unsigned long*: shmem_ulong_prod_reduce, \
        unsigned long long*: shmem_ulonglong_prod_reduce, \
        float*: shmem_float_prod_reduce, \
        double*: shmem_double_prod_reduce, \
        long double*: shmem_longdouble_prod_reduce, \
        double _Complex*: shmem_complexd_prod_reduce, \
        float _Complex*: shmem_complexf_prod_reduce \
    )(__VA_ARGS__)

/* Atomics with extended AMO types */
#define shmem_swap(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
SHMEM_BIND_C11_EXTENDED_AMO_EXTRAS(        *: shmem__swap,, \)        int*: shmem_int_swap, \
        long*: shmem_long_swap, \
        long long*: shmem_longlong_swap, \
        unsigned int*: shmem_uint_swap, \
        unsigned long*: shmem_ulong_swap, \
        unsigned long long*: shmem_ulonglong_swap, \
        float*: shmem_float_swap, \
        double*: shmem_double_swap \
    )(__VA_ARGS__)

#define shmem_atomic_swap(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR_OR_SCALAR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_EXTENDED_AMO_EXTRAS(            *: shmem_ctx__atomic_swap,, \)            int*: shmem_ctx_int_atomic_swap, \
            long*: shmem_ctx_long_atomic_swap, \
            long long*: shmem_ctx_longlong_atomic_swap, \
            unsigned int*: shmem_ctx_uint_atomic_swap, \
            unsigned long*: shmem_ctx_ulong_atomic_swap, \
            unsigned long long*: shmem_ctx_ulonglong_atomic_swap, \
            float*: shmem_ctx_float_atomic_swap, \
            double*: shmem_ctx_double_atomic_swap, \
            default: shmem_ctx_c11_generic_selection_failed \
        ), \
SHMEM_BIND_C11_EXTENDED_AMO_EXTRAS(        *: shmem__atomic_swap,, \)        int*: shmem_int_atomic_swap, \
        long*: shmem_long_atomic_swap, \
        long long*: shmem_longlong_atomic_swap, \
        unsigned int*: shmem_uint_atomic_swap, \
        unsigned long*: shmem_ulong_atomic_swap, \
        unsigned long long*: shmem_ulonglong_atomic_swap, \
        float*: shmem_float_atomic_swap, \
        double*: shmem_double_atomic_swap \
    )(__VA_ARGS__)

#define shmem_fetch(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
SHMEM_BIND_C11_EXTENDED_AMO_EXTRAS(        *: shmem__fetch,, \)        int*: shmem_int_fetch, \
        long*: shmem_long_fetch, \
        long long*: shmem_longlong_fetch, \
        unsigned int*: shmem_uint_fetch, \
        unsigned long*: shmem_ulong_fetch, \
        unsigned long long*: shmem_ulonglong_fetch, \
        float*: shmem_float_fetch, \
        double*: shmem_double_fetch, \
SHMEM_BIND_C11_EXTENDED_AMO_EXTRAS(        const *: shmem__fetch,, \)        const int*: shmem_int_fetch, \
        const long*: shmem_long_fetch, \
        const long long*: shmem_longlong_fetch, \
        const unsigned int*: shmem_uint_fetch, \
        const unsigned long*: shmem_ulong_fetch, \
        const unsigned long long*: shmem_ulonglong_fetch, \
        const float*: shmem_float_fetch, \
        const double*: shmem_double_fetch \
    )(__VA_ARGS__)

#define shmem_atomic_fetch(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR_OR_SCALAR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_EXTENDED_AMO_EXTRAS(            *: shmem_ctx__atomic_fetch,, \)            int*: shmem_ctx_int_atomic_fetch, \
            long*: shmem_ctx_long_atomic_fetch, \
            long long*: shmem_ctx_longlong_atomic_fetch, \
            unsigned int*: shmem_ctx_uint_atomic_fetch, \
            unsigned long*: shmem_ctx_ulong_atomic_fetch, \
            unsigned long long*: shmem_ctx_ulonglong_atomic_fetch, \
            float*: shmem_ctx_float_atomic_fetch, \
            double*: shmem_ctx_double_atomic_fetch, \
SHMEM_BIND_C11_EXTENDED_AMO_EXTRAS(            const *: shmem_ctx__atomic_fetch,, \)            const int*: shmem_ctx_int_atomic_fetch, \
            const long*: shmem_ctx_long_atomic_fetch, \
            const long long*: shmem_ctx_longlong_atomic_fetch, \
            const unsigned int*: shmem_ctx_uint_atomic_fetch, \
            const unsigned long*: shmem_ctx_ulong_atomic_fetch, \
            const unsigned long long*: shmem_ctx_ulonglong_atomic_fetch, \
            const float*: shmem_ctx_float_atomic_fetch, \
            const double*: shmem_ctx_double_atomic_fetch, \
            default: shmem_ctx_c11_generic_selection_failed \
        ), \
SHMEM_BIND_C11_EXTENDED_AMO_EXTRAS(        *: shmem__atomic_fetch,, \)        int*: shmem_int_atomic_fetch, \
        long*: shmem_long_atomic_fetch, \
        long long*: shmem_longlong_atomic_fetch, \
        unsigned int*: shmem_uint_atomic_fetch, \
        unsigned long*: shmem_ulong_atomic_fetch, \
        unsigned long long*: shmem_ulonglong_atomic_fetch, \
        float*: shmem_float_atomic_fetch, \
        double*: shmem_double_atomic_fetch, \
SHMEM_BIND_C11_EXTENDED_AMO_EXTRAS(        const *: shmem__atomic_fetch,, \)        const int*: shmem_int_atomic_fetch, \
        const long*: shmem_long_atomic_fetch, \
        const long long*: shmem_longlong_atomic_fetch, \
        const unsigned int*: shmem_uint_atomic_fetch, \
        const unsigned long*: shmem_ulong_atomic_fetch, \
        const unsigned long long*: shmem_ulonglong_atomic_fetch, \
        const float*: shmem_float_atomic_fetch, \
        const double*: shmem_double_atomic_fetch \
    )(__VA_ARGS__)


#define shmem_set(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
SHMEM_BIND_C11_EXTENDED_AMO_EXTRAS(        *: shmem__set,, \)        int*: shmem_int_set, \
        long*: shmem_long_set, \
        long long*: shmem_longlong_set, \
        unsigned int*: shmem_uint_set, \
        unsigned long*: shmem_ulong_set, \
        unsigned long long*: shmem_ulonglong_set, \
        float*: shmem_float_set, \
        double*: shmem_double_set \
    )(__VA_ARGS__)

#define shmem_atomic_set(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR_OR_SCALAR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_EXTENDED_AMO_EXTRAS(            *: shmem_ctx__atomic_set,, \)            int*: shmem_ctx_int_atomic_set, \
            long*: shmem_ctx_long_atomic_set, \
            long long*: shmem_ctx_longlong_atomic_set, \
            unsigned int*: shmem_ctx_uint_atomic_set, \
            unsigned long*: shmem_ctx_ulong_atomic_set, \
            unsigned long long*: shmem_ctx_ulonglong_atomic_set, \
            float*: shmem_ctx_float_atomic_set, \
            double*: shmem_ctx_double_atomic_set, \
            default: shmem_ctx_c11_generic_selection_failed \
        ), \
SHMEM_BIND_C11_EXTENDED_AMO_EXTRAS(        *: shmem__atomic_set,, \)        int*: shmem_int_atomic_set, \
        long*: shmem_long_atomic_set, \
        long long*: shmem_longlong_atomic_set, \
        unsigned int*: shmem_uint_atomic_set, \
        unsigned long*: shmem_ulong_atomic_set, \
        unsigned long long*: shmem_ulonglong_atomic_set, \
        float*: shmem_float_atomic_set, \
        double*: shmem_double_atomic_set \
    )(__VA_ARGS__)


/* Atomics with bitwise AMO types */
#define shmem_atomic_and(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR_OR_SCALAR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_BITWISE_AMO_EXTRAS(            *: shmem_ctx__atomic_and,, \)            int32_t*: shmem_ctx_int32_atomic_and, \
            int64_t*: shmem_ctx_int64_atomic_and, \
            unsigned int*: shmem_ctx_uint_atomic_and, \
            unsigned long*: shmem_ctx_ulong_atomic_and, \
            unsigned long long*: shmem_ctx_ulonglong_atomic_and, \
            default: shmem_ctx_c11_generic_selection_failed \
        ), \
SHMEM_BIND_C11_BITWISE_AMO_EXTRAS(        *: shmem__atomic_and,, \)        int32_t*: shmem_int32_atomic_and, \
        int64_t*: shmem_int64_atomic_and, \
        unsigned int*: shmem_uint_atomic_and, \
        unsigned long*: shmem_ulong_atomic_and, \
        unsigned long long*: shmem_ulonglong_atomic_and \
    )(__VA_ARGS__)

#define shmem_atomic_or(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR_OR_SCALAR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_BITWISE_AMO_EXTRAS(            *: shmem_ctx__atomic_or,, \)            int32_t*: shmem_ctx_int32_atomic_or, \
            int64_t*: shmem_ctx_int64_atomic_or, \
            unsigned int*: shmem_ctx_uint_atomic_or, \
            unsigned long*: shmem_ctx_ulong_atomic_or, \
            unsigned long long*: shmem_ctx_ulonglong_atomic_or, \
            default: shmem_ctx_c11_generic_selection_failed \
        ), \
SHMEM_BIND_C11_BITWISE_AMO_EXTRAS(        *: shmem__atomic_or,, \)        int32_t*: shmem_int32_atomic_or, \
        int64_t*: shmem_int64_atomic_or, \
        unsigned int*: shmem_uint_atomic_or, \
        unsigned long*: shmem_ulong_atomic_or, \
        unsigned long long*: shmem_ulonglong_atomic_or \
    )(__VA_ARGS__)

#define shmem_atomic_xor(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR_OR_SCALAR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_BITWISE_AMO_EXTRAS(            *: shmem_ctx__atomic_xor,, \)            int32_t*: shmem_ctx_int32_atomic_xor, \
            int64_t*: shmem_ctx_int64_atomic_xor, \
            unsigned int*: shmem_ctx_uint_atomic_xor, \
            unsigned long*: shmem_ctx_ulong_atomic_xor, \
            unsigned long long*: shmem_ctx_ulonglong_atomic_xor, \
            default: shmem_ctx_c11_generic_selection_failed \
        ), \
SHMEM_BIND_C11_BITWISE_AMO_EXTRAS(        *: shmem__atomic_xor,, \)        int32_t*: shmem_int32_atomic_xor, \
        int64_t*: shmem_int64_atomic_xor, \
        unsigned int*: shmem_uint_atomic_xor, \
        unsigned long*: shmem_ulong_atomic_xor, \
        unsigned long long*: shmem_ulonglong_atomic_xor \
    )(__VA_ARGS__)

#define shmem_atomic_fetch_and(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR_OR_SCALAR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_BITWISE_AMO_EXTRAS(            *: shmem_ctx__atomic_fetch_and,, \)            int32_t*: shmem_ctx_int32_atomic_fetch_and, \
            int64_t*: shmem_ctx_int64_atomic_fetch_and, \
            unsigned int*: shmem_ctx_uint_atomic_fetch_and, \
            unsigned long*: shmem_ctx_ulong_atomic_fetch_and, \
            unsigned long long*: shmem_ctx_ulonglong_atomic_fetch_and, \
            default: shmem_ctx_c11_generic_selection_failed \
        ), \
SHMEM_BIND_C11_BITWISE_AMO_EXTRAS(        *: shmem__atomic_fetch_and,, \)        int32_t*: shmem_int32_atomic_fetch_and, \
        int64_t*: shmem_int64_atomic_fetch_and, \
        unsigned int*: shmem_uint_atomic_fetch_and, \
        unsigned long*: shmem_ulong_atomic_fetch_and, \
        unsigned long long*: shmem_ulonglong_atomic_fetch_and \
    )(__VA_ARGS__)

#define shmem_atomic_fetch_or(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR_OR_SCALAR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_BITWISE_AMO_EXTRAS(            *: shmem_ctx__atomic_fetch_or,, \)            int32_t*: shmem_ctx_int32_atomic_fetch_or, \
            int64_t*: shmem_ctx_int64_atomic_fetch_or, \
            unsigned int*: shmem_ctx_uint_atomic_fetch_or, \
            unsigned long*: shmem_ctx_ulong_atomic_fetch_or, \
            unsigned long long*: shmem_ctx_ulonglong_atomic_fetch_or, \
            default: shmem_ctx_c11_generic_selection_failed \
        ), \
SHMEM_BIND_C11_BITWISE_AMO_EXTRAS(        *: shmem__atomic_fetch_or,, \)        int32_t*: shmem_int32_atomic_fetch_or, \
        int64_t*: shmem_int64_atomic_fetch_or, \
        unsigned int*: shmem_uint_atomic_fetch_or, \
        unsigned long*: shmem_ulong_atomic_fetch_or, \
        unsigned long long*: shmem_ulonglong_atomic_fetch_or \
    )(__VA_ARGS__)

#define shmem_atomic_fetch_xor(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_ctx_t: \
        _Generic(SHMEM_C11_TYPE_EVAL_PTR_OR_SCALAR(SHMEM_C11_ARG1(__VA_ARGS__)), \
SHMEM_BIND_C11_BITWISE_AMO_EXTRAS(            *: shmem_ctx__atomic_fetch_xor,, \)            int32_t*: shmem_ctx_int32_atomic_fetch_xor, \
            int64_t*: shmem_ctx_int64_atomic_fetch_xor, \
            unsigned int*: shmem_ctx_uint_atomic_fetch_xor, \
            unsigned long*: shmem_ctx_ulong_atomic_fetch_xor, \
            unsigned long long*: shmem_ctx_ulonglong_atomic_fetch_xor, \
            default: shmem_ctx_c11_generic_selection_failed \
        ), \
SHMEM_BIND_C11_BITWISE_AMO_EXTRAS(        *: shmem__atomic_fetch_xor,, \)        int32_t*: shmem_int32_atomic_fetch_xor, \
        int64_t*: shmem_int64_atomic_fetch_xor, \
        unsigned int*: shmem_uint_atomic_fetch_xor, \
        unsigned long*: shmem_ulong_atomic_fetch_xor, \
        unsigned long long*: shmem_ulonglong_atomic_fetch_xor \
    )(__VA_ARGS__)


/* Point-to-point synchronization */
#define shmem_wait_until(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
SHMEM_BIND_C11_SYNC_EXTRAS(        *: shmem__wait_until,, \)        short*: shmem_short_wait_until, \
        int*: shmem_int_wait_until, \
        long*: shmem_long_wait_until, \
        long long*: shmem_longlong_wait_until, \
        unsigned short*: shmem_ushort_wait_until, \
        unsigned int*: shmem_uint_wait_until, \
        unsigned long*: shmem_ulong_wait_until, \
        unsigned long long*: shmem_ulonglong_wait_until \
    )(__VA_ARGS__)

#define shmem_wait_until_all(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
             default: shmem_ctx_c11_generic_selection_failed, \
SHMEM_BIND_C11_SYNC_EXTRAS(        *: shmem__wait_until_all,, \)        short*: shmem_short_wait_until_all, \
        int*: shmem_int_wait_until_all, \
        long*: shmem_long_wait_until_all, \
        long long*: shmem_longlong_wait_until_all, \
        unsigned short*: shmem_ushort_wait_until_all, \
        unsigned int*: shmem_uint_wait_until_all, \
        unsigned long*: shmem_ulong_wait_until_all, \
        unsigned long long*: shmem_ulonglong_wait_until_all \
    )(__VA_ARGS__)

#define shmem_wait_until_all_vector(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
             default: shmem_ctx_c11_generic_selection_failed, \
SHMEM_BIND_C11_SYNC_EXTRAS(        *: shmem__wait_until_all_vector,, \)        short*: shmem_short_wait_until_all_vector, \
        int*: shmem_int_wait_until_all_vector, \
        long*: shmem_long_wait_until_all_vector, \
        long long*: shmem_longlong_wait_until_all_vector, \
        unsigned short*: shmem_ushort_wait_until_all_vector, \
        unsigned int*: shmem_uint_wait_until_all_vector, \
        unsigned long*: shmem_ulong_wait_until_all_vector, \
        unsigned long long*: shmem_ulonglong_wait_until_all_vector \
    )(__VA_ARGS__)

#define shmem_wait_until_any(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
             default: shmem_ctx_c11_generic_selection_failed, \
SHMEM_BIND_C11_SYNC_EXTRAS(        *: shmem__wait_until_any,, \)        short*: shmem_short_wait_until_any, \
        int*: shmem_int_wait_until_any, \
        long*: shmem_long_wait_until_any, \
        long long*: shmem_longlong_wait_until_any, \
        unsigned short*: shmem_ushort_wait_until_any, \
        unsigned int*: shmem_uint_wait_until_any, \
        unsigned long*: shmem_ulong_wait_until_any, \
        unsigned long long*: shmem_ulonglong_wait_until_any \
    )(__VA_ARGS__)

#define shmem_wait_until_any_vector(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
             default: shmem_ctx_c11_generic_selection_failed, \
SHMEM_BIND_C11_SYNC_EXTRAS(        *: shmem__wait_until_any_vector,, \)        short*: shmem_short_wait_until_any_vector, \
        int*: shmem_int_wait_until_any_vector, \
        long*: shmem_long_wait_until_any_vector, \
        long long*: shmem_longlong_wait_until_any_vector, \
        unsigned short*: shmem_ushort_wait_until_any_vector, \
        unsigned int*: shmem_uint_wait_until_any_vector, \
        unsigned long*: shmem_ulong_wait_until_any_vector, \
        unsigned long long*: shmem_ulonglong_wait_until_any_vector \
    )(__VA_ARGS__)

#define shmem_wait_until_some(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
             default: shmem_ctx_c11_generic_selection_failed, \
SHMEM_BIND_C11_SYNC_EXTRAS(        *: shmem__wait_until_some,, \)        short*: shmem_short_wait_until_some, \
        int*: shmem_int_wait_until_some, \
        long*: shmem_long_wait_until_some, \
        long long*: shmem_longlong_wait_until_some, \
        unsigned short*: shmem_ushort_wait_until_some, \
        unsigned int*: shmem_uint_wait_until_some, \
        unsigned long*: shmem_ulong_wait_until_some, \
        unsigned long long*: shmem_ulonglong_wait_until_some \
    )(__VA_ARGS__)

#define shmem_wait_until_some_vector(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
             default: shmem_ctx_c11_generic_selection_failed, \
SHMEM_BIND_C11_SYNC_EXTRAS(        *: shmem__wait_until_some_vector,, \)        short*: shmem_short_wait_until_some_vector, \
        int*: shmem_int_wait_until_some_vector, \
        long*: shmem_long_wait_until_some_vector, \
        long long*: shmem_longlong_wait_until_some_vector, \
        unsigned short*: shmem_ushort_wait_until_some_vector, \
        unsigned int*: shmem_uint_wait_until_some_vector, \
        unsigned long*: shmem_ulong_wait_until_some_vector, \
        unsigned long long*: shmem_ulonglong_wait_until_some_vector \
    )(__VA_ARGS__)

#define shmem_test(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
SHMEM_BIND_C11_SYNC_EXTRAS(        *: shmem__test,, \)        short*: shmem_short_test, \
        int*: shmem_int_test, \
        long*: shmem_long_test, \
        long long*: shmem_longlong_test, \
        unsigned short*: shmem_ushort_test, \
        unsigned int*: shmem_uint_test, \
        unsigned long*: shmem_ulong_test, \
        unsigned long long*: shmem_ulonglong_test \
    )(__VA_ARGS__)

#define shmem_test_all(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
             default: shmem_ctx_c11_generic_selection_failed, \
SHMEM_BIND_C11_SYNC_EXTRAS(        *: shmem__test_all,, \)        short*: shmem_short_test_all, \
        int*: shmem_int_test_all, \
        long*: shmem_long_test_all, \
        long long*: shmem_longlong_test_all, \
        unsigned short*: shmem_ushort_test_all, \
        unsigned int*: shmem_uint_test_all, \
        unsigned long*: shmem_ulong_test_all, \
        unsigned long long*: shmem_ulonglong_test_all \
    )(__VA_ARGS__)

#define shmem_test_any(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
             default: shmem_ctx_c11_generic_selection_failed, \
SHMEM_BIND_C11_SYNC_EXTRAS(        *: shmem__test_any,, \)        short*: shmem_short_test_any, \
        int*: shmem_int_test_any, \
        long*: shmem_long_test_any, \
        long long*: shmem_longlong_test_any, \
        unsigned short*: shmem_ushort_test_any, \
        unsigned int*: shmem_uint_test_any, \
        unsigned long*: shmem_ulong_test_any, \
        unsigned long long*: shmem_ulonglong_test_any \
    )(__VA_ARGS__)

#define shmem_test_some(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
             default: shmem_ctx_c11_generic_selection_failed, \
SHMEM_BIND_C11_SYNC_EXTRAS(        *: shmem__test_some,, \)        short*: shmem_short_test_some, \
        int*: shmem_int_test_some, \
        long*: shmem_long_test_some, \
        long long*: shmem_longlong_test_some, \
        unsigned short*: shmem_ushort_test_some, \
        unsigned int*: shmem_uint_test_some, \
        unsigned long*: shmem_ulong_test_some, \
        unsigned long long*: shmem_ulonglong_test_some \
    )(__VA_ARGS__)

#define shmem_test_all_vector(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
             default: shmem_ctx_c11_generic_selection_failed, \
SHMEM_BIND_C11_SYNC_EXTRAS(        *: shmem__test_all_vector,, \)        short*: shmem_short_test_all_vector, \
        int*: shmem_int_test_all_vector, \
        long*: shmem_long_test_all_vector, \
        long long*: shmem_longlong_test_all_vector, \
        unsigned short*: shmem_ushort_test_all_vector, \
        unsigned int*: shmem_uint_test_all_vector, \
        unsigned long*: shmem_ulong_test_all_vector, \
        unsigned long long*: shmem_ulonglong_test_all_vector \
    )(__VA_ARGS__)

#define shmem_test_any_vector(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
             default: shmem_ctx_c11_generic_selection_failed, \
SHMEM_BIND_C11_SYNC_EXTRAS(        *: shmem__test_any_vector,, \)        short*: shmem_short_test_any_vector, \
        int*: shmem_int_test_any_vector, \
        long*: shmem_long_test_any_vector, \
        long long*: shmem_longlong_test_any_vector, \
        unsigned short*: shmem_ushort_test_any_vector, \
        unsigned int*: shmem_uint_test_any_vector, \
        unsigned long*: shmem_ulong_test_any_vector, \
        unsigned long long*: shmem_ulonglong_test_any_vector \
    )(__VA_ARGS__)

#define shmem_test_some_vector(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR(SHMEM_C11_ARG0(__VA_ARGS__)), \
             default: shmem_ctx_c11_generic_selection_failed, \
SHMEM_BIND_C11_SYNC_EXTRAS(        *: shmem__test_some_vector,, \)        short*: shmem_short_test_some_vector, \
        int*: shmem_int_test_some_vector, \
        long*: shmem_long_test_some_vector, \
        long long*: shmem_longlong_test_some_vector, \
        unsigned short*: shmem_ushort_test_some_vector, \
        unsigned int*: shmem_uint_test_some_vector, \
        unsigned long*: shmem_ulong_test_some_vector, \
        unsigned long long*: shmem_ulonglong_test_some_vector \
    )(__VA_ARGS__)

#define shmem_sync(...) \
    _Generic(SHMEM_C11_TYPE_EVAL_PTR_OR_SCALAR(SHMEM_C11_ARG0(__VA_ARGS__)), \
        shmem_team_t: shmem_team_sync, \
        int: shmem_sync \
    )(__VA_ARGS__)

#endif /* C11 */

#endif /* SHMEM_H */
