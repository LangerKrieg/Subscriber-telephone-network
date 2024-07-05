#include <QCoreApplication>
#include "miniatsserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MiniAtsServer server;
    if (!server.listen(QHostAddress::Any, 12345)) {
        qCritical() << "Unable to start the server:" << server.errorString();
        return 1;
    }

    qDebug() << "Server started on port" << server.serverPort();

    return a.exec();
}
