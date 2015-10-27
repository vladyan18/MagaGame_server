#include "Government.h"
#include "MinisterOfJustice.h"
#include <fstream>

using namespace std;

bool TSOP(double attackLvl, double defenceLvl);

int MinisterOfJustice::sue(Government &its, Government &attack, bool proof)
{
	if (its.getMoney() > COST_OF_SUE)
	{
		its.setMoney(its.getMoney() - COST_OF_SUE);
		if (proof)
			helpLvl++;
		if (TSOP(getTSOPlvl(), attack.ministers[5]->getTSOPlvl()))
		{
			lvl++;
			attack.setHappiness(attack.getHappiness() - DECREASE_HAPPINESS_BY_SUE);
		}
		else
		{
			its.setHappiness(its.getHappiness() - DECREASE_HAPPINESS_BY_SUE);
		}
	}
}

void MinisterOfJustice::getInformation()
{
	ofstream fout("Civ.out", ios_base::app);
	fout << "У министра юстиции " << lvl << " lvl" << endl;
	fout.close();
}
