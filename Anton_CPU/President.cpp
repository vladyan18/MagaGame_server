#include "Government.h"
#include "President.h"
#include <fstream>
#include <cmath>

using namespace std;

int President::dismiss(Government &its, int numOfMinister)
{ 
    int numOfAttacker;
    its.ministers[numOfMinister]->setLvl(ceil(its.ministers[numOfMinister]->getLvl() / 2));
    its.ministers[numOfMinister]->status = 2;
    numOfAttacker = its.ministers[numOfMinister]->getWhooseRecruit();
    if (numOfAttacker != -1 )
    {
        Government *attacker = governments->getPtrToGov(numOfAttacker);
        Command fr;
        fr.args[0] = 5;
        fr.args[1] = 3;
        fr.args[2] = its.getNumber();
        fr.args[3] = numOfMinister+1;
        attacker->doMIDCommand(fr);
    }
    return 1;
}

void President::getInformation()
{
}

President::President(Government *its, ListOfGovernments *govs)
{
    this->helpKoeff = 2;
    this->its = its;
    this->governments = govs;
    lvl = 1;
}
