#include "Government.h"
#include "Defence.h"
#include <fstream>
#include <QDebug>

using namespace std;

int TSOP(double attackLvl, double defenceLvl);

int Defence::getNuclear() { return nuclear; }
int Defence::getMissleDefence() { return missileDefense; }

void Defence::setNuclear(int newNuclear) { nuclear = newNuclear; }
void Defence::setMissleDefence(int newMissleDefence) { missileDefense = newMissleDefence; }

Defence::Defence() {}

Defence::Defence(Government *its,int countOfTeam, ListOfGovernments *governments)
{
    this->its = its;
    this->governments = governments;
    this->countOfTeams = countOfTeam;
	nuclear = 0;
	missileDefense = 0;

}

int Defence::IncreaseCountOfNuclear(Government &its, int countOfNuclear)
{
    int result = 0;
	for (int i = 0;i < countOfNuclear;i++)
		if ((its.getMoney() >= COST_OF_INCREASE_COUNT_OF_NUCLEAR) && (lvl >= NEEDED_LVL_FOR_NUCLEAR))
		{
			nuclear++;
            result++;
			its.setMoney(its.getMoney() - COST_OF_INCREASE_COUNT_OF_NUCLEAR);
		}
    if (result > 0)
    return 1;
    else return 0;
}

int Defence::DecreaseCountOfNuclear(Government &its, int countOfNuclear)
{
    int result = 0;
	for (int i = 0;i < countOfNuclear;i++)
		if ((its.getMoney() >= COST_OF_DECREASE_COUNT_OF_NUCLEAR_OR_MISSLE) &&
			(lvl >= NEEDED_LVL_FOR_NUCLEAR) && nuclear>0)
		{
			nuclear--;
            result ++;
			its.setMoney(its.getMoney() - COST_OF_DECREASE_COUNT_OF_NUCLEAR_OR_MISSLE);
		}
    if (result > 0)
    return 1;
    else return 0;
}

int Defence::IncreaseCountOfMissleDefence(Government &its, int countOfMissle)
{
    int result = 0;
	for (int i = 0;i < countOfMissle;i++)
		if (its.getMoney() >= COST_OF_INCREASE_COUNT_OF_MISSLE)
		{
			missileDefense++;
            result++;
			its.setMoney(its.getMoney() - COST_OF_INCREASE_COUNT_OF_MISSLE);
		}
    if (result > 0)
        return 1;
    else return 0;
}

int Defence::DecreaseCountOfMissleDefence(Government &its, int countOfMissle)
{
    int result = 0;
	for (int i = 0;i < countOfMissle;i++)
		if ((its.getMoney() >= COST_OF_DECREASE_COUNT_OF_NUCLEAR_OR_MISSLE) &&
			(missileDefense>0))
		{
			missileDefense--;
            result++;
			its.setMoney(its.getMoney() - COST_OF_DECREASE_COUNT_OF_NUCLEAR_OR_MISSLE);
		}
    if (result > 0)
    return 1;
    else return 0;
}

int  Defence::NuclearStrike(Government &its, Government &attack, int countOfNuclear)
{
    if (nuclear > 0)
    {
	nuclear -= countOfNuclear;

    NukeRocket *newNuke = new NukeRocket(its.getNumber(), attack.getNumber(), countOfNuclear);
    its.nukesInAir->push_back(*newNuke);
    delete newNuke;

    Government *gov;

    for (int i = 0; i < its.getCountOfTeam(); i++)
    {
        gov = governments->getPtrToGov((i+1));
        if ( gov->getMissles() > 0 )
        {
            gov->outCodes += "3000 " + QString::number(its.getNumber()) + " " ;
        }
    }

    return 1;
    }
    else return 0;
}

