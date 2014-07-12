#ifdef __CATALOG_H__
#define __CATALOG_H__

//#include "records.h"
#include "page_access.h"

#define CONFIG_TABLE_NAME_SIZE	32
#define CONFIG_CATALOG_SIZE (4 * CONFIG_PAGE_SIZE)

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
};


#if 0
<catalog>
Tname@offset=|field:len|field:len|field:len|
</catalog>




<table>
001|ali|12|1984
002|veli|12|1982
</table>
#endif

#endif /* __CATALOG_H__ */

