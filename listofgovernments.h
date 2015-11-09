#ifndef LISTOFGOVERNMENTS_H
#define LISTOFGOVERNMENTS_H
#include <Anton_CPU/Government.h>
#include <map>
using namespace std;

class Government;

class ListOfGovernments
{
private:
    map<int, Government*, less<int> > govs;
public:
    ListOfGovernments();
    void addToList(int numberOfTeam, Government* gov);
    void deleteFromList(int numberOfTeam);
    Government* getPtrToGov(int numberOfTeam);
};

#endif // LISTOFGOVERNMENTS_H
