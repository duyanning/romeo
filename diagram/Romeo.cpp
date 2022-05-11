#include <iostream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <QUdpSocket>
#include <QThread>
#include <QtDebug>

#include "Romeo.h"

Romeo romeo;

ListeningThread::ListeningThread(QUdpSocket& s, Romeo* r)
    : udpSocket(s), romeo(r)
{
    stopped = false;
    udpSocket.bind();
}

void ListeningThread::run()
{
    QByteArray datagram;
    while (!stopped) {
        bool r = udpSocket.waitForReadyRead(1000);
        if (r) {
            datagram.resize(udpSocket.pendingDatagramSize());
            udpSocket.readDatagram(datagram.data(), datagram.size());

            //cout << QString(datagram.data()).toStdString() << endl;
            //qDebug() << QString(datagram.data()) << endl;
            romeo->onMsg(datagram);
        }

    }
}

void ListeningThread::stop()
{
    stopped = true;
    wait(); // 相当于join. 等待run结束. 主要是等待udpSocket.waitForReadyRead返回.
}

Romeo::Romeo()
    :
    listening_thread(udpSocket, this)
{
}

void Romeo::confess()
{
    QJsonObject confessionMsg;
    confessionMsg["msg_type"] = "confession";
    confessionMsg["instance_id"] = "duyanning@gmail.com";
    //confessionMsg["nonce"] = 12345;
    confessionMsg["nonce"] = "12345";

    QJsonDocument doc{ confessionMsg };
    udpSocket.writeDatagram(doc.toJson(), QHostAddress::LocalHost, 1314);

}

void Romeo::start_listening()
{
    listening_thread.start();
}

void Romeo::stop_listening()
{
    listening_thread.stop();
}

void Romeo::onMsg(QByteArray& jsonByteArray)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonByteArray);
    QJsonObject jsonObj = jsonDoc.object();

    qDebug().noquote() << jsonObj["msg_type"].toString() << endl;
}
