#pragma once
#include "Minister.h"
class ForeignMinister : public Minister
{
public:
	ForeignMinister();
	ForeignMinister(int countOfTeam);
	//диверсия
    int sabotage(Government &its, Government &attack, int numOfMinister);
	//завербовать министра
    int verb(Government &its, Government &attack, int numberOfMinister);
	//развербовать министра
    int reverb(Government &its, Government &attack, int numberOfMinister);
	//убить министра
    int kill(Government &its, Government &attack, int numberOfMinister);
	//слежка
    int track(Government &its, Government &attack, int numberOfMinister);
	//отдать приказ министру
    int order();
	// получить информацию о министре внутренних дел
	void getInformation(int countOfTeam);
    bool **verbedList;
private:

};
