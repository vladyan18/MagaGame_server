#pragma once
#include "Minister.h"
#include <deque>
#include <listofgovernments.h>
#include <CPU/nukesinair.h>

struct NukeInAir
{
    int from;
    int lifetime;
    int count;
};

class Defence : public Minister
{
public:
    Defence(int countOfTeam, ListOfGovernments*);
	Defence();
    deque <NukeInAir> nukesToUs;
	int getNuclear();
    void checkNukes(Government&);
    void explodeNuke(Government&, NukeRocket);
	int getMissleDefence();
    ListOfGovernments *governments;
    deque<NukeRocket> *nukesInAir;
	void setNuclear(int newNuclear);
	void setMissleDefence(int newMissleDefence);

	//���������� ���-�� ������� �����
    int IncreaseCountOfNuclear(Government &its, int countOfNuclear);
    int DecreaseCountOfNuclear(Government &its, int countOfNuclear);
	//���������� ���-�� ���
    int IncreaseCountOfMissleDefence(Government &its, int countOfMissle);
	//���������� ���-�� ���
    int DecreaseCountOfMissleDefence(Government &its, int countOfMissle);

	//������ ������� ������
    int NuclearStrike(Government &its, Government &attack, int countOfNuclear);
	//����� ������� ������
    int shootDownNucler(Government &its, int countOfMissle);
	//�������� ������� ����
    int stopNuclear(Government &its, Government &attack);
	//������� �� ���-�� ����������� ������
    int marinesAttack(Government &its, Government &attack);
	//����� �� ����������� 
    int raid(Government &its, Government &attack);
	//�������� ���������� �� ���� ��������
	void getInformation(Government &its);
private:
	int nuclear;
	int missileDefense;

    int countOfTeams;
};
