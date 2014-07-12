#include <stdio.h>

#include "records.h"
#include "catalog.h"
#include "page_access.h"

#define CONFIG_TABLE_NAME_SIZE	32


#define TABLE_OPERATIONS_PROMPT " 1) Create a table\n 2) Delete a table\n \
3) List current tables\n 4) Select table\n 5) Quit\n ?) Help\n"

#define SYSTEM_CATALOG_FILE "catalog.dat"

struct table
{
	int isExist;
	/* 0: for deleted tables */

    char name[CONFIG_TABLE_NAME_SIZE];
	/* Name of the table, this is also pKey */

	char field_names[CONFIG_MAX_NUM_OF_FIELDS][CONFIG_MAX_FIELD_SIZE];
    /* Field names */	
    
	char field_sizes[CONFIG_MAX_NUM_OF_FIELDS];
	/* Sizes of fields */

	/* total structure size is = 164 = sizeof(int) + CONFIG_TABLE_NAME_SIZE + 
		(CONFIG_MAX_NUM_OF_FIELDS x CONFIG_MAX_FIELD_SIZE) + CONFIG_MAX_NUM_OF_FIELDS */
	/* total size must be smaller than a page size */
};

void dump_table_struct(struct table mytable)
{
	int i = 0;
	printf("=========================\n");
	printf("isExists = %d\n", mytable.isExist);
	printf("name = %s\n", mytable.name);
	printf("sizeof(table) = %d\n", sizeof(mytable));
	for(i=0; i <= CONFIG_MAX_NUM_OF_FIELDS; i++)
	{
		printf("table.field_names[%d] = %s\n", i, mytable.field_names[i]);
		printf("table.field_sizes[%d] = %d\n", i, mytable.field_sizes[i]);
	}
	printf("=========================\n");
	
}

void create_table(void)
{
	int field_num = 0;
	int i;
	int result = -1;
    struct table new_table;
	struct table *target_table;
	char buf[CONFIG_PAGE_SIZE * 40]; // make this dynamic
	char *buf_ptr;
	int current_page;
  	int pos_on_current_page;

	memset(&new_table, 0, sizeof(struct table));
    new_table.isExist = 1;

	printf("===== %s =====\n", __func__);
	printf("Enter table name (max %d characters) :", CONFIG_MAX_FIELD_SIZE);
//	scanf("%s", &(new_table.name));
	printf("How many fields do you want (max %d fields) :", CONFIG_MAX_FIELD_SIZE);
//	scanf("%d", &field_num);
	printf("\ntable_name = %s field_num = %d \n", new_table.name, field_num);
	for(i=0; i <= (field_num - 1); i++){
		printf("field_num = %d\n", i);
		printf("Enter Field #%d size :", i);
//		scanf("%d", &(new_table.field_sizes[i]));
		printf("Enter Field #%d name :", i);
//		scanf("%s", (new_table.field_names[i]));
		printf("%d : Field_size = %d field_name = %s\n", i, (new_table.field_sizes[i]), (new_table.field_names[i]));
	}	
	strcpy(&(new_table.name), "adres\n");
	strcpy(&(new_table.field_names[0]), "adi\n");
	strcpy(&(new_table.field_names[1]), "soyadi\n");
	new_table.field_sizes[0] = 12;
	new_table.field_sizes[1] = 12;

	printf("Done\n");
	dump_table_struct(new_table);

    result = page_access_init(SYSTEM_CATALOG_FILE);
	if (result != ERR_OK)
		return;

	current_page = 0;

	/* buf_ptr = points to somewhere in buf */	
	/* &buf = byte 0 of page 0 */
	buf_ptr = &buf;
    printf("buf_ptf = %08x\n", buf_ptr);
    printf("*buf_ptf = %08x\n", *buf_ptr);
	printf("&buf = %08x\n", &buf);
	printf("buf = %08x\n", buf);
	/* this is target table, used as pivot when needed */
	//target_table = malloc(sizeof(struct table));
    target_table = &buf;
	printf("0target_table = %08x\n", target_table);
	
	page_read(current_page, &buf);
	//hexdump(buf, sizeof(struct table));
	do{
		
		if(!target_table->isExist)
		{
	printf("3target_table = %08x\n", target_table);
			memcpy(target_table, &new_table, sizeof(struct table));
			//hexdump(&buf, CONFIG_PAGE_SIZE);
//			hexdump(&new_table, sizeof(struct table));
//			hexdump(target_table, sizeof(struct table));

			if ( (page_write(current_page-1, buf) == ERR_OK) && 
					(page_write(current_page, buf) == ERR_OK) )
				if (page_access_close() == ERR_OK)
					result = 0;
			break;
		}	
	printf("1target_table = %08x\n", target_table);
		*target_table++;
		buf_ptr += sizeof(struct table);
	printf("2target_table = %08x\n", target_table);

		/* buf_ptr = pointer to current struct */
		/* current_page = page number on disk starting from zero.
		/* if remaining part of pagebuffer is smaller than a struct size it is overlapping */
		/*  (&buf - bufptr) % CONFIG_PAGE_SIZE > (CONFIG_PAGE_SIZE - sizeof(table)) */
		if ( ((buf_ptr - buf) % CONFIG_PAGE_SIZE) > (CONFIG_PAGE_SIZE - sizeof(struct table)) )
		{
			current_page++;
			result = page_read(current_page, 
								(buf + (current_page * CONFIG_PAGE_SIZE)), 
									CONFIG_PAGE_SIZE);
		}
		/* now it is safe to cast struct, we know trailing part of struct residing in &buf */
		
	} while(result != ERR_EOF);

}

