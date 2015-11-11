#include "Government.h"
#include "President.h"
#include <fstream>

using namespace std;

int President::dismiss(Government &its, int numOfMinister)
{ 
    int numOfAttacker;
	its.ministers[numOfMinister]->setLvl(its.ministers[numOfMinister]->getLvl() / 2);
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
}

void President::getInformation()
{
	ofstream fout("Civ.out", ios_base::app);
	fout << "У президента " << lvl << " lvl" << endl;
	fout.close();
}

President::President(ListOfGovernments *govs)
{
    this->governments = govs;
    lvl = 1;
    this->helpLvl = 1;
}
