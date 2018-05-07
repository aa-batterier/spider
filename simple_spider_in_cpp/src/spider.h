#include <iostream>
#include <cstring>
#include <deque>
#include <curl/curl.h>

using namespace std;

class Spider
{
	public:
		// Storage functions:
		string get_first(void)const{return addresses.front();}
		void add_last(string address){addresses.push_back(address);}
		void remove_first(void){addresses.pop_front();}
		bool is_empty(void)const{return addresses.empty();}
		int size(void)const{return addresses.size();}
		// Connections functions:
		void get_web_page(const char *address);
	private:
		// Connections functions:
		static size_t write_web_page(void *ptr,size_t size,size_t nmemb,void *stream);
		void extract_web_addresses(const string addOnAddr);
		void add_address(const string addOnAddr,string &address);
		// Varibles:
		string webContent;
		deque<string> addresses;
};
