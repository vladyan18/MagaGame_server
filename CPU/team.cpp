#include "team.h"
#include "QFile"
#include <QTextStream>
#include <QDebug>
#include <Anton_CPU/Minister.h>
#include <Anton_CPU/ForeignMinister.h>


int Team::countOfTeams = 1;
int Team::sumProfitInAgro = 0;
int Team::sumProfitInLightInd = 0;
int Team::sumProfitInHeavyInd = 0;
Team::Team(int num, int cOfTeams, ListOfGovernments *govs, Rialto *rialto, deque<NukeRocket> *nukesInAir)
{

    this->nukesInAir = nukesInAir;
    this->rialto = rialto;
    numOfTeam = num;
    countOfTeams = cOfTeams;

    government = new Government(this,numOfTeam,countOfTeams, govs, rialto, nukesInAir);
    sumProfitInAgro += 1000000;
    sumProfitInLightInd += 1000000;
    sumProfitInHeavyInd += 1000000;

    govs->addToList(num,government);
    recon = new reconInformation[countOfTeams];
        QFile outputFile(QString::number(numOfTeam)+"_team_output.txt");
        outputFile.open(QFile::WriteOnly);
        outputFile.close();
}

void Team::addCommand(Command com)
{
    listOfCommands.push_back(com);
}

Command Team::getTopCommand()
{
    Command *ret = new Command;
    int empty[7] = {-1,-1,-1,-1,-1, -1, -1};
    *ret->args = *empty;

    if (!listOfCommands.empty())
    {
    *ret = listOfCommands[0];
    listOfCommands.pop_front();   
    }
    return *ret;
}

void Team::readData()
{
    QString *temp = new QString;
    QTextStream stream(temp);
    Command com;

    QFile inputFile(QString::number(numOfTeam) + "_team_input.txt");
    inputFile.open(QFile::ReadOnly);
    *temp = inputFile.readAll();
    inputFile.close();

    listOfCommands.clear();   
    do
    {
        for (int i = 0; i<7; i++)
        {
            stream >> com.args[i];
        }
        addCommand(com);
    } while (!stream.atEnd());
    numOfCommands = listOfCommands.size();
}


void Team::writeData()
{
    QFile outputFile(QString::number(numOfTeam)+"_team_output.txt");

    QTextStream stream(&outputFile);
    outputFile.open(QFile::WriteOnly);

    stream.setRealNumberNotation(QTextStream::FixedNotation);
    stream.setRealNumberPrecision(0);

    stream  << government->getMoney() << endl
    << government->getNukes() << endl
    << government->getMissles() << endl
    << government->getHappiness() << endl
    << countOfTeams << endl
    << government->getHeavyIndustrial()<< endl
    << government->getLightIndustrial()<< endl
    << government->getAgricultural() << endl;

    for (int i = 0; i<=9;i++)
    {
        stream << government->ministers[i]->getLvl() << " ";
    }
    stream << endl;

    stream << government->outCodes << endl;

    for (int i = 0; i<listOfDidCommands.size();i++)
    {
        if (listOfDidCommands[i].args[0] != 0)
        {
            for (int j = 0; j<7;j++)
            {
                stream<< listOfDidCommands[i].args[j] << " ";
            }
            stream << listOfDidCommands[i].successful << endl;
        }
    }
    outputFile.close();

    outputFile.setFileName(QString::number(numOfTeam) + "_verb_matrix.txt");
    outputFile.open(QFile::WriteOnly);
    for (int i=0; i<countOfTeams; i++)
    {
        for (int j = 0; j<10; j++)
        {
            stream << government->isVerbed(i,j) << " ";
        }

        stream << endl;
    }
    outputFile.close();

    outputFile.setFileName(QString::number(numOfTeam) + "_recon_data.txt");
    outputFile.open(QFile::WriteOnly);
    for (int i=0; i<countOfTeams; i++)
    {
        if (recon[i].info.size() != 0)
        {
            if (recon[i].mode == 1)
            {
                qDebug() << "Записываем слежку в файл!";
                stream << "R " + QString::number(i+1) << endl;
                for (int j = 0; j < recon[i].info.size(); j++)
                {
                    for (int k = 0; k<7; k++)
                    {
                        stream << recon[i].info[j].args[k] << " ";
                    }
                    stream << endl;
                }
            }
        }
    }


    for (int i=0; i<countOfTeams; i++)
    {
        qDebug() << recon[i].greatFail->size();
        if (recon[i].greatFail->size() != 0)
        {
                qDebug() << "Записываем фейлы в файл!";
                stream << "F " + QString::number(i+1) << endl;
                for (int j = 0; j < recon[i].greatFail->size(); j++)
                {
                    for (int k = 0; k<7; k++)
                    {
                        stream << (recon[i].greatFail->at(j)).args[k] << " ";
                    }
                    stream << endl;
                }
        }
    }
    outputFile.close();

    for (int i=0; i<countOfTeams; i++)
    {
        recon[i].info.clear();
        recon[i].greatFail->clear();
    }

    this->listOfDidCommands.clear();
    listOfDidCommandsSize = 0;
}

void Team::prepare()
{
    for (int i = 0; i < countOfTeams; i++)
    {
        recon[i].clear();
    }

    government->prepare();
}

void Team::postPrepare()
{
    ForeignMinister *mid = (ForeignMinister*)(government->ministers[4]);
    if (mid->trackingTarget[0] != 0)
    {
        Government *target;
        target = this->government->governments->getPtrToGov(mid->trackingTarget[0]);
        qDebug() << "Начинаем слежку! " << QString::number( target->historyOfCommands.size() ) << " " << QString::number( mid->trackingTarget[0] ) <<" "<< QString::number( target->getMoney() );
        for (int i = 0; i < target->historyOfCommands.size() ; i++)
        {
             qDebug() << "Обнаружили цель!";
            if ( target->historyOfCommands.at(i).args[0] == mid->trackingTarget[1] )
            {
                qDebug() << "Обнаружили действие!";
                recon[mid->trackingTarget[0] - 1].info.push_back(target->historyOfCommands.at(i));
            }
        }

        if (recon[mid->trackingTarget[0] - 1].info.size() > 0)
        {
           recon[mid->trackingTarget[0] - 1].mode = 1;
        }
        mid->trackingTarget[0] = 0;
        mid->trackingTarget[1] = 0;
    }


    government->postPrepare();
}

int Team::sabotage(int numOfMin)
{
    int result = 0;
    qDebug() << "Приступаем к саботажу!";
    for (int i = 0; i<listOfCommands.size();i++)
    {

        if (listOfCommands[i].args[0] == numOfMin)
        {
          listOfDidCommands.push_back(listOfCommands[i]);
          listOfDidCommandsSize++;
          listOfCommands[i].args[0] = -1;
          listOfCommands[i].args[1] = -1;
          listOfCommands[i].args[2] = -1;
          listOfCommands[i].args[3] = -1;
          listOfCommands[i].args[4] = -1;
          listOfCommands[i].args[5] = -1;
          listOfCommands[i].args[6] = -1;
          qDebug() << "Саботаж удался!";
          result = 1;
        }
    }
    return result;
}

bool Team::isVerbed(int country, int min)
{
    return government->isVerbed(country,min);
}

void Team::updateReconList(int newCountOfTeams)
{

    delete []recon;
    recon = new reconInformation[newCountOfTeams];
}


void Team::addToGreatFails(int numberOfTeam, Command com)
{

    recon[numberOfTeam-1].greatFail->push_back(com);

}
