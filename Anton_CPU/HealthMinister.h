#pragma once
#include "Minister.h"
class HealthMinister : public Minister
{
public:
	HealthMinister() {}
	HealthMinister(int countOfTeam);
	//получить информацию и министре здравоозранения
    void getInformation(int countOfTeam);
	//заразить вирусом
    int infectingVirus(Government &its, Government &attack);
	//разработать вакцину
    int vaccine(Government &its, Government &attack);

	void setVirus(bool newVirus, int numOfTeam);
	bool getVirus(int numOfTeam);

	void setStepOfVirus(int newStep, int numOfTeam);
	int getStepOfVirus(int numOfTeam);

private:
	bool *virus;
	int *stepOfVirus;
};
