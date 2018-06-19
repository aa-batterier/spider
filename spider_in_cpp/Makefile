all: bin/spider

bin/spider: src/hash.cpp src/main.cpp src/spider.cpp src/spider.h src/hash.h
	g++ -Wall -g -o $@ src/hash.cpp src/main.cpp src/spider.cpp -std=c++17 -lcurl

clean:
	rm -rv bin/*
