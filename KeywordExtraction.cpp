#include "stdafx.h"
#include "KeywordExtraction.h"


map<string, double> KeywordExtraction::keywordExtraction(vector<string> data)
{
	map<string, double> prres;
	map<string, map<string, double>> links;
	map<string, double> linkouts;

	//生成所有的关系
	list<string> sentence;
	for (unsigned int i = 0; i < data.size(); i++) {
		
		if(data[i]=="。/w"){
			KeywordExtraction::SingleSentence(sentence,links,linkouts);
			sentence.clear();
			continue;
		}
		//去掉所有标点符号 
		if (data[i].find("/w") != -1)continue;
		sentence.push_back(data[i]);
	}

	//两层pagerank
	for (int i = 0; i < 2; i++) {
		pageRank(prres, links, linkouts);
	}
	

	
	return prres;
}


void KeywordExtraction::SingleSentence(list<string> data, 
	map<string, map<string, double>> &links, map<string, double> &linkouts)
{	/*入参：每一句话的字符串向量，链接关系表
	直接修改links*/

	//先去重,将同一个句子中重复的词视为出现一次
	data.unique();
	//统计关系
	list<string>::iterator iterx, itery;
	for (iterx = data.begin(); iterx != data.end(); iterx++) {
		for (itery = data.begin(); itery != data.end(); itery++) {
			if (links.find(*iterx) != links.end()) {
				links[*iterx][*itery] = 1;
			}
			else links[*iterx][*itery]++;
			if (linkouts.find(*iterx) == linkouts.end()) {
				linkouts[*iterx] = 1;
			}
			else linkouts[*iterx] += 1;
		}
	}
	return ;
}

void KeywordExtraction::pageRank(map<string, double> &prres, 
	map<string, map<string, double>> &links, map<string, double> &linkouts)
{
	//数据已经 
	//map<string, double> linkouts;
	map<string, map<string, double>>::iterator outr;
	//根据关系数进行赋值
	map<string, double> tempres;//用tempres存放结果
	map<string, double>::iterator iter;
	double init = 1;
	for (outr = links.begin(); outr != links.end(); outr++) {
		if (prres.find(outr->first) == prres.end())prres[outr->first] = init;//首次计算时，将其初始化为1
		map<string, double>::iterator inner;
		string k = outr->first;
		for (inner = outr->second.begin(); inner != outr->second.end(); inner++) {
			tempres[inner->first] += prres[outr->first] / linkouts[outr->first] * inner->second;
		}
	}
	prres = tempres;
	return;
	
}

KeywordExtraction::KeywordExtraction()
{
}


KeywordExtraction::~KeywordExtraction()
{
}