#pragma once
#include "Minister.h"
class Finance : public Minister
{
public:
    Finance(Government *its);
    Finance();
	//изменение дохода в 2 сферах экономики
    int increaseSphere(Government &its, int numberOfSphere, int number2OfSphere);
    int play(Government &its, int price, int money);
    int doTrans(Government &its, Government &to, int money);
    int giveFac(Government &its, Government &to, int type, int count);

	double getAgriculture();
	double getHeavyIndustry();
	double getLightIndustry();

    void setAgriculture(long newAgriculture);
    void setHeavyIndustry(long newHeavyIndustry);
    void setLightIndustry(long newLightIndustry);


	//получить информацию о министре финансов
	void getInformation();
private:
	double agriculture;
	double heavyIndustry;
	double lightIndustry;
};
