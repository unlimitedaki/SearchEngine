#include "stdafx.h"
#include "QueryAcc.h"


QueryAcc::QueryAcc()
{
}


QueryAcc::~QueryAcc()
{
}

 bool QueryAcc::Query(const string buff, list<pair<string, string>> &data) {
	list<pair<string, string>>::iterator iter;
	int count = 0;
	for (iter = data.begin(); iter != data.end(); iter++) {
		if (iter->first.find(buff) != -1) {
			cout << iter->first << "\t" << iter->second << endl;
			count++;
		}
	}

	return count != 0 ? true : false;
}