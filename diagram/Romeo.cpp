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

//ListeningThread::ListeningThread(QUdpSocket& s, Romeo* r)
//    : udpSocket(s), romeo(r)
//{
//    stopped = false;
//    //udpSocket.bind();
//}
//
//void ListeningThread::run()
//{
//    qDebug().noquote() << "listening thread: " << QThread::currentThread();
//
//    QByteArray datagram;
//    while (!stopped) {
//        // 下面这个函数会阻塞调用它的线程,所以我们设置一个超时时间.不然一直阻塞着,我们就没法检测变量stopped进而结束循环
//        bool r = udpSocket.waitForReadyRead(5000);
//        if (r) {
//            datagram.resize(udpSocket.pendingDatagramSize());
//            udpSocket.readDatagram(datagram.data(), datagram.size());
//
//            //cout << QString(datagram.data()).toStdString() << endl;
//            //qDebug() << QString(datagram.data()) << endl;
//            romeo->onMsg(datagram);
//        }
//
//    }
//}
//
//void ListeningThread::stop()
//{
//    stopped = true;
//    wait(); // 相当于join. 等待run结束. 主要是等待udpSocket.waitForReadyRead返回.
//}

void Romeo::processPendingDatagrams()
{
    qDebug().noquote() << "slot thread: " << QThread::currentThread();
    QByteArray datagram;
    do {
        bool has = udpSocket.hasPendingDatagrams();
        qint64 size = udpSocket.pendingDatagramSize();
        datagram.resize(size);
        //datagram.resize(udpSocket.pendingDatagramSize());
        udpSocket.readDatagram(datagram.data(), datagram.size());
    } while (udpSocket.hasPendingDatagrams());

    // Qt bug: 明明没有收到数据报,本slot也被调用, 此时pendingDatagramSize返回0
    // https://forum.qt.io/topic/60448/qudpsocket-haspendingdatagrams-broken-in-qt-5-5-on-windows-desktop/3
    if (datagram.size())
        onMsg(datagram);
}

Romeo::Romeo()
    //:
    //listening_thread(udpSocket, this)
{
    //udpSocket.bind();
    //connect(&udpSocket, SIGNAL(readyRead()),
    //    this, SLOT(processPendingDatagrams()));
}

void Romeo::start()
{
    udpSocket.bind();
    connect(&udpSocket, SIGNAL(readyRead()),
        this, SLOT(processPendingDatagrams()));
}

void Romeo::confess(const char* user_id, const char* nonce)
{
    qDebug().noquote() << user_id;
    qDebug().noquote() << nonce;


    QJsonObject confessionMsg;
    confessionMsg["msg_type"] = "confession";
    confessionMsg["user_id"] = user_id;
    confessionMsg["nonce"] = nonce;

    QJsonDocument doc{ confessionMsg };
    udpSocket.writeDatagram(doc.toJson(), QHostAddress::LocalHost, 1314);

}

void Romeo::start_listening()
{
    //listening_thread.start();
}

void Romeo::stop_listening()
{
    //listening_thread.stop();
}

void Romeo::onMsg(QByteArray& jsonByteArray)
{
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonByteArray);
    QJsonObject jsonObj = jsonDoc.object();

    // 没有noquote的话,输出的字符串都会被加上引号
    qDebug().noquote() << jsonObj["msg_type"].toString() << endl;

    // ECALL
    qDebug().noquote() << "ECALL: reassure_in_enclave";
    sgx_status_t ret = reassure_in_enclave(global_eid,
        jsonObj["user_id"].toString().toLocal8Bit().data(),
        jsonObj["nonce"].toString().toLocal8Bit().data()
        );
}

// OCALL
void confess_through_untrusted(const char* user_id, const char* nonce)
{
    qDebug().noquote() << "OCALL: confess_through_untrusted";
    romeo.confess(user_id, nonce);
}

