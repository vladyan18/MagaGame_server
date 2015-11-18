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
#include "secretary.h"
#include <fstream>
#include <listofgovernments.h>

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

Government::Government(int itsNumber, int itsCountOfTeam, ListOfGovernments *govs, Rialto *rialto, deque<NukeRocket> *nukesInAir)
{
    this->nukesInAir = nukesInAir;
    this->rialto = rialto;
    governments = govs;
	number = itsNumber;
	countOfTeam = itsCountOfTeam;
	money = START_MONEY;
	happiness = MAX_HAPPINESS;
    outCodes = "215 ";
    ministers[0] = new President(this,governments);
    ministers[1] = new Finance(this);
    ministers[2] = new Defence(this,countOfTeam, governments);
    ministers[3] = new MinisterFSB(this);
    ministers[4] = new ForeignMinister(this,countOfTeam);
    ministers[5] = new MinisterOfJustice(this);
    ministers[6] = new MVD(this);
    ministers[7] = new CommunicationMinister(this,countOfTeam, governments);
    ministers[8] = new HealthMinister(this,countOfTeam);
    ministers[9] = new secretary(this);

    internationalHelp = new double*[10];
    for (int i = 0; i < 10; i++)
    {
        internationalHelp[i] = new double[countOfTeam];
        for (int j = 0; j < countOfTeam; j++)
        {
            internationalHelp[i][j] = 0;
        }
    }


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
}

int Government::doCommand(Command com)
{
    switch(com.args[0])
    {
    case 1:
        if (ministers[0]->status == 0)
        return doPresidentCommand(com);
        else return 0;
        break;
    case 2:
        if (ministers[1]->status == 0)
        return doMinFinCommand(com);
        else return 0;
        break;
    case 3:
        if (ministers[2]->status == 0)
        return doMinDefCommand(com);
        else return 0;
        break;
    case 4:
        if (ministers[3]->status == 0)
        return doKGBCommand(com);
        else return 0;
        break;
    case 5:
        if (ministers[4]->status == 0)
        return doMIDCommand(com);
        else return 0;
        break;
    case 6:
        if (ministers[5]->status == 0)
        return doMinUstCommand(com);
        else return 0;
        break;
    case 7:
        if (ministers[6]->status == 0)
        return doMVDCommand(com);
        else return 0;
        break;
    case 8:
        if (ministers[7]->status == 0)
        return doMinComCommand(com);
        else return 0;
        break;
    case 9:
        if (ministers[8]->status == 0)
        return doMinHelCommand(com);
        else return 0;
        break;
    case 10:
        if (ministers[9]->status == 0)
        return doSecretaryCommand(com);
        else return 0;
        break;
    }
    return 0;
}

int Government::doPresidentCommand(Command com)
{
   President *pres = (President*)(this->ministers[0]);
   switch (com.args[1])
   {
   case -2: // оказать помощь
       return pres->help(*this, *governments->getPtrToGov(com.args[3]), com.args[2]-1);
       break;
   case 0:  // повысить уровень
       return pres->increaseLvl(*this);
       break;
   case 1:  // уволить
       return pres->dismiss(*this, com.args[2]-1);
       break;
   }
   return 0;
}

int Government::doMinFinCommand(Command com)
{
    Finance *fin = (Finance*)(this->ministers[1]);
    switch(com.args[1])
    {
    case -2:
        return fin->help(*this, *governments->getPtrToGov(com.args[3]), com.args[2]-1);
        break;
    case 0:
        return fin->increaseLvl(*this);
        break;
    case 1:
        return fin->increaseSphere(*this, com.args[2], com.args[3]);
        break;
    case 2:
        return fin->play(*this, com.args[2], com.args[3]);
        break;
    case 3:
        return fin->doTrans(*this, *governments->getPtrToGov(com.args[2]), com.args[3]);
        break;
    case 4:
        return fin->giveFac(*this, *governments->getPtrToGov(com.args[2]), com.args[3], com.args[4]);
        break;
    }
    return 0;
}

int Government::doMinDefCommand(Command com)
{
    Defence *def = (Defence*)(this->ministers[2]);
    switch(com.args[1])
    {
    case -2:
        return def->help(*this,*governments->getPtrToGov(com.args[3]), com.args[2]-1);
        break;
    case 0:
        return def->increaseLvl(*this);
        break;
    case 1:
        if (com.args[2] > 0) { return def->IncreaseCountOfNuclear(*this,com.args[2]); }
        else {return def->DecreaseCountOfNuclear(*this, com.args[2]);}
        break;
    case 2:
        if (com.args[2] > 0) { return def->IncreaseCountOfMissleDefence(*this, com.args[2]);}
        else {return def->DecreaseCountOfMissleDefence(*this, com.args[2]);}
        break;
    case 3:
        return def->NuclearStrike(*this, *governments->getPtrToGov(com.args[2]), com.args[3]);
        break;
    case 4:
        return def->shootDownNucler(*this, com.args[2]);
        break;
    case 5:
        return def->stopNuclear(*this, *governments->getPtrToGov(com.args[2]));
        break;
    case 6:
        return def->marinesAttack(*this, *governments->getPtrToGov(com.args[2]));
        break;
    case 7:
        return def->raid(*this, *governments->getPtrToGov(com.args[2]));
        break;
    case 8:
        return def->giveNukes(*this,*governments->getPtrToGov(com.args[2]), com.args[3]);
        break;
    case 9:
        return def->givePRO(*this,*governments->getPtrToGov(com.args[2]), com.args[3]);
        break;
    }
    return 0;
}

