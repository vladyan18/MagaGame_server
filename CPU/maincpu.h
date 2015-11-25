#ifndef MAINCPU_H
#define MAINCPU_H
#include <CPU/team.h>
#include <deque>
#include <QObject>
#include <listofgovernments.h>
#include <CPU/rialto.h>
#include <CPU/nukesinair.h>
using namespace std;

class MainCPU : public QObject
{
    Q_OBJECT
public:
    MainCPU();
    ListOfGovernments lGovs;
    deque<NukeRocket> nukesInAir;
    void  addTeam(int numberOfTeam);
    Rialto *rialto;
    void processData();
    vector<Team> teams;
    void saveInHistory(int numberOfTeam, Command command);
signals:
    void signalNewCountOfTeams(int newCount);
    void needToUpdateHistory();

private:
    void checkForMID(Command []);
    int gameTime;
};

#endif // MAINCPU_H
