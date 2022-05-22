#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <QUdpSocket>
#include <QThread>

#include "sgx_urts.h"
#include "Enclave_u.h"

class Romeo;

class ListeningThread : public QThread {
public:
    ListeningThread(QUdpSocket& s, Romeo* romeo);
    void stop();
protected:
    void run();
private:
    volatile bool stopped;
    QUdpSocket& udpSocket;
    Romeo* romeo;
};


class Romeo {
public:
    Romeo();
    void confess();
    void start_listening();
    void stop_listening();
    void onMsg(QByteArray& jsonByteArray);

private:
    QUdpSocket udpSocket;
    ListeningThread listening_thread;
};

extern Romeo romeo;
extern sgx_enclave_id_t global_eid;
