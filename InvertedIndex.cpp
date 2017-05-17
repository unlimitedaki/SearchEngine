#include "stdafx.h"
#include "InvertedIndex.h"




InvertedIndex::InvertedIndex(char * dir)
{
	//��ȡ���е��ļ���
	vector<string> srcfileNames;
	_finddata_t fileDir;

	long lfDir;
	if ((lfDir = _findfirst(dir, &fileDir)) == -1l) cout << "Empty Folder" << endl;
	else {
		//cout << "filenames :" << endl;
		do {
			//cout << '\r' << fileDir.name;
			srcfileNames.push_back(fileDir.name);
		} while (_findnext(lfDir, &fileDir) == 0);
	}
	createIndex(srcfileNames);
	//printIndex();
}

InvertedIndex::~InvertedIndex()
{
}

void InvertedIndex::createIndex(vector<string> &srcfileNames)
{

	for (unsigned int i = 0; i < srcfileNames.size(); i++) {
		//��������
		string filedata;
		string str;
		string filename;
		ifstream datain("retrieve-data/data/"+srcfileNames[i]);
		int len = srcfileNames[i].find(".txt") - srcfileNames[i].find("/") - 1;
		int begin = srcfileNames[i].find("/") + 1;

		/*if (i % 1000 == 0)*/cout << "\r" << i;

		filename = srcfileNames[i].substr(begin, len);
		while (getline(datain, str)) {
			filedata += str + '\n';
		}
		size_t po = filedata.find("text_token:") + 11;
		len = filedata.end() - po - filedata.begin() - 1;
		filedata = filedata.substr(po, len);
		datain.close();

		//������������
		string temp;
		stringstream ss(filedata);
		//��ȡ��
		while (ss >> temp) {
			if (temp.find("/w")!=-1 || temp.find("/nx") != -1)continue;//ȥ���������Լ���������ķ������
			int e = I_index[temp].size() - 1;

			if (e > 0 && I_index[temp][e] == i)
				continue;
			I_index[temp].push_back(i);
		}    
	}
}

void InvertedIndex::printIndex()
{
	ofstream fout("InvertedIndex.txt");
	map<string, vector<int>>::iterator iter;
	for (iter = I_index.begin(); iter != I_index.end(); iter++) {
		fout << iter->first << endl;
		for (unsigned int i = 0; i < iter->second.size(); i++) {
			fout << iter->second[i] << "\t";
		}
		fout << endl << endl;
	}
	fout.close();
}

map<string, vector<string>> InvertedIndex::readindex()
{
	ifstream fin("InvertedIndex.txt");
	map<string, vector<string>> Rindex;

	string line;
	while (getline(fin, line)) {
		vector<string> temp;
		string filenames;
		getline(fin, filenames);
		stringstream ss(line);
		string filename;
		while (ss >> filename) {
			temp.push_back(filename);
		}
		Rindex[line] = temp;
	}
	return Rindex;
}
