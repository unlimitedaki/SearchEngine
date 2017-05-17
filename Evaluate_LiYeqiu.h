#pragma once
#include<iostream>
using namespace std;
class Evaluate_LiYeqiu
{
	int correctOutput;
	int output;
	int correctAmount;
public:
	Evaluate_LiYeqiu(int co,int o,int ca);

	double Precision();
	double Recall();
	double F();

	~Evaluate_LiYeqiu();
};

