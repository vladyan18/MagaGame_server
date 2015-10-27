#pragma once

#include "Government.h"

class Government;

class Minister
{
public:
	Minister();
	virtual void getInformation() {}
	virtual ~Minister() {}
	double getLvl();
	double getHelpLvl();
	double getRecruitLvl();
	int getWhooseRecruit();
	double getTSOPlvl();
	
	void setLvl(double newLvl);
	void setHelpLvl(double newHelpLvl);
	void setRecruitLvl(double newRecruitLvl);
	void setWhooseRecruit(int newWhooseRecruit);
	//common function
	//�������� ���� �������
    int increaseLvl(Government &its);
	//������ ������� ��������
    int help(Government &its, Government &getsHelp, int helpNumberOfMinister);
protected:
		double lvl;
		double helpLvl;					//�������������� ������� ������
		double recruitLvl;				//�������������� ������� ��� �������
		int whooseRecruit;
};
