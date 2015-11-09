#pragma once
#include "Minister.h"
#include "Constants.h"
#include <fstream>
//#include "Defence.h"
//#include "Finance.h"
//#include "President.h"
#include <CPU/team.h>
#include <listofgovernments.h>
#include <QString>

using namespace std;

class Command;
class Minister;
class Government // p�������� ����������� 
{
public:
    Minister *ministers[COUNT_OF_MINISTER+1];
	~Government();
	Government();
	Government(const Government &rhs);
    Government(int itsNumber, int itsCountOfTeam, ListOfGovernments*);

	double getMoney();
	int getNumber();
	int getCountOfTeam();
    int getNukes();
    int getMissles();
	short int getHappiness();

    void changeMoney (double difference);
	void setMoney(double newMoney);
	void setNumber(int newNumber);
	void setCountOfTeam(int newCountOfTeam);
	void setHappiness(short int newHappines);
	//�������� ���������� � ������� ��������� ���-��
	void getInformation();
	//�������� ������ ���� � �����������
	void getFullInformation();
    void prepare();
    bool isVerbed(int country, int min);
    int doCommand(Command);
    int doPresidentCommand(Command);
    int doMinFinCommand(Command);
    int doMinDefCommand(Command);
    int doKGBCommand(Command);
    int doMIDCommand(Command);
    int doMinUstCommand(Command);
    int doMVDCommand(Command);
    int doMinComCommand(Command);
    int doMinHelCommand(Command);
    QString outCodes;
    bool isInRebellion = false;
private:
	double money;								//�����
	int number;									//����� �����������
	int countOfTeam;
	short int happiness;
    ListOfGovernments *governments;

};
