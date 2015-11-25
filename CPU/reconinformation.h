#ifndef RECONINFORMATION_H
#define RECONINFORMATION_H
#include <vector>
#include <command.h>
#include <QDebug>
using namespace std;

class reconInformation
{
public:
    void clear()
    {

        if (info.size() > 0)
        {

        info.clear();
        }

        if (greatFail->size() > 0)
        greatFail->clear();

    }

    void addToGreatFail(Command com1)
    {
        greatFail->push_back(com1);
    }

    reconInformation()
    {
        info.resize(1);
        greatFail = new vector<Command>(15);
        qDebug() << "Конструктор Р!";
    }
    ~reconInformation()
    {
        qDebug() << "Деструктор Р!";
    }

    vector<Command> *greatFail;
    vector<Command> info;

    int mode = 0;
};

#endif // RECONINFORMATION_H
