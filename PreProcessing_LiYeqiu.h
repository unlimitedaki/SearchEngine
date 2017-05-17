#include<iostream>
#include<list>
#include<string>
#include<vector>
#include<fstream>
#include"Song.h"
#include<io.h>
#include<algorithm>
#include<set>
#include"NLPIR_Query_LiYeqiu.h"
using namespace std;

class PreProcessing_LiYeqiu
{
private:
	/*list<pair<string, string>> raw_data;
	list<pair<string, string>> cooked_data;*/
	map<string, double> idf;
	
public:
	//vector<Song> songs;
	static vector<Song> OpenAllFiles(char* dir);
	//建立倒排索引，读取倒排索引
	static void ReserveIndex(vector<Song> & Songs, ofstream &out);
	static set<int> IndexSetting(string query, map<string, vector<int>> & R_index,map<int,vector<string>> &keyword);
	static map<string, vector<int>> readIndex(string filename);
	//提取querys
	static vector<string> getQuerys(string filename);
	//生成关键词表（tf-idf），读取关键词表
	static void Keyword(vector<Song> & Songs,string filename);
	static map<int, vector<string>> readKeyword(string filename);
	//lM
	static vector<pair<double, string>> Unigram(string query, vector<Song>& Songs, ofstream &out,set<int> &index);

	static void Matching(string query, vector<Song>& Songs, ofstream &out, set<int> &index);

	void Openfile(const string &filename);
	static void Query_Compare(string query, vector<Song>& Songs, ofstream &out, set<int> &index);
	
	
	
	void RedReduction();
	list<pair<string, string>>& GetCookedData();
	void WriteFile(const string &filename);
	
	

	//

	static void Compare(string s1, string s2, vector<Song> &songs);

	

	
	//以上for歌词
	/* 歌名查询
	void SongnamesUnigram(string query,ofstream &out);

	void SongnameFuzzy(string query,ofstream &out);

	void SongnameSim(string query, ofstream &out);

	void BM25(string query, ofstream &out);*/
	
	

};

