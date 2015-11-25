#include "Government.h"
#include "MVD.h"
#include <fstream>

using namespace std;

int TSOP(double attackLvl, double defenceLvl);

MVD::MVD(Government *its)
{
    this->its = its;
	resultOfSearching = false;
}

int MVD::suppressRebellion(Government &its)
{
	if (its.getMoney() >= COST_OF_SUPRESS_REBELLION)
	{
        if (its.isInRebellion)
        {
            its.outCodes += "203 ";
            if (its.getHappiness() < 50)
            its.setHappiness(50);
        }
        else
        {
            its.outCodes += "204 ";
            its.setHappiness(its.getHappiness() - DECREASE_HAPPINESS_AFTER_SUPRESS);
        }

		its.setMoney(its.getMoney() - COST_OF_SUPRESS_REBELLION);
        its.isInRebellion = false;
        its.stepOfRebellion = 0;

        return 1;
	}
    return 0;
}

int MVD::checkVerbed(Government &its)
{
    int answer = 0;
	if (its.getMoney() >= COST_OF_CHECK_VERBED)
	{
		its.setMoney(its.getMoney() - COST_OF_CHECK_VERBED);
		for (int i = 0; i < COUNT_OF_MINISTER;i++)
			if (its.ministers[i]->getWhooseRecruit() != -1)
            {
                its.outCodes+= "214 ";
                return 0;
                break;
            }
		resultOfSearching = answer;
	}
    return 1;
}

int MVD::disverbed(Government &its, Government &attack, int numberOfMinister)
{
    int luck = 0;
    this->numberOfEnemy = attack.getNumber();

	if (its.getMoney() >= COST_OF_DISVERBED)
	{
		its.setMoney(its.getMoney() - COST_OF_DISVERBED);
        luck = TSOP(getLvl(), attack.ministers[4]->getTSOPlvl(5));
        if (luck > 0)
		{
            lvl++;
            Command fr;
            fr.args[0] = 5;
            fr.args[1] = 3;
            fr.args[2] = its.getNumber();
            fr.args[3] = numberOfMinister+1;
            attack.doMIDCommand(fr);
            return luck;
		}
	}
    return luck;
}

void MVD::getInformation()
{
}
