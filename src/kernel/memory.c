/**
 * @file: kernel/memory.c
 * @author: lhxl
 * @data: 2025-5-3
 * @version: build9
 **/

#include <kernel/memory.h>
#include <kernel/printk.h>
#include <kernel/const.h>
#include <kernel/global.h>
#include <kernel/lib/string.h>
#include <kernel/function.h>

PRIVATE u64* get_gdt();
PRIVATE void flush_tlb();

/**
 * @note Default use 2M page.
 */
void init_memory()
{
	// Set kernel length.
	memory_desc.kernel_code_start = (u64)&_text;
	memory_desc.kernel_code_end = (u64)&_etext;
	memory_desc.kernel_data_end = (u64)&_edata;
	memory_desc.kernel_end = (u64)&_end;
	// Get memory struct.
	struct Memory* memory = (struct Memory*)0xFFFF800000007E00;
	for (int i = 0; i < 32; i++)
	{
		memory_desc.memory_table[i].address = memory->address;
		memory_desc.memory_table[i].length = memory->length;
		memory_desc.memory_table[i].type = memory->type;
		memory_desc.memory_table_size = i;
		memory++;
		if (memory->type > 4 || memory->length == 0 || memory->type < 1)
		{
			break;
		}
	}
	// Get total memory.
	u64 Total_memory = memory_desc.memory_table[memory_desc.memory_table_size].address + memory_desc.memory_table[memory_desc.memory_table_size].length;
	// init bits map.
	memory_desc.bits_map = (u64*)(memory_desc.kernel_end + PAGE_4K - 1 & PAGE_4K_MASK);
	memory_desc.bits_map_size = Total_memory >> PAGE_2M_SHIFT;
	memory_desc.bits_map_length = ((Total_memory >> PAGE_2M_SHIFT) + sizeof(u64) * 8 - 1) / 8 & ~(sizeof(u64) - 1);
	memset(memory_desc.bits_map, 0xFF, memory_desc.bits_map_length);
	// init pages.
	memory_desc.pages = (struct Page*)((u64)memory_desc.bits_map + memory_desc.bits_map_length + PAGE_4K - 1 & PAGE_4K_MASK);
	memory_desc.pages_size = Total_memory >> PAGE_2M_SHIFT;
	memory_desc.pages_length = (Total_memory >> PAGE_2M_SHIFT) * sizeof(struct Page) + sizeof(u64) - 1 & ~(sizeof(u64) - 1);
	memset(memory_desc.pages, 0, memory_desc.pages_length);
	// init zones.
	memory_desc.zones = (struct Zone*)((u64)memory_desc.pages + memory_desc.pages_length + PAGE_4K - 1 & PAGE_4K_MASK);
	memory_desc.zones_size = 0;
	memory_desc.zones_length = 5 * sizeof(struct Zone) + sizeof(u64) - 1 & ~(sizeof(u64) - 1);
	memset(memory_desc.zones, 0, memory_desc.zones_length);

	for (int i = 0; i < memory_desc.memory_table_size; i++)
	{
		if (memory_desc.memory_table[i].type != 1)
		{
			continue;
		}
		u64 start = PAGE_2M_ALIGN(memory_desc.memory_table[i].address);
		u64 end = ((memory_desc.memory_table[i].address + memory_desc.memory_table[i].length) >> PAGE_2M_SHIFT) << PAGE_2M_SHIFT;
		if (end <= start)
		{
			continue;
		}
		// Setup zones.
		struct Zone* zone = memory_desc.zones + memory_desc.zones_size;
		memory_desc.zones_size++;
		zone->start_address = start;
		zone->end_address = end;
		zone->capacity = end - start;
		zone->using_pages = 0;
		zone->free_pages = zone->capacity >> PAGE_2M_SHIFT;
		zone->page_count = 0;
		zone->attribute = 0;
		zone->memory_desc = &memory_desc;
		zone->page_size = zone->free_pages;
		zone->pages = memory_desc.pages + (start >> PAGE_2M_SHIFT);
		// Setup each page of the zone
		struct Page* page = zone->pages;
		for (int j = 0; j < zone->page_size; j++, page++)
		{
			page->zone = zone;
			page->address = start + PAGE_2M * j;
			page->attribute = 0;
			page->count = 0;
			page->age = 0;
			*(memory_desc.bits_map + ((page->address >> PAGE_2M_SHIFT) >> 6)) ^= 1UL << (page->address >> PAGE_2M_SHIFT) % 64;
		}
	}
	// Setup page0 because type of memory0~2M is not always 1, but it contains the kernel.
	memory_desc.pages->zone = memory_desc.zones;
	memory_desc.pages->address = 0;
	memory_desc.pages->attribute = 0;
	memory_desc.pages->count = 0;
	memory_desc.pages->age = 0;
	memory_desc.zones_length = memory_desc.zones_size * sizeof(struct Zone) + sizeof(u64) - 1 & ~(sizeof(u64) - 1);
	ZONE_DMA_INDEX = 0;
	ZONE_NORMAL_INDEX = 0;
	for (int i = 0; i < memory_desc.zones_size; i++)
	{
		struct Zone* zone = memory_desc.zones + i;
		if (zone->start_address == 0x100000000)
		{
			ZONE_UNMAPPED_INDEX = i;
		}
	}
	memory_desc.end_of_mem_desc = (u64)memory_desc.zones + memory_desc.zones_length + sizeof(u64) * 32 & ~(sizeof(u64) - 1);
	int size = vir2phy(memory_desc.end_of_mem_desc) >> PAGE_2M_SHIFT;
	for (int i = 0; i <= size; i++)
	{
		page_init(memory_desc.pages + i, PAGE_TABLE_MAPPED | PAGE_KERNEL_INIT | PAGE_ACTIVE | PAGE_KERNEL);
	}
	Global_CR3 = get_gdt();
	for (int i = 0; i < 10; i++)
	{
		*(phy2vir(Global_CR3) + i) = 0UL;
	}
	flush_tlb();
}

