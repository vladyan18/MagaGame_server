#include "Minister.h"
#include "Government.h"

double Minister::getLvl() { return lvl; }
double Minister::getHelpLvl() { return helpLvl; }
double Minister::getRecruitLvl() { return recruitLvl; }
int Minister::getWhooseRecruit() { return whooseRecruit; }
double Minister::getTSOPlvl(int numOfMinister)
{
    double help = 0;
    for (int i = 0; i < its->getCountOfTeam();i++)
    {
        help+= its->internationalHelp[numOfMinister-1][i];
        its->internationalHelp[numOfMinister-1][i] = 0;
    }
    return lvl + help;
}
double Minister::getOurTSOPLvl(int numOfMinister)
{
    double help = 0;
    help+= its->internationalHelp[numOfMinister-1][its->getNumber()-1];
    return lvl + help;
}

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
        return 1;
	}
    return 0;
}

int Minister::help(Government &its, Government &getsHelp, int helpNumberOfMinister)
{
	if (its.getMoney() >= COST_OF_HELP)
	{
        if (getsHelp.internationalHelp[helpNumberOfMinister][its.getNumber()-1] == 0)
        {
            getsHelp.internationalHelp[helpNumberOfMinister][its.getNumber()-1] =  (this->lvl / 4)*this->helpKoeff;
            its.setMoney(its.getMoney() - COST_OF_HELP);
            return 1;
        }
        else
        {
            return 0;
        }


	}
    return 0;
}
