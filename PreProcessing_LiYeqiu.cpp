#include "stdafx.h"
#include "PreProcessing_LiYeqiu.h"

bool cmp(const pair<double, string> &p1, const pair<double, string> &p2) {
	return p1.first > p2.first;
}

vector<Song> PreProcessing_LiYeqiu::OpenAllFiles(char * dir)
{
	//获取所有的文件名
	vector<string> songNames;
	vector<Song> songs;
	ifstream fns("retrieve-data/filenames.txt");
	string temp;
	while (getline(fns, temp)) {
		stringstream ss(temp);
		ss >> temp;//日期
		ss >> temp;//时间
		ss >> temp;//大小
		ss >> temp;//文件名
		songNames.push_back(temp);
		Song tempsong("retrieve-data/data/" + temp);
		songs.push_back(tempsong);
	}
	/*_finddata_t fileDir;
	
	long lfDir;
	if ((lfDir = _findfirst(dir, &fileDir)) == -1l) cout << "Empty Folder" << endl;
	else {
		cout << "filenames :" << endl;
		do {
			cout << '\r' << fileDir.name;
			songNames.push_back(fileDir.name);
		} while (_findnext(lfDir, &fileDir) == 0);
	}
	cout << endl; */
	//将文件一个个打开并使用
	/*for (unsigned int i = 0; i < songNames.size(); i++) {
		Song tempsong("retrieve-data/data/"+songNames[i]);
		songs.push_back(tempsong);
	}*/
	for (map<string, double>::iterator iter = Song::idf.begin(); iter != Song::idf.end(); iter++) {
		iter->second = log10(Song::idf.size() / (iter->second+1));
	}
	return songs;
}

void PreProcessing_LiYeqiu::ReserveIndex(vector<Song> & Songs, ofstream &out)
{
	//建立倒排索引表
	map<string, vector<int>> R_index;
	string temp;
	for (unsigned int i = 0; i < Songs.size(); i++) {
		vector<string> words = Songs[i].wordDivision();
		for (unsigned int j = 0; j < words.size(); j++) {
			if (words[j].find("/w") != -1 || words[j].find("/nx") != -1)continue;
			int e = R_index[words[j]].size() - 1;
			if (e < 0 || R_index[words[j]][e] != i) {
				R_index[words[j]].push_back(i);
			}
		}
	}
	cout << endl;
	//写入文件;
	map<string, vector<int>>::iterator iter;
	for (iter = R_index.begin(); iter != R_index.end(); iter++) {
		out << iter->first << endl;
		for (unsigned int i = 0; i < iter->second.size(); i++) {
			out << iter->second[i] << "\t";
		}
		out << endl << endl;
	}
	out.close();
}

//输出格式 下标\n关键词\t关键词\t...\n
void PreProcessing_LiYeqiu::Keyword(vector<Song> & Songs, string filename) {
	ofstream out(filename);
	for (unsigned int i = 0; i < Songs.size(); i++){
		out << i<< endl;
		cout << i << endl;
		Songs[i].Caltf_idf();
		//将map-tf_idf装入vector排序
		vector<pair<double, string>> tf_idf_vec;
		map<string, double>::iterator iter;
		for (iter = Songs[i].tf_idf.begin(); iter != Songs[i].tf_idf.end(); iter++) {
			if(iter->first.find("/w") != -1 || iter->first.find("/nx") != -1)continue;//去除标点符号以及不明含义的符号组合)
			tf_idf_vec.push_back(make_pair(iter->second, iter->first));
		}
		sort(tf_idf_vec.begin(), tf_idf_vec.end(), cmp);

		for (unsigned int j = 0; j < 30 && j < tf_idf_vec.size(); j++) {
			out << tf_idf_vec[j].second << "\t";
		}
		out << endl;
	}
	out.close();
}

map<int, vector<string>> PreProcessing_LiYeqiu::readKeyword(string filename)
{
	fstream fin(filename);
	map<int, vector<string>> keywords;
	string line;
	while (getline(fin, line)) {
		vector<string> temp;
		string data;
		stringstream ss(line);
		int num; ss >> num;
		
		getline(fin, data);
		stringstream sd(data);
		string word;
		while (sd >> word) {
			temp.push_back(word);
		}
		keywords[num] = temp;
	}
	return keywords;
}

set<int> PreProcessing_LiYeqiu::IndexSetting(string query, map<string, 
	vector<int>>& R_index,map<int,vector<string>> &keyword)
{
	set<int> includeIndex;
	stringstream ss(query);
	string word;
	while (ss >> word) {
		if (R_index.find(word) != R_index.end()) {
			vector<int>::iterator iter;
			for (iter = R_index[word].begin(); iter != R_index[word].end();iter++) {
				if (find(keyword[*iter].begin(), keyword[*iter].end(), word) == keyword[*iter].end())continue;
				includeIndex.insert(*iter);
			}
		}
	}
	return includeIndex;
}