void delete_table(void)
{
	printf("This is %s\n", __func__);
}

void list_tables(void)
{
	printf("This is %s\n", __func__);
}

void select_table(void)
{
	printf("This is %s\n", __func__);
}

/**
 * <A short one line description>
 *
 * <Longer description>
 * <May span multiple lines or paragraphs as needed>
 *
 * @param  Description of method's or function's input parameter
 * @param  ...
 * @return Description of the return value
 */
int main(int argc, char* argv[])
{
	int ch;
    /* keypress character */
	printf("Welcome to poorman's db, type ? for help\n");
	printf(TABLE_OPERATIONS_PROMPT);
    printf("keypress = %08x\n ", ch);
	
	create_table();
	return 0;
	while((ch = getchar()) != EOF){
		switch (ch)
		{
			case 0x31:
				create_table();			
				break;
			case 0x32:
				delete_table();			
				break;
			case 0x33:
				list_tables();			
				break;
			case 0x34:
				select_table();
				break;
			case 0x35:
				return 0;
				break;
			default:
				printf("Command not recognized.\n Type ? for help\n");
				continue;
		}
	}

	return 0;
	
#if 0
	struct record rec;

	sprintf(rec.field[3], "onurkom\n");
	
    printf("--->%s\n", rec.field[3]);
	//printf("size of fx is %d\n", sizeof(rec.field));
    return 0;

#endif
#if 0
	char fx[4][16] = {"1asdasd\n", "2adsasdas\n", "3asdsadas\n", "4asdadasd\n"};
	struct record rec;
    sprintf(fx[3], "onur\n");
   printf("--->%s\n", fx[3]);
	printf("size of fx is %d\n", sizeof(fx));
	char S[10][11];
	int i,j,k;
	char A;
	for (i=0;i<=9;i++){
		scanf ("%s",A);
		for (j=0;j<=10;j++)
		{
			S[i][j]=A;
		}
	}

	for (i=0;i<=9;i++){
		for (j=0;j<=10;j++)
		{
			printf("i=%d j=%d data=%s\n", i,j,S[i][j]);
		}
	}
#endif
#if 0	
	int i,j,k=0;

	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
		{
			sprintf((rec.field[j][i]), "y%d\n", k);
			printf("field %d %d is now %d\n", i,j,k);
			k++;
		}
	
	for(i=0; i<4; i++)

		for(j=0; j<4; j++)
		{
			printf("i=%d j=%d field=%s\n", i,j,rec.field[i][j]);
		}
#endif
	printf("here\n");
	return 0;
}
