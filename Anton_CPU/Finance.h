#pragma once
#include "Minister.h"
class Finance : public Minister
{
public:
	Finance();
	//изменение дохода в 2 сферах экономики
    int increaseSphere(Government &its, int numberOfSphere, int number2OfSphere);
    int play(Government &its, int price, int money);
    int doTrans(Government &its, Government &to, int money);

	double getAgriculture();
	double getHeavyIndustry();
	double getLightIndustry();

	void setAgriculture(double newAgriculture);
	void setHeavyIndustry(double newHeavyIndustry);
	void setLightIndustry(double newLightIndustry);


	//получить информацию о министре финансов
	void getInformation();
private:
	double agriculture;
	double heavyIndustry;
	double lightIndustry;
};
