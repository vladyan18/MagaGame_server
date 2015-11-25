#include "maincpu.h"
#include <ctime>
#include <QDebug>
#include <QFile>



MainCPU::MainCPU()
{
    rialto = new Rialto(&lGovs);
    gameTime = -1;
    QFile historyFile("history.txt");
    historyFile.open(QFile::WriteOnly);
    historyFile.close();
}


void MainCPU::addTeam(int numberOfTeam)
{
    Team *team = new Team(numberOfTeam, teams.size() + 1, &lGovs, rialto, &nukesInAir);
    teams.push_back(*team);

    qDebug() << "Обновление списков " << teams.size();
    for(int i = 0; i<teams.size() - 1; i++)
    {
        teams[i].government->updateVerbedList( teams.size() );
        teams[i].updateReconList( teams.size() );
        qDebug() << "Список обновлен";
    }
        qDebug() << "Обновление списков закончено";
}

void MainCPU::processData()
{
    gameTime++;
    QFile historyFile("history.txt");
    QTextStream stream(&historyFile);
    historyFile.open(QFile::Append);
    stream << endl <<"N" << " "<< QString::number(gameTime) << endl;
    historyFile.close();

    Team::sumProfitInAgro = 0;
    Team::sumProfitInHeavyInd = 0;
    Team::sumProfitInLightInd = 0;
    for (int i = 0; i< teams.size();i++)        
    {
        Team::sumProfitInAgro += teams[i].government->getAgricultural();
        Team::sumProfitInHeavyInd += teams[i].government->getHeavyIndustrial();
        Team::sumProfitInLightInd += teams[i].government->getLightIndustrial();
        teams[i].prepare();
                        qDebug() << "Читаем!";
        teams[i].readData();
    }

    Command *currPriority = new Command[teams.size()];
    bool eofList = false;
    srand( time(NULL) );
    while (!eofList)
    {
        eofList = true;
        for (unsigned int i = 0; i<teams.size();i++)
        {
            qDebug() << "Берем из очереди команду!";
            currPriority[i] = teams[i].getTopCommand();
            currPriority[i].numOfTeam = i;
            if (currPriority[i].args[0] > 0)
            currPriority[i].lvlOfMin = teams[i].government->ministers[ currPriority[i].args[0] - 1 ]->getLvl();
            else currPriority[i].lvlOfMin = 0;
                            qDebug() << "Взяли команду!";
            eofList = eofList && (currPriority[i].args[0] == -1);
                            qDebug() << "Проверили на конец листа!";
        }

        if (!eofList)
        {
            Command temp;
            bool didIt = false;
            for (unsigned int j = 0; j < teams.size(); j++)
            {
              currPriority[j].adPriority = rand() % 100 + 1;
            }

            while (!didIt)
            {
                didIt = true;
                for (unsigned int j = 1; j < teams.size(); j++)
                {

                    if (currPriority[j].lvlOfMin > currPriority[j-1].lvlOfMin)
                    {
                        temp = currPriority[j];
                        currPriority[j] = currPriority[j-1];
                        currPriority[j-1] = temp;
                        didIt = false;
                    } else if (currPriority[j].lvlOfMin == currPriority[j-1].lvlOfMin && currPriority[j].adPriority > currPriority[j-1].adPriority)
                    {
                        temp = currPriority[j];
                        currPriority[j] = currPriority[j-1];
                        currPriority[j-1] = temp;
                        didIt = false;
                    }
                }
            }
                qDebug() << "Проверяем на диверсии!";
            checkForMID(currPriority);
            int result;
            for (unsigned int j = 0; j<teams.size();j++)
            {
                qDebug() << "Выполняем команду!";
                result = teams[ currPriority[j].numOfTeam ].government->doCommand(currPriority[j]);
                Command temp = currPriority[j];
                temp.successful = result;
                if (temp.args[0] != -1)
                teams[ currPriority[j].numOfTeam ].listOfDidCommands.push_back(temp);
                teams[ currPriority[j].numOfTeam ].listOfDidCommandsSize +=1;
                saveInHistory(teams[ currPriority[j].numOfTeam ].numOfTeam, temp );

            }
        }
    }


    rialto->processData();
    for (int i = 0; i<teams.size();i++)
    {
        teams[i].postPrepare();
    }

    for (int i = 0; i<teams.size();i++)
    {
        teams[i].writeData();
    }
    emit needToUpdateHistory();

    /*for (unsigned int j = 0; j<teams.size();j++)
    {
       // teams[j].listOfDidCommands.clear();
    }*/

}

void MainCPU::saveInHistory(int numberOfTeam, Command command)
{
    QFile historyFile("history.txt");
    QTextStream stream(&historyFile);
    historyFile.open(QFile::Append);
    stream << QString::number(numberOfTeam) << " ";
    for (int i = 0; i < 7; i++) {stream << QString::number(command.args[i]) << " ";}
    stream << QString::number(command.successful) << endl;
    historyFile.close();
}

int TSOP(double attackLvl, double defenceLvl);

// Переделать с итераторами блеать!!
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
        if (TSOP(teams[i].government->ministers[4]->getOurTSOPLvl(5) , teams[commands[i].args[2]-1].government->ministers[commands[i].args[3]-1]->getTSOPlvl(commands[i].args[3]) ))
            {
            qDebug() << "ТСОП - победа!";

            didIt = teams[ commands[i].args[2]-1 ].sabotage( commands[i].args[3]);
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
        teams[i].listOfDidCommandsSize +=1;
        break;
        }

    if (commands[i].args[0] == 5 && commands[i].args[1] == 4)
        {
        temp = commands[i];
        temp.successful = 0;
        Team *target = &(teams[commands[i].args[2]-1]);
        if (teams[i].isVerbed(commands[i].args[2]-1, commands[i].args[3]-1 ) )
            {

            for (unsigned int j = 0; j < target->listOfCommands.size(); j++)
            {
                if ( target->listOfCommands[j].args[0]  == commands[i].args[3])
                {
                 target->listOfCommands[j].args[0]  = commands[i].args[3];
                 target->listOfCommands[j].args[1]  = commands[i].args[4];
                 target->listOfCommands[j].args[2]  = commands[i].args[5];
                 target->listOfCommands[j].args[3]  = commands[i].args[6];
                 target->listOfCommands[j].args[4]  = -1;
                 target->listOfCommands[j].args[5]  = -1;
                 target->listOfCommands[j].args[6]  = -1;
                 temp.successful = 1;
                 break;
                }
            }
            if (!temp.successful)
            {
                target->listOfCommands.push_back(*(new Command()));
                target->listOfCommands[target->listOfCommands.size() - 1].args[0] = commands[i].args[3];
                target->listOfCommands[target->listOfCommands.size() - 1].args[1] = commands[i].args[4];
                target->listOfCommands[target->listOfCommands.size() - 1].args[2] = commands[i].args[5];
                target->listOfCommands[target->listOfCommands.size() - 1].args[3] = commands[i].args[6];
                target->listOfCommands[target->listOfCommands.size() - 1].args[4] = -1;
                target->listOfCommands[target->listOfCommands.size() - 1].args[5] = -1;
                temp.successful = 1;
                qDebug() << target->listOfCommands[target->listOfCommands.size() - 1].args[0] <<" "<< target->listOfCommands[target->listOfCommands.size() - 1].args[1] <<" "<< target->listOfCommands[target->listOfCommands.size() - 1].args[2];
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
        teams[i].listOfDidCommandsSize +=1;
        break;
        }
    }
}

