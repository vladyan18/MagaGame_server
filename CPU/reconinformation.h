#ifndef RECONINFORMATION_H
#define RECONINFORMATION_H
#include <vector>
#include <CPU/team.h>
using namespace std;

class Command;

class reconInformation
{
public:
    reconInformation() {}
    vector<Command> info;
    vector<Command> greatFail;
    int mode = 0;
};

#endif // RECONINFORMATION_H
