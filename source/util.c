#include <string.h>
#include "types.h"
#include "util.h"



void wait(u32 cycles)
{
	cycles >>= 2;
	while(cycles)
	{
		__asm("nop");
		cycles--;
	}
}

// case insensitive string compare function
int strnicmp(const char *str1, const char *str2, u32 len)
{
	int diff;
	
	if(len == 0)
		return 0;
	
	for(;; str1++, str2++)
	{	
		if(len != 0) len --;
		else return 0;
		diff = tolower(*str1) - tolower(*str2);
		if(diff != 0 || *str1 == '\0')
			return diff;
	}
	
	return 0;
}

// custom safe strncpy, string is always 0-terminated for buflen > 0
void strncpy_s(char *dest, const char *src, u32 nchars, const u32 buflen)
{
	char c;

	if(!buflen)
		return;
		
	if(buflen > 1)
	{
		if(nchars >= buflen)
			nchars = buflen - 1;
		
		while(nchars--)
		{
			c = *src++;
			
			if(c == '\0')
				break;
			
			*dest++ = c;
		}
	}
	
	*dest = '\0';
}

// custom safe memcpy
void memcpy_s(void *dstBuf, size_t dstBufSize, size_t dstBufOffset,
				void *srcBuf, size_t srcBufSize, size_t srcBufOffset, bool reverse)
{
	size_t dstRemaining, srcRemaining, actualSize;
	
	if(dstBufOffset >= dstBufSize)
		return;
	if(srcBufOffset >= srcBufSize)
		return;
	
	dstRemaining = dstBufSize - dstBufOffset;
	srcRemaining = srcBufSize - srcBufOffset;
	
	actualSize = min(dstRemaining, srcRemaining);
	
	if(reverse)
	{
		u8 *src = srcBuf + srcBufOffset + actualSize - 1;
		u8 *dst = dstBuf + dstBufOffset + actualSize - 1;
		
		do {
			*dst = *src;
			dst--;
			src--;
			actualSize --;
		} while(actualSize);
	}
	else
		memcpy(dstBuf+dstBufOffset, srcBuf+srcBufOffset, actualSize);
}

u32 getleu32(const void* ptr)
{
	const u8* p = (const u8*)ptr;
	
	return (u32)((p[0]<<0) | (p[1]<<8) | (p[2]<<16) | (p[3]<<24));
}

u32 swap32(u32 val)
{
	return ((val>>24) |
	        (val>>8  & 0x0000FF00) |
	        (val<<8  & 0x00FF0000) |
	        (val<<24));
}
