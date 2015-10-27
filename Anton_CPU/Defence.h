#pragma once
#include "Minister.h"
class Defence : public Minister
{
public:
	Defence(int countOfTeam);
	Defence();

	int getNuclear();
	int getMissleDefence();
	int getNuclearOnYou1(int NumOfTeam);
	int getNuclearOnYou2(int NumOfTeam);

	void setNuclear(int newNuclear);
	void setMissleDefence(int newMissleDefence);
	void setNuclearOnYou1(int numOfTeam, int newNuclearOnYou1);
	void setNuclearOnYou2(int numOfTeam, int newNuclearOnYou2);

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
    int shootDownNucler(Government &its, Government &attack, int countOfMissle);
	//�������� ������� ����
    int stopNuclear(Government &its, Government &attack, int countOfNuclear);
	//������� �� ���-�� ����������� ������
    int marinesAttack(Government &its, Government &attack);
	//����� �� ����������� 
    int raid(Government &its, Government &attack);
	//�������� ���������� �� ���� ��������
	void getInformation(Government &its);
private:
	int nuclear;
	int missileDefense;
	int * nuclearOnYou1;//������, ���������� � ���������� ����
	int * nuclearOnYou2; //������ ���������� � ���� ����
};
