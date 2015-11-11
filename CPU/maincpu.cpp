#include "maincpu.h"
#include <QDebug>



MainCPU::MainCPU()
{
    rialto = new Rialto(&lGovs);
}


void MainCPU::addTeam(int numberOfTeam)
{
    Team *team = new Team(numberOfTeam, teams.size() + 1, &lGovs, rialto);
    teams.push_back(*team);

    for(int i = 0; i<teams.size()-1; i++)
    {
        teams[i].government->updateVerbedList(teams.size() );
    }
}

void MainCPU::processData()
{
    for (int i = 0; i< teams.size();i++)        
    {
        teams[i].prepare();
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
                Command temp = currPriority[j];
                temp.successful = result;
                if (temp.args[0] != -1)
                teams[j].listOfDidCommands.push_back(temp);
            }
        }
    }


    rialto->processData();
    for (int i = 0; i<teams.size();i++)
    {
        teams[i].writeData();
    }

}

bool TSOP(double attackLvl, double defenceLvl);

void MainCPU::checkForMID(Command *commands)
{
    Command temp;
    bool didIt = false;
    for (int i = 0; i<teams.size(); i++)
    {
    if (commands[i].args[0] == 5 && commands[i].args[1] == 1)
        {
        temp = commands[i];
        if (teams[i].government->getMoney() >= COST_OF_SABOTAGE)
        {
            qDebug() << "Попытка саботажа.";
            teams[i].government->changeMoney(-COST_OF_SABOTAGE);
        if (TSOP(teams[i].government->ministers[4]->getTSOPlvl() , teams[commands[i].args[2]-1].government->ministers[commands[i].args[3]-1]->getTSOPlvl() ))
            {
            qDebug() << "ТСОП - победа!";

                if (commands[ commands[i].args[2]-1 ].args[0] == commands[i].args[3])
                {
                    didIt = true;
                    if (commands[ commands[i].args[2]-1 ].args[0] != -1)
                    teams[commands[i].args[2]-1 ].listOfDidCommands.push_back(commands[ commands[i].args[2]-1 ]);
                    commands[ commands[i].args[2]-1 ].args[0] = -1;
                    commands[ commands[i].args[2]-1 ].args[1] = -1;
                    commands[ commands[i].args[2]-1 ].args[2] = -1;
                    commands[ commands[i].args[2]-1 ].args[3] = -1;
                    commands[ commands[i].args[2]-1 ].args[4] = -1;
                    commands[ commands[i].args[2]-1 ].args[5] = -1;
                }

            if (!didIt) {didIt = teams[ commands[i].args[2]-1 ].sabotage( commands[i].args[3]);}
                if (didIt)
                {
                    teams[i].government->ministers[4]->increaseLvl((*teams[i].government));
                    temp.successful = 1;
                    teams[commands[i].args[2]-1].government->outCodes += "100 ";
                }
            }
        }
        commands[i].args[0] = -1;
        commands[i].args[1] = -1;
        commands[i].args[2] = -1;
        commands[i].args[3] = -1;
        commands[i].args[4] = -1;
        commands[i].args[5] = -1;
        teams[i].listOfDidCommands.push_back(temp);
        break;
        }

    if (commands[i].args[0] == 5 && commands[i].args[1] == 4)
        {
        temp = commands[i];
        if (teams[i].isVerbed(commands[i].args[2]-1, commands->args[3]-1 ) )
            {

                if (true /*commands[commands[i].args[2]-1].args[0] == commands->args[3]*/)
                {
                 commands[commands[i].args[2]-1].args[0]  = commands->args[3];
                 commands[commands[i].args[2]-1].args[1]  = commands->args[4];
                 commands[commands[i].args[2]-1].args[2]  = commands->args[5];
                 commands[commands[i].args[2]-1].args[3]  = commands->args[6];
                 commands[commands[i].args[2]-1].args[4]  = -1;
                 commands[commands[i].args[2]-1].args[5]  = -1;
                 commands[commands[i].args[2]-1].args[6]  = -1;
                 temp.successful = 1;
                }

            }
        commands[i].args[0] = -1;
        commands[i].args[1] = -1;
        commands[i].args[2] = -1;
        commands[i].args[3] = -1;
        commands[i].args[4] = -1;
        commands[i].args[5] = -1;
        commands[i].args[6] = -1;

        teams[i].listOfDidCommands.push_back(temp);
        break;
        }
    }
}

