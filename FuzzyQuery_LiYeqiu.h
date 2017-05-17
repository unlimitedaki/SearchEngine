#pragma once

#include<iostream>
#include<string>
#include<list>
#include<vector>

using namespace std;

class FuzzyQuery_LiYeqiu
{
public:
	FuzzyQuery_LiYeqiu();
	~FuzzyQuery_LiYeqiu();

	int getlength(char ch);

	//bool FuzzyQuery(const string buff, list<pair<string, string>> &data);

	bool FuzzyQurey2(const string buff, list<pair<string, string>> &data);
};

