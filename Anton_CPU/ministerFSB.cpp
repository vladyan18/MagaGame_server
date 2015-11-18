#include "Government.h"
#include "ministerFSB.h"
#include <fstream>

using namespace std;

bool TSOP(double attackLvl, double defenceLvl);

MinisterFSB::MinisterFSB(Government *its)
{
    this->its = its;
}

int MinisterFSB::recruitDefence(Government &its, int numOfMinister, int countOfHelp)
{
    if ((its.getMoney() >= COST_OF_RECRUIT_DEFENCE || isDefending) && countOfHelp <= kgbPower)
	{
        if (!isDefending)
        {
            its.setMoney(its.getMoney() - COST_OF_RECRUIT_DEFENCE);
        for (int i = 0; i<10; i++)
            its.ministers[i]->setRecruitLvl(0);
        }

        its.ministers[numOfMinister]->setRecruitLvl(its.ministers[3]->getLvl() * countOfHelp/100);
        kgbPower -= countOfHelp;
        isDefending = true;
        return 1;
	}
    return 0;
}

void MinisterFSB::getInformation()
{
}

int MinisterFSB::findRecruited(Government &its, Government &searching)
{
	int countOfRecruited = 0;
    int resultOfSearching[10];

	if (its.getMoney() > COST_OF_FIND_RECRUTED)
	{
		its.setMoney(its.getMoney() - COST_OF_FIND_RECRUTED);
		bool result = false;  //найден ли ћ»ƒ в вашем государстве
		int countOfRecruited = 0; //количество найденных рекрутов

        for (int i = 0;i < 10;i++)
			resultOfSearching[i] = 0;

        for (int i = 0;i < 10;i++)
		{
            if (its.ministers[i]->getWhooseRecruit() == searching.getNumber() && TSOP(getLvl(), searching.ministers[4]->getTSOPlvl(5)))
                 // проверка всех министров на завербованность конкретного государтсва
				{
					result = true;
					countOfRecruited++;
					resultOfSearching[i] = 1;
				}
		}

		if (result)
        {
			lvl++;
            its.outCodes += "207 " + QString::number(searching.getNumber()) + " ";
        }
        else
        {
            its.outCodes +="216 ";
        }
	}
	
	int *answer = new int[countOfRecruited];
	for (int i = 0;i < countOfRecruited;i++) //заносим ответ в новый динамический массив
	{
		int j = 0;
		if (resultOfSearching[i] == 1)
		{
			answer[j] = i;
			j++;
		}
	}
	
    return 1;
}
