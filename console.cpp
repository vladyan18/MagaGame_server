#include "console.h"
#include "ui_console.h"
#include "Anton_CPU/Defence.h"
#include "CPU/nukesinair.h"
#include <vector>

Console::Console(MainCPU *serverPU, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Console)
{
    this->serverPU = serverPU;
    ui->setupUi(this);
    prefix = "#";
    allCommands << "giveMoney" << "giveNukes" << "givePRO" << "help" << "clear" << "explodeNuke" << "giveLvl";
    definitions << "дать денег. Кому, сколько" << "дать ЯР. Кому, сколько" << "дать ПРО. Кому, сколько" << "получить список команд" << "очистить консоль" << "взорвать ЯР. У кого, сколько, от кого" << "дать уровень. Страна, министр, число";
}

Console::~Console()
{
    delete ui;
}

void Console::on_inputLine_returnPressed()
{
    if (ui->inputLine->text() != "")
    {
    QString command, line, temp;
    vector<QString> args;
    QTextStream stream(&line);

    line = ui->inputLine->text();
    stream >> command;

    while( !stream.atEnd() )
    {
        stream >> temp;
        args.push_back( temp );
    }

    ui->dispay->append(prefix + ui->inputLine->text() );
    ui->inputLine->clear();
    doCommand(command, args);
    }
}

void Console::doCommand(QString command, vector<QString> args)
{
    bool ok = false;
    int arg1, arg2, arg3;
    switch( allCommands.indexOf(command) )
    {
     case 0: //----------------------------------------------------------
        if (args.size() >= 2)
        {
        arg1 = QString(args[0]).toInt(&ok);
        arg2 = QString(args[1]).toInt(&ok);
        }
        if (!ok) {ui->dispay->append("Ошибка аргументов"); break;}

        if (arg1 <= serverPU->teams.size() && arg1 >= 1 )
        {
        serverPU->teams[arg1 - 1].government->changeMoney( arg2 );
        ui->dispay->append("Выполнено");
        } else {ui->dispay->append("Такого государства не существует");}

        break;
    case 1: //-------------------------------------------------------------
        if (args.size() >= 2)
        {
        arg1 = QString(args[0]).toInt(&ok);
        arg2 = QString(args[1]).toInt(&ok);
        }
        if (!ok) {ui->dispay->append("Ошибка аргументов"); break;}

        if (arg1 <= serverPU->teams.size() && arg1 >= 1 )
        {
        serverPU->teams[arg1 - 1].government->setNukes( serverPU->teams[arg1 - 1].government->getNukes() + arg2 );
        ui->dispay->append("Выполнено");
        } else {ui->dispay->append("Такого государства не существует");}

        break;
    case 2: //-------------------------------------------------------------
        if (args.size() >= 2)
        {
        arg1 = QString(args[0]).toInt(&ok);
        arg2 = QString(args[1]).toInt(&ok);
        }
        if (!ok) {ui->dispay->append("Ошибка аргументов"); break;}

        if (arg1 <= serverPU->teams.size() && arg1 >= 1 )
        {
        serverPU->teams[arg1 - 1].government->setPRO( serverPU->teams[arg1 - 1].government->getMissles() + arg2 );
        ui->dispay->append("Выполнено");
        } else {ui->dispay->append("Такого государства не существует");}

        break;
    case 3: //-------------------------------------------------------------
        for (int i = 0; i < allCommands.size(); i++)
        {
            ui->dispay->append(" " + allCommands.at(i) + "  - " + definitions.at(i));
        }
        break;
    case 4: //-------------------------------------------------------------
        ui->dispay->clear();
        break;
    case 5: //-------------------------------------------------------------
        if (args.size() >= 3)
        {
        arg1 = QString(args[0]).toInt(&ok);
        arg2 = QString(args[1]).toInt(&ok);
        arg3 = QString(args[2]).toInt(&ok);
        }
        if (!ok) {ui->dispay->append("Ошибка аргументов"); break;}

        if (arg1 <= serverPU->teams.size() && arg1 >= 1 && arg3 <= serverPU->teams.size() && arg3 >= 1 )
        {
            NukeRocket newRocket = *(new NukeRocket(arg3,arg1,arg2));
            newRocket.lifetime = 0;
            serverPU->nukesInAir.push_back(newRocket);
        ui->dispay->append("Выполнено");
        } else {ui->dispay->append("Такого государства не существует");}

        break;
    case 6: //-------------------------------------------------------------
        if (args.size() >= 3)
        {
        arg1 = QString(args[0]).toInt(&ok);
        arg2 = QString(args[1]).toInt(&ok);
        arg3 = QString(args[2]).toInt(&ok);
        }
        if (!ok) {ui->dispay->append("Ошибка аргументов"); break;}

        if (arg1 <= serverPU->teams.size() && arg1 >= 1 && arg2 <= 10 && arg2 >= 1 )
        {
            serverPU->teams[arg1 - 1].government->ministers[arg2-1]->setLvl(serverPU->teams[arg1 - 1].government->ministers[arg2-1]->getLvl() + arg3);
        ui->dispay->append("Выполнено");
        } else {ui->dispay->append("Такого государства/министра не существует");}

        break;
    default:
        ui->dispay->append("Команда \"" + command + "\" не найдена");
        break;
    }
    ui->dispay->append("");
}
