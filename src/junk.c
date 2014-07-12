	/* PSEUDO Code for next part */
	/*
		do{
			if (next_is_overlapping)
				add_another_page_to_tail
			cast_to_next	
			if(slot_free)
				insert_there
			break
		}while(NOT_EOF)
    */

	#if 0	
	{
    	
	
	}
	
	do{
		memcpy(target_table, bufptr, sizeof(table));
		if (!target_table->isExist)
		{
			memcpy(bufptr, new_table, sizeof(table));
			if (write_page(SYSTEM_CATALOG_FILE, i, buf) == ERR_OK)
				if (commit_pages(SYSTEM_CATALOG_FILE) == ERR_OK)
					result = 0;
		}
		else
		{
			/* seek next */
			if (next is overlapping)
			{ read extra page to tail }
			
			
		}
	}
	i = 0;
    init_pages(SYSTEM_CATALOG_FILE);
	bufptr = &buf;
	target_table = malloc(sizeof(table));
	while( read_page(SYSTEM_CATALOG_FILE, i, bufptr) == ERR_OK )
	{
		memcpy(target_table, bufptr, sizeof(table));
		if (!target_table->isExist)
		{
			memcpy(bufptr, new_table, sizeof(table));
			if (write_page(SYSTEM_CATALOG_FILE, i, buf) == ERR_OK)
				if (commit_pages(SYSTEM_CATALOG_FILE) == ERR_OK)
					result = 0;
		}
		else
		{
			bufptr += sizeof(table);
			
		}
		
 		do{
			read_page(SYSTEM_CATALOG_FILE, i, bufptr); //check exception
			target_table = bufptr;
		}while(target_table->isExist);
#if 0
		/* Find a free slot */ 
		if (!target_table->isExist)
		{
			memcpy(bufptr, new_table, sizeof(table));
			if (write_page(SYSTEM_CATALOG_FILE, i, buf) == ERR_OK)
				if (commit_pages(SYSTEM_CATALOG_FILE) == ERR_OK)
					result = 0;
		}
		else
		{
			/* Is it spanning over pages ?*/
			if (CONFIG_PAGE_SIZE / sizeof(table) < 2)
			{
				bufptr += CONFIG_PAGE_SIZE;
				i++;
				continue;
			}
			else
			{
				/* Move pointer to next table */
				bufptr += sizeof(table);
			}
		}
#endif		
#endif
