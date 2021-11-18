#pragma once
#include <iostream>
#include <vector>
#define ABSOLUTE_ERROR 10e-2
#define MAX_TIME 1800
using namespace std;
class engine {
public:
	double I = 0;
	double overheatTemperature = 0;
	double Hm = 0;
	double Hv = 0;
	double C = 0;
	vector<int> startM;
	vector<int> startV;
	double getVc(double ambientTemperature, double engineTemperature)
	{
		return C * (ambientTemperature - engineTemperature);
	}

	double getVh()
	{
		return M * Hm + V * V * Hv;
	}
	double M = 0;
	double V = 0;
};
void input(engine& eng1, double nI, double noverT, double nHm, double nHv, double nC, vector<int> nstartM, vector<int> nstartV, double nM, double nV);
int Stand(engine& eng1, double ambienttemp);