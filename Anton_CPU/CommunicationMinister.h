#pragma once
#include "Minister.h"
#include "listofgovernments.h"
class CommunicationMinister : public Minister
{
public:
	CommunicationMinister() {}
    CommunicationMinister(Government *its,int countOfTeam, ListOfGovernments *gov);
	void setItsSlander(bool newItsSlander, int numOfTeam);
	//void setItsRebellion(int newItsRebellion);

	bool getItsSlander(int numOfTeam);
	//int getItsRebellion();
    void updateSlander();

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
    bool *itsSlander;
private:
        //����� �����������, ��������� ���� (-1, ���� �����������)
    int countOfTeam;
    ListOfGovernments *governments;
	//int itsRebellion;	//����� �����������, ��������� ����� (-1, ���� �����������)
};
