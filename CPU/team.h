#ifndef TEAM_H
#define TEAM_H
#include <deque>
#include <iostream>
#include <Anton_CPU/Government.h>
#include <QObject>
#include <listofgovernments.h>
#include <CPU/rialto.h>
#include <CPU/nukesinair.h>
#include <CPU/reconinformation.h>
#include <command.h>

using namespace std;
class Rialto;
class NukesInAir;
class reconInformation;

class Government;
class ListOfGovernments;

class Team
{
public:
    Team(int, int, ListOfGovernments*, Rialto*, deque<NukeRocket>* );
    int numOfTeam;
    Command getTopCommand();
    void addCommand(Command);
    void setNum(int);
    void readData();
    void writeData();
    void prepare();
    void postPrepare();
    void addToGreatFails(int numberOfTeam, Command com);

    void updateReconList(int newCountOfTeams);
    bool isVerbed(int country, int min);
    int sabotage(int numOfMin);
    unsigned int numOfCommands;
    Government *government;
    Rialto *rialto;
    deque<NukeRocket> *nukesInAir;

    deque< Command > listOfDidCommands;
    reconInformation *recon;
    deque< Command > listOfCommands;
    static int countOfTeams;
    static int sumProfitInAgro;
    static int sumProfitInLightInd;
    static int sumProfitInHeavyInd;
    int listOfDidCommandsSize;

private:



};


#endif // TEAM_H
