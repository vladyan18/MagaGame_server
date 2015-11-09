#ifndef MAINCPU_H
#define MAINCPU_H
#include <CPU/team.h>
#include <vector>
#include <QObject>
#include <listofgovernments.h>
using namespace std;

class MainCPU : public QObject
{
    Q_OBJECT
public:
    MainCPU();
    ListOfGovernments lGovs;
    void  addTeam(int numberOfTeam);
    void processData();
signals:
    void signalNewCountOfTeams(int newCount);

private:
    vector<Team> teams;
    void checkForMID(Command []);
};

#endif // MAINCPU_H
