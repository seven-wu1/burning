#include "main.h"

 unsigned char StringCompare2( const uint8_t *String1, uint8_t *String2)
{
	unsigned char i=0;
	unsigned char String1_Length=0;
	unsigned char String2_Length=0;
	const uint8_t *p1;
	uint8_t *p2;
	p1=String1;
	p2=String2;
	while(*p1!='\r' && *p1!='\0')
	{
		p1++;
		String1_Length++;
		if(String1_Length>254)
		{
			return 1;
		}
	}
	while(*p2 !='\r' && *p2 !='\0')
	{
		p2++;
		String2_Length++;
		if(String2_Length>254)
		{
			return 1;
		}
	}
	if(String1_Length==String2_Length)
	{
		p1=String1;
		p2=String2;
		for(i=0;i<String1_Length;i++)
		{
			if(*p1!=*p2) 
				return 1;
			
			p1++;
			p2++;
		}
		return 0;
	}
	else 
		return 1;
 
}
unsigned char string_compare_len(const uint8_t *String1,uint8_t *String2,uint8_t LEN)
{
	unsigned char i=0;
	const uint8_t *p1=String1;
	uint8_t *p2=String2;
	for(i=0;i<LEN;i++)
	{
		if(*p1!=*p2)
			return 1;
		p1++;
		p2++;
	}
	return 0;
}
 
