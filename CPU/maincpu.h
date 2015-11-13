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
signals:
    void signalNewCountOfTeams(int newCount);

private:
    vector<Team> teams;
    void checkForMID(Command []);
};

#endif // MAINCPU_H
