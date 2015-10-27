#include "Government.h"
#include "Defence.h"
#include "Finance.h"
#include "President.h"
#include "ministerFSB.h"
#include "ForeignMinister.h"
#include "MinisterOfJustice.h"
#include "MVD.h"
#include "CommunicationMinister.h"
#include "HealthMinister.h"
#include <fstream>

using namespace std;

double Government::getMoney() { return money; }
int Government::getNumber() { return number; }
int Government::getCountOfTeam() { return countOfTeam; }
short int Government::getHappiness() { return happiness; }

void Government::changeMoney(double difference) {setMoney(getMoney() + difference);}
void Government::setMoney(double newMoney) { money = newMoney; }
void Government::setNumber(int newNumber) { number = newNumber; }
void Government::setCountOfTeam(int newCountOfTeam) { countOfTeam = newCountOfTeam; }
void Government::setHappiness(short int newHappiness) { happiness = newHappiness; }

Government::Government(int itsNumber, int itsCountOfTeam)
{
	number = itsNumber;
	countOfTeam = itsCountOfTeam;
	money = START_MONEY;
	happiness = MAX_HAPPINESS;
	ministers[0] = new President();
	ministers[1] = new Finance();
	ministers[2] = new Defence(countOfTeam);
	ministers[3] = new MinisterFSB();
	ministers[4] = new ForeignMinister(countOfTeam);
	ministers[5] = new MinisterOfJustice();
	ministers[6] = new MVD();
	ministers[7] = new CommunicationMinister(countOfTeam);
	ministers[8] = new HealthMinister(countOfTeam);
}

Government::~Government()
{
	//for (int i = 0;i < COUNT_OF_MINISTER;i++)
	//{
	//	delete ministers[i];
	//}
}

Government::Government(const Government &rhs)
{
	for (int i = 0;i < COUNT_OF_MINISTER;i++)
		*ministers[i] = *(rhs.ministers[i]);
}

Government::Government() {}

void Government::getInformation()
{
	ofstream fout("Civ.out", ios_base::app);
	fout << "Бюджет:= " << money << endl;
	fout << "Счастье населения:= " << happiness << endl;
	fout.close();
}

void Government::getFullInformation()
{
	ofstream fout("Civ.out", ios_base::app);
	getInformation();

	President *presidentInfo = (President*)(this->ministers[0]);
	presidentInfo->getInformation();

	Finance *financeInfo = (Finance*)(this->ministers[1]);
	financeInfo->getInformation();

	Defence *defenceInfo = (Defence*)(this->ministers[2]);
	defenceInfo->getInformation(*this);

	MinisterFSB *FSBInfo = (MinisterFSB*)(this->ministers[3]);
	FSBInfo->getInformation();

	ForeignMinister *ForeignInfo = (ForeignMinister*)(this->ministers[4]);
	ForeignInfo->getInformation(countOfTeam);

	MinisterOfJustice *MinisterOfJusticeInfo = (MinisterOfJustice*)(this->ministers[5]);
	MinisterOfJusticeInfo->getInformation();

	MVD *MVDInfo = (MVD*)(this->ministers[6]);
	MVDInfo->getInformation();

	CommunicationMinister *CommunicationMinisterInfo = (CommunicationMinister*)(this->ministers[7]);
	CommunicationMinisterInfo->getInformation(countOfTeam);

	HealthMinister *HealthMinisterInfo = (HealthMinister*)(this->ministers[8]);
	HealthMinisterInfo->getInformation(countOfTeam);

	fout.close();
}

int Government::doCommand(Command com)
{
    President *pres = (President*)(this->ministers[0]);
    Finance *fin = (Finance*)(this->ministers[1]);
    Defence *def = (Defence*)(this->ministers[2]);

    switch(com.args[0])
    {
    case 1:

        switch (com.args[1])
        {
        case -2:
            return pres->help(*this, *this, com.args[2]);
            break;
        case 0:
            return pres->increaseLvl(*this);
            break;
        case 1:
            return pres->dismiss(*this, com.args[2]);
            break;
        }

        break;
    case 2:
        switch (com.args[1])
        {
        case -2:
            return fin->help(*this, *this, com.args[2]);
            break;
        case 0:
            return fin->increaseLvl(*this);
            break;
        case 1:
            return fin->increaseSphere(*this, com.args[2], com.args[3]);
            break;
        case 2: //TO DO
            break;
        }

        break;
    case 3:
        switch (com.args[1])
        {
        case -2:
            return def->help(*this, *this, com.args[2]);
            break;
        case 0:
            return def->increaseLvl(*this);
            break;
        case 1:
            if (com.args[2] > 0)
            {
                return def->IncreaseCountOfNuclear(*this, com.args[2]);
            }
            else
            {
                return def->DecreaseCountOfNuclear(*this, com.args[2]);
            }
            break;
        case 2:
            if (com.args[2] > 0)
            {
                return def->IncreaseCountOfMissleDefence(*this, com.args[2]);
            }
            else
            {
                return def->DecreaseCountOfMissleDefence(*this, com.args[2]);
            }
            break;
        case 3:
         //   return def->NuclearStrike(*this);
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;

        }
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        break;
    case 8:
        break;
    case 9:
        break;
    case 10:
        break;
    }

}
