#pragma once
#include "Minister.h"
class MVD : public Minister
{
public:
	MVD();
	//подавить восстание
    int suppressRebellion(Government &its);
	//проверить, есть ли в вашем государстве завербованные министры
    int checkVerbed(Government &its);
	//развербовать министра
    int disverbed(Government &its, Government &attack, int numberOfMinister);
	// получить информацию о министре МВД
	void getInformation();
private:
	bool resultOfSearching;
};
