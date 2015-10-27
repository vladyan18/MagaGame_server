#pragma once
#include "Minister.h"
#include "Constants.h"
#include <fstream>
//#include "Defence.h"
//#include "Finance.h"
//#include "President.h"
#include <CPU/team.h>

using namespace std;

class Command;
class Minister;
class Government // p�������� ����������� 
{
public:
	Minister *ministers[COUNT_OF_MINISTER];
	~Government();
	Government();
	Government(const Government &rhs);
	Government(int itsNumber, int itsCountOfTeam);

	double getMoney();
	int getNumber();
	int getCountOfTeam();
	short int getHappiness();

    int doCommand(Command);
    void changeMoney (double difference);
	void setMoney(double newMoney);
	void setNumber(int newNumber);
	void setCountOfTeam(int newCountOfTeam);
	void setHappiness(short int newHappines);
	//�������� ���������� � ������� ��������� ���-��
	void getInformation();
	//�������� ������ ���� � �����������
	void getFullInformation();
private:
	double money;								//�����
	int number;									//����� �����������
	int countOfTeam;
	short int happiness;
};
