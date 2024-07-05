#include "miniatsserver.h"
#include "clientconnection.h"
#include "QDebug"

MiniAtsServer::MiniAtsServer(QObject *parent) : QTcpServer(parent), maxConnections(2)
{
}

void MiniAtsServer::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "New client connect to Server";
    ClientConnection *client = new ClientConnection(socketDescriptor, this);

    connect(client, &ClientConnection::connected, this, &MiniAtsServer::clientConnected);
    connect(client, &ClientConnection::disconnected, this, &MiniAtsServer::clientDisconnected);
    connect(client, &ClientConnection::callRequest, this, &MiniAtsServer::handleCallRequest);
    connect(client, &ClientConnection::pickUpPhone,this, &MiniAtsServer::handlePickUpPhone);
    connect(client, &ClientConnection::callConnected, this, &MiniAtsServer::handleCallConnected);
    connect(client, &ClientConnection::callDisconnected, this, &MiniAtsServer::handleCallDisconnected);
    connect(client, &ClientConnection::receivedMessage, this, &MiniAtsServer::handleReceivedMessage);
}

void MiniAtsServer::clientConnected(ClientConnection *client)
{
    // Добавление клиента в QMap
    clients.insert(client->getPhoneNumber(), client);
}

void MiniAtsServer::handlePickUpPhone(ClientConnection *client) {
    if (currentCalls.size() >= maxConnections)
    {
        client->changeStatus("ЗАНЯТО");
        return;
    } else {
        client->changeStatus("ГОТОВ");
    }
}

void MiniAtsServer::handleReceivedMessage(ClientConnection *sender, const QString &textMessage) {
    if (currentCalls.contains(sender)) {
        ClientConnection* secondClient = currentCalls.value(sender);
        secondClient->sendMessage("MESSAGE:" + textMessage);
    } else if (currentCalls.values().contains(sender)){
        ClientConnection* secondClient;

        foreach (ClientConnection *key, currentCalls.keys()) {
            if(currentCalls.value(key) == sender) {
                secondClient = key;
                break;
            }
        }

        secondClient->sendMessage("MESSAGE:" + textMessage);
    }
}

void MiniAtsServer::clientDisconnected(ClientConnection *client)
{
    int mapSize = clients.size();
    qDebug() << "Size of QMap: " << mapSize;

    qDebug() << client->getPhoneNumber();
    clients.remove(client->getPhoneNumber());
    client->deleteLater();

    mapSize = clients.size();
    qDebug() << "Size of QMap: " << mapSize;

    qDebug() << "Client disconnect";
}

void MiniAtsServer::handleCallRequest(ClientConnection *caller, const QString &calleeNumber)
{
    if (clients.contains(calleeNumber))
    {
        ClientConnection *callee = clients[calleeNumber];
        if (!(callee->getStatus() == "РАЗГОВОР"))
        {
            QTimer *timer = new QTimer(this);
            connect(timer, &QTimer::timeout, this, [this, callee, caller, timer]() {
                if (caller->getStatus() == "ПОЛОЖЕНА") {
                    timer->stop();  // Остановить таймер, если состояние стало "ГОТОВ"
                    timer->deleteLater();  // Удалить таймер после остановки
                    callee->changeStatus("ПОЛОЖЕНА");
                    return;
                }
                if (callee->getStatus() != "ГОТОВ") {
                    if (callee->getStatus() != "ВЫЗОВ") {
                        callee->changeStatus("ВЫЗОВ");
                    }
                } else {
                    timer->stop();  // Остановить таймер, если состояние стало "ГОТОВ"
                    timer->deleteLater();  // Удалить таймер после остановки

                    currentCalls.insert(caller, callee);
                    emit caller->callConnected(caller, callee);
                    qDebug() << "Connections now: " << currentCalls.size();
                }
            });
            timer->start(500);  // Запустить таймер с интервалом 500 мс
        }
        else
        {
            caller->changeStatus("ЗАНЯТО");
        }
    }
}

void MiniAtsServer::handleCallConnected(ClientConnection *caller, ClientConnection *callee)
{
    caller->changeStatus("РАЗГОВОР");
    callee->changeStatus("РАЗГОВОР");
}

void MiniAtsServer::handleCallDisconnected(ClientConnection *client)
{
    qDebug() << "Connections before hangup: " << currentCalls.size();

    if (currentCalls.contains(client)) {
        ClientConnection* secondClient = currentCalls.value(client);
        client->changeStatus("ПОЛОЖЕНА");
        secondClient->changeStatus("ГОТОВ");
        currentCalls.remove(client);
    } else if (currentCalls.values().contains(client)){
        ClientConnection* secondClient;

        foreach (ClientConnection *key, currentCalls.keys()) {
            if(currentCalls.value(key) == client) {
                secondClient = key;
                break;
            }
        }

        client->changeStatus("ПОЛОЖЕНА");
        secondClient->changeStatus("ГОТОВ");
        currentCalls.remove(secondClient);
    } else {
        // Изменить состояние абонента, который положил трубку на "ПОЛОЖЕНО"
        client->changeStatus("ПОЛОЖЕНА");
    }

    qDebug() << "Connections after hangup: " << currentCalls.size();
}
