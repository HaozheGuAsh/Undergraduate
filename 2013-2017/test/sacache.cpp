#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <vector>
#include <algorithm>


using namespace std;

/*Set Associative Mapping with 240 Bytes 6-Way Cache*/
/*16 bits address*/
/*4 bytes line*/
/*Thus 2 bits offset, 10 lines*/

class cacheline
{
public:
	unsigned int tag;
	unsigned int used;
	bool dirty;
	string block[4];
	void initialize();
};

void cacheline::initialize()
{
	tag = 0;
	used = 0;
	dirty = 0;
	for (int i = 0; i < 4;i++)
	{
		block[i].clear();
	}
}

class cacheset
{
public:
	vector<cacheline> set;
	int size;
	void initialize();
};

void cacheset::initialize()
{
	size = 0;
	for (int i = 0;i < 6;i++)
	{
		cacheline line;
		line.initialize();
		set.insert(set.begin(), line);
	}
}

int main(int argc, char * argv[])
{
	if (argc != 2) { cout << "invalid command line" << endl; }

	/*Create cache memory and Initialize*/
	cacheset cache[10];
	string memory[65536];
	for (int i = 0;i < 10;i++) cache[i].initialize();
	for (int i = 0;i < 65536;i++) memory[i].clear();



	/*Read input file*/
	ifstream input(argv[1]);
	string address, operation, data;

	/*Setup output file*/
	char outfilename[200];
	string originalname = argv[1];
	//strcpy(outfilename, "sa");
	strcat(outfilename, originalname.substr(0, originalname.size() - 4).c_str());
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

		unsigned int curtag, curline, curoffset;
		curtag = value >> 2;
		curline = curtag % 10;
		curoffset = value << 30 >> 30;
		//cout <<hex <<"operation: "<<operation << " address: "<<value<<" tag: " << curtag << "  set: " << curline << " offset: " << curoffset << endl;


		if (!strcmp(operation.c_str(), "FF"))
		{
			//cout << "write" << endl;
			int incacheindex = -1;
			for (int i = 0; i < 6;i++)
			{
				if (cache[curline].set[i].tag == curtag) { incacheindex = i;break; }
			}

			//cout << "cache index: " << incacheindex;
			if (incacheindex !=-1)
			{
				/*update*/
				cache[curline].set[incacheindex].block[curoffset] = data;
				cache[curline].set[incacheindex].dirty = 1;

				/*Move to front*/
				vector<cacheline>::iterator it;
				it = cache[curline].set.begin()+incacheindex;
				cacheline tmp = *it;
				cache[curline].set.erase(it);
				cache[curline].set.insert(cache[curline].set.begin(), tmp);
				//cout << "updata in cache at set: " <<curline<<"  linesize:  "<<cache[curline].size<<endl;
			}
			/*not in cache*/
			else
			{
				/*add line*/
				int lineindex = cache[curline].size;
				if (lineindex < 6)
				{
					cacheline newline;
					newline.initialize();
					newline.tag = curtag;
					newline.dirty = 0;
					cache[curline].set.insert(cache[curline].set.begin(), newline);
					cache[curline].size++;
					unsigned int memaddress;
					memaddress = curtag << 2;
					for (int i = 0;i < 4;i++)
					{
						//cout << hex << (memaddress | i)<<"    ";
						cache[curline].set[0].block[i] = memory[(memaddress | i)];
					}
					/*update*/
					cache[curline].set[0].block[curoffset] = data;
					cache[curline].set[0].dirty = 1;
					//cout<<"add line & update  at set: "<<curline <<"size: "<< cache[curline].size <<endl;
				}
				/*Need to replace line using LRU*/
				else
				{
					/*No write back, just replace*/
					if (cache[curline].set[5].dirty == 0)
					{
						cache[curline].set[5].initialize();
						cache[curline].set[5].tag = curtag;
						unsigned int memaddress;
						memaddress = curtag << 2;
						for (int i = 0;i < 4;i++)
						{
							//cout << hex << (memaddress | i)<<"    ";
							cache[curline].set[5].block[i] = memory[(memaddress | i)];
						}

						/*update*/
						cache[curline].set[5].block[curoffset] = data;
						cache[curline].set[5].dirty = 1;

						/*Move to front*/
						vector<cacheline>::iterator it;
						it = cache[curline].set.begin()+5;
						cacheline tmp = *it;
						cache[curline].set.erase(it);
						cache[curline].set.insert(cache[curline].set.begin(), tmp);
						
						//cout << "replace & updata in cache  at set: " <<curline << "size: " << cache[curline].size << endl;
					}
					/*Do write back then replace*/
					else
					{
						/*Write back*/
						unsigned int memaddress;
						memaddress = cache[curline].set[5].tag << 2;
						for (int i = 0;i < 4;i++)
						{
							//cout << hex << (memaddress | i)<<"    ";
							memory[(memaddress | i)] = cache[curline].set[5].block[i];
						}

						/*Replace line*/
						cache[curline].set[5].initialize();
						cache[curline].set[5].tag = curtag;
						
						memaddress = curtag << 2;
						for (int i = 0;i < 4;i++)
						{
							//cout << hex << (memaddress | i)<<"    ";
							cache[curline].set[5].block[i] = memory[(memaddress | i)];
						}
						/*update*/
						cache[curline].set[5].block[curoffset] = data;
						cache[curline].set[5].dirty = 1;

						/*Move to front*/
						vector<cacheline>::iterator it;
						it = cache[curline].set.begin() + 5;
						cacheline tmp = *it;
						cache[curline].set.erase(it);
						cache[curline].set.insert(cache[curline].set.begin(), tmp);
						//cout << "write back & replace & updata in cache at set: " << curline << "size: " << cache[curline].size << endl;
					}
				}

			}

		}
		else if (!strcmp(operation.c_str(), "00"))
		{
			/*read*/

			int incacheindex = -1;
			for (int i = 0; i < 6;i++)
			{
				if (cache[curline].set[i].tag == curtag) { incacheindex = i;break; }
			}


			if (incacheindex != -1)
			{
				//cout << "line: " << incacheindex << "size: " << cache[curline].size << endl;
				/*Move to front*/
				vector<cacheline>::iterator it;
				it = cache[curline].set.begin() + incacheindex;
				cacheline tmp = *it;
				cache[curline].set.erase(it);
				cache[curline].set.insert(cache[curline].set.begin(), tmp);
				//cout << "updata in cache" << endl;

				output << hex << cache[curline].set[0].block[curoffset] << " 1 " << cache[curline].set[0].dirty << endl;
				//cout << "hit 1" <<"dirty "<< cache[curline].set[0].dirty << endl;
			}
			/*not in cache*/
			else
			{
				/*add line*/
				int lineindex = cache[curline].size;
				if (lineindex < 6)
				{
					cacheline newline;
					newline.initialize();
					newline.tag = curtag;
					newline.dirty = 0;
					cache[curline].set.insert(cache[curline].set.begin(), newline);
					cache[curline].size++;
					unsigned int memaddress;
					memaddress = curtag << 2;
					for (int i = 0;i < 4;i++)
					{
						//cout << hex << (memaddress | i)<<"    ";
						cache[curline].set[0].block[i] = memory[(memaddress | i)];
					}

					/*read*/
					output << hex << cache[curline].set[0].block[curoffset] << " 0 0" << endl;;
					//cout << "hit 0" << "dirty 0"<< endl;
					//cout<<"add line & update"<<endl;
				}
				/*Need to replace line using LRU*/
				else
				{
					/*No write back, just replace*/
					if (cache[curline].set[5].dirty == 0)
					{
						cache[curline].set[5].initialize();
						cache[curline].set[5].tag = curtag;
						unsigned int memaddress;
						memaddress = curtag << 2;
						for (int i = 0;i < 4;i++)
						{
							//cout << hex << (memaddress | i)<<"    ";
							cache[curline].set[5].block[i] = memory[(memaddress | i)];
						}

						/*Move to front*/
						vector<cacheline>::iterator it;
						it = cache[curline].set.begin() + 5;
						cacheline tmp = *it;
						cache[curline].set.erase(it);
						cache[curline].set.insert(cache[curline].set.begin(), tmp);

						/*read*/
						output << hex << cache[curline].set[0].block[curoffset] << " 0 0" << endl;;
						//cout << "hit 0" << "dirty 0"<< endl;

						//cout << "replace & updata in cache" << endl;
					}
					/*Do write back then replace*/
					else
					{
						/*Write back*/
						unsigned int memaddress;
						memaddress = cache[curline].set[5].tag << 2;
						for (int i = 0;i < 4;i++)
						{
							//cout << hex << (memaddress | i)<<"    ";
							memory[(memaddress | i)] = cache[curline].set[5].block[i];
						}

						/*Replace line*/
						cache[curline].set[5].initialize();
						cache[curline].set[5].tag = curtag;
						
						memaddress = curtag << 2;
						for (int i = 0;i < 4;i++)
						{
							//cout << hex << (memaddress | i)<<"    ";
							cache[curline].set[5].block[i] = memory[(memaddress | i)];
						}

						/*Move to front*/
						vector<cacheline>::iterator it;
						it = cache[curline].set.begin() + 5;
						cacheline tmp = *it;
						cache[curline].set.erase(it);
						cache[curline].set.insert(cache[curline].set.begin(), tmp);

						/*read*/
						output << hex << cache[curline].set[0].block[curoffset] << " 0 1" << endl;;
						//cout << "hit 0" << "dirty 1"<< endl;
						//cout << "write back & replace & updata in cache" << endl;
					}
				}

			}
			
			
		}
		else
		{
			cout << "Undefined operation:  " << operation << endl;
		}
	}


}