#include "Government.h"
#include "ministerFSB.h"
#include <fstream>

using namespace std;

bool TSOP(double attackLvl, double defenceLvl);

int MinisterFSB::recruitDefence(Government &its, int help[COUNT_OF_MINISTER])
{
	if (its.getMoney() >= COST_OF_RECRUIT_DEFENCE)
	{
		lvl++;
		for (int i = 0;i < COUNT_OF_MINISTER;i++)
			its.ministers[i]->setRecruitLvl(lvl*help[i] / 100); //i-�� ������� ����������, ������� % ����� �������� i ��������
		its.setMoney(its.getMoney() - COST_OF_RECRUIT_DEFENCE);
	}
}

void MinisterFSB::getInformation()
{
	ofstream fout("Civ.out", ios_base::app);
	fout << "� ��������� ��� " << lvl << " lvl" << endl;
	fout.close();
}

int* MinisterFSB::findRecruited(Government &its, Government &searching)
{
	int countOfRecruited = 0;
	int resultOfSearching[COUNT_OF_MINISTER];

	if (its.getMoney() > COST_OF_FIND_RECRUTED)
	{
		its.setMoney(its.getMoney() - COST_OF_FIND_RECRUTED);
		bool result = false;  //������ �� ��� � ����� �����������
		int countOfRecruited = 0; //���������� ��������� ��������

		for (int i = 0;i < COUNT_OF_MINISTER;i++) 
			resultOfSearching[i] = 0;

		for (int i = 0;i < COUNT_OF_MINISTER;i++)
		{
			if (TSOP(getTSOPlvl(), searching.ministers[4]->getTSOPlvl())) 
				if (its.ministers[i]->getWhooseRecruit() == searching.getNumber()) // �������� ���� ��������� �� ��������������� ����������� �����������
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
	for (int i = 0;i < countOfRecruited;i++) //������� ����� � ����� ������������ ������
	{
		int j = 0;
		if (resultOfSearching[i] == 1)
		{
			answer[j] = i;
			j++;
		}
	}
	
	return answer;
}
