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
#include <fstream>
#include "spider.h"

/* The needed namespaceses. */
using namespace std;

/*
 * Function: main
 * Usage: This is the main function.
 * ----------------------------------
 */
int main(int argc,char *argv[])
{
	if (argc != 3)
	{
		cerr << "usage: " << argv[0] << " <hostname or default> <filename>" << endl;
		exit(1);
	}
	Spider spider;
	if (strncmp(argv[1],"default",7) == 0)
		spider.grab_web(DEFAULT_ADDRESS);
	else
		spider.grab_web(argv[1]);
	ofstream outFile;
	outFile.open(argv[2]);
	while (!spider.is_empty())
	{
		string address = spider.get_first();
		spider.remove_first();
		outFile << address << endl;
		cout << "Number of elements in list: " << spider.size() << endl;
		spider.grab_web(address.c_str());
	}
	outFile.close();
	exit(0);
}
