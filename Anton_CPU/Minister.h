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
    double getTSOPlvl(int numOfMinister);
    double getOurTSOPLvl(int numOfMinister);
	
	void setLvl(double newLvl);
	void setHelpLvl(double newHelpLvl);
	void setRecruitLvl(double newRecruitLvl);
	void setWhooseRecruit(int newWhooseRecruit);
	//common function
	//�������� ���� �������
    int increaseLvl(Government &its);
	//������ ������� ��������
    int help(Government &its, Government &getsHelp, int helpNumberOfMinister);
    Government *its;
    int status = 0;
    int numberOfEnemy = 0;
protected:
		double lvl;
		double helpLvl;					//�������������� ������� ������
		double recruitLvl;				//�������������� ������� ��� �������
		int whooseRecruit;
        int helpKoeff = 1;

};
