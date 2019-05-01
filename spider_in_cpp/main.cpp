/*
 * Information about sourcedevelopment.
 * -------------------------------------
 *  Initial creator: Andreas Johansson.
 *  Date created: 06-05-2018
 *  Last updated by: Andreas Johansson.
 *  Date for update: 19-06-2018
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
	if (argc != 4)
	{
		std::cerr << "usage: " << argv[0] << " <hostname or default> <filename for addresses or default> <filename for web content or default>" << std::endl;
		exit(1);
	}
	Spider spider;
	std::string startAddress,addressFile,contentFile;
	strncmp(argv[1],"default",7) == 0 ? startAddress = DEFAULT_ADDRESS : startAddress = argv[1];
	strncmp(argv[2],"default",7) == 0 ? addressFile = DEFAULT_ADDRESS_FILE : addressFile = argv[2];
	strncmp(argv[3],"default",7) == 0 ? contentFile = DEFAULT_CONTENT_FILE : contentFile = argv[2];
	spider.grab_web(startAddress);
	if (!spider.printToFile(startAddress,addressFile,contentFile))
	{
		std::cerr << "Failed to open file." << std::endl;
		exit(1);
	}
	while (!spider.is_empty())
	{
		std::string address = spider.get_first();
		spider.remove_first();
		std::cout << "Number of elements in list: " << spider.size() << std::endl;
		spider.grab_web(address);
		if (!spider.printToFile(address,addressFile,contentFile))
		{
			std::cerr << "Failed to open file." << std::endl;
			exit(1);
		}
	}
	exit(0);
}
