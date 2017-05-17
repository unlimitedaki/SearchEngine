#include<iostream>
#include<list>
#include<string>
#include<vector>
#include<fstream>
#include<map>
#include<sstream>
#include<io.h>
#include<algorithm>

using namespace std;
class InvertedIndex
{
	map<string, vector<int>> I_index;
public:
	InvertedIndex(char * dir);
	~InvertedIndex();

	void createIndex(vector<string> &srcfileNames);

	void printIndex();

	map<string, vector<string>> readindex();
};
