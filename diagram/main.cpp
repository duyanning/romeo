#include <QApplication>

// Romeo
#include <iostream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include <QUdpSocket>
#include <QThread>

#include "diagramwindow.h"

#include "Romeo.h"

using namespace std;




int main(int argc, char *argv[])
{

    romeo.start_listening();






    QApplication app(argc, argv);
    DiagramWindow view;
    view.show();
    return app.exec();
}
