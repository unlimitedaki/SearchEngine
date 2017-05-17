#include "stdafx.h"
#include "threshold.h"


threshold::threshold()
{
}

double threshold::deviate(vector<pair<double, string>> simm)
{
	vector<double> thresholds;
	for (unsigned int i = 0; i < simm.size()-2; i++) {
		double th = (simm[i].first - simm[i + 2].first) / 2;
		thresholds.push_back(th);
	}
	int pos;
	double m = Max(thresholds,pos);
	pos ++;
	cout << "max : " << m << endl << "pos : " << pos << endl;
	return m;
}

double threshold::pairwise(vector<pair<double, string>> simm)
{
	vector<double> thresholds;
	for (unsigned int i = 0; i < simm.size() - 1; i++) {
		double th = simm[i].first - simm[i+1].first;
		thresholds.push_back(th);
	}
	int pos;
	double m = Max(thresholds, pos);
	pos ++;
	cout << "max : " << m << endl << "pos : " << pos << endl;
	return m;
}

double threshold::window(vector<pair<double, string>> simm ,int k)
{
	vector<double> thresholds;
	for (unsigned int i = 0; i < simm.size() - k; i++) {
		double th = simm[i].first - simm[i + k].first;
		
		thresholds.push_back(th);
	}

	int pos;
	double m = Max(thresholds, pos);
	pos++;
	cout << "max : " << m << endl << "pos : " << pos << endl;
	return m;

	return 0.0;
}

double threshold::fakesigmoid(vector<pair<double, string>> simm)
{
	int length = simm.size(), pos = 0;
	double max = simm[1].first, min = simm[length - 1].first;
	double mean = (max - min) / 2 + min;
	double mindiff = mean;

	for (int i = 0; i < length; i++) {
		double diff = fabs(simm[i].first - mean);
		if (diff < mindiff)
		{
			mindiff = diff;
			pos = i;
		}
	}     
	pos++;
	cout << "max : " << mindiff << endl << "pos : " << pos << endl;

	return mindiff;
}

double threshold::matchingSigmoid(vector<pair<double, string>> simm)
{
	vector<pair<double,double>> matchings;//<a,ma>
	int length = simm.size();
	double a;  // x ~~(0,12000) /1000
	//拟合函数 f(x) = a·sigmoid(1/1000 * (x - length/2))^2;
	for (a = 1.0; a < 2; a += 0.0001) {
		double sum = 0;
		for (int i = 0; i < length; i++) {
			double sig = sigmoid(1 / (double)1000 * (i - length / 2));
			sum += fabs(a*sig*sig - simm[i].first);
		}
		sum /= (double)length;
		matchings.push_back(make_pair(a, sum));
	}
	//找到拟合度最高的函数
	double  bestMatchinga = -1;
	double bestMatching = 1000;
	for (unsigned int i = 0; i < matchings.size(); i++) {
		if (bestMatching > matchings[i].second) {
			bestMatchinga = matchings[i].first;
			bestMatching = matchings[i].second;
		}
	}

	//求导取最大斜率；
	double threshold_sig = 0;
	double max = 0;
	//S'(X) = S(x)(1-S(x));
	for (int i = 0; i < length; i++) {
		double sX = 2 * bestMatchinga *
			sigmoid(1 / (double)1000 * (i - length / 2)) * derivation(length, i);
		
		if (sX > threshold_sig) {
			threshold_sig = sX;
			max = simm[i].first;
		}
		
	}
	//取数
	int count;
	for (count = 0; count < length; count++) {
		if (simm[count].first < max) break;
	}
	
	cout << "max : " << max << endl << "pos : " << count << endl;
	return threshold_sig;
}


threshold::~threshold()
{
}

double sigmoid(double x)
{	
	//e double exp(double)
	double sig;
	sig = 1 - 1 / (1 + exp(0-x));
	return sig;
}

double Max(vector<double> src, int &pos)
{
	double max = 0;
	unsigned int i = 0;
	for (; i < src.size(); i++) {
		if (src[i] > max) {
			max = src[i];
			pos = i + 1;
		}
	}
	//pos = i;
	return max;
}

double derivation(int length,double x)
{
	double sig = sigmoid(1 / (double)1000 * (x - length / 2));
	return (double)1/1000*sig*(1 - sig);
}