int Government::doKGBCommand(Command com)
{
    MinisterFSB *kgb = (MinisterFSB*)(this->ministers[3]);
    switch(com.args[1])
    {
    case -2:
        return kgb->help(*this,*governments->getPtrToGov(com.args[3]),com.args[2]-1);
        break;
    case 0:
        return kgb->increaseLvl(*this);
        break;
    case 1:
        return kgb->recruitDefence(*this, com.args[2]-1, com.args[3]);
        break;
    case 2:
        return kgb->findRecruited(*this, *governments->getPtrToGov(com.args[2]));
        break;
    }
    return 0;
}

int Government::doMIDCommand(Command com)
{
    ForeignMinister *mid = (ForeignMinister*)(this->ministers[4]);
    switch(com.args[1])
    {
    case -2:
        return mid->help(*this, *governments->getPtrToGov(com.args[3]), com.args[2]-1);
        break;
    case 0:
        return mid->increaseLvl(*this);
        break;
    case 2:
        return mid->verb(*this, *governments->getPtrToGov(com.args[2]), com.args[3]-1);
        break;
    case 3:
        return mid->reverb(*this, *governments->getPtrToGov(com.args[2]), com.args[3]-1);
        break;
    case 5:        
        return mid->kill(*this, *governments->getPtrToGov(com.args[2]), com.args[3]-1);
        break;
    case 6:
        return mid->track(*this, *governments->getPtrToGov(com.args[2]), com.args[3]-1);
        break;
    }
    return 0;
}

int Government::doMinUstCommand(Command com)
{
    MinisterOfJustice *minust = (MinisterOfJustice*)(this->ministers[5]);
    switch(com.args[1])
    {
    case -2:
        return minust->help(*this, *governments->getPtrToGov(com.args[3]), com.args[2]-1);
        break;
    case 0:
        return minust->increaseLvl(*this);
        break;
    case 1:
        return minust->sue(*this, *governments->getPtrToGov(com.args[2]), 0); // Доделать механизм пруфов
        break;
    }

    return 0;
}

int Government::doMVDCommand(Command com)
{
    MVD *mvd = (MVD*)(this->ministers[6]);
    switch (com.args[1])
    {
    case -2:
        return mvd->help(*this, *governments->getPtrToGov(com.args[3]), com.args[2]-1);
        break;
    case 0:
        return mvd->increaseLvl(*this);
        break;
    case 1:
        return mvd->suppressRebellion(*this);
        break;
    case 2:
        return mvd->checkVerbed(*this);
        break;
    case 3:
        if (this->ministers[com.args[2]-1]->getWhooseRecruit() != -1)
        return mvd->disverbed(*this,*governments->getPtrToGov(this->ministers[com.args[2]-1]->getWhooseRecruit()), com.args[2]-1);
        else return (1);
        break;
    }
    return 0;
}

int Government::doMinComCommand(Command com)
{
    CommunicationMinister *mincom = (CommunicationMinister*)(this->ministers[7]);
    switch(com.args[1])
    {
    case -2:
        return mincom->help(*this, *governments->getPtrToGov(com.args[3]), com.args[2]-1);
        break;
    case 0:
        return mincom->increaseLvl(*this);
        break;
    case 1:
        return mincom->accuse(*this,*governments->getPtrToGov(com.args[2]));
        break;
    case 2:
        return mincom->disslander(*this) ;
        break;
    case 3:
        return mincom->increaseHappiness(*this, 10);
        break;
    case 4:
        return mincom->fireRebellion(*this, *governments->getPtrToGov(com.args[2]), 10);
    }
    return 0;
}

int Government::doMinHelCommand(Command com)
{
    HealthMinister *minhel = (HealthMinister*)(this->ministers[8]);
    switch(com.args[1])
    {
    case -2:
        return minhel->help(*this, *governments->getPtrToGov(com.args[3]), com.args[2]-1);
        break;
    case 0:
        return minhel->increaseLvl(*this);
        break;
    case 1:
        return minhel->vaccine(*this, *governments->getPtrToGov(com.args[2]));
        break;
    case 2:
        return minhel->infectingVirus(*this, *governments->getPtrToGov(com.args[2]));
        break;
    }
    return 0;
}

