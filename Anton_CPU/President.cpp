#include "Government.h"
#include "President.h"
#include <fstream>

using namespace std;

int President::dismiss(Government &its, int numOfMinister)
{ 
	its.ministers[numOfMinister]->setLvl(its.ministers[numOfMinister]->getLvl() / 2);
	its.ministers[numOfMinister]->setWhooseRecruit(-1);
}

void President::getInformation()
{
	ofstream fout("Civ.out", ios_base::app);
	fout << "У президента " << lvl << " lvl" << endl;
	fout.close();
}

President::President()
{
	lvl = 2;
}
