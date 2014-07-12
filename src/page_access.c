#include <stdio.h>
//#include <stdlib.h>
#include <page_access.h>
#include <sys/fcntl.h>
#include <sys/stat.h>	//stat

int fd;


int page_access_init(char *file_name)
{
	/* TODO: Exception handling */
	fd = open(file_name, O_RDWR | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH);
	lseek(fd, 0, SEEK_SET);	
	printf("::%s:: Init page access fd = %p file = %s\n", __func__, fd, file_name);
	return ERR_OK;
}

int page_read(int page_id, char *page_data)
{
	int res;
	printf("::%s:: reading page %d to target = %08x fd = %p\n", __func__, page_id, page_data, fd);
	/* TODO: Exception handling */
//	fseek(fd, page_id * CONFIG_PAGE_SIZE, SEEK_SET);	
//	memset(page_data, 0, CONFIG_PAGE_SIZE * sizeof(char));
	res = read(fd, page_data, CONFIG_PAGE_SIZE * sizeof(char));
	printf("::%s:: read %d bytes [res = %d]\n", __func__, res, res);
	hexdump(page_data, CONFIG_PAGE_SIZE);
	return ERR_OK;
}

int page_write(int page_id, char *page_data)
{
	/* TODO: Exception handling */
	printf("::%s:: updating page = %d\n", __func__, page_id);
	if (page_id < 0)   //workaround
		return ERR_OK;
	lseek(fd, page_id * CONFIG_PAGE_SIZE, SEEK_SET);	
	hexdump(page_data + (page_id * CONFIG_PAGE_SIZE), CONFIG_PAGE_SIZE);
	write(fd, page_data + (page_id * CONFIG_PAGE_SIZE), CONFIG_PAGE_SIZE * sizeof(char));
	return ERR_OK;
}

int page_access_close(void)
{
	/* TODO: Exception handling */
	close(fd);
	return ERR_OK;
}