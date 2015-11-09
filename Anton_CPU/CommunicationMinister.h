#pragma once
#include "Minister.h"
#include "listofgovernments.h"
class CommunicationMinister : public Minister
{
public:
	CommunicationMinister() {}
    CommunicationMinister(int countOfTeam, ListOfGovernments *gov);
	void setItsSlander(bool newItsSlander, int numOfTeam);
	//void setItsRebellion(int newItsRebellion);

	bool getItsSlander(int numOfTeam);
	//int getItsRebellion();

	//сделать заявления в международные СМИ
    int accuse(Government &its, Government &attack);
	//опровергнуть ложь
    int disslander(Government &its);
	//улучшить настроение населения в своем государстве 
    int increaseHappiness(Government &its, int countOfUp);
	//поджечь восстание
    int fireRebellion(Government &its, Government &attack, int countOfFire);
	// получить информацию о министрепо связям с общественностью
	void getInformation(int countOfTeam);
private:
	bool *itsSlander;		//номер государтсва, кинувшего ложь (-1, если отсутствует)
    int countOfTeam;
    ListOfGovernments *governments;
	//int itsRebellion;	//номер государтсва, кинувшего вирус (-1, если отсутствует)
};
