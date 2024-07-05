#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onConnected();
    void onDisconnected();
    void on_pickUpButton_clicked();
    void on_hangUpButton_clicked();
    void on_dialButton_clicked();
    void on_sendTextMessage();

    void onTextMessageReceived(const QString &text);
    void onPhoneStatusChanged(const QString &status);

private:
    Ui::MainWindow *ui;
    Client *client;
};

#endif // MAINWINDOW_H
