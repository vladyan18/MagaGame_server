#ifndef RIALTO_H
#define RIALTO_H
#include <Anton_CPU/Government.h>
#include <listofgovernments.h>
#include <vector>
using namespace std;

class ListOfGovernments;

struct player
{
    int number;
    int lvl;
    int money;
    int bet;
    double koeff;
};

class Rialto
{
public:
    Rialto();
    Rialto(ListOfGovernments *govs) {this->governments = govs;}
    void processData();

    int addPlayer(int number, int lvl, int money, int bet)
    {
        player *newPlayer = new player;
        newPlayer->lvl = lvl;
        newPlayer->money = money;
        newPlayer->number = number;
        newPlayer->bet = bet;
        players.push_back(*newPlayer);
        delete newPlayer;
        return 1;
    }

private:
    ListOfGovernments *governments;
    vector<player> players;
};

#endif // RIALTO_H
