// SearchEngine_LiYeqiu.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"Evaluate_LiYeqiu.h"
#include"PreProcessing_LiYeqiu.h"
#include"QueryAcc.h"
#include"FuzzyQuery_LiYeqiu.h"
#include"NLPIR.h"
#include"NLPIR_Query_LiYeqiu.h"
#include"etc.h"
#include"threshold.h"
#include"KeywordExtraction.h"
#include"InvertedIndex.h"
//#include"Song.h"

//#pragma comment(lib, "NLPIR.lib")

using namespace std;


//matching vsm lm
//查询
//\n
//10个result
//@@@
int main()
{
	//PreProcessing_LiYeqiu pre;
	cout << "Preprocessing" << endl;
	cout << "Open files" << endl;
	vector<Song> src = PreProcessing_LiYeqiu::OpenAllFiles("retrieve-data/data/*.txt");
	/*ofstream indexout("InvertedIndex.txt");
	PreProcessing_LiYeqiu::ReserveIndex(src, indexout);
	PreProcessing_LiYeqiu::Keyword(src, "retrieve-data/keywords.txt");*/
	cout << " read Reverse Index and Keyword" << endl;
	map<int,vector<string>> keyword = PreProcessing_LiYeqiu::readKeyword("retrieve-data/keywords.txt");
	map<string, vector<int>> R_index = PreProcessing_LiYeqiu::readIndex("InvertedIndex.txt");
	cout << "Query" << endl;
	vector<string> querys = PreProcessing_LiYeqiu::getQuerys("query.token.txt");
	/*vector<set<int>> includeIndexs; 
	for (unsigned int i = 0; i < querys.size(); i++) {
		set<int> includeIndex = PreProcessing_LiYeqiu::IndexSetting(querys[i], R_index, keyword);
		includeIndexs.push_back(includeIndex);
	}*/
	int tb, te;
	//lm
	//ofstream lm("Aki/1527405091 LM-R_index.txt");
	//tb = clock();
	//for (unsigned int i = 1; i < querys.size(); i++) {
	//	set<int> includeIndex = PreProcessing_LiYeqiu::IndexSetting(querys[i], R_index, keyword);
	//	PreProcessing_LiYeqiu::Unigram(querys[i], src, lm, includeIndex);
	//}
	//te = clock();
	//cout << "lm\t" << te - tb << endl;
	//vsm
	/*ofstream vsm("Aki/1527405091 VSM-R_index.txt");

	for (unsigned int i = 0; i < src.size(); i++) {
		src[i].Caltf_idf();
		src[i].calmod();
	}
	tb = clock();
	for (unsigned int i = 0; i < querys.size(); i++) {
		set<int> includeIndex = PreProcessing_LiYeqiu::IndexSetting(querys[i], R_index,keyword);
		PreProcessing_LiYeqiu::Query_Compare(querys[i], src, vsm, includeIndex);
	}
	te = clock();
	cout << "vsm\t" << te - tb << endl;*/
	//matching
	ofstream matching("AKI/1527405091 matching-R_index.txt");
	tb = clock();
	for (unsigned int i = 0; i < querys.size(); i++) {
		set<int> includeIndex = PreProcessing_LiYeqiu::IndexSetting(querys[i], R_index, keyword);
		PreProcessing_LiYeqiu::Matching(querys[i], src, matching, includeIndex);
	}
	te = clock();
	cout << "matching\t" << te - tb << endl;
	return 0;
}
//需求改了，没你们什么事了

////倒排索引
//InvertedIndex II("retrieve-data/data/*.txt");
//II.printIndex();

//拿了一个文档试试关键词
////PreProcessing_LiYeqiu pre;
////vector<Song> src = PreProcessing_LiYeqiu::OpenAllFiles("retrieve-data/data/*.txt");

//Song s("retrieve-data/data/n458477593.txt");
//map<string, double> res = KeywordExtraction::keywordExtraction(s.GetData());
//map<double, string> fakesortedmap = fakemapsort(res);
//map<double,string>::iterator it;
//for (it = fakesortedmap.begin(); it != fakesortedmap.end();it++) {
//cout << it->second << "\t" << it->first << endl;
//}


//阈值估计 and 各模型结果输出
/*ifstream qu("retrieve-data/query.token.txt");
vector<string> querys;
string str;
while (getline(qu, str)) {
querys.push_back(str);
}*/
//PreProcessing_LiYeqiu pre;
//vector<Song> src = PreProcessing_LiYeqiu::OpenAllFiles("retrieve-data/data/*.txt");

