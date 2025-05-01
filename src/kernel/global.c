/**
 * @file: kernel/global.c
 * @author: lhxl
 * @data: 2025-5-1
 * @version: build8
 **/

#include <kernel/global.h>

struct Screen screen;

// memory
struct MemoryDescriptor memory_desc;
u64 zone_unmapped_index;
char _text;
char _etext;
char _edata;
char _end;
u32 ZONE_DMA_INDEX = 0;
u32 ZONE_NORMAL_INDEX = 0;
u32 ZONE_UNMAPPED_INDEX = 0;
u64* Global_CR3 = nullptr;