map<string, vector<int>> PreProcessing_LiYeqiu::readIndex(string filename)
{
	ifstream fin(filename);
	map<string, vector<int>> Rindex;

	string line;
	while (getline(fin, line)) {
		vector<int> temp;
		string fileindexs;
		getline(fin, fileindexs);
		stringstream ss(fileindexs);
		int fileindex;
		while (ss >> fileindex) {
			temp.push_back(fileindex);
		}
		getline(fin, fileindexs);//此行为空行
		Rindex[line] = temp;
	}
	return Rindex;
}

vector<string> PreProcessing_LiYeqiu::getQuerys(string filename)
{
	vector<string> res;
	ifstream querys(filename);
	string str;
	while (getline(querys, str)) {
		res.push_back(str);
	}
	return res;
}


void PreProcessing_LiYeqiu::Query_Compare(string query, vector<Song> & Songs, ofstream &out, set<int> &index)
{
	vector<pair<double,string> > simm;
	Song qsong(query,1);
	qsong.Caltf_idf();//

	set<int>::iterator iter;
	for (iter = index.begin(); iter != index.end(); iter++) {
		double res = Similarity(qsong, Songs[*iter]);
		simm.push_back(make_pair(res, Songs[*iter].name));
	}

	sort(simm.begin(), simm.end(), cmp);
	out << query << endl << endl;
	for (unsigned int i = 0; i < 10 && i<simm.size() ; i++) {
		out << simm[i].first<<"\t"<<simm[i].second << endl;
	}
	out << "@@@" << endl;
}

//Unigram model
vector<pair<double,string>> PreProcessing_LiYeqiu::Unigram(string query, vector<Song>& Songs
	, ofstream &out, set<int> &index)
{
	Song qsong(query,1);
	vector<pair<double, string>> unigram_re;
	set<int>::iterator iter;
	for (iter = index.begin(); iter != index.end();iter++) {
		double res = CalUnigram(qsong, Songs[*iter]);
		unigram_re.push_back(make_pair(res, Songs[*iter].name));
	}
	out << query << endl << endl;
	sort(unigram_re.begin(), unigram_re.end(), cmp);
	for (unsigned int i = 0; i < 10 && i < unigram_re.size(); i++) {
		out << unigram_re[i].first << "\t" << unigram_re[i].second << endl;
	}
	out << "@@@" << endl;
	return unigram_re;
}

void PreProcessing_LiYeqiu::Matching(string query, vector<Song>& Songs, ofstream & out, set<int> &index)
{
	vector<pair<double, string>> simm;
	Song qsong(query, 1);
	double all_idf = 0;
	vector<string> words;
	stringstream ss(query);
	string word;
	while (ss >> word) {
		words.push_back(word);
		all_idf += Song::idf[word];
	}

	set<int>::iterator iter;
	for (iter = index.begin(); iter != index.end();iter++) {
		double this_idf = 0;
		for (unsigned int j = 0; j < words.size(); j++) {
			if (Songs[*iter].tf.find(words[j]) != Songs[*iter].tf.end() ){
				this_idf += Song::idf[words[j]];
			}
		}
		double this_sim = this_idf / all_idf;
		simm.push_back(make_pair(this_sim, Songs[*iter].name));
	}
	/*for (unsigned int i = 0; i < Songs.size(); i++) {
		double this_idf = 0;
		for (unsigned int j = 0; j < words.size(); j++){
			if (Songs[i].tf.find(words[j]) != Songs[i].tf.end()) {
				this_idf += Song::idf[words[j]];
			}
		}
		double this_sim = this_idf / all_idf;
		simm.push_back(make_pair(this_sim, Songs[i].name));
	}*/

	out << query << endl << endl;
	sort(simm.begin(), simm.end(), cmp);
	for (int i = 0; i < 10 && i < simm.size(); i++) {
		out << simm[i].first << "\t" << simm[i].second << endl;
	}
	out << "@@@" << endl;
}

//void PreProcessing_LiYeqiu::Compare(string s1, string s2, vector<Song> &songs)
//{
//	Song so1, so2;
//	bool flag = 0;
//	vector<Song>::iterator iter;
//	for (iter = songs.begin(); iter != songs.end(); iter++) {
//		if (iter->name == s1) {
//			so1 = *iter;
//			flag = 1;
//			break;
//		}
//	}
//	if (!flag) { cout << "can't find Song No.1" << endl; return; }
//	flag = 0;
//	for (iter = songs.begin(); iter != songs.end(); iter++) {
//		if (iter->name == s2) {
//			so2 = *iter;
//			flag = 1;
//			break;
//		}
//	}
//	if (!flag) { cout << "can't find Song No.2" << endl; return; }
//	cout << "Similarity of " << s1 << " and " << s2 <<
//		" is " << Similarity(so1, so2) << endl;
//	return;
//	
//}







