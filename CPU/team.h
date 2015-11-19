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

using namespace std;
class Rialto;
class NukesInAir;
class reconInformation;

struct Command
{
    int args[7];
    int successful = 0;
};

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
    void updateReconList(int newCountOfTeams);
    bool isVerbed(int country, int min);
    int sabotage(int numOfMin);
    unsigned int numOfCommands;
    Government *government;
    Rialto *rialto;
    deque<NukeRocket> *nukesInAir;

    deque< Command > listOfDidCommands;
    reconInformation* recon;
    deque< Command > listOfCommands;
    static int countOfTeams;
    int listOfDidCommandsSize;

private:



};


#endif // TEAM_H
