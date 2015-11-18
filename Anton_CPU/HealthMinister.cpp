#include "Government.h"
#include "HealthMinister.h"
#include <fstream>
#include <cmath>
#include <qdebug.h>

using namespace std;

bool TSOP(double attackLvl, double defenceLvl);

void HealthMinister::setVirus(bool newVirus, int numOfTeam) { virus[numOfTeam-1] = newVirus; }
bool HealthMinister::getVirus(int numOfTeam) { return virus[numOfTeam-1]; }

void HealthMinister::setStepOfVirus(int newStep, int numOfTeam) { stepOfVirus[numOfTeam-1] = newStep; }
int HealthMinister::getStepOfVirus(int numOfTeam) { return stepOfVirus[numOfTeam-1]; }

HealthMinister::HealthMinister(Government *its, int countOfTeam)
{

    this->its = its;
    this->countOfTeams = its->getCountOfTeam();
    qDebug() << "MinHelDebug: " << QString::number(this->countOfTeams);
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
	if (its.getMoney() >= COST_OF_INFECTING)
	{
		its.setMoney(its.getMoney() - COST_OF_INFECTING);
        if (TSOP(getLvl(), attack.ministers[8]->getTSOPlvl(9)))
		{
            HealthMinister *attackHealthMinister = (HealthMinister*)(attack.ministers[8]);
            attackHealthMinister->setVirus(true, its.getNumber());
            attack.outCodes += "208 ";
			lvl++;
            return 1;
		}
	}
    return 0;
}

int HealthMinister::vaccine(Government &its, Government &attack)
{
	if (its.getMoney() >= COST_OF_VACCINE)
	{
		its.setMoney(its.getMoney() - COST_OF_VACCINE);
        if (virus[attack.getNumber() - 1])
        {
            if (TSOP(getLvl(), attack.ministers[8]->getTSOPlvl(9)))
			{
                virus[attack.getNumber() - 1 ] = false;
                stepOfVirus[attack.getNumber() - 1] = 1;
				lvl++;
                return 1;
			}
        } else {its.outCodes += "209 ";}
	}
    return 0;
}

void HealthMinister::getInformation(int countOfTeam)
{
}

void HealthMinister::doHarmFromViruses()
{
    qDebug() << "Проверка на вирусы: " << QString::number(countOfTeams);
    for (int i = 0; i< this->countOfTeams; i++)
    {
        qDebug() << virus[i] << "!";
        if (virus[i])
        {
            qDebug() << "Обнаружен вирус!";
            its->setHappiness(its->getHappiness() - pow(2,stepOfVirus[i]) );
            stepOfVirus[i]++;
        }
    }
}
