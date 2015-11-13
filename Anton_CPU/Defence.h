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
    int shootDownNucler(Government &its, int countOfMissle);
	//отменить ядерный удар
    int stopNuclear(Government &its, Government &attack);
	//напасть на гос-во сухопутными силами
    int marinesAttack(Government &its, Government &attack);
	//набег на государство 
    int raid(Government &its, Government &attack);
	//получить информацию об этом министре
	void getInformation(Government &its);
private:
	int nuclear;
	int missileDefense;

    int countOfTeams;
};
