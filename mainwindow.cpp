#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
#include <QDebug>

using namespace std;
QTcpSocket *SClients[20];
Clients *listClients[20];
int numOfTeams = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _serv = new QTcpServer(this);
connect(_serv, SIGNAL(newConnection()), this, SLOT(newuser()));
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_pushButton_clicked()
{
   _serv->listen(QHostAddress::Any,QString(ui->lineEdit->text()).toInt());
   ui->label->setText("Сервер запущен");
   ui->pushButton->setDisabled(true);
   ui->pushButton_2->setEnabled(true);
   *listClients = new Clients[20];
}

void MainWindow::on_pushButton_2_clicked()
{
  _serv->close();
  ui->label->setText("Сервер остановлен");
  ui->pushButton_2->setDisabled(true);
  ui->pushButton->setEnabled(true);
for (int i=1;i<=numOfTeams;i++) {
    if (listClients[i]->connected)
     {
        listClients[i]->socket->disconnectFromHost();
     }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QByteArray doc;
    QFile inpf;
    for (int i = 1;i<=numOfTeams;i++)
    {
        if (listClients[i]->connected)
        {

         inpf.setFileName(QString::number(i) + "_team_output.txt");
         inpf.open(QFile::ReadOnly);
         doc = "3" + inpf.readAll();
         inpf.close();


         inpf.setFileName(QString::number(i) + "_verb_matrix.txt");
         inpf.open(QFile::ReadOnly);
         doc += "\nM \n" + inpf.readAll();
         inpf.close();

         inpf.setFileName(QString::number(i) + "_recon_data.txt");
         inpf.open(QFile::ReadOnly);
         doc += "\nP \n" + inpf.readAll();
         inpf.close();

         listClients[i]->socket->write(doc);

        }
        listClients[i]->receivedData = false;
    }
    updateList();



    ui->pushButton_4->setEnabled(true);
}

void MainWindow::newuser() {
     QString answ1,name;

     QTcpSocket* clientSocket=_serv->nextPendingConnection();

     clientSocket->waitForReadyRead(2000);


     answ1 = clientSocket->read(1);
     name = clientSocket->readAll();


        qDebug() << "получили номер " + answ1;
     int num = QString(answ1).toInt();

if ((num>numOfTeams)||(listClients[num]->connected == false))
   {
        qDebug() << "добавляем команду, имя: " << name;
     listClients[num]= new Clients();
     listClients[num]->socket = clientSocket;
     listClients[num]->setNumber(num);
     listClients[num]->setName(name);
     listClients[num]->setConnectionSign();
     listClients[num]->connected = true;

     if(num>numOfTeams)
     {
     numOfTeams++;

     mcpu.addTeam(num);
     }


    connect(listClients[num],SIGNAL(adapterSendReadClient(int)),this, SLOT(slotReadClient(int)));
    connect(listClients[num]->socket,SIGNAL(disconnected()),listClients[num], SLOT(onDisconnected()));
    connect(listClients[num],SIGNAL(doUpdateList()),this, SLOT(doUpdateList()));

    QFile of(QString::number(num) + "_team_input.txt");
    QTextStream stream(&of);
    of.open(QFile::WriteOnly);
    stream << "-1 -1 -1 -1 -1 -1 -1 \n";
    of.close();

    listClients[num]->receivedData = true;

    updateList();
   }
   else
   {
   clientSocket->disconnectFromHost();
   }


}

void MainWindow::doUpdateList()
{
    updateList();
}

void Clients::adapterReadClient()
{
        qDebug() << "Адаптер получил данные";
  emit adapterSendReadClient(this->getNumber());
}

void Clients::onDisconnected()
{
    this->connected = false;
    emit doUpdateList();
}

void MainWindow::slotReadClient(int num)
{

    QByteArray doc;
    doc = listClients[num]->socket->readAll();
    QFile of(QString::number(num) + "_team_input.txt");
    QTextStream stream(&of);
    of.open(QFile::WriteOnly);
    stream << doc;
    of.close();
    listClients[num]->receivedData = true;
    updateList();
}

void Clients::setNumber(int number)
{
    this->num=number;
}

int Clients::getNumber()
{
    return(this->num);
}

QString Clients::getName()
{
    return(this->name);
}

void Clients::setName(QString newName)
{
    this->name = newName;
}

void Clients::setConnectionSign()
{

     connect(this->socket,SIGNAL(readyRead()),this, SLOT(adapterReadClient()));
}

void MainWindow::on_listWidget_itemDoubleClicked()
{
     listClients[ui->listWidget->currentRow()+1]->socket->disconnectFromHost();

}

void MainWindow::updateList()
{
    ui->listWidget->clear();
    for (int i=1;i<=numOfTeams;i++)
    {
        if (listClients[i]->connected)
        {
            ui->listWidget->addItem(QString::number(listClients[i]->getNumber()) +" " + listClients[i]->getName());
        }
        else
        {
            ui->listWidget->addItem(QString::number(listClients[i]->getNumber()) +" Отключен.");
        }
        if (listClients[i]->receivedData)
        {
            ui->listWidget->item(i-1)->setText(ui->listWidget->item(i-1)->text() + " | Данные приняты");
        }
    }

}

void MainWindow::on_pushButton_4_clicked()
{
    mcpu.processData();
    for (int i = 0; i < numOfTeams;i++)
    {
        ui->listWidget->item(i)->setText(ui->listWidget->item(i)->text() + " Обработано");
    }
    ui->pushButton_4->setDisabled(true);
}
