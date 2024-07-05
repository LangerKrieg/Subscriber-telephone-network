#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QRandomGenerator>

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr);
    void connectToServer(const QHostAddress &address, quint16 port);
    void disconnectFromServer();
    void setPhoneNumber(const QString &phoneNumber);
    void sendMessage(const QString &message);
    void pickUpPhone();
    void hangUpPhone();
    void sendTextMessage(const QString &text);
    void dialNumber(const QString &number);
    QString generatePhoneNumber();

signals:
    void phoneStatusChanged(const QString &status);
    void textMessageReceived(const QString &text);

private slots:
    void onReadyRead();

private:
    QTcpSocket *socket;
    QString phoneNumber;
    QString currentStatus;
};

#endif // CLIENT_H
