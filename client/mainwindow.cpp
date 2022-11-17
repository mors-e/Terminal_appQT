#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead,this,&MainWindow::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_connect_clicked() //кнопка подключения
{
    socket->connectToHost("127.0.0.1", 2323);
    ui->lineEdit_2->setText("connect");
}

void MainWindow::SendToServer(QString str)
{
    Data.clear();
    QDataStream out (&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_2);
    out << str;
    socket->write(Data);
    ui->lineEdit->clear();
    ui->listWidget_2->addItem(str);
}


void MainWindow::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if (in.status() == QDataStream::Ok){
        QString str;
        in << str;
        ui->listWidget_2->addItem(str);
    }else {
        ui->listWidget_2->addItem("error");
    }
}


// Вставить
void MainWindow::on_Paste_clicked()
{
    QListWidgetItem *it = ui->listWidget->item(ui->listWidget->currentRow());
    if (it != 0){
        QString past_com = ui->listWidget->currentItem()->text();
        ui->lineEdit->setText(past_com);
        ui->listWidget->currentItem()->setForeground(Qt::blue);
    }
    else{
        QMessageBox::critical(this, "Error", "Row not selected");
    }
}

void MainWindow::on_Save_clicked() // Сохранить
{

    QString command = ui->lineEdit->text();
    if (command != ""){
        ui ->listWidget->addItem(command);
        ui ->lineEdit->clear();
    }
    else{
        QMessageBox::critical(this, "Error", "Commands field is empty");
    }
}


void MainWindow::on_Remove_clicked() // Удалить
{
    QListWidgetItem *it = ui->listWidget->item(ui->listWidget->currentRow());
    if (it != 0){
        delete it;
    }else{
        QMessageBox::critical(this, "Error", "Row not selected");
    }
}


void MainWindow::on_Run_clicked() // Отправить
{
    QString com = ui->lineEdit->text();
    ui->lineEdit->clear();
    ui->listWidget_2->addItem(com);
    if (com != ""){
        QByteArray ba = com.toLocal8Bit(); // меняем чтобы отправить через system в консоль
        const char *c_str2 = ba.data();
        system(c_str2);
    }
    /* ОТПРАВКА НА СЕРВЕР.(там происходит уже выполнение команд)
    QString com = ui->lineEdit->text();
    if (com != ""){
        SendToServer(com);
    }else{
        QMessageBox::critical(this, "Error", "Not commands");
    }
    */
}
void MainWindow::on_lineEdit_returnPressed() // Отправить через enter
{
    QString com = ui->lineEdit->text();
    ui->lineEdit->clear();
    ui->listWidget_2->addItem(com);
    if (com != ""){
        QByteArray ba = com.toLocal8Bit(); // меняем чтобы отправить через system в консоль
        const char *c_str2 = ba.data();
        system(c_str2);
    }
    /* ОТПРАВКА НА СЕРВЕР.(там происходит уже выполнение команд)
    QString com = ui->lineEdit->text();
    if (com != ""){
        SendToServer(com);
    }else{
        QMessageBox::critical(this, "Error", "Not commands");
    }
    */
}





