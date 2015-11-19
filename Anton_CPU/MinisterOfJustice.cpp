#include "Government.h"
#include "MinisterOfJustice.h"
#include <fstream>
#include<QMessageBox>

using namespace std;

bool TSOP(double attackLvl, double defenceLvl);
MinisterOfJustice::MinisterOfJustice(Government *its)
{
    this->its = its;
}

int MinisterOfJustice::sue(Government &its, Government &attack, bool proof)
{
    int luck = 0;
    this->numberOfEnemy = attack.getNumber();

    QMessageBox *isItProof = new QMessageBox(
                "Есть доказательства?",
                "У команды №" + QString::number(its.getNumber()) + " есть доказательства против №"+ QString::number(attack.getNumber()) +"?",
                QMessageBox::Information,
                QMessageBox::Yes,
                QMessageBox::No,
                QMessageBox::NoButton);
    int n = isItProof->exec();

	if (its.getMoney() > COST_OF_SUE)
	{
		its.setMoney(its.getMoney() - COST_OF_SUE);
        if (n == QMessageBox::Yes)
			helpLvl++;
        luck = TSOP(getLvl(), attack.ministers[5]->getTSOPlvl(6));
        if (luck)
		{
			lvl++;
			attack.setHappiness(attack.getHappiness() - DECREASE_HAPPINESS_BY_SUE);
            return luck;
		}
		else
		{
			its.setHappiness(its.getHappiness() - DECREASE_HAPPINESS_BY_SUE);

		}
	}
    return luck;
}

void MinisterOfJustice::getInformation()
{
}
