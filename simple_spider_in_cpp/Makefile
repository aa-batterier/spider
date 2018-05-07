all: bin/spider

bin/spider: src/main.cpp src/spider.cpp src/spider.h
	g++ -Wall -g -o $@ src/main.cpp src/spider.cpp -lcurl

clean:
	rm -rv bin/*
