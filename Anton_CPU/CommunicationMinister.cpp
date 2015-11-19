#include "Government.h"
#include "CommunicationMinister.h"
#include <fstream>

using namespace std;

bool TSOP(double attackLvl, double defenceLvl);

CommunicationMinister::CommunicationMinister(Government *its, int countOfTeam, ListOfGovernments *govs)
{
    this->its = its;
    this->governments = govs;
    this->countOfTeam = countOfTeam;
    itsSlander = new bool[countOfTeam];
	for (int i = 0;i < countOfTeam;i++)
		itsSlander[i] = false;
}

void CommunicationMinister::setItsSlander(bool newItsSlander, int numOfTeam) { itsSlander[numOfTeam-1] = newItsSlander; }
//void CommunicationMinister::setItsRebellion(int newItsRebellion) { itsRebellion = newItsRebellion; }

bool CommunicationMinister::getItsSlander(int numOfTeam) { return itsSlander[numOfTeam-1]; }
//int CommunicationMinister::getItsRebellion() { return itsRebellion; }

int CommunicationMinister::accuse(Government &its, Government &attack)
{
	if (its.getMoney() >= COST_OF_ACCUSE)
	{
		its.setMoney(its.getMoney() - COST_OF_ACCUSE);
        this->numberOfEnemy = attack.getNumber();
        int luck = TSOP(getLvl(), attack.ministers[7]->getTSOPlvl(8));
        switch (luck)
        {
           case 1:
            {
                CommunicationMinister *attackCommunicationMinister = (CommunicationMinister*)(its.ministers[7]);
                attackCommunicationMinister->setItsSlander(true, its.getNumber());
                attack.outCodes += "200 ";
                lvl++;
                return 1;
            }
           case -1:
            {
                return -1;
            }
        }
	}
    else
    {
        return 0;
    }
}

int CommunicationMinister::disslander(Government &its)
{
    Government *attack;
    int luck;
    for (int i = 0; i<its.getCountOfTeam(); i++)
    {
        if (itsSlander[i])
        {
            attack = governments->getPtrToGov(i+1);
            this->numberOfEnemy = attack->getNumber();
            if (its.getMoney() >= COST_OF_DISSLANDER)
            {
                its.setMoney(its.getMoney() - COST_OF_DISSLANDER);
                luck = (TSOP(getOurTSOPLvl(8), attack->ministers[7]->getTSOPlvl(8)));
                if ( luck &&
                    (getItsSlander(attack->getNumber())))
                {
                    lvl++;
                    itsSlander[attack->getNumber()-1] = false;
                    its.setHappiness(its.getHappiness() + DECREASE_HAPPINESS_BY_SLANDER);
                    attack->setHappiness(attack->getHappiness() - DECREASE_HAPPINESS_BY_SLANDER);
                    attack->outCodes += "201 ";
                    return 1;
                }
                else
                {
                    return luck;
                }
            }
            else
            {
                return 0;
            }
        }
    }

    return 0;
}

int CommunicationMinister::increaseHappiness(Government &its, int countOfUp)
{
    int result = 0;
    for (int i = 0;i < countOfUp;i++)
        if (its.getMoney() >= 50000)
		{
            its.setMoney(its.getMoney() - 50000);
            its.setHappiness(its.getHappiness() + 1);
            result++;
        }
    return result;
}

int CommunicationMinister::fireRebellion(Government &its, Government &attack, int countOfFire)
{
    int result = 0;
    int luck;
    this->numberOfEnemy = attack.getNumber();

		if (its.getMoney() >= COST_OF_FIRE_REBELLION)
		{
			its.setMoney(its.getMoney() - COST_OF_FIRE_REBELLION);
            luck = TSOP(getOurTSOPLvl(8), attack.ministers[7]->getTSOPlvl(8) + attack.ministers[6]->getTSOPlvl(7));
            if (luck)
			{
				lvl++;
                attack.setHappiness(attack.getHappiness() - 10);
                result++;
            }
		}
    return luck;
}

void CommunicationMinister::getInformation(int countOfTeam)
{
}

void CommunicationMinister::updateSlander()
{
    bool *newSlander = new bool[its->getCountOfTeam()];

    for (int i = 0; i < its->getCountOfTeam(); i++)
    {
        if (i < its->getCountOfTeam() - 1)
        newSlander[i] = itsSlander[i];
        else
        newSlander[i] = 0;
    }

    itsSlander = newSlander;
}
