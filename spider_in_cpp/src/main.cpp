/*
 * Information about sourcedevelopment.
 * -------------------------------------
 *  Initial creator: Andreas Johansson.
 *  Date created: 06-05-2018
 *  Last updated by: Andreas Johansson.
 *  Date for update: 08-05-2018
 */

/*
 * File: main.cpp 
 * ----------------
 *  This is conrains the main function.
 */

/* Include files necessary for the headerfile. */
#include <cstdlib>
#include "spider.h"

/*
 * Function: main
 * Usage: This is the main function.
 * ----------------------------------
 */
int main(int argc,char *argv[])
{
	if (argc != 3)
	{
		std::cerr << "usage: " << argv[0] << " <hostname or default> <filename>" << std::endl;
		exit(1);
	}
	Spider spider;
	if (strncmp(argv[1],"default",7) == 0)
	{
		spider.grab_web(DEFAULT_ADDRESS);
		spider.printToFile(DEFAULT_ADDRESS);
	}
	else
	{
		spider.grab_web(argv[1]);
		spider.printToFile(argv[1]);
	}
	while (!spider.is_empty())
	{
		std::string address = spider.get_first();
		spider.remove_first();
		std::cout << "Number of elements in list: " << spider.size() << std::endl;
		spider.grab_web(address);
		spider.printToFile(address);
	}
	exit(0);
}
