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

	//������� ��������� � ������������� ���
    int accuse(Government &its, Government &attack);
	//������������ ����
    int disslander(Government &its);
	//�������� ���������� ��������� � ����� ����������� 
    int increaseHappiness(Government &its, int countOfUp);
	//������� ���������
    int fireRebellion(Government &its, Government &attack, int countOfFire);
	// �������� ���������� � ���������� ������ � ���������������
	void getInformation(int countOfTeam);
private:
	bool *itsSlander;		//����� �����������, ��������� ���� (-1, ���� �����������)
    int countOfTeam;
    ListOfGovernments *governments;
	//int itsRebellion;	//����� �����������, ��������� ����� (-1, ���� �����������)
};
