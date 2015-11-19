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
	//повысить свой уровень
    int increaseLvl(Government &its);
	//помочь другому министру
    int help(Government &its, Government &getsHelp, int helpNumberOfMinister);
    Government *its;
    int status = 0;
    int numberOfEnemy = 0;
protected:
		double lvl;
		double helpLvl;					//дополнительный уровень помощи
		double recruitLvl;				//дополнительный уровень при вербоке
		int whooseRecruit;
        int helpKoeff = 1;

};
