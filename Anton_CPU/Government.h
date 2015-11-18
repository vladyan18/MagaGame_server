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
#include <CPU/rialto.h>
#include <CPU/nukesinair.h>

using namespace std;

class Command;
class Minister;
class Government // pеализует государство 
{
public:
    Minister *ministers[COUNT_OF_MINISTER+1];
	~Government();
	Government();
	Government(const Government &rhs);
    Government(int itsNumber, int itsCountOfTeam, ListOfGovernments*, Rialto*, deque<NukeRocket>*);

	double getMoney();
	int getNumber();
	int getCountOfTeam();
    int getNukes();
    int getMissles();
    void setNukes(int newNukes);
    void setPRO(int newPRO);
	short int getHappiness();

    void changeMoney (double difference);
	void setMoney(double newMoney);
	void setNumber(int newNumber);
	void setCountOfTeam(int newCountOfTeam);
	void setHappiness(short int newHappines);
	//получить информацию о текущем состоянии гос-ва
	void getInformation();
	//получить полную инфу о государстве
	void getFullInformation();
    void prepare();
    void postPrepare();
    void updateVerbedList(int countOfTeam);
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
    int doSecretaryCommand(Command);
    QString outCodes;
    bool isInRebellion = false;
    long getHeavyIndustrial();
    long getLightIndustrial();
    long getAgricultural();
    void setHeavyIndustrial(long);
    void  setLightIndustrial(long);
    void setAgricultural(long);
    Rialto *rialto;
    double **internationalHelp;
    deque<NukeRocket> *nukesInAir;
private:
	double money;								//казна
	int number;									//номер государства
	int countOfTeam;
	short int happiness;
    ListOfGovernments *governments;



};