int Government::doSecretaryCommand(Command com)
{
    secretary *sec = (secretary*)(this->ministers[8]);
    switch(com.args[1])
    {
    case -2:
        return sec->help(*this, *governments->getPtrToGov(com.args[3]), com.args[2]-1);
        break;
    case 0:
        return sec->increaseLvl(*this);
        break;
    }
    return 0;
}

void Government::prepare()
{

        CommunicationMinister *com = (CommunicationMinister*)(this->ministers[7]);
        for (int i = 0; i < countOfTeam; i++)
        {
            if (com->itsSlander[i]) {this->setHappiness(this->getHappiness() - 10);}
        }

        Defence *def = (Defence*)(this->ministers[2]);
        outCodes = "";

        for (int i = 0; i<COUNT_OF_MINISTER; i++)
        {
            ministers[i]->setHelpLvl(0);
            if (ministers[i]->status != 0)
            ministers[i]->status -= 1;
        }

        Finance *fin = (Finance*)(this->ministers[1]);
        int budget = fin->getAgriculture() + fin->getHeavyIndustry()
                + fin->getLightIndustry();

         budget -= (def->getNuclear()*50000 + def->getMissleDefence()*50000);

         for (int i = 0; i <countOfTeam; i++)
         {
             for (int j = 0; j<10;j++)
             {
                 if ( isVerbed(i,j) ) {budget -= 50000;}
             }
         }

         if (this->isInRebellion){budget /= 2;}

        this->setMoney(getMoney() + budget);

        HealthMinister *hel = (HealthMinister*)(this->ministers[8]);
        hel->doHarmFromViruses();

        for (int i = 0; i<10; i++)
        {
            for (int j = 0; j < countOfTeam; j++)
            {
                internationalHelp[i][j] = 0;
            }
        }

        MinisterFSB *kgb = (MinisterFSB*)(this->ministers[3]);
        kgb->kgbPower = 100;
        kgb->isDefending = false;

        if(this->getHappiness() < 0)
        {
            this->setHappiness(0);
        }
}

void Government::postPrepare()
{
    Defence *def = (Defence*)(this->ministers[2]);
    def->checkNukes(*this);

    if (this->happiness < 50)
    {
        this->isInRebellion = true;
        this->outCodes += "202 ";
    }

    if(this->getHappiness() < 0)
    {
        this->setHappiness(0);
    }
}

int Government::getNukes()
{
         Defence *def = (Defence*)(this->ministers[2]);
         return def->getNuclear();
}

int Government::getMissles()
{
         Defence *def = (Defence*)(this->ministers[2]);
         return def->getMissleDefence();
}

void Government::setNukes(int newNukes)
{
    Defence *def = (Defence*)(this->ministers[2]);
    def->setNuclear(newNukes);
}

void Government::setPRO(int newPRO)
{
    Defence *def = (Defence*)(this->ministers[2]);
    def->setMissleDefence(newPRO);
}



bool Government::isVerbed(int country, int min)
{
    ForeignMinister *mid = (ForeignMinister*)(ministers[4]);
    return mid->verbedList[country][min];
}

long Government:: getHeavyIndustrial()
{
     Finance *fin = (Finance*)(ministers[1]);
     return fin->getHeavyIndustry();
}

long Government::getLightIndustrial()
{
     Finance *fin = (Finance*)(ministers[1]);
     return fin->getLightIndustry();
}

long Government::getAgricultural()
{
     Finance *fin = (Finance*)(ministers[1]);
     return fin->getAgriculture();
}

void Government:: setHeavyIndustrial(long newValue)
{
     Finance *fin = (Finance*)(ministers[1]);
     fin->setHeavyIndustry(newValue);
}

void Government::setLightIndustrial(long newValue)
{
     Finance *fin = (Finance*)(ministers[1]);
     fin->setLightIndustry(newValue);
}

void Government::setAgricultural(long newValue)
{
     Finance *fin = (Finance*)(ministers[1]);
     fin->setAgriculture(newValue);
}

void Government::updateVerbedList(int countOfTeam)
{
    this->countOfTeam = countOfTeam;
     ForeignMinister *mid = (ForeignMinister*)(ministers[4]);
     mid->updateVerbedList(countOfTeam);

     ((CommunicationMinister*)(ministers[7]))->updateSlander();

     double **newInternationalHelp;

     newInternationalHelp = new double*[10];
     for (int i = 0; i < 10; i++)
     {
         newInternationalHelp[i] = new double[countOfTeam];
         for (int j = 0; j < countOfTeam; j++)
         {
             if (j < countOfTeam - 1)
             newInternationalHelp[i][j] = internationalHelp[i][j];
             else
             newInternationalHelp[i][j] = 0;
         }
     }

     internationalHelp = newInternationalHelp;
}
