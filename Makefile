CC := gcc
FLAGS := -Wall -Wextra
LIBS := -pthread

%.o:	%.c
	$(CC) $(FLAGS) $< -c -o $@ $(LIBS)
%:	%.c %.o
	$(CC) $(FLAGS) $< -o $@ $(LIBS)

HashMap.o:	rodats/hashmap/HashMap.c
RTrie.o:	rodats/hashmap/RTrie.c
