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
#include <QDebug>
#include <deque>

using namespace std;

int TSOP(double attackLvl, double defenceLvl);

double Government::getMoney() { return money; }
int Government::getNumber() { return number; }
int Government::getCountOfTeam() { return countOfTeam; }
short int Government::getHappiness() { return happiness; }

void Government::changeMoney(double difference) {setMoney(getMoney() + difference);}
void Government::setMoney(double newMoney) { money = newMoney; }
void Government::setNumber(int newNumber) { number = newNumber; }
void Government::setCountOfTeam(int newCountOfTeam) { countOfTeam = newCountOfTeam; }
void Government::setHappiness(short int newHappiness) { happiness = newHappiness; }

Government::Government(Team *team,int itsNumber, int itsCountOfTeam, ListOfGovernments *govs, Rialto *rialto, deque<NukeRocket> *nukesInAir)
{

    this->team = team;
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
    historyOfCommands.push_back(com);
    Government *enemy;
    int result;

    switch(com.args[0])
    {
    case 1:
        if (ministers[0]->status == 0)
        {
            result =  doPresidentCommand(com);
            if (result == 1) return 1;
            if (result == -1)
            {
            }
        }
        return 0;
        break;
    case 2:
        if (ministers[1]->status == 0)
    {
        result = doMinFinCommand(com);
        qDebug() << "Результат по ТСОП " << QString::number(result);
        if (result == 1) return 1;
        if (result == -1)
        {
            enemy = governments->getPtrToGov((ministers[1]->numberOfEnemy));
            enemy->team->recon[this->getNumber()-1].greatFail->push_back(com);
        }
    }
    return 0;
        break;
    case 3:
        if (ministers[2]->status == 0)
    {
        result = doMinDefCommand(com);
        if (result == 1) return 1;
        if (result == -1)
        {
            enemy = governments->getPtrToGov((ministers[2]->numberOfEnemy));
            enemy->team->recon[this->getNumber()-1].greatFail->push_back(com);
        }
    }
    return 0;
        break;
    case 4:
        if (ministers[3]->status == 0)
    {
        result = doKGBCommand(com);
        if (result == 1) return 1;
        if (result == -1)
        {
            enemy = governments->getPtrToGov((ministers[3]->numberOfEnemy));
            enemy->team->recon[this->getNumber()-1].greatFail->push_back(com);
        }
    }
    return 0;
        break;
    case 5:
        if (ministers[4]->status == 0)
    {
        result = doMIDCommand(com);
        if (result == 1) return 1;
        if (result == -1)
        {
            enemy = governments->getPtrToGov((this->ministers[4]->numberOfEnemy));
            //enemy->team->recon[this->getNumber()-1].greatFail.push_back(com);
            (enemy->team->recon[this->getNumber()-1]).addToGreatFail(com);
        }
    }
    return 0;
        break;
    case 6:
        if (ministers[5]->status == 0)
    {
        result = doMinUstCommand(com);
        if (result == 1) return 1;
        if (result == -1)
        {
            enemy = governments->getPtrToGov((ministers[5]->numberOfEnemy));
            enemy->team->recon[this->getNumber()-1].greatFail->push_back(com);
        }
    }
    return 0;
        break;
    case 7:
        if (ministers[6]->status == 0)
    {
        result = doMVDCommand(com);
        if (result == 1) return 1;
        if (result == -1)
        {
            enemy = governments->getPtrToGov((ministers[6]->numberOfEnemy));
            enemy->team->recon[this->getNumber()-1].greatFail->push_back(com);
        }
    }
    return 0;
        break;
    case 8:
        if (ministers[7]->status == 0)
    {
        result = doMinComCommand(com);
        if (result == 1) return 1;
        if (result == -1)
        {
            enemy = governments->getPtrToGov((ministers[7]->numberOfEnemy));
            enemy->team->recon[this->getNumber()-1].greatFail->push_back(com);
        }
    }
    return 0;
        break;
    case 9:
        if (ministers[8]->status == 0)
    {
        result = doMinHelCommand(com);
        if (result == 1) return 1;
        if (result == -1)
        {
            enemy = governments->getPtrToGov((ministers[8]->numberOfEnemy));
            enemy->team->recon[this->getNumber()-1].greatFail->push_back(com);
        }
    }
    return 0;
        break;
    case 10:
        if (ministers[9]->status == 0)
    {
        result = doSecretaryCommand(com);
        if (result == 1) return 1;
        if (result == -1)
        {
            enemy = governments->getPtrToGov((ministers[9]->numberOfEnemy));
            enemy->team->recon[this->getNumber()-1].greatFail->push_back(com);
        }
    }
    return 0;
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
    outCodes = "";
    this->countOfTeam = team->countOfTeams;

        for (int i = 0; i<COUNT_OF_MINISTER; i++)
        {
            ministers[i]->setHelpLvl(0);
            if (ministers[i]->status != 0)
            ministers[i]->status -= 1;
        }

        Defence *def = (Defence*)(this->ministers[2]);
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
        for (int i = 0; i<10; i++)
        ministers[i]->setRecruitLvl(0);

        if(this->getHappiness() < 0)
        {
            this->setHappiness(0);
        }

}

void Government::postPrepare()
{
    Defence *def = (Defence*)(this->ministers[2]);
    def->checkNukes(*this);

    HealthMinister *hel = (HealthMinister*)(this->ministers[8]);
    hel->doHarmFromViruses();

    CommunicationMinister *com = (CommunicationMinister*)(this->ministers[7]);
    for (int i = 0; i < countOfTeam; i++)
    {
        if (com->itsSlander[i]) {this->setHappiness(this->getHappiness() - 10);}
    }

    if (this->happiness < 50)
    {
        this->isInRebellion = true;
        this->stepOfRebellion = 1;
        this->outCodes += "202 ";
    }

    if (this->isInRebellion)
    {
        this->setAgricultural(this->getAgricultural() * (100 - stepOfRebellion) / 100);
        this->setHeavyIndustrial(this->getHeavyIndustrial() * (100 - stepOfRebellion) / 100);
        this->setLightIndustrial(this->getLightIndustrial() * (100 - stepOfRebellion) / 100);
        this->setMoney(this->getMoney() * (100 - stepOfRebellion) / 100);
        this->setNukes(ceil(this->getNukes() * (100 - stepOfRebellion) / 100));
        this->setPRO(ceil(this->getMissles() * (100 - stepOfRebellion) / 100));
        stepOfRebellion++;
    }

    if(this->getHappiness() < 0)
    {
        this->setHappiness(0);
    }

    if (this->underAttack.size() > 0)
    {
        for (unsigned int i = 0; i < this->underAttack.size(); i++)
        {
            this->timeUntilWar[i] -= 1;
            if (this->timeUntilWar[i] == 0)
            {
                Government *attacker = governments->getPtrToGov(this->underAttack[i]);
                int luck;
                luck = TSOP(attacker->ministers[2]->getTSOPlvl(3), this->ministers[0]->getTSOPlvl(1) + this->ministers[2]->getTSOPlvl(3));
                if (luck > 0)
                {
                    this->setMoney(this->getMoney() / 2);

                    this->setAgricultural(this->getAgricultural() / 2);
                    this->setHeavyIndustrial(this->getHeavyIndustrial() / 2);
                    this->setLightIndustrial(this->getLightIndustrial() / 2);

                    for (int i = 0; i< 10; i++)
                    {
                        this->ministers[i]->setLvl(this->ministers[i]->getLvl() / 2);
                        if (this->ministers[i]->getLvl() < 1) this->ministers[i]->setLvl(1);

                        if (this->ministers[i]->getLvl() > attacker->ministers[i]->getLvl())
                        {
                            attacker->ministers[i]->setLvl(attacker->ministers[i]->getLvl() + ceil((this->ministers[i]->getLvl() - attacker->ministers[i]->getLvl())/2) );
                        }
                    }
                    this->setNukes(this->getNukes() / 2);
                    this->setHappiness(this->getHappiness() / 2);
                    this->setPRO(this->getMissles() / 2);
                    this->outCodes += QString::number(500)  + " " + QString::number(attacker->getNumber() ) + " ";
                    attacker->outCodes += "309 " + QString::number( this->getNumber() ) + " ";
                    attacker->ministers[2]->increaseLvl(*attacker);
                }
                else
                {
                    attacker->setHappiness(attacker->getHappiness() - 10);
                    attacker->outCodes += "311 " + QString::number(this->getNumber()) + " ";
                    this->outCodes += "312 " + QString::number(attacker->getNumber()) + " ";
                }

                underAttack.pop_front();
                timeUntilWar.pop_front();
            }
        }
    }


    historyOfCommands.clear();
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
