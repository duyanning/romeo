#include <iostream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <QUdpSocket>
#include <QThread>
#include <QtDebug>

#include "Romeo.h"
#include "sgx_urts.h"
#include "Enclave_u.h"

Romeo romeo;
sgx_enclave_id_t global_eid = 0;

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
        // 下面这个函数会阻塞调用它的线程,所以我们设置一个超时时间.不然一直阻塞着,我们就没法检测变量stopped进而结束循环
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

    // 没有noquote的话,输出的字符串都会被加上引号
    qDebug().noquote() << jsonObj["msg_type"].toString() << endl;
}
