//#include <QtCore/QCoreApplication>
#include <iostream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <QUdpSocket>
#include <QThread>

using namespace std;

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
        udpSocket.waitForReadyRead(-1);
        datagram.resize(udpSocket.pendingDatagramSize());
        udpSocket.readDatagram(datagram.data(), datagram.size());

        cout << QString(datagram.data()).toStdString() << endl;

    }
}

void ListeningThread::stop()
{
    stopped = true;
}



int main(int argc, char *argv[])
{
    QUdpSocket udpSocket;
    ListeningThread listening_thread(udpSocket);

    listening_thread.start();

    //QCoreApplication a(argc, argv);

    //return a.exec();
    QJsonObject confessionMsg;
    confessionMsg["instance_id"] = "duyanning@gmail.com";
    //confessionMsg["instance_id"] = QString::fromLocal8Bit("duyanning@gmail.comÖÐ¹ú");
    confessionMsg["nonce"] = 12345;

    QJsonDocument doc{ confessionMsg };

    //QTextStream out(stdout);
    //out << QString(doc.toJson());


    cout << QString(doc.toJson()).toStdString() << endl;
    //cout << QString(doc.toJson()).toLocal8Bit().constData() << endl; // ok
    //cout << QString::fromUtf8(doc.toJson()).toStdString() << endl;
    // cout << QString::fromUtf8(doc.toJson()).toLocal8Bit().constData() << endl; // ok

    udpSocket.writeDatagram(doc.toJson(), QHostAddress::LocalHost, 1314);


    
    //cout << QString("abc");
    for (;;)
        ;

    listening_thread.stop();

    cout << "the end" << endl;
}
