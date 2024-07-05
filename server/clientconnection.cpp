#include "clientconnection.h"
#include "QDebug"

ClientConnection::ClientConnection(qintptr socketDescriptor, QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket, &QTcpSocket::readyRead, this, &ClientConnection::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &ClientConnection::onDisconnected);
}

QString ClientConnection::getPhoneNumber() const
{
    return phoneNumber;
}

QString ClientConnection::getStatus() const
{
    return status;
}

void ClientConnection::onReadyRead()
{
    QByteArray data = socket->readAll();
    QString message = QString::fromUtf8(data);
    QStringList messageParts = message.split(":");
    qDebug() << messageParts[0];
    qDebug() << messageParts[1];

    if (messageParts.size() > 1)
    {
        QString command = messageParts[0];
        phoneNumber = messageParts[1];
        if (command == "SET_NUMBER" && messageParts.size() == 2) {
            emit connected(this);
        }
        else if (command == "PICKUP" && messageParts.size() == 2) {
            emit pickUpPhone(this);
        }
        else if (command == "DIAL" && messageParts.size() > 2)
        {
            QString calleeNumber = messageParts[2];
            emit callRequest(this, calleeNumber);
        }
        else if (command == "MESSAGE" && messageParts.size() == 2) {
            QString textMessage = messageParts[1];
            emit receivedMessage(this, textMessage);
        }
        else if (command == "HANGUP")
        {
            emit callDisconnected(this);
        }
    }
}

void ClientConnection::onDisconnected()
{
    emit disconnected(this);
}

void ClientConnection::sendMessage(const QString &message)
{
    QByteArray data = message.toUtf8();
    socket->write(data);
}

void ClientConnection::changeStatus(const QString &clientStatus) {
    status = clientStatus;
    sendMessage("STATUS:" + status);
}