//void PreProcessing_LiYeqiu::SongnamesUnigram(string query,ofstream &out)
//{
//	double lamda = 0.8;
//	vector < pair<double, string> > ptmd;// P(t|d) = λP(t|Md) + (1 - λ)P(t|Mc)
//	map<string,double> ptmc;
//	int allsize = 0;//为计算ptmc准备
//	vector<string> qwords;
//	vector<string> srcwords;
//	qwords = DivideWords(query);
//	list<pair<string, string> >::iterator iter;
//	vector < vector<double> > count;//count 行为歌名，列为查询分词
//
//	vector < string > names;
//	for (iter = cooked_data.begin(); iter != cooked_data.end(); iter++) {
//		double this_ptmd = 0;
//		vector < double > exs;
//		
//		srcwords = DivideWords(iter->first);
//		names.push_back(iter->first);
//		allsize += srcwords.size();
//		for (unsigned int i = 0; i < qwords.size(); i++) {
//			double ex = exist(qwords[i], iter->first);
//			if (ptmc.find(qwords[i]) != ptmc.end()) {
//				ptmc[qwords[i]] += (int)ex;
//			}
//			else ptmc[qwords[i]] = 1;
//			exs.push_back(ex / (double)srcwords.size());
//		}
//		count.push_back(exs);
//	}
//
//	map<string, double>::iterator iter2;
//	for (iter2 = ptmc.begin(); iter2 != ptmc.end(); iter2++) {
//		iter2->second /= allsize;
//	}
//	
//	for (int i = 0; i < count.size(); i++) {//every name
//		double this_ptmd=1;
//		for (unsigned int j = 0; j < count[i].size(); j++) {
//			this_ptmd *= lamda*count[i][j] + (1 - lamda)*ptmc[qwords[j]];
//		}
//		ptmd.push_back(make_pair(this_ptmd, names[i]));
//	}
//
//	sort(ptmd.begin(), ptmd.end(), cmp);
//	out << query << endl << endl;
//	for (int i = 0; i < 10 && i<ptmd.size(); i++) {
//		out <<ptmd[i].second << endl;
//	}
//	out << "@@@" << endl;
//}
//
//void PreProcessing_LiYeqiu::SongnameFuzzy(string query,ofstream &out)
//{
//	vector<pair<double, string> > fuzzyRes;
//	fuzzyRes = NLPIR_Query_LiYeqiu::Query(query,cooked_data);
//
//	sort(fuzzyRes.begin(), fuzzyRes.end(), cmp);
//
//	out << query << endl << endl;
//	for (int i = 0; i < fuzzyRes.size()&&i < 10; i++) {
//		if (fuzzyRes[i].first > 0.01) {
//			out << fuzzyRes[i].first << "\t" << fuzzyRes[i].second << endl;
//		}
//	}
//	out << "@@@" << endl;
//}



