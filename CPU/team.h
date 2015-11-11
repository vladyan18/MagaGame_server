#ifndef TEAM_H
#define TEAM_H
#include <deque>
#include <iostream>
#include <Anton_CPU/Government.h>
#include <QObject>
#include <listofgovernments.h>
#include <CPU/rialto.h>

using namespace std;
class Rialto;

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
    Team(int, int, ListOfGovernments*, Rialto* );
    int numOfTeam;
    Command getTopCommand();
    void addCommand(Command);
    void setNum(int);
    void readData();
    void writeData();
    void prepare();
    bool isVerbed(int country, int min);
    int sabotage(int numOfMin);
    unsigned int numOfCommands;
    Government *government;
    Rialto *rialto;

    deque< Command > listOfDidCommands;


private:

    static int countOfTeams;
    deque< Command > listOfCommands;
};


#endif // TEAM_H
