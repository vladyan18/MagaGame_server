#include "Government.h"
#include "HealthMinister.h"
#include <fstream>
#include <cmath>
#include <qdebug.h>

using namespace std;

int TSOP(double attackLvl, double defenceLvl);

void HealthMinister::setVirus(bool newVirus, int numOfTeam) { virus[numOfTeam-1] = newVirus; }
bool HealthMinister::getVirus(int numOfTeam) { return virus[numOfTeam-1]; }

void HealthMinister::setStepOfVirus(int newStep, int numOfTeam) { stepOfVirus[numOfTeam-1] = newStep; }
int HealthMinister::getStepOfVirus(int numOfTeam) { return stepOfVirus[numOfTeam-1]; }

HealthMinister::HealthMinister(Government *its, int countOfTeam)
{

    this->its = its;
    this->countOfTeams = its->getCountOfTeam();

	virus = new bool[countOfTeam];
	stepOfVirus = new int[countOfTeam];

	for (int i = 0;i < countOfTeam;i++)
	{
		virus[i] = false;
        stepOfVirus[i] = 1;
	}
}

int HealthMinister::infectingVirus(Government &its, Government &attack)
{
    int luck = 0;
    this->numberOfEnemy = attack.getNumber();

	if (its.getMoney() >= COST_OF_INFECTING)
	{
		its.setMoney(its.getMoney() - COST_OF_INFECTING);
        luck = TSOP(getLvl(), attack.ministers[8]->getTSOPlvl(9));
        if (luck > 0)
		{
            HealthMinister *attackHealthMinister = (HealthMinister*)(attack.ministers[8]);
            attackHealthMinister->setVirus(true, its.getNumber());
            attackHealthMinister->setStepOfVirus(1, its.getNumber());
            attack.outCodes += "208 ";
			lvl++;
            return luck;
		}
	}
    return luck;
}

int HealthMinister::vaccine(Government &its, Government &attack)
{
    int luck = 0;
    this->numberOfEnemy = attack.getNumber();

	if (its.getMoney() >= COST_OF_VACCINE)
	{
		its.setMoney(its.getMoney() - COST_OF_VACCINE);
        if (virus[attack.getNumber() - 1])
        {
            luck = TSOP(getLvl(), attack.ministers[8]->getTSOPlvl(9));
            if (luck > 0)
			{
                virus[attack.getNumber() - 1 ] = false;
                stepOfVirus[attack.getNumber() - 1] = 1;
				lvl++;
                return luck;
			}
        } else {its.outCodes += "209 ";}
	}
    return luck;
}

void HealthMinister::getInformation(int countOfTeam)
{
}

void HealthMinister::doHarmFromViruses()
{

    for (int i = 0; i< this->countOfTeams; i++)
    {
        if (virus[i])
        {

            its->setHappiness(its->getHappiness() - pow(2,stepOfVirus[i]) );
            stepOfVirus[i]++;
        }
    }
}
