#include <QApplication>

// Romeo
#include <iostream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <QUdpSocket>
#include <QThread>

#include <tchar.h>

#include "diagramwindow.h"

#include "Romeo.h"


#include "sgx_urts.h"
#include "Enclave_u.h"

using namespace std;




int main(int argc, char *argv[])
{
    qDebug().noquote() << "main thread: " << QThread::currentThread();
    QApplication app(argc, argv);

    romeo.start_listening();
    romeo.start();

    sgx_launch_token_t token = { 0 };
    sgx_status_t ret = SGX_ERROR_UNEXPECTED;
    int updated = 0;


    ret = sgx_create_enclave(_T("F:\\romeo\\diagram\\x64\\Debug\\Enclave.signed.dll"), 1, &token, &updated, &global_eid, NULL);
    if (ret != SGX_SUCCESS) {
        qDebug().noquote() << "sgx error: sgx_create_enclave" << endl;
    }




    //if (SGX_SUCCESS != sgx_destroy_enclave(global_eid)) {
    //    qDebug().noquote() << "sgx error: sgx_destroy_enclave" << endl;
    //}

    DiagramWindow view;
    view.show();
    return app.exec();
}
