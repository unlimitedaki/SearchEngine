#include "stdafx.h"
#include "Evaluate_LiYeqiu.h"


Evaluate_LiYeqiu::Evaluate_LiYeqiu(int co=-1, int o=-1, int ca=-1)
{
	correctOutput = co;
	output = o;
	correctAmount = ca;
}

double Evaluate_LiYeqiu::Precision() {
	if (output > 0) {
		return (double)correctOutput / (double)output;
	}
	else {
		cout << "illegal input" << endl;
		return -1;
	}
}


double Evaluate_LiYeqiu::Recall() {
	if (correctAmount > 0) {
		return (double)correctOutput / (double)correctAmount;
	}
	else {
		cout << "Illegal Input" << endl;
		return -1;
	}
}

double Evaluate_LiYeqiu::F() {
	if (correctAmount > 0 && output) {
		double P = Precision(), R = Recall();
		return (2*R*P) / (R+ P);
	}
	else {
		cout << "Illegal Input" << endl;
		return -1;
	}
}

Evaluate_LiYeqiu::~Evaluate_LiYeqiu()
{
}
