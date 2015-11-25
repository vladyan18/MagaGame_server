#ifndef HISTORYDISPLAY_H
#define HISTORYDISPLAY_H

#include <QDialog>
#include <command.h>

namespace Ui {
class HistoryDisplay;
}

class List {
public:
    int role;
    QString text;
    int command;
    int arg[5];
    int cost;
    List() {
     role = -1;
     command = -1;
     arg[0] = -1;
     arg[1] = -1;
     arg[2] = -1;
     arg[3] = -1;
     arg[4] = -1;
     cost = 0;
    }
};

class HistoryDisplay : public QDialog
{
    Q_OBJECT

public:
    explicit HistoryDisplay(QWidget *parent = 0);
    ~HistoryDisplay();
public slots:
    void updateData();

private:
    Ui::HistoryDisplay *ui;
    List cmds;
    void receivedCommand(Command);
    void presidentSaid(Command);
    void minFinSaid(Command);
    void minDefSaid(Command);
    void KGBSaid(Command);
    void midSaid(Command);
    void minUstSaid(Command);
    void MVDSaid(Command);
    void minComSaid(Command);
    void minHelSaid(Command);
    void zamSaid(Command);
    QString *namesOfMins;
};

#endif // HISTORYDISPLAY_H
