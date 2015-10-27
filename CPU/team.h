#ifndef TEAM_H
#define TEAM_H
#include <deque>
#include <iostream>
#include <Anton_CPU/Government.h>
#include <QObject>

using namespace std;

struct Command
{
    int args[6];
    bool successful = false;
};

class Government;
class Team
{
public:
    Team(int, int);
    int numOfTeam;
    Command getTopCommand();
    void addCommand(Command);
    void setNum(int);
    void readData();
    void writeData();
    unsigned int numOfCommands;
    Government *government;

    deque< Command > listOfDidCommands;


private:

    static int countOfTeams;
    deque< Command > listOfCommands;
};


#endif // TEAM_H
