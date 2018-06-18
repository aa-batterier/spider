/*
 * Information about sourcedevelopment.
 * -------------------------------------
 *  Initial creator: Andreas Johansson.
 *  Date created: 06-05-2018
 *  Last updated by: Andreas Johansson.
 *  Date for update: 08-05-2018
 */

/*
 * File: spider.cpp
 * -----------------
 *  Provides the functions for the spider program.
 */

/* Include files necessary for the headerfile. */
#include "spider.h"

/* The needed namespaceses. */
using namespace std;

/*
 * Function: grab_web
 * Usage: Grabs the websites.
 * ---------------------------
 */
void Spider::grab_web(const string address)
{
	webContent = get_web_page(address.c_str());
	if (webContent.size() > 1)
		extract_web_addresses(address);
}

/*
 * Function: get_web_page
 * Usage: Gets the web page.
 * --------------------------
 */
string Spider::get_web_page(const char *address)
{
	string content;
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
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,&content);
		curl_easy_setopt(curl,CURLOPT_TIMEOUT,15000);
		curl_easy_setopt(curl,CURLOPT_USERAGENT,"libcurl-agent/1.0");
		if ((res = curl_easy_perform(curl)) != CURLE_OK)
			cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
		else
			cout << content.size() << " bytes retrieved." << endl;
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	return content;
}

/*
 * Function: write_web_page
 * Usage: Writes the web page content.
 * ------------------------------------
 */
size_t Spider::write_web_page(void *ptr,size_t size,size_t nmemb,void *stream)
{
	string &buffer = *(string*)stream;
	buffer.append((char*)ptr,size*nmemb);
	return size*nmemb;
}

/*
 * Function: extract_web_addresses
 * Usage: Extract the web addresses from the web page.
 * ----------------------------------------------------
 */
void Spider::extract_web_addresses(const string addOnAddr)
{
	char *prev = (char*)webContent.c_str(),*correct = prev;
	for (;;)
	{
		string address;
		if ((prev = strstr(correct,"href=")) == NULL)
			break;
		if ((prev = strtok(prev,"\'\"")) == NULL)
			break;
		if ((correct = strtok(NULL,"\'\"")) == NULL)
			break;
		int i = 0;
		for (; *correct != '\0'; correct++,i++)
			address += *correct;
		add_address(addOnAddr,address);
		add_last(address);
		correct++;
	}
}

/*
 * Function: add_address
 * Usage: Adds an address.
 * ------------------------
 */
void Spider::add_address(string addOnAddr, string &address)
{
	if (addOnAddr[addOnAddr.size()-1] == '/')
		addOnAddr[addOnAddr.size()-1] = '\0';
	if (address.compare(0,4,"http") != 0)
		address = addOnAddr + address;
}
