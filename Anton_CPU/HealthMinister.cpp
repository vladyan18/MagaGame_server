#include "Government.h"
#include "HealthMinister.h"
#include <fstream>

using namespace std;

bool TSOP(double attackLvl, double defenceLvl);

void HealthMinister::setVirus(bool newVirus, int numOfTeam) { virus[numOfTeam] = newVirus; }
bool HealthMinister::getVirus(int numOfTeam) { return virus[numOfTeam]; }

void HealthMinister::setStepOfVirus(int newStep, int numOfTeam) { stepOfVirus[numOfTeam] = newStep; }
int HealthMinister::getStepOfVirus(int numOfTeam) { return stepOfVirus[numOfTeam]; }

HealthMinister::HealthMinister(int countOfTeam)
{
	virus = new bool[countOfTeam];
	stepOfVirus = new int[countOfTeam];

	for (int i = 0;i < countOfTeam;i++)
	{
		virus[i] = false;
		stepOfVirus[i] = 0;
	}
}

int HealthMinister::infectingVirus(Government &its, Government &attack)
{
	if (its.getMoney() >= COST_OF_INFECTING)
	{
		its.setMoney(its.getMoney() - COST_OF_INFECTING);
		if (TSOP(getTSOPlvl(), attack.ministers[7]->getTSOPlvl()))
		{
			HealthMinister *attackHealthMinister = (HealthMinister*)(its.ministers[7]);
			attackHealthMinister->setVirus(true, its.getNumber());
			lvl++;
		}
	}
}

int HealthMinister::vaccine(Government &its, Government &attack)
{
	if (its.getMoney() >= COST_OF_VACCINE)
	{
		its.setMoney(its.getMoney() - COST_OF_VACCINE);
		if (virus[attack.getNumber()])
			if (TSOP(getTSOPlvl(), attack.ministers[7]->getTSOPlvl()))
			{
				virus[attack.getNumber()] = false;
				stepOfVirus[attack.getNumber()] = 0;
				lvl++;
			}
	}
}

void HealthMinister::getInformation(int countOfTeam)
{
	ofstream fout("Civ.out", ios_base::app);
	fout << "У министра по здравоохранению " << lvl << " lvl" << endl;
	int countOfVirus = 0;
	for (int i = 0;i < countOfTeam; i++)
		if (virus[i])
			countOfVirus++;
	if (countOfVirus > 0)
		fout << "Количество вирусов в вашем гос-ве: " << countOfVirus;

	fout << "Уровень вирусов в вашей стране: ";
	for (int i = 0;i < countOfTeam; i++)
		if (virus[i])
			fout << stepOfVirus[i] << " ";
	fout << endl;

	fout.close();
}
