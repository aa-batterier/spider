#include <fstream>
#include "spider.h"

using namespace std;

int main(int argc,char *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr,"usage: %s <hostname> <filename>\n",argv[0]);
		//exit(1);
		return 1; 
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
		cout << "Number of elements in list:" << spider.size() << endl;
		spider.grab_web(addressChar);
		delete [] addressChar;
	}
	outFile.close();
	//exit(0);
	return 0;
}
