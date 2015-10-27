#include <ctime>
#include "stdlib.h"
#include <cmath>
using namespace std;

bool TSOP(double attackLvl, double defenceLvl) // вычисление победителя 
{
    double dLvl = attackLvl - defenceLvl; // delta lvl

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
