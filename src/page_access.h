#ifndef __PAGE_ACCESS_H__
#define __PAGE_ACCESS_H__

#define CONFIG_PAGE_SIZE 256

int read_page(char *file_name, int page_id, char *page_data);
int write_page(char *file_name, int page_id, char *page_data);

#define ERR_OK		0
#define ERR_EOF		-1
#define ERR_OPEN 	-2
#define ERR_READ	-3
#define ERR_WRITE	-4

#endif /* __PAGE_ACCESS_H__ */