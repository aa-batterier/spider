all: spider

spider: hash.cpp main.cpp spider.cpp spider.h hash.h
	g++ -Wall -g -o $@ hash.cpp main.cpp spider.cpp -std=c++17 -lcurl

clean:
	rm -rv spider 
