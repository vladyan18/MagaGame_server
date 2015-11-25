#include "rialto.h"
#include <stdlib.h>
#include <time.h>
#include <QTime>
#include <cmath>
#include <QDebug>
using namespace std;

Rialto::Rialto()
{
}

void Rialto::processData()
{
    qDebug() << "Запускаем биржу! Число игроков: " + QString::number(players.size());
    if (players.size() > 0)
    {
        double sMoments = 0;
        double sForces = 0;
        double newPoint = 0, midForce = 0,midLvl = 0;
        int randBet = 0;
        double sum = 0;
        double biggestM = 0;

        for (int i = 0; i<players.size(); i++)
        {
            sum += players[i].money;
            midLvl += players[i].lvl;
        }

        midLvl /= players.size();

        for (int i = 0; i<players.size(); i++)
        {
            if (players[i].money > biggestM) biggestM = players[i].money;
            sMoments += players[i].bet*players[i].money*players[i].lvl/midLvl;
            sForces += players[i].money*players[i].lvl/midLvl;
        }

        midForce = sForces / (players.size()*10);

        QTime midnight(0,0,0);
        qsrand(midnight.secsTo(QTime::currentTime()));
        randBet = ( (qrand() & 201) - 100);
        qDebug() << "Случайная цена: " << randBet;
        qDebug() << "Фиктивная сила: " << midForce;
        sMoments +=  randBet * midForce;
        sForces += midForce;

        newPoint = sMoments / sForces;
        qDebug() << "Равновесная цена: " << newPoint;

        int rMin = 201;
        int winner = -1;

        for (int i = 0; i<players.size();i++)
        {
            if (abs(players[i].bet - newPoint) < rMin)
            {
              rMin = abs(players[i].bet - newPoint);
              winner = i;
            }
        }

        double winKoef = 1;
        for (int i = 0; i<players.size();i++)
        {
            if (i == winner) continue;
            players[i].koeff = (players[i].money/biggestM)*(rMin / abs(players[i].bet - newPoint) ) /*/ log10(10 + abs(players[i].bet - newPoint)/rMin))*/;
            winKoef += players[i].koeff;
            qDebug() << QString::number(1 + i) + " коэфф = " + QString::number(players[i].koeff);
        }
        winKoef = 1 / winKoef;
            qDebug() <<  " коэффициент победителя " + QString::number(winKoef);

            Government *temp;
            for (int i = 0; i<players.size();i++)
            {
                if (i == winner) players[i].koeff = winKoef;
                else players[i].koeff *= winKoef;
                temp = governments->getPtrToGov( players[i].number );
                temp->changeMoney( int(sum * players[i].koeff) );
                temp->outCodes += "206 " + QString::number( int(sum * players[i].koeff - players[i].money) ) + " ";
            }

            players.clear();

    }

}
