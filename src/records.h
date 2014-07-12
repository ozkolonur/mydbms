#ifndef __RECORDS_H__
#define __RECORDS_H__

#define CONFIG_MAX_NUM_OF_FIELDS	8
#define CONFIG_MAX_FIELD_SIZE		16
/* One record is 8 x 16 = 128 bytes */
/* Page size is 256 so, two records for any page */

struct record
{
	int isExists; 
	/* 0: for deleted records */

	char *fields[CONFIG_MAX_NUM_OF_FIELDS];
	/* One can add extra fields according to needs */
};


int record_add(char *pKey, char *record_data);
int record_del(char *pKey);
int record_update(char *pKey, char *record_data);
int record_find_less_than(char *pKey);
int record_find_more_than(char *pKey);
int record_find_equal_to(char *pKey);
int record_list_all(void);

#endif /* __RECORDS_H__ */