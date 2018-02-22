all: bin/spider

lib/connections.o: src/connections.c src/spider.h
	gcc -Wall -g -c -o $@ src/connections.c -lcurl

lib/list.o: src/list.c src/spider.h
	gcc -Wall -g -c -o $@ src/list.c

lib/main.o: src/main.c src/spider.h
	gcc -Wall -g -c -o $@ src/main.c

lib/text.o: src/text.c src/spider.h
	gcc -Wall -g -c -o $@ src/text.c

bin/spider: lib/connections.o lib/list.o lib/main.o lib/text.o src/spider.h
	gcc -Wall -g -o $@ lib/connections.o lib/list.o lib/main.o lib/text.o -lcurl

clean:
	rm -v bin/* lib/*
