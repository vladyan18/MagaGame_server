#include "Government.h"
#include "Finance.h"
#include <fstream>
#include <QDebug>

using namespace std;

double Finance::getAgriculture() { return agriculture; }
double Finance::getHeavyIndustry() { return heavyIndustry; }
double Finance::getLightIndustry() { return lightIndustry; }

void Finance::setAgriculture(long newAgriculture) { agriculture = newAgriculture; }
void Finance::setHeavyIndustry(long newHeavyIndustry) { heavyIndustry = newHeavyIndustry; }
void Finance::setLightIndustry(long newLightIndustry) { lightIndustry = newLightIndustry; }

int Finance::increaseSphere(Government &its, int numberOfSphere, int number2OfSphere)
{

	if (its.getMoney() >= COST_OF_INCREASE_ECONOMIC)
	{
        int *sphere, *sphere2, result = 0;
        switch (numberOfSphere)
        {
        case 1:
            sphere = &(its.team->sumProfitInAgro);
            break;
        case 2:
            sphere = &(its.team->sumProfitInHeavyInd);
            break;
        case 3:
            sphere = &(its.team->sumProfitInLightInd);
            break;
        }

        switch (number2OfSphere)
        {
        case 1:
            sphere2 = &(its.team->sumProfitInAgro);
            break;
        case 2:
            sphere2 = &(its.team->sumProfitInHeavyInd);
            break;
        case 3:
            sphere2 = &(its.team->sumProfitInLightInd);
            break;
        }

        if (*sphere < its.team->countOfTeams * 2000000)
        {
        its.setMoney(its.getMoney() - COST_OF_INCREASE_ECONOMIC/2);
		switch (numberOfSphere)
            {
            case 1:
                agriculture += SPHERE_INCREASE;
                break;
            case 2:
                heavyIndustry += SPHERE_INCREASE;
                break;
            case 3:
                lightIndustry += SPHERE_INCREASE;
                break;

            }
        *sphere += SPHERE_INCREASE;
        result = 1;
        }

        if (*sphere2 < its.team->countOfTeams *2000000)
        {
        its.setMoney(its.getMoney() - COST_OF_INCREASE_ECONOMIC/2);
        switch (number2OfSphere)
            {
            case 1:
                agriculture += SPHERE_INCREASE;
                break;
            case 2:
                heavyIndustry += SPHERE_INCREASE;
                break;
            case 3:
                lightIndustry += SPHERE_INCREASE;
                break;
            }
        result = 1;
        }
        *sphere2 += SPHERE_INCREASE;
        return result;
	}
    else
    {
        return 0;
    }
}

int Finance::play(Government &its, int price, int money)
{
    if (its.getMoney() >= money)
    {
        its.changeMoney( -money );

        its.rialto->addPlayer(its.getNumber(), this->getLvl(), money, price);
        return 1;
    }
    else
    {

        return 0;
    }
    return 1;
}

int Finance::doTrans(Government &its, Government &to, int money)
{
    if (its.getMoney() >= money)
    {
        its.changeMoney(-money);
        to.changeMoney( money );
        to.outCodes += "205 " + QString::number( money ) + " " + QString::number( its.getNumber() ) + " ";
        return 1;
    }
    else {return 0;}
}

int Finance::giveFac(Government &its, Government &to, int type,int count)
{
    switch(type)
    {
    case 1:
        if (its.getAgricultural() >= count)
        {
            its.setAgricultural(its.getAgricultural() - count);
            to.setAgricultural(to.getAgricultural() + count);
            to.outCodes+= "212 " + QString::number(type) + " ";
            return 1;
        }
        break;
    case 2:
        if (its.getHeavyIndustrial() >= count)
        {
            its.setHeavyIndustrial(its.getHeavyIndustrial() - count);
            to.setHeavyIndustrial(to.getHeavyIndustrial() + count);
            to.outCodes+= "212 " + QString::number(its.getNumber()) + " " + QString::number(type) + " " + QString::number(count) + " ";
            return 1;
        }
        break;
    case 3:
        if (its.getLightIndustrial() >= count)
        {
            its.setLightIndustrial(its.getLightIndustrial() - count);
            to.setLightIndustrial(to.getLightIndustrial() + count);
            to.outCodes+= "212 " + QString::number(type) + " ";
            return 1;
        }
        break;
    }

    return 0;
}

Finance::Finance(Government *its)
{
    this->its = its;
	agriculture = START_SPHERE;
	heavyIndustry = START_SPHERE;
	lightIndustry = START_SPHERE;

}

void Finance::getInformation()
{
	ofstream fout("Civ.out", ios_base::app);
	fout << "У министра финансов " << lvl << " lvl" << endl;
	fout << "Доход от сельского хозяйства:= " << agriculture << endl;
	fout << "Доход от тяжелой промышленности:= " << heavyIndustry << endl;
	fout << "Доход от легкой промышленности:= " << lightIndustry << endl;
	fout.close();
}
