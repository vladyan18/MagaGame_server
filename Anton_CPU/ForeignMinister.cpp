#include "Government.h"
#include "ForeignMinister.h"
#include <fstream>

using namespace std;

bool TSOP(double attackLvl, double defenceLvl);

ForeignMinister::ForeignMinister(){}

ForeignMinister::ForeignMinister(int countOfTeam)
{
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

// ���������� 
int ForeignMinister::sabotage(Government &its, Government &attack, int numOfMinister)
{
}

int ForeignMinister::verb(Government &its, Government &attack, int numberOfMinister)
{
	if ((its.getMoney() >= COST_OF_VERB)&&(lvl>=VERB_LVL))
	{
		its.setMoney(its.getMoney() - COST_OF_VERB);
		if (TSOP(getTSOPlvl(), attack.ministers[numberOfMinister]->getTSOPlvl()))
		{
			lvl++;
            verbedList[attack.getNumber()-1][numberOfMinister] = true;
			attack.ministers[numberOfMinister]->setWhooseRecruit(its.getNumber());
		}
	}
}
//��������
int ForeignMinister::reverb(Government &its, Government &attack, int numberOfMinister)
{
    verbedList[attack.getNumber()-1][numberOfMinister] = false;
    attack.ministers[numberOfMinister-1]->setWhooseRecruit(-1);
    attack.outCodes += "101 ";
}
//��������
int ForeignMinister::order() {}
//��������
int ForeignMinister::kill(Government &its, Government &attack, int numberOfMinister)
{
	if ((its.getMoney() >= COST_OF_KILL))
	{
		its.setMoney(its.getMoney() - COST_OF_KILL);
        if (TSOP(getTSOPlvl(), attack.ministers[numberOfMinister-1]->getTSOPlvl()))
		{
			lvl++;
            attack.ministers[numberOfMinister-1]->setLvl(1);
            verbedList[attack.getNumber()-1][numberOfMinister] = false;
            attack.outCodes += QString::number(110 + numberOfMinister - 1);
		}
	}
}
//��������
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
	fout << "� �������� ����������� ��� " << lvl << " lvl" << endl;
	fout.close();
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
