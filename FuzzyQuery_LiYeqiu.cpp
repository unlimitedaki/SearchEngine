#include "stdafx.h"
#include "FuzzyQuery_LiYeqiu.h"


FuzzyQuery_LiYeqiu::FuzzyQuery_LiYeqiu()
{
}


FuzzyQuery_LiYeqiu::~FuzzyQuery_LiYeqiu()
{
}

/*bool FuzzyQuery_LiYeqiu::FuzzyQuery(const string buff, list<pair<string, string>> &data) {
	size_t found;
	size_t count=0;
	string str;
	list<pair<string, string>>::iterator iter;
	//list<pair<string, string>> foundData;

	for (iter = data.begin(); iter != data.end(); iter++) {
		int cnt = 0;
		str = iter->first;
		found = str.find_first_of(buff);
		while (found != string::npos) {
			cnt++;
			str[found] = '*';
			//str[found + 1] = '*';//双字
			found = str.find_first_of(buff);
		}
		
		if (cnt/(double)buff.length()>=0.70) {
			cout << cnt << "\t";
			cout << iter->first << "\t" << iter->second << endl; count++;
		}
	}
	cout << count << endl;
	return count != 0 ? true : false;
}*/

bool FuzzyQuery_LiYeqiu::FuzzyQurey2(const string buff, list<pair<string, string>> &data) {
	size_t count = 0;
	string str;
	list<pair<string, string>>::iterator iter;

	for (iter = data.begin(); iter != data.end(); iter++) {
		int cnt = 0,len;
		str = iter->first;
		for (int i = 0; i < buff.length()-1; i++) {
			string word="";
			len = getlength(buff[i]);
			for (int j = 0; j < len; j++) {
				word += buff[i + j];
			}
			i += len;
			if (str.find(word)!=-1) 
				cnt++;
		}

		if (cnt / (double)(0.618*str.length())) {
			cout << cnt << "\t";
			cout << iter->first << "\t" << iter->second << endl; count++;
		}

	}
	cout << count << endl;
	return count != 0 ? true : false;

}

int FuzzyQuery_LiYeqiu::getlength(char ch) {//判定字符的长度（双字或单字等等）
	if (ch & 128 && ch & 64 && ch & 32 && ch & 16)
		return 4;
	else if (ch & 128 && ch & 64 && ch & 32)
		return 3;
	else if (ch & 128 && ch & 64)
		return 2;
	else return 1;
}