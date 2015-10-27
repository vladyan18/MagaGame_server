#pragma once
#include "Minister.h"
class CommunicationMinister : public Minister
{
public:
	CommunicationMinister() {}
	CommunicationMinister(int countOfTeam);
	void setItsSlander(bool newItsSlander, int numOfTeam);
	//void setItsRebellion(int newItsRebellion);

	bool getItsSlander(int numOfTeam);
	//int getItsRebellion();

	//������� ��������� � ������������� ���
    int accuse(Government &its, Government &attack);
	//������������ ����
    int disslander(Government &its, Government &attack);
	//�������� ���������� ��������� � ����� ����������� 
    int increaseHappiness(Government &its, int countOfUp);
	//������� ���������
    int fireRebellion(Government &its, Government &attack, int countOfFire);
	// �������� ���������� � ���������� ������ � ���������������
	void getInformation(int countOfTeam);
private:
	bool *itsSlander;		//����� �����������, ��������� ���� (-1, ���� �����������)
	//int itsRebellion;	//����� �����������, ��������� ����� (-1, ���� �����������)
};
