#include<iostream>
#include<list>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<map>

#include<io.h>
#include<algorithm>

using namespace std;
class KeywordExtraction
{

public:
	static map<string, double>  keywordExtraction(vector<string> data);

	static void SingleSentence(list<string> data,
		map<string, map<string, double>> &links, map<string, double> &linkouts);
	
	static void pageRank(map<string, double> &prres, 
		map<string, map<string, double>> &links,
		map<string, double> &linkouts);

	KeywordExtraction();
	~KeywordExtraction();
};

