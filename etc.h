#include<iostream>
#include<list>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<map>
#include"NLPIR.h"
#include<algorithm>


#include<time.h>
#include<windows.h>
#include<Mmsystem.h>
#pragma comment(lib,"Winmm.lib")

using namespace std;
void RandomLines(string filename);
void adjustRange(vector<pair<double, string>> &simm);
void deleteMin(vector<pair<double, string>> &simm);

map<double,string> fakemapsort(map<string, double> res);