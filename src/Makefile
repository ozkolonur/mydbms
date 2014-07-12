CC 	= gcc
CFLAGS 	= -O0 -ggdb -I.

dbms: Makefile main.c
	$(CC) $(CFLAGS) main.c page_access.c hexdump.c -o mydbms
	$(CC) $(CFLAGS) test.c hexdump.c -o test

clean:
	rm -Rf mydbms
