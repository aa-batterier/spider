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
	spider.get_web_page(argv[1]);
	while (!spider.is_empty())
	{
		string address = spider.get_first();
		spider.remove_first();
		outFile << address << endl;
		cout << "Number of elements in list:" << spider.size() << endl;
		spider.get_web_page(address);
	}
	outFile.close();
	//exit(0);
	return 0;
}
