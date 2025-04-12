/**
 * @file: kernel/printk.c
 * @author: lhxl
 * @data: 2025-4-12
 * @version: build5
 **/

#include "kernel/const.h"
#include "kernel/global.h"
#include "kernel/font.h"

#include "kernel/printk.h"

PRIVATE char* __itoa(char* buffer, long long number, int base, u8 sign);

int __printk(const char* format, ...)
{
	va_list args;
	va_start(args, format);
	__color_printk(0x00000000, 0xFFFFFFFF, format, args);
	va_end(args);
}

int __color_printk(u32 frontColor, u32 backgroundColor, const char* format, ...)
{
	char buffer[1024] = {0};
	va_list args;
	va_start(args, format);
	int i = __vsprintf(buffer, format, args);
	va_end(args);
	for (int j = 0; j < i; j++)
	{
		switch (buffer[j])
		{
		case '\r':
		case '\n':
			screen.Position.x = 0;
			screen.Position.y = screen.Position.y + screen.CharSize.y + 1;
			continue;
		case '\t':
			do
			{
				__putchar(frontColor, backgroundColor, ' ');
			} while (screen.Position.x % (screen.CharSize.x * 4) != 0);
			continue;
		case '\'':
			__putchar(frontColor, backgroundColor, '\'');
			continue;
		case '\"':
			__putchar(frontColor, backgroundColor, '\"');
			continue;
		case '\\':
			__putchar(frontColor, backgroundColor, '\\');
			continue;
		default:
			break;
		}
		__putchar(frontColor, backgroundColor, buffer[j]);
	}
	return i;
}

int __vsprintf(char* buffer, const char* format, va_list args)
{
	char* pbuffer = buffer;
	int flag_format = false;
	int flag_long = false;
	int precision = 0;
	while (*format != '\0')
	{
		if (*format == '%' && flag_format == false)
		{
			flag_format = true;
			format++;
			continue;
		}
		if (flag_format == true)
		{
			switch (*format)
			{
			case '0'...'9':
				precision = *format - '0';
				break;
			case 'b':
				flag_format = false;
				if (flag_long == true)
				{
					flag_long = false;
					pbuffer = __itoa(pbuffer, va_arg(args, u64), 2, precision);
					break;
				}
				pbuffer = __itoa(pbuffer, va_arg(args, u32), 2, precision);
				break;
			case 'c':
				flag_format = false;
				*pbuffer++ = (char)va_arg(args, u32);
				break;
			case 'd':
				flag_format = false;
				if (flag_long == true)
				{
					flag_long = false;
					pbuffer = __itoa(pbuffer, va_arg(args, u64), 10, precision);
					break;
				}
				pbuffer = __itoa(pbuffer, va_arg(args, u32), 10, precision);
				break;
			case 'l':
				flag_long = true;
				break;
			case 'o':
				flag_format = false;
				if (flag_long == true)
				{
					flag_long = false;
					pbuffer = __itoa(pbuffer, va_arg(args, u64), 8, precision);
					break;
				}
				pbuffer = __itoa(pbuffer, va_arg(args, u32), 8, precision);
				break;
			case 's':
				flag_format = false;
				char* str = (char*)va_arg(args, ptr_t);
				while (*str)
				{
					*pbuffer++ = *str;
					str++;
				}
				break;
			case 'x':
				flag_format = false;
				if (flag_long == true)
				{
					flag_long = false;
					pbuffer = __itoa(pbuffer, va_arg(args, u64), 16, precision);
					break;
				}
				pbuffer = __itoa(pbuffer, va_arg(args, u32), 16, precision);
				break;
			case '%':
			default:
				flag_format = false;
				*pbuffer++ = '%';
				break;
			}
			format++;
			continue;
		}
		*pbuffer++ = *format;
		format++;
	}
	return pbuffer - buffer;
}

void __putchar(u32 frontColor, u32 backgroundColor, u8 character)
{
	u32* base_addr = screen.bufferAddress;
	u16 x = screen.Position.x;
	u16 y = screen.Position.y;
	u16 res_x = screen.Resolution.x;
	u8* font = font_ascii[character];
	for (int i = 0; i < 16; i++)
	{
		u32* addr = base_addr + (y + i) * res_x + x;
		u8 mask = 0b10000000;
		for (int j = 0; j < 8; j++)
		{
			*(addr + j) = mask & font[i] ? frontColor : backgroundColor;
			mask >>= 1;
		}
	}
	screen.Position.x += 8;
	if (x == screen.Resolution.x)
	{
		screen.Position.y = screen.Position.y + screen.CharSize.y + 1;
		screen.Position.x = 0;
	}
}

PRIVATE char* __itoa(char* buffer, long long number, int base, u8 precision)
{
	long long temp = number;
	char temp_buffer[64] = {0};
	char* p_buffer = buffer;
	char* p_temp_buffer = temp_buffer;
	u8 size = 0;
	if (temp < 0)
	{
		temp = -temp;
		*p_buffer++ = '-';
	}
	if (temp == 0)
	{
		*p_buffer++ = '0';
		return p_buffer;
	}
	while (temp > 0)
	{
		int rem = (int)(temp % base);
		temp /= base;
		*p_temp_buffer++ = rem < 10 ? rem + '0' : rem + 'A' - 10;
		size++;
	}
	if (precision > size)
	{
		precision -= size;
		while (precision > 0)
		{
			*p_temp_buffer++ = ' ';
			precision--;
		}
	}
	while (p_temp_buffer > temp_buffer)
	{
		p_temp_buffer--;
		*p_buffer++ = *p_temp_buffer;
	}
	return p_buffer;
}