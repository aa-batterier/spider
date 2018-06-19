/*
 * Information about sourcedevelopment.
 * -------------------------------------
 *  Initial creator: Andreas Johansson.
 *  Date created: 06-05-2018
 *  Last updated by: Andreas Johansson.
 *  Date for update: 19-06-2018
 */

/*
 * File: spider.cpp
 * -----------------
 *  Provides the functions for the spider program.
 */

/* Include files necessary for the headerfile. */
#include "spider.h"

/*
 * Function: grab_web
 * Usage: Grabs the websites.
 * ---------------------------
 */
void Spider::grab_web(const std::string address)
{
	_webContent = get_web_page(address.c_str());
	if (!_webHash.contains(address,_webContent))
	{
		_webHash.add(address,_webContent);
		if (_webContent.size() > 1)
			extract_web_addresses(address);
	}
}

/*
 * Function: printToFile
 * Usage: Prints to file.
 * -----------------------
 * Prints the web address and web content to the specified file/files.
 */
const bool Spider::printToFile(const std::string address,const std::string addressFile,const std::string contentFile)
{
	std::ofstream addressOut(addressFile,std::ios::app),contentOut(contentFile,std::ios::app);
	if (addressOut.fail() || contentOut.fail())
		return false;
	addressOut << _webHash.getKey(address) << std::endl;
	addressOut.close();
	contentOut << _webHash.getValue(address) << std::endl;
	contentOut.close();
	return true;
}

/*
 * Function: get_web_page
 * Usage: Gets the web page.
 * --------------------------
 */
const std::string Spider::get_web_page(const char *address)
{
	std::string content;
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
			std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
		else
			std::cout << content.size() << " bytes retrieved." << std::endl;
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
	std::string &buffer = *(std::string*)stream;
	buffer.append((char*)ptr,size*nmemb);
	return size*nmemb;
}

/*
 * Function: extract_web_addresses
 * Usage: Extract the web addresses from the web page.
 * ----------------------------------------------------
 */
void Spider::extract_web_addresses(const std::string addOnAddr)
{
	char *prev = (char*)_webContent.c_str(),*correct = prev;
	for (;;)
	{
		std::string address;
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
void Spider::add_address(std::string addOnAddr, std::string &address)
{
	if (addOnAddr[addOnAddr.size()-1] == '/')
		addOnAddr[addOnAddr.size()-1] = '\0';
	if (address.compare(0,4,"http") != 0)
		address = addOnAddr + address;
}
