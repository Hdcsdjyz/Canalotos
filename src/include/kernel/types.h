/**
 * @file: include/kernel/types.h
 * @author: lhxl
 * @data: 2025-5-13
 * @version: build10
 **/

#ifndef _KRENEL_TYPES_H_
#define _KRENEL_TYPES_H_

typedef unsigned char 		u8;
typedef unsigned short 		u16;
typedef unsigned int		u32;
typedef unsigned long long	u64;

typedef char 		s8;
typedef short 		s16;
typedef int			s32;
typedef long long	s64;

typedef u64 size_t;
typedef u64 ptr_t;
typedef u64 pid_t;

typedef void (*int_handler)();
typedef void (*irq_handler)();
typedef u64 (*func)(u64 arg);

#endif