u64 page_init(struct Page* page, u64 flags)
{
	if (!page->attribute)
	{
		*(memory_desc.bits_map + ((page->address >> PAGE_2M_SHIFT) >> 6)) |= 1UL << (page->address >> PAGE_2M_SHIFT) % 64;
		page->attribute = flags;
		page->count++;
		page->zone->using_pages++;
		page->zone->free_pages--;
		page->zone->page_count++;
	}
	else if (page->attribute & PAGE_REFERENCED || page->attribute & PAGE_KERNEL_SHARED || flags & PAGE_REFERENCED || flags & PAGE_KERNEL_SHARED)
	{
		page->attribute |= flags;
		page->count++;
		page->zone->page_count++;
	}
	else
	{
		*(memory_desc.bits_map + ((page->address >> PAGE_2M_SHIFT) >> 6)) |= 1UL << (page->address >> PAGE_2M_SHIFT) % 64;
		page->attribute |= flags;
	}
	return 0;
}

u64 page_clean(struct Page* page)
{
	if (!page->attribute)
	{
		page->attribute = 0;
	}
	else if(page->attribute & PAGE_REFERENCED || page->attribute & PAGE_KERNEL_SHARED)
	{
		page->count--;
		page->zone->page_count--;
		if (!page->count)
		{
			page->attribute = 0;
			page->zone->using_pages--;
			page->zone->free_pages++;
		}
	}
	else
	{
		*(memory_desc.bits_map + ((page->address >> PAGE_2M_SHIFT) >> 6)) &= ~(1UL << (page->address >> PAGE_2M_SHIFT) % 64);

		page->attribute = 0;
		page->count = 0;
		page->zone->using_pages--;
		page->zone->free_pages++;
		page->zone->page_count--;
	}
	return 0;
}

PRIVATE u64* get_gdt()
{
	u64* temp;
	__asm__ __volatile__(
		"	movq	%%cr3, %0	\n\t"
		: "=r"(temp)
		:
		: "memory"
	);
	return temp;
}

PRIVATE void flush_tlb()
{
	do
	{
		u64 temp;
		__asm__ __volatile__(
			"	movq	%%cr3, %0	\n\t"
			"	movq	%0, %%cr3	\n\t"
			: "=r"(temp)
			:
			: "memory"
		);
	} while(0);
}

/**
 *
 * @param zone_type zone of tha page to be allocated
 * @param number number of pages
 * @param flags flags of page
 * @return pointer of the first allocated page
 * @note Number should not bigger than 64.
 */
struct Page* alloc_page(u64 zone_type, u64 number, u64 flags)
{
	int zone_start = 0;
	int zone_end = 0;
	// The switch is temporarily useless.
	switch (zone_type)
	{
	case ZONE_DMA:
		zone_start = 0;
		zone_end = ZONE_DMA_INDEX;
		break;
	case ZONE_NORMAL:
		zone_start = ZONE_DMA_INDEX;
		zone_end = ZONE_NORMAL_INDEX;
		break;
	case ZONE_UNMAPPED:
		zone_start = ZONE_UNMAPPED_INDEX;
		zone_end = memory_desc.zones_size - 1;
		break;
	default:
		__color_printk(RED, BLACK, "alloc_page error!\n");
		return nullptr;
	}

	for (int i = zone_start; i <= zone_end; i++)
	{
		// Search for a zone with enough pages.
		if ((memory_desc.zones + i)->free_pages < number)
		{
			continue;
		}
		struct Zone* zone = memory_desc.zones + i;
		u64 start_page = zone->start_address >> PAGE_2M_SHIFT;
		u64 end_page = zone->end_address >> PAGE_2M_SHIFT;
		u64 temp = 64 - start_page % 64;
		for (u64 j = start_page; j <= end_page; j += j % 64 ? temp : 64)
		{
			u64* bit = memory_desc.bits_map + (j >> 6);
			u64 shift = j % 64;
			for (u64 k = shift; k < 64 - shift; k++)
			{
				if (!((*bit >> k | *(bit + 1) << (64 - k)) & (number == 64 ? 0xFFFFFFFFFFFFFFFFUL : (1UL << number) - 1)))	// combine u64 high and next u64 low
				{
					u64 n_page = j + k - 1;
					for (u64 l = 0; l < number; l++)
					{
						struct Page* page = memory_desc.pages + n_page + l;
						page_init(page, flags);
					}
					return memory_desc.pages + n_page;
				}
			}
		}
	}
	return nullptr;
}