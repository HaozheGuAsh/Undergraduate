#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>


using namespace std;


class page
{
public:
	int pagenum;
	bool use;
	void initialize();
};

void page::initialize()
{
	pagenum = -1;
	use = 1;
}

int main(int argc, char * argv[])
{
	page rampage[4];
	int rampagecount = 0;
	for (int i = 0;i < 4;i++)rampage[i].initialize();
	unsigned int pagetable[16];
	

	if (argc != 2) { cout << "invalid command line" << endl; }

	/*Setup output file*/
	char outfilename[200];
	string originalname = argv[1];
	strcpy(outfilename, "vm-out.txt");
	ofstream output(outfilename);

	/*Read input file*/
	ifstream input(argv[1]);

	for (int i = 0;i < 16;i++)
	{
		stringstream ss;
		string address;
		input >> address;

		//address
		ss << address;
		ss >> hex >> pagetable[i];
//		cout << hex<<pagetable[i] << endl;
	}

	string addressstr;
	int replaceindex = 0;
	unsigned int access;
	while (input >> addressstr)
	{
		stringstream ss;
		ss << addressstr;
		ss >> hex >> access;
		cout <<hex<< access << endl;
		if (rampagecount < 4)
		{
			//cout << "add page at: " <<rampagecount<< endl;
			rampage[rampagecount].initialize();
			int searchindex = -1;
			for (int i = 0;i < 16;i++)
			{
				//cout << hex << "access: " << access << " pagetable at : " << i << "is:  " << pagetable[i] << "up to: " << pagetable[i] + 4096 << endl;
				if (access >= pagetable[i] && access < (pagetable[i] + 4096))
				{
					searchindex = i;
					//cout << searchindex << endl;
					break;
				}
			}
			if (searchindex == -1) { cout << "ERROR1: No page contains address accessed" << endl; }
			rampage[rampagecount].pagenum = searchindex;
			rampagecount++;
		}
		else
		{
			cout << "current use bit: ";
			for (int i = 0;i < 4;i++)
			{
				cout << rampage[i].use << "  ";
			}
			cout << endl;
			bool inrampage = 0;
			for (int i = 0;i < 4;i++)
			{
				if (access >= pagetable[rampage[i].pagenum] && access < (pagetable[rampage[i].pagenum] + 4096))
				{
					inrampage = 1;
					rampage[i].use = 1;
					cout << "Found in ram at: " << i << endl;
					break;
				}
			}


			/*Need clock algorithm for page replacement*/
			if (!inrampage)
			{
				bool foundreplace = 0;
				while (!foundreplace)
				{
					if (replaceindex == 4) replaceindex = 0;
					if (rampage[replaceindex].use == 0) { foundreplace = 1; }
					else { cout << " set at : " << replaceindex;rampage[replaceindex].use = 0; }

					replaceindex++;
					cout << "index at: " << replaceindex;
					
				}

				int searchindex = -1;
				for (int i = 0;i < 16;i++)
				{
					if (access >= pagetable[i] && access < (pagetable[i] + 4112))
					{
						searchindex = i;
						break;
					}
				}
				if (searchindex == -1) { cout << "ERROR2: No page contains address accessed" << endl; }
				rampage[replaceindex-1].initialize();
				rampage[replaceindex-1].pagenum = searchindex;
				cout << "replace at page :  " << replaceindex-1 << endl;
			}
		}


		for (int i = 0;i < 4;i++)
		{
			if (rampage[i].pagenum == -1)output << " ";
			else output << hex << pagetable[rampage[i].pagenum] << " ";
		}
		output << endl;
	}
}