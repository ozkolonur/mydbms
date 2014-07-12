#include <stdio.h>

FILE *fp;

int main(int argc, char *argv[])
{
	char tmp[256];
	int ret;

	memset(&tmp, 0, 256);
    fp = fopen("catalog.dat", "a+w");
	fseek(fp, 0, SEEK_SET);
	ret = ftell(fp);
	printf("current position = %d\n", ret);	
	ret = fread(&tmp, 256, sizeof(char), fp);
	printf("ret = %d\n", ret);
	perror("1test");
	memset(&tmp, 0xa, 256);
	fseek(fp, 0, SEEK_SET);
	ret = ftell(fp);
	printf("current position = %d\n", ret);	
	ret = fwrite(&tmp, 256, sizeof(char), fp);
	perror("2test");
	printf("ret = %d\n", ret);
	hexdump(&tmp, 256);
	fclose(fp);
	perror("3test");
	return 0;
}