#include<iostream>
#include<list>
#include<string>
#include<vector>
#include<fstream>
//#include"Song.h"
#include<io.h>
#include<cmath>
#include<algorithm>

#include"NLPIR_Query_LiYeqiu.h"

using namespace std;
class threshold
{
public:
	threshold();
	static double deviate(vector<pair<double, string> > simm);

	static double pairwise(vector<pair<double, string> > simm);

	static double window(vector<pair<double, string> > simm, int k);

	static double fakesigmoid(vector<pair<double, string> > simm);

	static double matchingSigmoid(vector<pair<double, string> > simm);

	~threshold();
};

double sigmoid(double x);
double Max(vector<double> src,int &pos);

double derivation(int length,double x);