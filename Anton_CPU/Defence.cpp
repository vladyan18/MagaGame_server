#include "Government.h"
#include "Defence.h"
#include <fstream>
#include <QDebug>

using namespace std;

bool TSOP(double attackLvl, double defenceLvl);

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
	for (int i = 0;i < countOfTeam;i++)
	{
        nukesToUs[i].from = 0;
        nukesToUs[i].count = 0;
        nukesToUs[i].lifetime = 0;
	}
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
    return result;
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
    return result;
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
    return result;
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
    return result;
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

    for (int i = 0; i < countOfTeams; i++)
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
            qDebug() << "На нас летит " + QString::number(toUs1);
    while (nukesInAir->size() > 0 && countOfMissle > 0)
    {
        currentRocket = NULL;

        if (toUs3 == 0)
        {
            for (int i = 0; i < nukesInAir->size(); i++)
                if (nukesInAir->at(i).count > 0 && nukesInAir->at(i).from != its.getNumber())
                {
                    qDebug() << "В небе ракета!";
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

            if (TSOP(its.ministers[2]->getTSOPlvl(3), governments->getPtrToGov(currentRocket->from)->ministers[2]->getTSOPlvl(3)) )
            {
            qDebug() << "Ракета сбита!";
            currentRocket->count--;
            result++;
            if (toUs3 > 0) {toUs3--;}
            } else qDebug() << "Промах!";
            countOfMissle--;
            used++;
    }


    int toUs2 = 0;
    for (int i = 0; i < nukesInAir->size(); i++)
        if ( nukesInAir->at(i).to == its.getNumber() && nukesInAir->at(i).count > 0 )
        {
            toUs2++;
        }
    qDebug() << "Теперь на нас летит " + QString::number(toUs2);

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
    int luck;
    luck = TSOP(getTSOPlvl(3), attack.ministers[0]->getTSOPlvl(1) + attack.ministers[2]->getTSOPlvl(3));
    if (luck)
	{
        result = 1;
		its.setMoney(its.getMoney() + attack.getMoney());
		Defence *attacked = (Defence*)(attack.ministers[2]);
		nuclear += attacked->getNuclear();
		missileDefense += attacked->getMissleDefence();
        attack.outCodes += QString::number(500)  + QString::number(its.getNumber() ) + " ";
	}
    return luck;
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
        if (luck)
		{
			lvl++;
            result = 1;
            attack.outCodes += QString::number(400 + its.getNumber()) + " ";
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
    governments->getPtrToGov(rocket.from)->ministers[2]->increaseLvl(*governments->getPtrToGov(rocket.from));
    for (int i = 0; i<rocket.count; i++)
    {
    its.setHappiness(its.getHappiness() / 2);
    its.setMoney(its.getMoney() / 2);
    // toDo
    }

    its.outCodes +="300 ";
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
