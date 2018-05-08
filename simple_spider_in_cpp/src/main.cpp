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
#include <stdlib.h>
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
		cerr << "usage: " << argv[0] << " <hostname> <filename>" << endl;
		exit(1);
	}
	Spider spider;
	ofstream outFile;
	outFile.open(argv[2]);
	spider.grab_web(argv[1]);
	while (!spider.is_empty())
	{
		string addressString = spider.get_first();
		spider.remove_first();
		char *addressChar = new char[addressString.size()+1];
		copy(addressString.begin(),addressString.end(),addressChar);
		addressChar[addressString.size()] = '\0';
		outFile << addressString << endl;
		cout << "Number of elements in list: " << spider.size() << endl;
		spider.grab_web(addressChar);
		delete [] addressChar;
	}
	outFile.close();
	exit(0);
}
