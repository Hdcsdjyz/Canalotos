/**
 * @file: kernel/lib/string.h
 * @author: lhxl
 * @data: 2025-5-13
 * @version: build10
 **/

#ifndef __LIB_STRING_H_
#define __LIB_STRING_H_

#include <kernel/types.h>

size_t strlen(const char* str);
void* memcpy(void* p_dst, void* p_src, size_t size);
void memset(void* p_dst, char ch, size_t size);
char* strcpy(char* p_dst, char* p_src);
int memcmp(void* p_dst, void* p_src, size_t size);

#endif