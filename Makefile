CC := gcc
FLAGS := -Wall -Wextra
LIBS := -pthread

Test:	HashMap.o RTrie.o Test.c Streamer.o
	$(CC) $(FLAGS) Test.c HashMap.o RTrie.o Streamer.o -o Test $(LIBS)

Streamer.o:	Streamer.c
	$(CC) $(FLAGS) -c Streamer.c -o Streamer.o $(LIBS)

HashMap.o:	rodats/hashmap/HashMap.c
	$(CC) $(FLAGS) -c rodats/hashmap/HashMap.c -o HashMap.o $(LIBS)

RTrie.o:	rodats/hashmap/RTrie.c
	$(CC) $(FLAGS) -c rodats/hashmap/RTrie.c -o RTrie.o $(LIBS)

clean:
	rm -f *.o
