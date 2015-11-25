#ifndef CONSOLE_H
#define CONSOLE_H

#include <QDialog>
#include <CPU/maincpu.h>

namespace Ui {
class Console;
}

class Console : public QDialog
{
    Q_OBJECT

public:
    explicit Console(MainCPU *serverPU, QWidget *parent = 0);
    ~Console();

private slots:
    void on_inputLine_returnPressed();

private:
    Ui::Console *ui;
    QString prefix;
    QStringList allCommands;
    QStringList definitions;
    MainCPU *serverPU;
    void doCommand(QString command, vector<QString> args);
};

#endif // CONSOLE_H
