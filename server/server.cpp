#include "server.h"
#include <iostream>



Server::Server(){
    if(this->listen(QHostAddress::Any, 2323)){
        qDebug() << "start";

    }else {
        qDebug() << "error";
    }
}

void Server::incomingConnection(qintptr socketDescriptor){
    socket = new QTcpSocket;
    socket ->setSocketDescriptor(socketDescriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);

    Sockets.push_back(socket);
    qDebug()<<"client connected"<< socketDescriptor;
}

void Server::slotReadyRead(){ // Слот чтения сообщений и вывода в коносль
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_6_2);
    if (in.status() == QDataStream::Ok){
        QString str;
        in >> str;
        if (str != ""){
            QByteArray ba = str.toLocal8Bit(); // меняем чтобы отправить через system в консоль
            const char *c_str2 = ba.data();
            system(c_str2);
        }
    }else{
        qDebug()<< "DataStream error";
    }
}

void Server::SentToClient(QString str){ // отправка клиенту
    Data.clear();
    QDataStream out (&Data, QIODevice::ReadWrite);
    out.setVersion(QDataStream::Qt_6_2);
    out << str;
    socket->write(Data);
}