int Defence::shootDownNucler(Government &its, int countOfMissle)
{

    this->nukesInAir = its.nukesInAir;
    NukeRocket *currentRocket;
    int result = 0, used = 0;
    int luck;

    int toUs1 = 0;
    int toUs3;
    for (int i = 0; i < nukesInAir->size(); i++)
        if ( nukesInAir->at(i).to == its.getNumber() && nukesInAir->at(i).count > 0 )
        {
            toUs1++;
        }
    toUs3 = toUs1;

    while (nukesInAir->size() > 0 && countOfMissle > 0)
    {
        currentRocket = NULL;

        if (toUs3 == 0)
        {
            for (int i = 0; i < nukesInAir->size(); i++)
                if (nukesInAir->at(i).count > 0 && nukesInAir->at(i).from != its.getNumber())
                {

                    currentRocket = &(nukesInAir->at(i));
                    break;
                }
        }
        else
        {
            if (toUs3 > 0)
            {
                for (int i = 0; i < nukesInAir->size(); i++)
                    if ( nukesInAir->at(i).to == its.getNumber() && nukesInAir->at(i).count > 0 )
                    {
                        currentRocket = &(nukesInAir->at(i));
                        break;
                    }
            }
        }

        if (currentRocket == NULL) {break;}

            if ((TSOP(its.ministers[2]->getTSOPlvl(3), governments->getPtrToGov(currentRocket->from)->ministers[2]->getTSOPlvl(3))) > 0 )
            {

            currentRocket->count--;
            result++;
            if (currentRocket->count == 0) {governments->getPtrToGov(currentRocket->from)->outCodes += "308 " + QString::number(its.getNumber()) + " ";}
            if (toUs3 > 0) {toUs3--;}
            }

            countOfMissle--;
            used++;
    }


    int toUs2 = 0;
    for (int i = 0; i < nukesInAir->size(); i++)
        if ( nukesInAir->at(i).to == its.getNumber() && nukesInAir->at(i).count > 0 )
        {
            toUs2++;
        }


    this->setMissleDefence(this->getMissleDefence() - used);
    if (toUs1 > 0 && toUs2 == 0) { this->lvl += 1; }
    its.outCodes += "3001 " + QString::number(result) + " ";
    return used;
}

void Defence::getInformation(Government &its)
{
}

int Defence::stopNuclear(Government &its, Government &attack)
{
    this->nukesInAir = its.nukesInAir;
    for (int i = 0 ;i < nukesInAir->size(); i++)
    {
        if ( nukesInAir->at(i).from == its.getNumber() && nukesInAir->at(i).to == attack.getNumber())
        {
           nukesInAir->at(i).count = 0;
           break;
        }
    }
    return 1;
}

//нуждается в доработке
int Defence::marinesAttack(Government &its, Government &attack)
{
    int result = 0;
    this->numberOfEnemy = attack.getNumber();
    attack.underAttack.push_back( its.getNumber() );
    attack.timeUntilWar.push_back(2);
    attack.outCodes += "313 " + QString::number(its.getNumber()) + " ";
    its.outCodes += "314 " + QString::number(attack.getNumber()) + " ";
    return 1;

}

int Defence::raid(Government &its, Government &attack)
{
    int result = 0;
    this->numberOfEnemy = attack.getNumber();
    int luck;

	if (its.getMoney() > COST_OF_RAID)
	{
		its.setMoney(its.getMoney() - COST_OF_RAID);
        luck = TSOP(getLvl(), attack.ministers[2]->getTSOPlvl(3));
        if (luck > 0)
		{
			lvl++;
            result = 1;
            attack.outCodes += "400 " + QString::number(its.getNumber()) + " ";
			if (attack.getMoney() >= RAID_MONEY)
			{
				attack.setMoney(attack.getMoney() - RAID_MONEY);
				its.setMoney(its.getMoney() + RAID_MONEY);
			}
			else
			{
				its.setMoney(its.getMoney() + attack.getMoney());
				attack.setMoney(0);
			}
		}
	}
    return luck;
}

void Defence::checkNukes(Government &its)
{
    this->nukesInAir = its.nukesInAir;
    for (int i = 0; i<nukesInAir->size();i++)
    {
        if (nukesInAir->at(i).to == its.getNumber())
        nukesInAir->at(i).lifetime--;
    }

    while (nukesInAir->size() > 0)
    {
        if(nukesInAir->at(0).count <= 0)
        {
            nukesInAir->pop_front();
        }
        else
            break;
    }

    for (int i = 0; i<nukesInAir->size();i++)
    {
        if (nukesInAir->at(i).lifetime <= 0 && nukesInAir->at(i).to == its.getNumber())
        {
            explodeNuke(its,nukesInAir->at(i));
            nukesInAir->at(i).count = 0;
        }
    }
}

