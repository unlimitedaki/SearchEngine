#pragma once

#include<iostream>
#include<string>
#include<list>

using namespace std;

class QueryAcc
{
public:
	QueryAcc();
	~QueryAcc();

	bool Query(const string buff, list<pair<string, string>>& data);

};

