#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>


using namespace std;

/*Direct Mapping with 256 Cache(2^8)*/
/*16 bits address*/
/*8 bytes line*/
/*Thus 3 bits offset, 5 bits line and 8 bits tag*/

class cacheline
{
public:
	unsigned int tag;
	unsigned int line;
	bool dirty;
	string block[8];
	void initialize();
};

void cacheline::initialize()
{
	tag = 0;
	line = 0;
	dirty = 0;
	for (int i = 0; i < 8;i++)
	{
		block[i].clear();
	}
}

int main(int argc, char * argv[])
{
	if (argc != 2) { cout << "invalid command line" << endl;  }
	
	/*Create cache memory and Initialize*/
	cacheline cache[32];
	string memory[65536];
	for (int i = 0;i < 32;i++) cache[i].initialize();
	for (int i = 0;i < 65536;i++) memory[i].clear();

	

	/*Read input file*/
	ifstream input(argv[1]);
	string address,operation,data;

	/*Setup output file*/
	char outfilename[200];
	string originalname = argv[1];
	//strcpy(outfilename, "dm");
	strcat(outfilename, originalname.substr(0,originalname.size()-4).c_str());
	strcat(outfilename, "-out.txt");
	ofstream output(outfilename);


	while (input >> address >> operation >> data)
	{
		//cout << address << "  " << operation << "  " << data << endl;
		/*setup input*/
		stringstream ss;
		unsigned int value;

		//address
		ss << address;
		ss >> hex >> value;
		//cout << hex << "address is: " << value << endl;
		

		//operation
		//cout << "operation is: " << operation << endl;


		//data
		//cout << "data is: " << data << endl;

		unsigned int curtag, curline,curoffset;
		curtag = value >> 8;
		curline = value << 24 >> 27;
		curoffset = value << 29 >> 29;
		//cout <<hex << "tag: " << curtag << "  line: " << curline << " offset: " << curoffset << endl;


		if (!strcmp(operation.c_str(), "FF"))
		{
			//cout << "write" << endl;
			if (cache[curline].tag == curtag)
			{
				/*update*/
				cache[curline].block[curoffset] = data;
				cache[curline].dirty = 1;
				//cout << "updata in cache" << endl;
			}
			/*not in cache*/
			else
			{
				/*replace line*/
				if (cache[curline].dirty == 0)
				{
					cache[curline].tag = curtag;
					cache[curline].line = curline;
					cache[curline].dirty = 0;
					unsigned int memaddress;
					memaddress = curtag << 8;
					memaddress |= curline << 3;
					for (int i = 0;i < 8;i++)
					{
						//cout << hex << (memaddress | i)<<"    ";
						cache[curline].block[i] = memory[(memaddress | i)];
					}

					/*update*/
					cache[curline].block[curoffset] = data;
					cache[curline].dirty = 1;

					//cout << "replace & updata in cache" << endl;

				}
				/*not in cache and need write back*/
				else
				{
					/*write back*/
					unsigned int memaddress;
					memaddress = cache[curline].tag << 8;
					memaddress |= cache[curline].line << 3;
					for (int i = 0;i < 8;i++)
					{
						//cout << hex << (memaddress | i) << "    ";
						memory[(memaddress | i)] = cache[curline].block[i];
					}

					/*replace line*/
					cache[curline].tag = curtag;
					cache[curline].line = curline;
					cache[curline].dirty = 0;
					
					memaddress = curtag << 8;
					memaddress |= curline << 3;
					for (int i = 0;i < 8;i++)
					{
						//cout << hex << (memaddress | i)<<"    ";
						cache[curline].block[i] = memory[(memaddress | i)];
					}

					/*update*/
					cache[curline].block[curoffset] = data;
					cache[curline].dirty = 1;
					//cout << "write back & replace & updata in cache" << endl;
				}
			}

		}
		else if (!strcmp(operation.c_str(), "00"))
		{
			//cout << "read" << endl;
			if (cache[curline].tag == curtag)
			{
				/*read*/
				output << hex << cache[curline].block[curoffset] << " 1 " << cache[curline].dirty << endl;
				//cout << "hit 1" <<"dirty "<<cache[curline].dirty<< endl;
			}
			/*not in cache*/
			else
			{
				/*replace line*/
				if (cache[curline].dirty == 0)
				{
					cache[curline].tag = curtag;
					cache[curline].line = curline;
					cache[curline].dirty = 0;
					unsigned int memaddress;
					memaddress = curtag << 8;
					memaddress |= curline << 3;
					for (int i = 0;i < 8;i++)
					{
						//cout << hex << (memaddress | i)<<"    ";
						cache[curline].block[i] = memory[(memaddress | i)];
					}

					/*read*/
					output << hex << cache[curline].block[curoffset] << " 0 0" << endl;;
					//cout << "hit 0" << "dirty 0"<< endl;

				}
				/*not in cache and need write back*/
				else
				{
					/*write back*/
					unsigned int memaddress;
					memaddress = cache[curline].tag << 8;
					memaddress |= cache[curline].line << 3;
					for (int i = 0;i < 8;i++)
					{
						//cout << hex << (memaddress | i) << "    ";
						memory[(memaddress | i)] = cache[curline].block[i];
					}

					/*replace line*/
					cache[curline].tag = curtag;
					cache[curline].line = curline;
					cache[curline].dirty = 0;
					
					memaddress = curtag << 8;
					memaddress |= curline << 3;
					for (int i = 0;i < 8;i++)
					{
						//cout << hex << (memaddress | i)<<"    ";
						cache[curline].block[i] = memory[(memaddress | i)];
					}

					/*read*/
					output << hex << cache[curline].block[curoffset] << " 0 1" << endl;;
					//cout << "hit 0" << "dirty 1"  << endl;
				}
			}
		}
		else
		{
			cout << "Undefined operation:  " << operation <<endl;
		}
	}
	
	
}