#include "stdafx.h"

#include "etc.h"

//Ëæ»úº¯ÊýÊÇÉ¶
void RandomLines(string filename) {
	vector<string> data;
	ifstream querys(filename);
	ofstream out("../disordered_query.txt");
	string temp;
	while (getline(querys, temp)) {
		data.push_back(temp);
	}
	querys.close();
	random_shuffle(data.begin(), data.end());

	for (unsigned int i = 0; i < data.size() && i < 10; i++) {
		out << data[i] << endl;
	}
	out.close();
	return;
}

void adjustRange(vector<pair<double, string>>& simm)
{
	double max = -1;
	for (unsigned int i = 0; i < simm.size(); i++) {
		max = max > simm[i].first ? max : simm[i].first;
	}

	for (unsigned int i = 0; i < simm.size(); i++) {
		simm[i].first /= max;
	}
	return;
}

void deleteMin(vector<pair<double, string>>& simm)
{
	unsigned int i = 0;
	while (i < simm.size()) {
		if (simm[i].first <= 1) {
			simm.erase(simm.begin() + i);
		}
		else i++;
	}
}

map<double,string> fakemapsort(map<string, double> res)
{
	map<double, string> fakesor;
	map<string, double>::iterator iter;
	for (iter = res.begin(); iter != res.end(); iter++) {
		fakesor[iter->second] = iter->first;
	}
	return fakesor;
}