/*拿了一个文档试试关键词
Song s("retrieve-data/data/n458477593.txt");
map<string, double> res = KeywordExtraction::keywordExtraction(s.GetData());
map<double, string> fakesortedmap = fakemapsort(res);
map<double,string>::iterator it;
for (it = fakesortedmap.begin(); it != fakesortedmap.end();it++) {
cout << it->second << "\t" << it->first << endl;
}*/

/*for (int i = 0; i < src.size(); i++) {
cout << "\r" << src[i].name;
src[i].Caltf_idf();
src[i].calmod();
}*/


/*PreProcessing_LiYeqiu::Query_Compare(querys[i], src, vsm);
PreProcessing_LiYeqiu::Matching(querys[i], src, matching);*/

/*
ofstream lm("Aki/1527405091 LM-file-threshold.txt");
ofstream vsm("Aki/1527405091 VSM-file.txt");
ofstream matching("AKI/1527405091 matching-file.txt");
vector<pair<double, string>> simm;
for (unsigned int i = 0; i < querys.size() && i < 20; i++) {
	cout << querys[i] << endl;
	simm = PreProcessing_LiYeqiu::Unigram(querys[i], src, lm);
	deleteMin(simm);
	threshold::deviate(simm);
	threshold::pairwise(simm);
	threshold::window(simm, 4);
	threshold::fakesigmoid(simm);
	threshold::matchingSigmoid(simm);
	PreProcessing_LiYeqiu::Query_Compare(querys[i], src, vsm);
	PreProcessing_LiYeqiu::Matching(querys[i], src, matching);
}


ofstream lm("Aki/1527405091 LM-file-threshold.txt");
ofstream vsm("Aki/1527405091 VSM-file.txt");
ofstream matching("AKI/1527405091 matching-file.txt");
time_t tb, te;
vector<pair<double, string>> simm;
for (unsigned int i = 0; i < querys.size() && i < 20; i++) {
cout << querys[i] << endl;
simm = PreProcessing_LiYeqiu::Unigram(querys[i], src, lm);
deleteMin(simm);
tb = clock();
threshold::deviate(simm);
te = clock();
cout << "deviate :" << te - tb;
tb = clock();
threshold::pairwise(simm);
te = clock();
cout << "deviate :" << te - tb;
tb = clock();
threshold::window(simm, 4);
te = clock();
cout << "window :" << te - tb;
tb = clock();
threshold::fakesigmoid(simm);
te = clock();
cout << "fakesigmoid :" << te - tb;
tb = clock();
threshold::matchingSigmoid(simm);
te = clock();
cout << "matchingSigmoid :" << te - tb;
*/


//vector<Song> songs;
//songs=PreProcessing_LiYeqiu::OpenAllFiles("result_Aki/*.txt");

//FuzzyQuery_LiYeqiu FQtest;
//NLPIR_Query_LiYeqiu Qtest;
//Qtest.Query(query, data);
//cout << FQtest.FuzzyQurey2( query , data ) << endl;

/*预处理
pre.Openfile("data_without_space.txt");
pre.RedReduction();
pre.WriteFile("../cooked_data.txt");*/


/*打乱query
RandomLines("../query.txt");
//三项测试
list<pair<string, string>> data;
vector<string> querys;
PreProcessing_LiYeqiu pre;
pre.Openfile("../cooked_data.txt");//直接读入已经去重的文件
querys = PreProcessing_LiYeqiu::getQuerys("../disordered_query.txt");
data = pre.GetCookedData();

//ofstream matching("Aki/1527405091 matching.txt");
//ofstream vsm("Aki/1527405091 VSM.txt");
//ofstream lm("Aki/1527405091 LM.txt");
ofstream bm("Aki/1527405091 bm25.txt");


for (unsigned int i = 0; i < querys.size() && i<10 ; i++) {
cout <<"Query : "<< querys[i] << endl;
cout << "---------------------------------------" << endl;
pre.SongnameFuzzy(querys[i],matching);
cout << "---------------------------------------" << endl;
pre.SongnameSim(querys[i],vsm);
pre.SongnamesUnigram(querys[i],lm);
pre.BM25(querys[i], bm);
}

向量空间模型测试代码（对歌词）
//Song song1("result_Aki/ALittleStory.txt");
string s1 = "ALittleStory", s2 = "Butter-Fly-tri.Version-", query;
Song q("None", 1);
PreProcessing_LiYeqiu::Compare(s1, s2,songs);
PreProcessing_LiYeqiu::Query_Compare("None", songs);

/*语言模型 unigram （歌词）
string query = "流星";
//PreProcessing_LiYeqiu::Unigram(query, songs);*/
/*语言模型 unigram 歌名*/
//PreProcessing_LiYeqiu pre;
//pre.Openfile("../cooked_data.txt");