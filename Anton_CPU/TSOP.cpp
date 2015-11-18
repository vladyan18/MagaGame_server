#include <ctime>
#include "stdlib.h"
#include <cmath>
#include <QDebug>
using namespace std;

bool TSOP(double attackLvl, double defenceLvl)
{
    double dLvl = attackLvl - defenceLvl; // delta lvl
    qDebug() << "Произошло вычисление по ТСОП. 1:" + QString::number(attackLvl) +" , 2:" + QString::number(defenceLvl);

    if (dLvl >= 0)
	{
        double chanceToWin = 0.5;
        for (int i = 2; i <= dLvl+1; i++) //вычисляет шанс на победу атакующего
		{
            chanceToWin += pow(0.5,i);
		}
        chanceToWin *= 100;

        srand(clock());
        if (chanceToWin >= rand() % 100 + 1)
			return true;
		else
			return false;

	}
	else
	{
		return false;
	}
}
