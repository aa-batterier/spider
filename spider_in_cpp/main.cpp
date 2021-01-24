/*
 * Information about sourcedevelopment.
 * -------------------------------------
 *  Initial creator: Andreas Johansson.
 *  Date created: 06-05-2018
 *  Last updated by: Andreas Johansson.
 *  Date for update: 24-01-2021
 */

/*
 * File: main.cpp 
 * ----------------
 *  This is contains the main function
 *  and some help functions.
 */

/* Include files necessary for the headerfile. */
#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>
#include "spider.h"

/* Function prototypes. */

/*
 * Function: one_content_file 
 * Usage: Writes the web content to one file.
 * -------------------------------------------
 *  one_content_file writes all the web content
 *  to one file and returns true on success and 
 *  false on failure.
 */
const bool one_content_file(Spider spider,const std::string startAddress = DEFAULT_ADDRESS,const std::string addressFile = DEFAULT_ADDRESS_FILE,const std::string contentFile = DEFAULT_CONTENT_FILE);

/*
 * Function: multiple_content_files 
 * Usage: Writes the web content to multiple files.
 * -------------------------------------------------
 *  multiple_content_file writes the web content
 *  to multiple files and returns true on success and 
 *  false on failure.
 */
const bool multiple_content_files(Spider spider,const std::string startAddress = DEFAULT_ADDRESS,const std::string addressFile = DEFAULT_ADDRESS_FILE,const std::string contentFolder = DEFAULT_CONTENT_FOLDER);

/*
 * Function: main
 * Usage: This is the main function.
 * ----------------------------------
 */
int main(int argc,char *argv[])
{
	if (argc != 5)
	{
		std::cerr << "usage: " << argv[0] << " <hostname or default> <filename for addresses or default> <-f for folder> <foldername if -f is flaged or default> <filename f -f is not flaged for web content or default>" << std::endl;
		exit(1);
	}
	Spider spider;
	std::string startAddress,addressFile;
	strncmp(argv[1],"default",7) == 0 ? startAddress = DEFAULT_ADDRESS : startAddress = argv[1];
	strncmp(argv[2],"default",7) == 0 ? addressFile = DEFAULT_ADDRESS_FILE : addressFile = argv[2];
        if (strncmp(argv[3],"-f",2) != 0)
        {
                std::string contentFile;
	        strncmp(argv[3],"default",7) == 0 ? contentFile = DEFAULT_CONTENT_FILE : contentFile = argv[3];
                if (one_content_file(spider,startAddress,addressFile,contentFile))
                        exit(1);
        }
        else
        {
                std::string contentFolder;
	        strncmp(argv[4],"default",7) == 0 ? contentFolder= DEFAULT_CONTENT_FOLDER : contentFolder = argv[4];
                if (multiple_content_files(spider,startAddress,addressFile,contentFolder))
                        exit(1);
        }
	exit(0);
}

/*
 * Function: one_content_file 
 * Usage: Writes the web content to one file.
 * -------------------------------------------
 */
const bool one_content_file(Spider spider,const std::string startAddress,const std::string addressFile,const std::string contentFile)
{
	spider.grab_web(startAddress);
	if (!spider.printToFile(startAddress,addressFile,contentFile))
	{
		std::cerr << "Failed to open file." << std::endl;
                return false;
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
                        return false;
		}
	}
        return true;
}

/*
 * Function: multiple_content_files 
 * Usage: Writes the web content to multiple files.
 * -------------------------------------------------
 */
const bool multiple_content_files(Spider spider,const std::string startAddress,const std::string addressFile,const std::string contentFolder)
{
        if (mkdir(contentFolder.c_str(),0777) == -1)
        {
                std::cerr << "Failed to create folder, error: " << strerror(errno) << std::endl;
                return false;
        }
	spider.grab_web(startAddress);
	if (!spider.printToFile(startAddress,addressFile,contentFolder + "/" + startAddress))
	{
		std::cerr << "Failed to open file." << std::endl;
                return false;
	}
	while (!spider.is_empty())
	{
		std::string address = spider.get_first();
		spider.remove_first();
		std::cout << "Number of elements in list: " << spider.size() << std::endl;
		spider.grab_web(address);
		if (!spider.printToFile(address,addressFile,contentFolder + "/" + address))
		{
			std::cerr << "Failed to open file." << std::endl;
                        return false;
		}
	}
        return true;
}
