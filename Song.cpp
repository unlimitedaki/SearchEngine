#include "stdafx.h"
#include "Song.h"
/*强行初始化idf,不初始化他不让我用我能怎么办,一会用的时候删了
pair<string, double> inits[]{
	make_pair("init",-1),
};*/
//算了还是普通地初始化吧
map<string, double> Song::idf = map<string, double>();
Song::Song()
{
}

Song::Song(string src,int Q)
{

	if (Q == 0) {
		int len = src.find(".txt") - src.find("/") - 1;
		int begin = src.find("/") + 1;
		name = src.substr(begin, len);
		string str;
		ifstream datain(src);
		for (int i = 0; i < 5; i++) {
			getline(datain, str);
		}
		getline(datain, filedata);
		size_t po = filedata.find("text_token:") + 11;
		len = filedata.end() - po - filedata.begin() - 1;
		filedata = filedata.substr(po, len);
		datain.close();

		//计算tf idf（初始值）
		
	}
	else {
		name = "query";
		filedata = src;
	}
	wordDivision();
	Tf_idf(Q);
	
}

vector<string> Song::wordDivision()
{
	stringstream ss(filedata);
	string temp;
	while (ss >> temp) {
		words.push_back(temp);
	}
	return words;
}





void Song::Tf_idf(int Q)
{
	int s = words.size();
	for (int i = 0; i < s; i++) {
		if (tf.find(words[i]) != tf.end())continue;
		tf[words[i]] = caltf(words[i], words, s);
		
	}
	if (Q == 0) {//文件时计算，此时的idf暂存每个词出现的文档数量，文件全部完成之后再计算
		map<string, double>::iterator iter;
		for (iter = tf.begin(); iter != tf.end(); iter++) {
			if (idf.find(iter->first) == idf.end())idf[iter->first] = 1;
			else idf[iter->first] += 1;
		}
		
	}
}




double Song::Matching(Song s1, Song src)
{

	return 0.0;
}

Song::~Song()
{
}

void Song::calmod()
{
	double mod=0;
	map<string, double>::iterator iter;
	for (iter = tf_idf.begin(); iter != tf_idf.end(); iter++) {
		mod += iter->second*iter->second;
	}
	mod = sqrt((double)mod);
	for (iter = tf_idf.begin(); iter != tf_idf.end(); iter++) {
		iter->second /= mod;
	}
}

vector<string> Song::GetData()
{
	return words;
}


double Song::caltf(const string target, vector<string>& data, int size)
{
	int count = 0;
	for (unsigned int i = 0; i < data.size(); i++) {
		if (data[i] == target)count++;
	}
	return count / (double)size;
}

void Song::Caltf_idf()
{
	//double ti;//short for tf_idf
	map<string, double>::iterator iter;

	for (iter = tf.begin(); iter != tf.end(); iter++) {
		tf_idf[iter->first] = iter->second*idf[iter->first];
	}
}


double Similarity(Song s1, Song s2)
{
	double divisor1=0,divisor2=0,dividend=0;
	double sim = 0;
	map<string, double>::iterator iter;
	for (iter = s1.tf_idf.begin(); iter != s1.tf_idf.end();iter++) {
		sim += (iter->second*s2.tf_idf[iter->first]);
	}
	
	return sim;
}

double CalUnigram(Song query, Song src)
{
	double res = 1;
	map<string, double>::iterator iter;
	for (iter = query.tf.begin(); iter != query.tf.end(); iter++) {
		if (src.tf.find(iter->first) != src.tf.end()) {
			res *= src.tf[iter->first] + 1;//+1平滑
		}
		
	}
	return res;
}

double Similarity(vector<double> query, vector<double> src)
{
	double divisor1 = 0, divisor2 = 0, dividend = 0;
	for (unsigned int i = 0; i < query.size(); i++) {
		divisor1 += query[i] * query[i];
		divisor2 += src[i] * src[i];
		dividend += src[i] * query[i];
	}
	if (sqrt((double)divisor1)*sqrt((double)divisor2) == 0)return 0;
	else {
		double sim = dividend / (sqrt((double)divisor1)*sqrt((double)divisor2));
		return sim;
	}
		
}




