#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <QObject>
#include <QTcpSocket>

class ClientConnection : public QObject
{
    Q_OBJECT

public:
    explicit ClientConnection(qintptr socketDescriptor, QObject *parent = nullptr);
    QString getPhoneNumber() const;
    QString getStatus() const;
    void sendMessage(const QString &message);
    void changeStatus(const QString &clientStatus);

signals:
    void connected(ClientConnection *client);
    void disconnected(ClientConnection *client);
    void pickUpPhone(ClientConnection *client);
    void callRequest(ClientConnection *caller, const QString &calleeNumber);
    void callConnected(ClientConnection *caller, ClientConnection *callee);
    void callDisconnected(ClientConnection *client);
    void receivedMessage(ClientConnection *sender, const QString &senderText);

private slots:
    void onReadyRead();
    void onDisconnected();

private:
    QTcpSocket *socket;
    QString phoneNumber;
    QString status;
};

#endif // CLIENTCONNECTION_H
