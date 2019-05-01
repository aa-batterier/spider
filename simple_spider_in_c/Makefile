all: spider

connections.o: connections.c spider.h
	gcc -Wall -g -c -o $@ connections.c -lcurl

list.o: list.c spider.h
	gcc -Wall -g -c -o $@ list.c

main.o: main.c spider.h
	gcc -Wall -g -c -o $@ main.c

memory.o: memory.c spider.h
	gcc -Wall -g -c -o $@ memory.c

text.o: text.c spider.h
	gcc -Wall -g -c -o $@ text.c

spider: connections.o list.o main.o memory.o text.o spider.h
	gcc -Wall -g -o $@ connections.o list.o main.o memory.o text.o -lcurl

clean:
	rm -v spider *.o
