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
void input(engine& eng1, double nI, double noverT, double nHm, double nHv, double nC, vector<int> nstartM, vector<int> nstartV, double nM, double nV) {
	eng1.I = nI;
	eng1.overheatTemperature = noverT;
	eng1.Hm = nHm;
	eng1.Hv = nHv;
	eng1.C = nC;
	eng1.startM = nstartM;
	eng1.startV = nstartV;
	eng1.M = nM;
	eng1.V = nV;
}
int Stand(engine &eng1, double ambienttemp) {
	int ptime = 0;
	int numberMV = 0;
	eng1.M = eng1.startM[numberMV];
	eng1.V = eng1.startV[numberMV];
	double enginetemp = ambienttemp;
	double a = eng1.M * eng1.I;
	double eps = eng1.overheatTemperature - enginetemp;
	while (eps > ABSOLUTE_ERROR && ptime < MAX_TIME)
	{
		ptime++;
		eng1.V += a;
		if (numberMV < eng1.startM.size() - 2)
			numberMV += eng1.V < eng1.startV[numberMV + 1] ? 0 : 1;
		double up = (eng1.V - eng1.startV[numberMV]);
		double down = (eng1.startV[numberMV + 1] - eng1.startV[numberMV]);
		double factor = (eng1.startM[numberMV + 1] - eng1.startM[numberMV]);
		eng1.M = up / down * factor + eng1.startM[numberMV];

		enginetemp += eng1.getVc(ambienttemp, enginetemp) + eng1.getVh();

		a = eng1.M * eng1.I;

		eps = eng1.overheatTemperature - enginetemp;
	}
	return ptime;
}

int main() {
	engine eng1;
	double ambienttemp = 0.0;
	cin >> ambienttemp;
	input(eng1, 0.1, 110, 0.01, 0.0001, 0.1, { 20, 75, 100, 105, 75, 0 }, { 0, 75, 150, 200, 250, 300 }, 0, 0);
	//////////
	if (Stand(eng1, ambienttemp) == 1800) {
		cout << "The engine is not overheated";
	} else {
		cout << Stand(eng1, ambienttemp) << " sec";
	}
	return 0;
}
