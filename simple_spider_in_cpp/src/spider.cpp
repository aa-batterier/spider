#include "spider.h"

using namespace std;

void Spider::get_web_page(const char *address)
{
	CURLcode res;
	curl_global_init(CURL_GLOBAL_ALL);
	CURL *curl = curl_easy_init();
	if (curl)
	{
		curl_easy_setopt(curl,CURLOPT_URL,address);
#ifdef SKIP_PEER_VERIFICATION
		curl_easy_setopt(curl,CURLOPT_SSL_VERIFYPEER,0L);
#endif
#ifdef SKIP_HOSTNAME_VERIFICATION
		curl_easy_setopt(curl,CURLOPT_SSL_VERIFYHOST,0L);
#endif
		curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,write_web_page);
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,&webContent);
		curl_easy_setopt(curl,CURLOPT_TIMEOUT,15000);
		curl_easy_setopt(curl,CURLOPT_USERAGENT,"libcurl-agent/1.0");
		if ((res = curl_easy_perform(curl)) != CURLE_OK)
		{
			fprintf(stderr,"curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
		}
		else
		{
		//	cout << webContent << endl;
		}
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	string addressString(address);
	extract_web_addresses(addressString);
}

size_t Spider::write_web_page(void *ptr,size_t size,size_t nmemb,void *stream)
{
	/*string temp(static_cast<const char*>(ptr), size * nmemb);
	webContent = temp;*/
	string &buffer = *(string*)stream;
	buffer.assign((char*)ptr,size*nmemb);
	cout << buffer << endl;
	return size*nmemb;
}

void Spider::extract_web_addresses(const string addOnAddr)
{
	char *prev = new char[webContent.size()+1];
	copy(webContent.begin(),webContent.end(),prev);
	prev[webContent.size()] = '\0';
	char *correct = prev;
	for (;;)
	{
		string address;
		if ((prev = strstr(correct,"href=")) == NULL)
		{
			break;
		}
		if ((prev = strtok(prev,"\'\"")) == NULL)
		{
			break;
		}
		if ((correct = strtok(NULL,"\'\"")) == NULL)
		{
			break;
		}
		int i = 0;
		for (; *correct != '\0'; correct++,i++)
		{
			//address.append(*correct);
			address += *correct;
		}
		add_address(addOnAddr,address);
		add_last(address);
		correct++;
	}
	delete [] prev;
	correct = NULL;
}

void Spider::add_address(const string addOnAddr, string &address)
{
	int addrLen = addOnAddr.size(),last = addrLen-1;
	char *cleanAddr = new char[addrLen+1];
	copy(addOnAddr.begin(),addOnAddr.end(),cleanAddr);
	cleanAddr[addrLen] = '\0';
	if (cleanAddr[last] == '/')
	{
		cleanAddr[last] = '\0';
		addrLen--;
	}
	if (address.compare(0,4,"http") != 0)
	{
		string tmp = address;
		address.assign(cleanAddr);
		address += tmp;
	}
	delete [] cleanAddr;
}
