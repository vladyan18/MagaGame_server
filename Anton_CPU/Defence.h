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

	//увеличение кол-ва ядерных ракет
    int IncreaseCountOfNuclear(Government &its, int countOfNuclear);
    int DecreaseCountOfNuclear(Government &its, int countOfNuclear);
	//увеличение кол-ва ПРО
    int IncreaseCountOfMissleDefence(Government &its, int countOfMissle);
	//уменьшение кол-ва ПРО
    int DecreaseCountOfMissleDefence(Government &its, int countOfMissle);

	//запуск ядерной ракеты
    int NuclearStrike(Government &its, Government &attack, int countOfNuclear);
	//сбить ядерную ракету
    int shootDownNucler(Government &its, Government &attack, int countOfMissle);
	//отменить ядерный удар
    int stopNuclear(Government &its, Government &attack, int countOfNuclear);
	//напасть на гос-во сухопутными силами
    int marinesAttack(Government &its, Government &attack);
	//набег на государство 
    int raid(Government &its, Government &attack);
	//получить информацию об этом министре
	void getInformation(Government &its);
private:
	int nuclear;
	int missileDefense;
	int * nuclearOnYou1;//ракеты, выпущенные в предыдущем ходу
	int * nuclearOnYou2; //ракеты выпущенные в этом ходу
};
