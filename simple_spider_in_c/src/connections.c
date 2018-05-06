#include "spider.h"

/*
 * Function: get_web_page
 * Usage: Scrapes down the web page.
 * ----------------------------------
 */
void get_web_page(const char *address,Memory *memory)
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
		//curl_easy_setopt(curl,CURLOPT_WRITEDATA,(void*)memory);
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,memory);
		curl_easy_setopt(curl,CURLOPT_TIMEOUT,15000);
		curl_easy_setopt(curl,CURLOPT_USERAGENT,"libcurl-agent/1.0");
		if ((res = curl_easy_perform(curl)) != CURLE_OK)
		{
			fprintf(stderr,"curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
		}
		else
		{
			printf("%lu bytes retrieved.\n",(long)memory->size);
		}
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}