void Defence::explodeNuke(Government &its, NukeRocket rocket)
{
    int neighbour1 = 0, neighbour2 = 0;
    Government *ptrToN1, *ptrToN2;
    governments->getPtrToGov(rocket.from)->outCodes += "307 " + QString::number( its.getNumber() ) + " " + QString::number( rocket.count ) + " ";
    if (rocket.from != 0)
    governments->getPtrToGov(rocket.from)->ministers[2]->increaseLvl(*governments->getPtrToGov(rocket.from));
    for (int i = 0; i<rocket.count; i++)
    {
    its.setHappiness(its.getHappiness() / 2);
    its.setMoney(its.getMoney() / 2);
    its.setAgricultural(its.getAgricultural() / 2);
    its.setHeavyIndustrial(its.getHeavyIndustrial() / 2);
    its.setLightIndustrial(its.getLightIndustrial() / 2);
    this->setNuclear(this->getNuclear() / 2);
    this->setMissleDefence(this->getMissleDefence() / 2);
qDebug() << "ядерный взрыв, число команд: " << its.getCountOfTeam();
    if (its.getCountOfTeam() > 1)
        {
            if (its.getCountOfTeam() == 2)
            {
                neighbour1 = its.getNumber() + 1;
                if (neighbour1 > 2) {neighbour1 = 1;}

                ptrToN1 = governments->getPtrToGov(neighbour1);
                qDebug() << "ядерный взрыв, две команды, номер соседа: " << ptrToN1->getNumber();
                ptrToN1->setHappiness( ptrToN1->getHappiness() *3 /4 );
                ptrToN1->setMoney( ptrToN1->getMoney() *3 /4 );
                ptrToN1->setAgricultural( ptrToN1->getAgricultural() *3 /4 );
                ptrToN1->setHeavyIndustrial( ptrToN1->getHeavyIndustrial() *3 /4 );
                ptrToN1->setLightIndustrial( ptrToN1->getLightIndustrial() *3 /4 );
            }
            else
            {
                neighbour1 = its.getNumber() + 1;
                if (neighbour1 > its.getCountOfTeam()) {neighbour1 = 1;}

                neighbour2 = its.getNumber() - 1;
                if (neighbour2 < 1) {neighbour1 = its.getCountOfTeam();}
                ptrToN1 = governments->getPtrToGov(neighbour1);
                ptrToN2 = governments->getPtrToGov(neighbour2);

                                ptrToN1->setHappiness( ptrToN1->getHappiness() *3 /4 );
                                ptrToN2->setHappiness( ptrToN2->getHappiness() *3 /4 );

                                ptrToN1->setMoney( ptrToN1->getMoney() *3 /4 );
                                ptrToN2->setMoney( ptrToN2->getMoney() *3 /4 );

                                ptrToN1->setAgricultural( ptrToN1->getAgricultural() *3 /4 );
                                ptrToN1->setHeavyIndustrial( ptrToN1->getHeavyIndustrial() *3 /4 );
                                ptrToN1->setLightIndustrial( ptrToN1->getLightIndustrial() *3 /4 );
                                ptrToN2->setAgricultural( ptrToN2->getAgricultural() *3 /4 );
                                ptrToN2->setHeavyIndustrial( ptrToN2->getHeavyIndustrial() *3 /4 );
                                ptrToN2->setLightIndustrial( ptrToN2->getLightIndustrial() *3 /4 );
                }
        }
    }

    its.outCodes +="300 ";
    qDebug() << "После взрыва, номер соседа: " << neighbour1;
    if (neighbour1 != 0) {ptrToN1->outCodes += "306 " + QString::number(its.getNumber()) + " ";}
    if (neighbour2 != 0) {ptrToN2->outCodes += "306 " + QString::number(its.getNumber()) + " ";}

}

int Defence::giveNukes(Government &its, Government &attack, int count)
{
    if (its.getNukes() >= count)
    {
        its.setNukes(its.getNukes() - count);
        attack.setNukes(attack.getNukes() + count);
        attack.outCodes+= "210 " + QString::number(its.getNumber()) + " " + QString::number(count);
        return 1;
    }
    return 0;

}

int Defence::givePRO(Government &its, Government &attack, int count)
{
    if (its.getMissles() >= count)
    {
        its.setPRO(its.getMissles() - count);
        attack.setPRO(attack.getMissles() + count);
        attack.outCodes+= "211 " + QString::number(its.getNumber()) + " " + QString::number(count);
        return 1;
    }
    return 0;
}
