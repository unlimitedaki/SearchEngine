/*
��ÿһ������ļ��н�ÿһ���ʶ���ֿ�����ÿһ���ʶ���һ��tf��idf
tf-idf�ȱȽϵ�ʱ������ɣ�ÿ��������鷳
*/

#include<iostream>
#include<list>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<map>
#include"NLPIR.h"

using namespace std;

class Song{
private:
	
	
	vector<string> words;
	string filedata;
public:
	map <string, double> tf_idf;//���ڷ���
	static map<string, double> idf;
	map < string, double > tf;
	string name;//���ڷ���
	Song();
	//Song(string filename);
	Song(string src, int Q = 0);//1 for query��0 for lrc file

	//5-15
	vector<string> wordDivision();
	void Tf_idf(int Q);
	static double caltf(const string target, vector<string> &data, int size);
	void Caltf_idf();












	
	
	friend double Similarity( Song s1,  Song s2);

	friend double CalUnigram(Song query, Song src);

	friend double Similarity(vector<double> query, vector<double> src);
	
	static double Matching(Song s1, Song src);

	~Song();

	void calmod();

	vector<string> GetData();
};
