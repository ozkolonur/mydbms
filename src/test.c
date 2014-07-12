#include <stdio.h>
#include <unistd.h>
#include <sys/fcntl.h>
int fp;

int main(int argc, char *argv[])
{
	char tmp[256];
	int ret;

	memset(&tmp, 0, 256);
    fp = open("catalog.dat", O_RDWR);
	lseek(fp, 0, SEEK_SET);
	//ret = ftell(fp);
	//printf("current position = %d\n", ret);	
	ret = read(fp, &tmp, 256);
	printf("ret = %d\n", ret);
	perror("1test");
	memset(&tmp, 0xa, 256);
	lseek(fp, 0, SEEK_SET);
	//ret = ftell(fp);
	//printf("current position = %d\n", ret);	
	ret = write(fp, &tmp, 256);
	perror("2test");
	printf("ret = %d\n", ret);
	hexdump(&tmp, 256);
	close(fp);
	perror("3test");
	return 0;
}