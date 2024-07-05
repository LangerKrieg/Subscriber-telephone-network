#include "client.h"

Client::Client(QObject *parent) : QObject(parent), currentStatus("ПОЛОЖЕНА")
{
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
}

void Client::connectToServer(const QHostAddress &address, quint16 port)
{
    socket->connectToHost(address, port);
    qDebug() << "Клиент соединен с сервером по порту: " << address;
}

void Client::disconnectFromServer() {
    socket->disconnectFromHost();
    qDebug() << "Клиент отключен от сервера.";
}

void Client::setPhoneNumber(const QString &phoneNumber)
{
    this->phoneNumber = phoneNumber;
    sendMessage("SET_NUMBER:" + phoneNumber);
}

void Client::sendMessage(const QString &message)
{
    QByteArray data = message.toUtf8();
    socket->write(data);
}

void Client::pickUpPhone()
{
    sendMessage("PICKUP:" + phoneNumber);
}

void Client::hangUpPhone()
{
    sendMessage("HANGUP:" + phoneNumber);
}

void Client::dialNumber(const QString &number)
{
    sendMessage("DIAL:" + phoneNumber + ":" + number);
}

void Client::sendTextMessage(const QString &text)
{
    sendMessage("MESSAGE:" + phoneNumber + " говорит " + text);
}

void Client::onReadyRead()
{
    QByteArray data = socket->readAll();
    QString message = QString::fromUtf8(data);
    QStringList messageParts = message.split(":");

    if (messageParts.size() > 1)
    {
        QString command = messageParts[0];
        QString status = messageParts[1];

        if (command == "MESSAGE" && messageParts.size() == 2)
        {
            QString text = messageParts[1];
            emit textMessageReceived(text);
        }
        else if (command == "STATUS")
        {
            currentStatus = status;
            emit phoneStatusChanged(status);
        }
    }

}

QString Client::generatePhoneNumber()
{
    QString phoneNumber;
    for (int i = 0; i < 10; ++i) {
        int digit = QRandomGenerator::global()->bounded(10); // Генерируем случайную цифру от 0 до 9
        phoneNumber.append(QString::number(digit));
    }
    return phoneNumber;
}
