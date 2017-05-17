#include "stdafx.h"
#include "NLPIR_Query_LiYeqiu.h"
#include <algorithm>  

using namespace std;

vector<string> DivideWords(string s) {
	vector<string> words;
	if (!NLPIR_Init()) {
		cout << "NLPIR_Init() failed!" << endl;
		return vector<string>();
	}

	const char* buff = s.c_str();
	const char*	dres;
	string temps;
	dres = NLPIR_ParagraphProcess(buff, 0);//第二个参数为0，不返回词性
	stringstream ss(dres);
	while (ss >> temps) {
		words.push_back(temps);
		//cout << temps << endl;
	}

	return words;
}

NLPIR_Query_LiYeqiu::NLPIR_Query_LiYeqiu()
{
}


NLPIR_Query_LiYeqiu::~NLPIR_Query_LiYeqiu()
{
}


vector<pair<double, string> > NLPIR_Query_LiYeqiu::Query(const string buff, list<pair<string, string>> &data) {
	vector<pair<double, string> > res;
	list<pair<string, string>>::iterator iter;
	//size_t found;
	size_t count = 0;
	vector<string> dividedWords;
	
	string str;

	dividedWords = DivideWords(buff);

	for (iter = data.begin(); iter != data.end(); iter++) {
		int cnt = 0;
		str = iter->first;
		
		
		cnt = exist(dividedWords, str);

		res.push_back(make_pair(cnt / (double)dividedWords.size(), str));
	}

	return res;
}

/*string NLPIR_Query_LiYeqiu::divide(int &i, const char *str) {
	int j;
	string word = "";
	for ( j = i; str[j] != '/';j++){
		if (str[j] == ' ')continue;//过滤多余空格
		if (str[j] == '\0')break;
		word += str[j];
	}
	for (; str[j] != ' '&&str[j]!='\0'; j++);
	i = j;
	return word;
}*/
//这个函数计算出现次数(大小写不敏感)
int exist(vector<string> querys, string str) {
	int cnt = 0;
	transform(str.begin(), str.end(), str.begin(), ::tolower);
	for (int i = 0; i < querys.size(); i++) {

		transform(querys[i].begin(), querys[i].end(), querys[i].begin(), ::tolower);
		if (str.find(querys[i]) != -1) cnt++;
	}
	return cnt;
}

int exist(string query, string str)
{
	int cnt = 0;
	size_t found;
	transform(str.begin(), str.end(), str.begin(), ::tolower);

	transform(query.begin(), query.end(), query.begin(), ::tolower);
	while ((found = str.find(query) )!= -1) {
		str = str.substr(found + 1, str.size() - found - 1);
		cnt++;
	}
	return cnt;
}
