CC := gcc
FLAGS := -Wall -Wextra
LIBS := -pthread -lm -lc

Test:	Test.c MManager.o Streamer.o
	$(CC) $(FLAGS) Test.c MManager.o Streamer.o RTrie.o HashMap.o -o Test $(LIBS)

MManager.o:	MManager.h MManager.c HashMap.o
	$(CC) $(FLAGS) -c MManager.c -o MManager.o $(LIBS)

HashMap.o:	rodats/hashset/HashMap.c RTrie.o
	$(CC) $(FLAGS) -c rodats/hashset/HashMap.c RTrie.o -o HashMap.o $(LIBS)

Streamer.o:	Streamer.c
	$(CC) $(FLAGS) -c Streamer.c -o Streamer.o $(LIBS)

HashMap.o:	rodats/hashset/HashMap.c
	$(CC) $(FLAGS) -c rodats/hashset/HashMap.c -o HashMap.o $(LIBS)

RTrie.o:	rodats/hashset/RTrie.c
	$(CC) $(FLAGS) -c rodats/hashset/RTrie.c -o RTrie.o $(LIBS)

clean:
	rm -f *.o