//void PreProcessing_LiYeqiu::BM25(string query, ofstream & out)
//{
//	vector<pair<double, string> > scores;
//	vector < vector<double> > R_qi_d;
//	double avgdl = 0;
//	vector<double> dl;
//	map < string, double > idf;
//	list<pair<string, string> >::iterator iter;
//	vector<string> qwords;
//	vector<string> srcwords;
//	vector<string> names;//names[i] 对应tf_idf[i]
//	qwords = DivideWords(query);
//	for (iter = cooked_data.begin(); iter != cooked_data.end(); iter++) {
//		vector<double> fis;
//
//		srcwords = DivideWords(iter->first);
//		avgdl += srcwords.size();
//		dl.push_back(srcwords.size());
//		names.push_back(iter->first);
//		for (int i = 0; i < qwords.size(); i++) {
//			double fi = exist(qwords[i], iter->first);
//			fis.push_back(fi);
//			if (fi != 0) {//idf暂存出现该词的文档数
//				if (idf.find(qwords[i]) != idf.end()) {
//					idf[qwords[i]] ++;
//				}
//				else idf[qwords[i]] = 1;
//			}
//		}
//		R_qi_d.push_back(fis);//暂存查询中每个词在文档中的出现次数
//	}
//	//计算R(qi,d)
//	avgdl /= R_qi_d.size();
//	for (unsigned int i =0 ;i<R_qi_d.size();i++) {
//		for (unsigned int j = 0; j < R_qi_d[i].size(); j++) {
//			R_qi_d[i][j] = (R_qi_d[i][j] * 3) / (R_qi_d[i][j] + 2 * (0.25 + 0.75*(dl[i] / avgdl)));
//			//R(qi,d) = (fi*(k1+1))/(fi + k1(1 - b + b * (dl/avgdl))) k1 = 2 , b = 0.75;
//		}
//	}
//
//
//	//重算idf BM25
//	map<string, double>::iterator iter2;
//	for (iter2 = idf.begin(); iter2 != idf.end(); iter2++) {
//		iter2->second = log10((double)(cooked_data.size()-iter2->second+0.5) / (iter2->second + 0.5));
//	}
//	//计算score
//	for (unsigned int i = 0; i < R_qi_d.size(); i++) {
//		double s = 0;
//		for (unsigned int j = 0; j < R_qi_d[i].size(); j++) {
//			s += idf[qwords[j]] * R_qi_d[i][j];
//		}
//		scores.push_back(make_pair(s, names[i]));
//	}
//
//	//输出
//	sort(scores.begin(), scores.end(), cmp);
//	out << query << endl << endl;
//	for (unsigned int i = 0; i < 10 && i<scores.size(); i++) {
//		out << scores[i].second << endl;
//	}
//	out << "@@@" << endl;
//}
//
//void PreProcessing_LiYeqiu::SongnameSim(string query, ofstream &out)
//{
//	vector<pair<double, string> > simm;
//	vector < vector<double> >tf_idf;
//	
//	map < string, double > idf;
//	list<pair<string, string> >::iterator iter;
//	vector<string> qwords;
//	vector<string> srcwords;
//	vector<string> names;//names[i] 对应tf_idf[i]
//	qwords = DivideWords(query);
//	for (iter = cooked_data.begin(); iter != cooked_data.end(); iter++) {
//		vector<double> tf;
//
//		srcwords = DivideWords(iter->first);
//		names.push_back(iter->first);
//		for (int i = 0; i < qwords.size(); i++) {
//			double ex = exist(qwords[i], iter->first)/(double)srcwords.size();
//			if (ex != 0) {//idf暂存出现该词的文档数
//				if (idf.find(qwords[i]) != idf.end()) {
//					idf[qwords[i]] ++;
//				}
//				else idf[qwords[i]] = 1;
//			}
//			tf.push_back(ex);
//		}
//		tf_idf.push_back(tf);
//	}
//
//	//重算idf
//	map<string, double>::iterator iter2;
//	for (iter2 = idf.begin(); iter2 != idf.end(); iter2++) {
//		iter2->second = log10((double)cooked_data.size()/(iter2->second + 1));
//	}
//
//	for (unsigned int i = 0; i < tf_idf.size(); i++) {
//		for (unsigned int  j = 0; j < tf_idf[i].size(); j++){
//			tf_idf[i][j] *= idf[qwords[j]];
//		}
//	}
//
//	//计算自身的tf idf
//	vector<double> selftfidf;
//	for (int i = 0; i < qwords.size(); i++) {
//		double ex = exist(qwords[i], query) / (double)srcwords.size();
//		selftfidf.push_back(ex);
//	}
//	for (unsigned int j = 0; j < qwords.size(); j++) {
//		selftfidf[j] *= idf[qwords[j]];
//	}
//
//	//求相似度
//	for (unsigned int i = 0; i < tf_idf.size(); i++) {
//		double this_sim = Similarity(selftfidf, tf_idf[i]);
//		simm.push_back(make_pair(this_sim, names[i]));
//	}
//
//	sort(simm.begin(), simm.end(), cmp);
//	out << query << endl << endl;
//	for (unsigned int i = 0; i < 10 && i<simm.size(); i++) {
//		out <<simm[i].second << endl;
//	}
//	out << "@@@" << endl;
//}



//void PreProcessing_LiYeqiu::Openfile(const string &filename) {
//	ifstream in(filename);
//	string line;
//	while (getline(in, line)) {
//		string song, singer;
//		song=line.substr(0,line.find("\t"));
//		line = line.substr(line.find("\t") + 1,line.size()-1);
//		singer = line.substr(0,line.find("\t"));
//		cooked_data.push_back(make_pair(song, singer));
//	}
//	in.close();
//	return;
//
//}
//
//
//
//void PreProcessing_LiYeqiu::RedReduction() {
//	cooked_data.sort();
//	cooked_data.unique(); 
//	return;
//}
//
//void PreProcessing_LiYeqiu::WriteFile(const string &filename) {
//	ofstream out(filename);
//	list<pair<string, string>>::iterator iter;
//
//	for (iter = cooked_data.begin(); iter != cooked_data.end(); iter++) {
//		out << iter->first << "\t" << iter->second << endl;
//	}
//
//	out.close();
//	return;
//}
//
//list<pair<string, string>>& PreProcessing_LiYeqiu::GetCookedData() {
//	return cooked_data;
//}