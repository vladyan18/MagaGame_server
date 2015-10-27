#pragma once
#include "Minister.h"
class HealthMinister : public Minister
{
public:
	HealthMinister() {}
	HealthMinister(int countOfTeam);
	//�������� ���������� � �������� ���������������
    void getInformation(int countOfTeam);
	//�������� �������
    int infectingVirus(Government &its, Government &attack);
	//����������� �������
    int vaccine(Government &its, Government &attack);

	void setVirus(bool newVirus, int numOfTeam);
	bool getVirus(int numOfTeam);

	void setStepOfVirus(int newStep, int numOfTeam);
	int getStepOfVirus(int numOfTeam);

private:
	bool *virus;
	int *stepOfVirus;
};
