#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QTcpServer>
#include <QtWidgets>
#include <QObject>
#include <CPU/maincpu.h>
#include <console.h>
#include <historydisplay.h>



namespace Ui {
class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();
    void slotReadClient(int);
    void doUpdateList();


    void newuser();

    void on_listWidget_itemDoubleClicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();
    void on_toolButton_clicked();

signals:
    void needToUpdateHistory();
private:
    Ui::MainWindow *ui;
   QTcpServer *_serv;

    MainCPU mcpu;
    Console *console;
    HistoryDisplay historyDisplay;
   void updateList();
};

class Clients : public QObject
{
    Q_OBJECT
public:
        QTcpSocket *socket;
        int getNumber();
        void setNumber(int);
        QString getName();
        void setName(QString);
        void setConnectionSign();
        bool connected = false;
        bool receivedData = false;

public slots:
        void adapterReadClient();
        void onDisconnected();
signals:
        void adapterSendReadClient(int);
        void doUpdateList();
private:

    int num;
    QString name;



};

#endif // MAINWINDOW_H
