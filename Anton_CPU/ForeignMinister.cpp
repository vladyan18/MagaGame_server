#include "Government.h"
#include "ForeignMinister.h"
#include <fstream>

using namespace std;

bool TSOP(double attackLvl, double defenceLvl);

ForeignMinister::ForeignMinister(){}

ForeignMinister::ForeignMinister(int countOfTeam)
{
	verbedList = new bool*[countOfTeam];
	for (int i = 0;i < countOfTeam;i++)
	{
		verbedList[i] = new bool[COUNT_OF_MINISTER];
		verbedList[i][10] = false;
	}
}

// доработать 
int ForeignMinister::sabotage(Government &its, Government &attack, int numOfMinister)
{
	if (its.getMoney() > COST_OF_SABOTAGE)
	{
		its.setMoney(its.getMoney() - COST_OF_SABOTAGE);
	}
}

int ForeignMinister::verb(Government &its, Government &attack, int numberOfMinister)
{
	if ((its.getMoney() >= COST_OF_VERB)&&(lvl>=VERB_LVL))
	{
		its.setMoney(its.getMoney() - COST_OF_VERB);
		if (TSOP(getTSOPlvl(), attack.ministers[numberOfMinister]->getTSOPlvl()))
		{
			lvl++;
			verbedList[attack.getNumber()][numberOfMinister] = true;
			attack.ministers[numberOfMinister]->setWhooseRecruit(its.getNumber());
		}
	}
}
//дописать
int ForeignMinister::reverb(Government &its, Government &attack, int numberOfMinister)
{
	verbedList[attack.getNumber()][numberOfMinister] = false;
	attack.ministers[numberOfMinister]->setWhooseRecruit(-1);
}
//дописать
int ForeignMinister::order() {}
//дописать
int ForeignMinister::kill(Government &its, Government &attack, int numberOfMinister)
{
	if ((its.getMoney() >= COST_OF_KILL))
	{
		its.setMoney(its.getMoney() - COST_OF_KILL);
		if (TSOP(getTSOPlvl(), attack.ministers[numberOfMinister]->getTSOPlvl()))
		{
			lvl++;
			attack.ministers[numberOfMinister]->setLvl(1);
		}
	}
}
//доделать
int ForeignMinister::track(Government &its, Government &attack, int numberOfMinister)
{
	if ((its.getMoney() >= COST_OF_TRACK))
	{
		its.setMoney(its.getMoney() - COST_OF_TRACK);
		if (TSOP(getTSOPlvl(), attack.ministers[numberOfMinister]->getTSOPlvl()))
		{
			lvl++;
		}
	}
}

void ForeignMinister::getInformation(int countOfTeam)
{
	ofstream fout("Civ.out", ios_base::app);
	fout << "У министра иностранных дел " << lvl << " lvl" << endl;
	fout.close();
}
