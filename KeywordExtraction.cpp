#include "stdafx.h"
#include "KeywordExtraction.h"


map<string, double> KeywordExtraction::keywordExtraction(vector<string> data)
{
	map<string, double> prres;
	map<string, map<string, double>> links;
	map<string, double> linkouts;

	//�������еĹ�ϵ
	list<string> sentence;
	for (unsigned int i = 0; i < data.size(); i++) {
		
		if(data[i]=="��/w"){
			KeywordExtraction::SingleSentence(sentence,links,linkouts);
			sentence.clear();
			continue;
		}
		//ȥ�����б����� 
		if (data[i].find("/w") != -1)continue;
		sentence.push_back(data[i]);
	}

	//����pagerank
	for (int i = 0; i < 2; i++) {
		pageRank(prres, links, linkouts);
	}
	

	
	return prres;
}


void KeywordExtraction::SingleSentence(list<string> data, 
	map<string, map<string, double>> &links, map<string, double> &linkouts)
{	/*��Σ�ÿһ�仰���ַ������������ӹ�ϵ��
	ֱ���޸�links*/

	//��ȥ��,��ͬһ���������ظ��Ĵ���Ϊ����һ��
	data.unique();
	//ͳ�ƹ�ϵ
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
	//�����Ѿ� 
	//map<string, double> linkouts;
	map<string, map<string, double>>::iterator outr;
	//���ݹ�ϵ�����и�ֵ
	map<string, double> tempres;//��tempres��Ž��
	map<string, double>::iterator iter;
	double init = 1;
	for (outr = links.begin(); outr != links.end(); outr++) {
		if (prres.find(outr->first) == prres.end())prres[outr->first] = init;//�״μ���ʱ�������ʼ��Ϊ1
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