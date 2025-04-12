/**
 * @file: kernel/lib/string.h
 * @author: lhxl
 * @data: 2025-4-12
 * @version: build5
 **/

#ifndef __LIB_STRING_H_
#define __LIB_STRING_H_

size_t strlen(const char* str);
void* memcpy(void* p_dst, void* p_src, size_t size);
void memset(void* p_dst, char ch, int size);
char* strcpy(char* p_dst, char* p_src);

#endif