CFLAGS=-Wall -Wextra -ggdb

vec: main.c
	$(CC) $(CFLAGS) -o vec main.c