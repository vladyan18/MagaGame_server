#include "Government.h"
#include "Defence.h"
#include <fstream>

using namespace std;

bool TSOP(double attackLvl, double defenceLvl);

int Defence::getNuclear() { return nuclear; }
int Defence::getMissleDefence() { return missileDefense; }
int Defence::getNuclearOnYou1(int NumOfTeam) { return nuclearOnYou1[NumOfTeam]; }
int Defence::getNuclearOnYou2(int NumOfTeam) { return nuclearOnYou2[NumOfTeam]; }

void Defence::setNuclear(int newNuclear) { nuclear = newNuclear; }
void Defence::setMissleDefence(int newMissleDefence) { missileDefense = newMissleDefence; }
void Defence::setNuclearOnYou1(int numOfTeam, int newNuclearOnYou1) { nuclearOnYou1[numOfTeam] = newNuclearOnYou1; }
void Defence::setNuclearOnYou2(int numOfTeam, int newNuclearOnYou2) { nuclearOnYou2[numOfTeam] = newNuclearOnYou2; }

Defence::Defence() {}

Defence::Defence(int countOfTeam)
{
	nuclear = 0;
	missileDefense = 0;
	nuclearOnYou2 = new int[countOfTeam];
	nuclearOnYou1 = new int[countOfTeam];
	for (int i = 0;i < countOfTeam;i++)
	{
		nuclearOnYou1[i] = 0;
		nuclearOnYou2[i] = 0;
	}
}

int Defence::IncreaseCountOfNuclear(Government &its, int countOfNuclear)
{
	for (int i = 0;i < countOfNuclear;i++)
		if ((its.getMoney() >= COST_OF_INCREASE_COUNT_OF_NUCLEAR) && (lvl >= NEEDED_LVL_FOR_NUCLEAR))
		{
			nuclear++;
			its.setMoney(its.getMoney() - COST_OF_INCREASE_COUNT_OF_NUCLEAR);
		}
}

int Defence::DecreaseCountOfNuclear(Government &its, int countOfNuclear)
{
	for (int i = 0;i < countOfNuclear;i++)
		if ((its.getMoney() >= COST_OF_DECREASE_COUNT_OF_NUCLEAR_OR_MISSLE) &&
			(lvl >= NEEDED_LVL_FOR_NUCLEAR) && nuclear>0)
		{
			nuclear--;
			its.setMoney(its.getMoney() - COST_OF_DECREASE_COUNT_OF_NUCLEAR_OR_MISSLE);
		}

}

int Defence::IncreaseCountOfMissleDefence(Government &its, int countOfMissle)
{
	for (int i = 0;i < countOfMissle;i++)
		if (its.getMoney() >= COST_OF_INCREASE_COUNT_OF_MISSLE)
		{
			missileDefense++;
			its.setMoney(its.getMoney() - COST_OF_INCREASE_COUNT_OF_MISSLE);
		}
}

int Defence::DecreaseCountOfMissleDefence(Government &its, int countOfMissle)
{
	for (int i = 0;i < countOfMissle;i++)
		if ((its.getMoney() >= COST_OF_DECREASE_COUNT_OF_NUCLEAR_OR_MISSLE) &&
			(missileDefense>0))
		{
			missileDefense--;
			its.setMoney(its.getMoney() - COST_OF_DECREASE_COUNT_OF_NUCLEAR_OR_MISSLE);
		}
}

int  Defence::NuclearStrike(Government &its, Government &attack, int countOfNuclear)
{
	nuclear -= countOfNuclear;
	Defence *attackDefence = (Defence*)(attack.ministers[2]);
	attackDefence->setNuclearOnYou2(its.getNumber(), countOfNuclear);
}

int Defence::shootDownNucler(Government &its, Government &attack, int countOfMissle)
{
	while (countOfMissle > 0)
	{
		countOfMissle--;
		if ((TSOP(attack.ministers[2]->getTSOPlvl(), lvl+helpLvl)) && ((nuclearOnYou1[attack.getNumber()] > 0)))
		{
			nuclearOnYou1[attack.getNumber()]--;
		}
	}
}

void Defence::getInformation(Government &its)
{
	ofstream fout("Civ.out", ios_base::app);
	fout << "У министра обороны " << lvl << " lvl" << endl;
	fout << "Ядерные ракеты := " << nuclear << endl;
	fout << "ПРО:= " << missileDefense << endl;

	for (int i = 0;i < its.getCountOfTeam();i++)
		if (nuclearOnYou2[i]>0)
			fout << "Государство №" << i + 1 << "запустило в вас" << nuclearOnYou2[i] << "ракет" << endl;
	fout.close();
}

int Defence::stopNuclear(Government &its, Government &attack, int countOfNuclear)
{
	Defence *attacked = (Defence*)(attack.ministers[2]);
	attacked->setNuclearOnYou1(its.getNumber(), attacked->getNuclearOnYou1(its.getNumber()) - countOfNuclear);
	if (attacked->getNuclearOnYou1(its.getNumber()) < 0)
		attacked->setNuclearOnYou1(its.getNumber(), 0);
}
//нуждается в доработке
int Defence::marinesAttack(Government &its, Government &attack)
{
	if (TSOP(getTSOPlvl(), attack.ministers[0]->getTSOPlvl() + attack.ministers[2]->getTSOPlvl()))
	{
		its.setMoney(its.getMoney() + attack.getMoney());
		Defence *attacked = (Defence*)(attack.ministers[2]);
		nuclear += attacked->getNuclear();
		missileDefense += attacked->getMissleDefence();
	}
}

int Defence::raid(Government &its, Government &attack)
{
	if (its.getMoney() > COST_OF_RAID)
	{
		its.setMoney(its.getMoney() - COST_OF_RAID);
		if (TSOP(getTSOPlvl(), attack.ministers[0]->getTSOPlvl()))
		{
			lvl++;
			if (attack.getMoney() >= RAID_MONEY)
			{
				attack.setMoney(attack.getMoney() - RAID_MONEY);
				its.setMoney(its.getMoney() + RAID_MONEY);
			}
			else
			{
				its.setMoney(its.getMoney() + attack.getMoney());
				attack.setMoney(0);
			}
		}
	}
}
