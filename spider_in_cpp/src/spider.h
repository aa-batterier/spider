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
#include <cstring>
#include <deque>
#include <curl/curl.h>

#define DEFAULT_ADDRESS "https://web.archive.org/web/20080916124519/http://www.dmoz.org/"

/* The needed namespaceses. */
using namespace std;

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
		string get_first(void)const{return addresses.front();}

		/*
		 * Function: add_last
		 * Usage: Adds a string last.
		 * ---------------------------
		 *  add_last adds a string last to the queue/fifo.
		 */
		void add_last(string address){addresses.push_back(address);}

		/*
		 * Function: remove_first
		 * Usage: Removes the first string.
		 * ---------------------------------
		 *  remove_first removes the first string from the queue/fifo.
		 */
		void remove_first(void){addresses.pop_front();}

		/*
		 * Function: is_empty
		 * Usage: Returns a bool depending on if the fifo is empty.
		 * ----------------------------------------------------------
		 *  is_empty returns true if the queue/fifo is empty, if the
		 *  queue/fifo is not empty is_empty returns false.
		 */
		bool is_empty(void)const{return addresses.empty();}

		/*
		 * Function: size
		 * Usage: Returns the size.
		 * -------------------------
		 *  size returns the size of the queue/fifo (how many elements
		 *  there are in the queue/fifo).
		 */
		int size(void)const{return addresses.size();}

		/*
		 * Function: grab_web
		 * Usage: Grabs the websites.
		 * ---------------------------
		 *  grab_web grabs the website content and sort out the addresses to the queue/fifo.
		 */
		void grab_web(const string address);

	private:

		/*
		 * Function: get_web_page
		 * Usage: Gets the web page.
		 * --------------------------
		 *  get_web_page downloads the entire web page and returns it in a string.
		 *  If it fails it will return an empty string.
		 */
		static string get_web_page(const char *address);

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
		void extract_web_addresses(const string addOnAddr);

		/*
		 * Function: add_address
		 * Usage: Adds an address.
		 * ------------------------
		 *  add_address adds an address to those addresses who doens't have a fully webaddress,
		 *  (missing "https:://www..." in the begining).
		 */
		void add_address(string addOnAddr,string &address);

		/* Varibles. */

		/*
		 * Varible: webContent.
		 * ---------------------
		 *  In the string varible webContent I store the content of the website.
		 */
		string webContent;

		/*
		 * Varible: addresses.
		 * --------------------
		 *  In the dqueue varible addresses I store all the addresses from the websites.
		 */
		deque<string> addresses;
};

#endif
