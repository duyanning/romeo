#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <QUdpSocket>
#include <QThread>


class ListeningThread : public QThread {
public:
    ListeningThread(QUdpSocket& s);
    void stop();
protected:
    void run();
private:
    volatile bool stopped;
    QUdpSocket& udpSocket;
};


class Romeo {
public:
    Romeo();
    void confess();
    void start_listening();
    void stop_listening();

private:
    QUdpSocket udpSocket;
    ListeningThread listening_thread;
};

extern Romeo romeo;
