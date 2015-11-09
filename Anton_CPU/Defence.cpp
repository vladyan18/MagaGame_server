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

Defence::Defence(int countOfTeam, ListOfGovernments *governments)
{
    this->governments = governments;
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
	Defence *attackDefence = (Defence*)(attack.ministers[2]);

    NukeInAir *newNuke = new NukeInAir;
    newNuke->from = its.getNumber();
    newNuke->count = countOfNuclear;
    newNuke->lifetime = 2;
    attackDefence->nukesToUs.push_back(*newNuke);
    delete newNuke;
    attack.outCodes += QString::number(3100 + its.getNumber() ) + " ";
    // добавить оповещение всем!
    return 1;
    }
    else return 0;
}

int Defence::shootDownNucler(Government &its, int countOfMissle)
{

    int result = 0, used = 0;
    while (nukesToUs.size() > 0 && countOfMissle > 0)
    {
        if (nukesToUs[0].count > 0)
        {
            if (TSOP(its.ministers[2]->getTSOPlvl(), governments->getPtrToGov(nukesToUs[0].from)->ministers[2]->getTSOPlvl()))
            {
                qDebug() << "Ракета сбита!";
            nukesToUs[0].count--;
            } else qDebug() << "Промах!";
            countOfMissle--;
            used++;
        }
        else
        {
            nukesToUs.pop_front();
        }

        if (nukesToUs.size() == 0 ) {result = 1;}
    }

    this->setMissleDefence(this->getMissleDefence() - used);
    if (result && used) {this->lvl+=1;}
    return result;
}

void Defence::getInformation(Government &its)
{
}

int Defence::stopNuclear(Government &its, Government &attack)
{
	Defence *attacked = (Defence*)(attack.ministers[2]);
    for (int i = 0;i < attacked->nukesToUs.size();i++)
    {
        if (attacked->nukesToUs[i].from == its.getNumber())
        {
           attacked->nukesToUs[i].count = 0;
           break;
        }
    }
    return 1;
}

//нуждается в доработке
int Defence::marinesAttack(Government &its, Government &attack)
{
    int result = 0;
	if (TSOP(getTSOPlvl(), attack.ministers[0]->getTSOPlvl() + attack.ministers[2]->getTSOPlvl()))
	{
        result = 1;
		its.setMoney(its.getMoney() + attack.getMoney());
		Defence *attacked = (Defence*)(attack.ministers[2]);
		nuclear += attacked->getNuclear();
		missileDefense += attacked->getMissleDefence();
        attack.outCodes += QString::number(500 + its.getNumber() ) + " ";
	}
    return result;
}

int Defence::raid(Government &its, Government &attack)
{
    int result = 0;
	if (its.getMoney() > COST_OF_RAID)
	{
		its.setMoney(its.getMoney() - COST_OF_RAID);
		if (TSOP(getTSOPlvl(), attack.ministers[0]->getTSOPlvl()))
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
    return result;
}

void Defence::checkNukes(Government &its)
{
    for (int i = 0; i<nukesToUs.size();i++)
    {
        nukesToUs[i].lifetime--;
    }

    while (nukesToUs.size() > 0)
    {
        if(nukesToUs[0].count <= 0)
        {
            nukesToUs.pop_front();
        }
        else
            break;
    }

    while (nukesToUs.size() > 0)
    {
        if (nukesToUs[0].lifetime <= 0)
        {
            explodeNuke(its,nukesToUs[0]);
            nukesToUs.pop_front();
        }
        else
            break;
    }
}

void Defence::explodeNuke(Government &its, NukeInAir rocket)
{
    governments->getPtrToGov(rocket.from)->ministers[2]->increaseLvl(*governments->getPtrToGov(rocket.from));
    for (int i = 0; i<rocket.count; i++)
    {
    its.setHappiness(its.getHappiness() / 2);
    its.setMoney(its.getMoney() / 2);
    }

    its.outCodes +="300 ";
}
