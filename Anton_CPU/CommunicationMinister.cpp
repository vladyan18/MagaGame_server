#include "Government.h"
#include "CommunicationMinister.h"
#include <fstream>

using namespace std;

bool TSOP(double attackLvl, double defenceLvl);

CommunicationMinister::CommunicationMinister(int countOfTeam)
{
	itsSlander = new bool[countOfTeam];
	for (int i = 0;i < countOfTeam;i++)
		itsSlander[i] = false;
};

void CommunicationMinister::setItsSlander(bool newItsSlander, int numOfTeam) { itsSlander[numOfTeam] = newItsSlander; }
//void CommunicationMinister::setItsRebellion(int newItsRebellion) { itsRebellion = newItsRebellion; }

bool CommunicationMinister::getItsSlander(int numOfTeam) { return itsSlander[numOfTeam]; }
//int CommunicationMinister::getItsRebellion() { return itsRebellion; }

int CommunicationMinister::accuse(Government &its, Government &attack)
{
	if (its.getMoney() >= COST_OF_ACCUSE)
	{
		its.setMoney(its.getMoney() - COST_OF_ACCUSE);
		if (TSOP(getTSOPlvl(), attack.ministers[7]->getTSOPlvl()))
		{
			CommunicationMinister *attackCommunicationMinister = (CommunicationMinister*)(its.ministers[7]);
			attackCommunicationMinister->setItsSlander(true, its.getNumber());
			lvl++;
            return 1;
		}
        else
        {
            return 0;
        }
	}
    else
    {
        return 0;
    }
}

int CommunicationMinister::disslander(Government &its, Government &attack)
{
	if (its.getMoney() >= COST_OF_DISSLANDER)
	{
		its.setMoney(its.getMoney() - COST_OF_DISSLANDER);
		CommunicationMinister *attackCommunicationMinister = (CommunicationMinister*)(its.ministers[7]);
		if ((TSOP(getTSOPlvl(), attack.ministers[7]->getTSOPlvl())) &&
			(getItsSlander(attack.getNumber())))
		{
			lvl++;
			itsSlander[attack.getNumber()] = false;
			its.setHappiness(its.getHappiness() + DECREASE_HAPPINESS_BY_SLANDER);
			attack.setHappiness(attack.getHappiness() - DECREASE_HAPPINESS_BY_SLANDER);
            return 1;
        }
        else
        {
            return 0;
        }
	}
    else
    {
        return 0;
    }
}

int CommunicationMinister::increaseHappiness(Government &its, int countOfUp)
{
    int result = 0;
    for (int i = 0;i < countOfUp;i++)
		if (its.getMoney() >= COMMUNICATION_MINISTER_INCREASE_HAPPINESS)
		{
			its.setMoney(its.getMoney() - COMMUNICATION_MINISTER_INCREASE_HAPPINESS);
			its.setHappiness(its.getHappiness() + COMMUNICATION_MINISTER_INCREASE_HAPPINESS);
            result++;
        }
    return result;
}

int CommunicationMinister::fireRebellion(Government &its, Government &attack, int countOfFire)
{
    int result = 0;
	for (int i = 0;i < countOfFire;i++)
		if (its.getMoney() >= COST_OF_FIRE_REBELLION)
		{
			its.setMoney(its.getMoney() - COST_OF_FIRE_REBELLION);
			if (TSOP(getTSOPlvl(), attack.ministers[7]->getTSOPlvl() + attack.ministers[6]->getTSOPlvl()))
			{
				lvl++;
				attack.setHappiness(attack.getHappiness() + DECREASE_HAPPINESS_BY_REBELLION);
                result++;
            }
		}
    return result;
}

void CommunicationMinister::getInformation(int countOfTeam)
{
	ofstream fout("Civ.out", ios_base::app);
	fout << "� �������� �� ������ � ��������������� " << lvl << " lvl" << endl;
	for (int i = 0;i < countOfTeam;i++)
		if (itsSlander[i])
			fout << "����������� �" << i + 1 << " ���������� ���" << endl;
	fout.close();
}
