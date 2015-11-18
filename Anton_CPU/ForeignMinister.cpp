#include "Government.h"
#include "ForeignMinister.h"
#include <fstream>

using namespace std;

bool TSOP(double attackLvl, double defenceLvl);

ForeignMinister::ForeignMinister(){}

ForeignMinister::ForeignMinister(Government *its, int countOfTeam)
{
    this->its = its;
    this->countOfTeam = countOfTeam;
	verbedList = new bool*[countOfTeam];
	for (int i = 0;i < countOfTeam;i++)
	{
        verbedList[i] = new bool[10];
	}

    for (int i = 0; i<countOfTeam; i++)
    {
        for (int j = 0 ; j<10; j++)
        {
            verbedList[i][j] = false;
        }
    }
}

// доработать 
int ForeignMinister::sabotage(Government &its, Government &attack, int numOfMinister)
{
}

int ForeignMinister::verb(Government &its, Government &attack, int numberOfMinister)
{
	if ((its.getMoney() >= COST_OF_VERB)&&(lvl>=VERB_LVL))
	{
		its.setMoney(its.getMoney() - COST_OF_VERB);
        if (TSOP(getOurTSOPLvl(4), attack.ministers[numberOfMinister]->getTSOPlvl(numberOfMinister+1) + attack.ministers[numberOfMinister]->getRecruitLvl()))
		{
			lvl++;
            verbedList[attack.getNumber()-1][numberOfMinister] = true;
            attack.ministers[numberOfMinister]->setWhooseRecruit(its.getNumber());
            return 1;
		}
        else
        {
            if (attack.ministers[numberOfMinister]->getRecruitLvl() != 0)
            {
                attack.ministers[3]->increaseLvl(attack);
            }
        }
	}
    return 0;
}
//дописать
int ForeignMinister::reverb(Government &its, Government &attack, int numberOfMinister)
{   if(attack.ministers[numberOfMinister]->getWhooseRecruit() == its.getNumber())
    {
    verbedList[attack.getNumber()-1][numberOfMinister] = false;
    attack.ministers[numberOfMinister]->setWhooseRecruit(-1);
    attack.outCodes += "101 ";
    return 1;
    } else {return 0;}
}
//дописать
int ForeignMinister::order() {}
//дописать
int ForeignMinister::kill(Government &its, Government &attack, int numberOfMinister)
{
	if ((its.getMoney() >= COST_OF_KILL))
	{
		its.setMoney(its.getMoney() - COST_OF_KILL);
        if (TSOP(getOurTSOPLvl(4), attack.ministers[numberOfMinister]->getTSOPlvl(numberOfMinister+1)))
		{
			lvl++;
            attack.ministers[numberOfMinister]->setLvl(1);
            attack.ministers[numberOfMinister]->status = 2;
            verbedList[attack.getNumber()-1][numberOfMinister] = false;
            attack.ministers[numberOfMinister]->setWhooseRecruit(-1);
            attack.outCodes += QString::number(110) + " " + QString::number(numberOfMinister +1);
            return 1;
		}
	}
    return 0;
}
//доделать
int ForeignMinister::track(Government &its, Government &attack, int numberOfMinister)
{
	if ((its.getMoney() >= COST_OF_TRACK))
	{
		its.setMoney(its.getMoney() - COST_OF_TRACK);
        if (TSOP(getTSOPlvl(4), attack.ministers[numberOfMinister]->getTSOPlvl(numberOfMinister+1)))
		{
            this->trackingTarget[0] = attack.getNumber();
            this->trackingTarget[1] = numberOfMinister + 1;
			lvl++;
		}
	}
}

void ForeignMinister::getInformation(int countOfTeam)
{
}

void ForeignMinister:: updateVerbedList(int countOfTeam)
{
    this->countOfTeam = countOfTeam;
    bool **newVerbedList = new bool*[countOfTeam];
    for (int i = 0;i < countOfTeam;i++)
    {
        newVerbedList[i] = new bool[10];
    }

    for (int i = 0; i<countOfTeam; i++)
    {
        for (int j = 0 ; j<10; j++)
        {
            newVerbedList[i][j] = false;
        }
    }

    for (int i = 0; i<countOfTeam-1; i++)
    {
        for (int j = 0 ; j<10; j++)
        {
            newVerbedList[i][j] = verbedList[i][j];
        }
    }

    verbedList = newVerbedList;

}
