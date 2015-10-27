#include "Government.h"
#include "Finance.h"
#include <fstream>

using namespace std;

double Finance::getAgriculture() { return agriculture; }
double Finance::getHeavyIndustry() { return heavyIndustry; }
double Finance::getLightIndustry() { return lightIndustry; }

void Finance::setAgriculture(double newAgriculture) { agriculture = newAgriculture; }
void Finance::setHeavyIndustry(double newHeavyIndustry) { heavyIndustry = newHeavyIndustry; }
void Finance::setLightIndustry(double newLightIndustry) { lightIndustry = newLightIndustry; }

int Finance::increaseSphere(Government &its, int numberOfSphere, int number2OfSphere)
{
	if (its.getMoney() >= COST_OF_INCREASE_ECONOMIC)
	{
        its.setMoney(its.getMoney() - COST_OF_INCREASE_ECONOMIC);
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
        return 1;
	}
    else
    {
        return 0;
    }
}

Finance::Finance()
{
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
