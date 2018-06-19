/*
 * Information about sourcedevelopment.
 * -------------------------------------
 *  Initial creator: Andreas Johansson.
 *  Date created: 06-05-2018
 *  Last updated by: Andreas Johansson.
 *  Date for update: 08-05-2018
 */

/*
 * File: spider.h
 * ----------------
 *  Provides tools for the spider program.
 */

#ifndef _spider_h
#define _spider_h

/* Include files necessary for the headerfile. */
#include <iostream>
#include <fstream>
#include <cstring>
#include <deque>
#include <curl/curl.h>
#include "hash.h"

#define DEFAULT_ADDRESS "https://web.archive.org/web/20080916124519/http://www.dmoz.org/"

/* Classdefinitions. */

/*
 * Classdefinition: Spider
 * -------------------------
 *  This class contains all the functions and varibles the spider
 *  needs to operate.
 */
class Spider
{
	public:

		/* Function prototypes. */

		/*
		 * Function: get_first
		 * Usage: Returns the first string.
		 * ---------------------------------
		 *  get_first returns the first string from the queue/fifo.
		 */
		const std::string get_first(void) const {return _addresses.front();}

		/*
		 * Function: add_last
		 * Usage: Adds a string last.
		 * ---------------------------
		 *  add_last adds a string last to the queue/fifo.
		 */
		void add_last(const std::string address) {_addresses.push_back(address);}

		/*
		 * Function: remove_first
		 * Usage: Removes the first string.
		 * ---------------------------------
		 *  remove_first removes the first string from the queue/fifo.
		 */
		void remove_first(void) {_addresses.pop_front();}

		/*
		 * Function: is_empty
		 * Usage: Returns a bool depending on if the fifo is empty.
		 * ----------------------------------------------------------
		 *  is_empty returns true if the queue/fifo is empty, if the
		 *  queue/fifo is not empty is_empty returns false.
		 */
		const bool is_empty(void) const {return _addresses.empty();}

		/*
		 * Function: size
		 * Usage: Returns the size.
		 * -------------------------
		 *  size returns the size of the queue/fifo (how many elements
		 *  there are in the queue/fifo).
		 */
		const int size(void) const {return _addresses.size();}

		/*
		 * Function: grab_web
		 * Usage: Grabs the websites.
		 * ---------------------------
		 *  grab_web grabs the website content and sort out the addresses to the queue/fifo.
		 */
		void grab_web(const std::string address);

		/*
		 * Function: printToFile
		 * Usage: Prints to file.
		 * -----------------------
		 * Prints the web address and web content to the specified file/files.
		 */
		const bool printToFile(const std::string address,const std::string addressFile = "webAddresses.txt",const std::string contentFile = "webContent.txt");
	private:

		/*
		 * Function: get_web_page
		 * Usage: Gets the web page.
		 * --------------------------
		 *  get_web_page downloads the entire web page and returns it in a string.
		 *  If it fails it will return an empty string.
		 */
		static const std::string get_web_page(const char *address);

		/*
		 * Function: write_web_page
		 * Usage: Writes the web page content.
		 * ------------------------------------
		 *  write_web_page is a callback function used to write the entire web page to
		 *  a string. write_web_page will return the amout of data it has written.
		 */
		static size_t write_web_page(void *ptr,size_t size,size_t nmemb,void *stream);

		/*
		 * Function: extract_web_addresses
		 * Usage: Extract the web addresses from the web page.
		 * ----------------------------------------------------
		 *  extract_web_addresses extract all the web addresses from the website and puts
		 *  them into the queue/fifo.
		 */
		void extract_web_addresses(const std::string addOnAddr);

		/*
		 * Function: add_address
		 * Usage: Adds an address.
		 * ------------------------
		 *  add_address adds an address to those addresses who doens't have a fully webaddress,
		 *  (missing "https:://www..." in the begining).
		 */
		void add_address(std::string addOnAddr,std::string &address);

		/* Varibles. */

		/*
		 * Varible: _webContent.
		 * ---------------------
		 *  In the string varible webContent I store the content of the website.
		 */
		std::string _webContent;

		/*
		 * Varible: _addresses.
		 * --------------------
		 *  In the dqueue varible addresses I store all the addresses from the websites.
		 */
		std::deque<std::string> _addresses;
		
		/*
		 * Varible: _webHash.
		 * ------------------
		 *  Stores the web addresses and the web content.
		 */
		Hash _webHash;
};

#endif
