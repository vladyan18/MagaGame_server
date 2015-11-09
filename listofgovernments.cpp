#include "listofgovernments.h"

ListOfGovernments::ListOfGovernments()
{
}

void ListOfGovernments::addToList(int numberOfTeam, Government *gov)
{
    govs[numberOfTeam] = gov;
}

void ListOfGovernments::deleteFromList(int numberOfTeam)
{
    govs[numberOfTeam] = NULL;

}

Government* ListOfGovernments::getPtrToGov(int numberOfTeam)
{
    return govs[numberOfTeam];
}
