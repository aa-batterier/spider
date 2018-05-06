#include "spider.h"

using namespace std;

void Spider::get_web_page(const string address)
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
			printf("Bytes retrieved.\n");
		}
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	extract_web_addresses(address);
}

static size_t Spider::write_web_page(void *ptr,size_t size,size_t nmemb,string stream)
{
	string temp(static_cast<const char*>(ptr), size * nmemb);
	webContent = temp;
	return size*nmemb;
}

void Spider::extract_web_addresses(const string addOnAddr)
{
	char *prev = webContent,*correct = webContent;
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
			address.append(*correct);
		}
		add_address(addOnAddr,address);
		add_last(address);
		correct++;
	}
}

void Spider::add_address(const string addOnAddr, string &address)
{
	int addrLen = strlen(addOnAddr),last = addrLen-1;
	string cleanAddr;
	strncpy(cleanAddr,addOnAddr,addrLen);
	cleanAddr[addrLen] = '\0';
	if (cleanAddr[last] == '/')
	{
		cleanAddr[last] = '\0';
		addrLen--;
	}
	if (strncmp("http",address,4) != 0)
	{
		string tmp = address;
		strcat(strcpy(address,cleanAddr),tmp);
	}
}
