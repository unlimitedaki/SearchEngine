#include<iostream>
#include<string>
#include<list>
#include<vector>
#include <algorithm>  
#include<sstream>
#include"NLPIR.h"
#pragma once
#pragma comment(lib, "NLPIR.lib")
using namespace std;
class NLPIR_Query_LiYeqiu
{
public:

	
	NLPIR_Query_LiYeqiu();
	~NLPIR_Query_LiYeqiu();

	static vector<pair<double,string> > Query(const string query, list<pair<string, string>> &data);


	//static string divide(int &i, const char * str);

};

vector<string> DivideWords(string s);
int exist(vector<string> querys, string str);//for Fuzzy
int exist(string query, string str);