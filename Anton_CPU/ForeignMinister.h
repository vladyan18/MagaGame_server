#pragma once
#include "Minister.h"
class ForeignMinister : public Minister
{
public:
	ForeignMinister();
	ForeignMinister(int countOfTeam);
	//��������
    int sabotage(Government &its, Government &attack, int numOfMinister);
	//����������� ��������
    int verb(Government &its, Government &attack, int numberOfMinister);
	//������������ ��������
    int reverb(Government &its, Government &attack, int numberOfMinister);
	//����� ��������
    int kill(Government &its, Government &attack, int numberOfMinister);
	//������
    int track(Government &its, Government &attack, int numberOfMinister);
	//������ ������ ��������
    int order();
	// �������� ���������� � �������� ���������� ���
	void getInformation(int countOfTeam);
    bool **verbedList;
private:

};
