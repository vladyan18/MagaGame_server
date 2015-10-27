#include "Minister.h"
#include "Government.h"

double Minister::getLvl() { return lvl; }
double Minister::getHelpLvl() { return helpLvl; }
double Minister::getRecruitLvl() { return recruitLvl; }
int Minister::getWhooseRecruit() { return whooseRecruit; }
double Minister::getTSOPlvl() { return helpLvl + lvl; }

void Minister::setLvl(double newLvl) { lvl = newLvl; }
void Minister::setHelpLvl(double newHelpLvl) { helpLvl = newHelpLvl; }
void Minister::setRecruitLvl(double newRecruitLvl) { recruitLvl = newRecruitLvl; }
void Minister::setWhooseRecruit(int newWhooseRecruit) { whooseRecruit = newWhooseRecruit; }

Minister::Minister()
{
	lvl = 1;
	helpLvl = 0;
	whooseRecruit = -1; //-1 not a recruit
	recruitLvl = 0;
}

int Minister::increaseLvl(Government &its)
{
	if (its.getMoney() >= COST_OF_INCREASE_LVL)
	{
		lvl++;
		its.setMoney(its.getMoney() - COST_OF_INCREASE_LVL);
	}
}

int Minister::help(Government &its, Government &getsHelp, int helpNumberOfMinister)
{
	if (its.getMoney() >= COST_OF_HELP)
	{
		getsHelp.ministers[helpNumberOfMinister]->setHelpLvl(lvl / 4);
		its.setMoney(its.getMoney() - COST_OF_HELP);
	}
}
