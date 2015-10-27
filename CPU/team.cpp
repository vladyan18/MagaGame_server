#include "team.h"
#include "QFile"
#include <QTextStream>
#include <QDebug>

int Team::countOfTeams = 1;
Team::Team(int num, int cOfTeams)
{
    numOfTeam = num;
    countOfTeams = cOfTeams;
    government = new Government(numOfTeam,countOfTeams) ;
}

void Team::addCommand(Command com)
{
    listOfCommands.push_back(com);
}

Command Team::getTopCommand()
{
    Command *ret = new Command;
    int empty[6] = {-1,-1,-1,-1,-1, -1};
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

    listOfDidCommands.clear();
    listOfCommands.clear();   
    do
    {
        for (int i = 0; i<6; i++)
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
    << 0 << endl
   << 0 << endl;
    for (int i = 0; i<9;i++)
    {
        stream << government->ministers[i]->getLvl()  << " ";
    }
    stream << endl;
    for (int i = 0; i<listOfDidCommands.size();i++)
    {
        for (int j = 0; j<6;j++)
        {
            stream<< listOfDidCommands[i].args[j] << " ";
        }
        stream << listOfDidCommands[i].successful << endl;
    }
    outputFile.close();
}


