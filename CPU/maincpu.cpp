#include "maincpu.h"
#include <QDebug>


MainCPU::MainCPU()
{
}


void MainCPU::addTeam(int numberOfTeam)
{
    Team *team = new Team(numberOfTeam, teams.size() + 1);
    teams.push_back(*team);
}

void MainCPU::processData()
{
    for (int i = 0; i< teams.size();i++)
    {
                        qDebug() << "Читаем!";
        teams[i].readData();
    }

    Command *currPriority = new Command[teams.size()];
    bool eofList = false;
    while (!eofList)
    {
        eofList = true;
        for (unsigned int i = 0; i<teams.size();i++)
        {
            qDebug() << "Берем из очереди команду!";
            currPriority[i] = teams[i].getTopCommand();
                            qDebug() << "Взяли команду!";
            eofList = eofList && (currPriority[i].args[0] == -1);
                            qDebug() << "Проверили на конец листа!";
        }

        if (!eofList)
        {
                qDebug() << "Проверяем на диверсии!";
            checkForMID(currPriority);
            int result;
            for (unsigned int j = 0; j<teams.size();j++)
            {
                qDebug() << "Выполняем команду!";
                result = teams[j].government->doCommand(currPriority[j]);
            }
        }
    }


    for (int i = 0; i<teams.size();i++)
    {
        teams[i].writeData();
                        qDebug() << "Выводим инфу!";
        teams[i].government->getFullInformation();
                        qDebug() << "Выводим полную инфу!";
    }

}

void MainCPU::checkForMID(Command *commands)
{

}

