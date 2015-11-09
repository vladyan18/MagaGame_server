#ifndef TEAM_H
#define TEAM_H
#include <deque>
#include <iostream>
#include <Anton_CPU/Government.h>
#include <QObject>
#include <listofgovernments.h>

using namespace std;

struct Command
{
    int args[7];
    bool successful = false;
};

class Government;
class ListOfGovernments;

class Team
{
public:
    Team(int, int, ListOfGovernments*);
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

    deque< Command > listOfDidCommands;


private:

    static int countOfTeams;
    deque< Command > listOfCommands;
};


#endif // TEAM_H
