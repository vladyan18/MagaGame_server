#include "Government.h"
#include "MVD.h"
#include <fstream>

using namespace std;

bool TSOP(double attackLvl, double defenceLvl);

MVD::MVD()
{
	resultOfSearching = false;
}

int MVD::suppressRebellion(Government &its)
{
	if (its.getMoney() >= COST_OF_SUPRESS_REBELLION)
	{
        if (its.isInRebellion) {its.outCodes += "203 ";}
        else {its.outCodes += "204 ";}

		its.setMoney(its.getMoney() - COST_OF_SUPRESS_REBELLION);
        its.isInRebellion = false;
        its.setHappiness(its.getHappiness() - DECREASE_HAPPINESS_AFTER_SUPRESS);
	}
}

int MVD::checkVerbed(Government &its)
{
	if (its.getMoney() >= COST_OF_CHECK_VERBED)
	{
		its.setMoney(its.getMoney() - COST_OF_CHECK_VERBED);
		int answer = false;
		for (int i = 0; i < COUNT_OF_MINISTER;i++)
			if (its.ministers[i]->getWhooseRecruit() != -1)
				answer = true;
		resultOfSearching = answer;
	}
}
//правильно казывать входные данные через getWhooseRecruit!
int MVD::disverbed(Government &its, Government &attack, int numberOfMinister)
{
	if (its.getMoney() >= COST_OF_DISVERBED)
	{
		its.setMoney(its.getMoney() - COST_OF_DISVERBED);
		if (TSOP(getTSOPlvl(), attack.ministers[4]->getTSOPlvl()))
		{
			lvl++;
			its.ministers[numberOfMinister]->setWhooseRecruit(-1);
		}
	}
}

void MVD::getInformation()
{
	ofstream fout("Civ.out", ios_base::app);
	fout << "У министра внутренних дел " << lvl << " lvl" << endl;
	if (resultOfSearching)
		fout << "В вашем государстве есть завербованные министры" << endl;
	fout.close();
}
