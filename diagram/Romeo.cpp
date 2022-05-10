#include <iostream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <QUdpSocket>
#include <QThread>

#include "Romeo.h"

Romeo romeo;

ListeningThread::ListeningThread(QUdpSocket& s)
    : udpSocket(s)
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
    listening_thread(udpSocket)
{
}

void Romeo::confess()
{
    QJsonObject confessionMsg;
    confessionMsg["instance_id"] = "duyanning@gmail.com";
    confessionMsg["nonce"] = 12345;

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
