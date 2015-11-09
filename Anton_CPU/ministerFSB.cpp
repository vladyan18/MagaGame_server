#include "Government.h"
#include "ministerFSB.h"
#include <fstream>

using namespace std;

bool TSOP(double attackLvl, double defenceLvl);

int MinisterFSB::recruitDefence(Government &its, int numOfMinister, int countOfHelp)
{
    if (its.getMoney() >= COST_OF_RECRUIT_DEFENCE || isDefending)
	{
        //lvl++;
        its.ministers[numOfMinister]->setRecruitLvl(its.ministers[3]->getLvl() * countOfHelp/100);
        if (!isDefending){its.setMoney(its.getMoney() - COST_OF_RECRUIT_DEFENCE);}
        isDefending = true;
	}
}

void MinisterFSB::getInformation()
{
	ofstream fout("Civ.out", ios_base::app);
	fout << "У директора ФСБ " << lvl << " lvl" << endl;
	fout.close();
}

int MinisterFSB::findRecruited(Government &its, Government &searching)
{
	int countOfRecruited = 0;
	int resultOfSearching[COUNT_OF_MINISTER];

	if (its.getMoney() > COST_OF_FIND_RECRUTED)
	{
		its.setMoney(its.getMoney() - COST_OF_FIND_RECRUTED);
		bool result = false;  //найден ли МИД в вашем государстве
		int countOfRecruited = 0; //количество найденных рекрутов

		for (int i = 0;i < COUNT_OF_MINISTER;i++) 
			resultOfSearching[i] = 0;

		for (int i = 0;i < COUNT_OF_MINISTER;i++)
		{
			if (TSOP(getTSOPlvl(), searching.ministers[4]->getTSOPlvl())) 
				if (its.ministers[i]->getWhooseRecruit() == searching.getNumber()) // проверка всех министров на завербованность конкретного государтсва
				{
					result = true;
					countOfRecruited++;
					resultOfSearching[i] = 1;
				}
		}

		if (result)
			lvl++;
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
	
    return *answer;
}
