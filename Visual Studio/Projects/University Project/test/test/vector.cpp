#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
#include <signal.h>
#include <sstream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;
bool myfunction(int i, int j) {
	return (i == j);
}

int main0() {
	//int myints[] = { 10, 20, 20, 20, 30, 30, 20, 20, 10 };           // 10 20 20 20 30 30 20 20 10
	std::vector<string> myvector;
	myvector.push_back("ash");
	myvector.push_back("zz");
	myvector.push_back("jaden");
//	myvector.push_back("ash");
	myvector.push_back("mengda");
	myvector.push_back("dada");
	myvector.push_back("bin");
	//myvector.push_back("jaden");
	//myvector.push_back("zz");
	// using default comparison:
	std::vector<string>::iterator it;
	std::sort(myvector.begin(), myvector.end());
	it = std::unique(myvector.begin(), myvector.end());   // 10 20 30 20 10 ?  ?  ?  ?
	//                ^
	if (it == myvector.end())
	{
		cout << "here";
	}
	myvector.resize(std::distance(myvector.begin(), it)); // 10 20 30 20 10
	/*
	// using predicate comparison:
	std::unique(myvector.begin(), myvector.end(), myfunction);   // (no changes)

	// print out content:
	std::cout << "myvector contains:";
	for (it = myvector.begin(); it != myvector.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';*/

	return 0;
}