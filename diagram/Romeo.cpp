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
//        // ��������������������������߳�,������������һ����ʱʱ��.��Ȼһֱ������,���Ǿ�û��������stopped��������ѭ��
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
//    wait(); // �൱��join. �ȴ�run����. ��Ҫ�ǵȴ�udpSocket.waitForReadyRead����.
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

    // Qt bug: ����û���յ����ݱ�,��slotҲ������, ��ʱpendingDatagramSize����0
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

    // û��noquote�Ļ�,������ַ������ᱻ��������
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

