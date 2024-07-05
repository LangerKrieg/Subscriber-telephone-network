#ifndef MINIATSSERVER_H
#define MINIATSSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QMap>

class ClientConnection;

class MiniAtsServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit MiniAtsServer(QObject *parent = nullptr);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

private slots:
    void clientConnected(ClientConnection *client);
    void clientDisconnected(ClientConnection *client);
    void handlePickUpPhone(ClientConnection *client);
    void handleCallRequest(ClientConnection *caller, const QString &calleeNumber);
    void handleCallConnected(ClientConnection *caller, ClientConnection *callee);
    void handleCallDisconnected(ClientConnection *client);
    void handleReceivedMessage(ClientConnection *sender, const QString &textMessage);

private:
    QMap<QString, ClientConnection *> clients;
    QMap<ClientConnection*, ClientConnection*> currentCalls; //QMap для отслеживания соединений и абонентов в разговоре
    int maxConnections;
};

#endif // MINIATSSERVER_H
