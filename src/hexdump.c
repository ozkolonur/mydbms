#include <stdio.h>
#include "hexdump.h"

#define CFG_HEXDUMP_NBYTES_ON_LINE	16

void hexdump(char *data, unsigned int len);

void hexdump(char *data, unsigned int len)
{
    unsigned int uiOffset=0, uiLineBytes=0, i=0;

    while(len>0){
	uiLineBytes = (len > CFG_HEXDUMP_NBYTES_ON_LINE)?CFG_HEXDUMP_NBYTES_ON_LINE:len;
	printf("\n 0x%08x  ", uiOffset);
	
	for(i=0; i<uiLineBytes; i++){
	    printf("%02x ", *(unsigned char*)(data+i));
	}
	
	if (uiLineBytes<CFG_HEXDUMP_NBYTES_ON_LINE)
	    for(i=0;i<(CFG_HEXDUMP_NBYTES_ON_LINE-uiLineBytes);i++)
		printf("   ");
	
	printf(" ");
	for(i=0; i<uiLineBytes; i++){
	    if ((*(data+i) < 0x20) || (*(data+i) > 0x7e))
		putchar('.');
	    else
	    	printf("%c", *(data+i));
	}	
	if (uiLineBytes<CFG_HEXDUMP_NBYTES_ON_LINE)
	    for(i=0;i<(CFG_HEXDUMP_NBYTES_ON_LINE - uiLineBytes); i++)
		printf(" ");

	data += (char)uiLineBytes;
	len -= uiLineBytes;
	uiOffset += uiLineBytes;
    }
    printf("\n");
}

