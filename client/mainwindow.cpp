#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    client(new Client(this))
{
    ui->setupUi(this);

    // Connect signals and slots
    connect(client, &Client::phoneStatusChanged, this, &MainWindow::onPhoneStatusChanged);
    connect(client, &Client::textMessageReceived, this, &MainWindow::onTextMessageReceived);
    connect(ui->messageTextEdit, &QTextEdit::textChanged, this, &MainWindow::on_sendTextMessage);

    onConnected();
    ui->phoneStatusLabel->setText("ПОЛОЖЕНА");
}

MainWindow::~MainWindow()
{
    onDisconnected();
    delete ui;
}

void MainWindow::onConnected()
{

    client->connectToServer(QHostAddress::LocalHost, 12345);
    QString phoneNumber = client->generatePhoneNumber();
    client->setPhoneNumber(phoneNumber);
    ui->clientNumber->setText(phoneNumber);
    ui->hangUpButton->setEnabled(false);
    ui->dialButton->setEnabled(false);

}

void MainWindow::onDisconnected()
{
    client->hangUpPhone();
    client->disconnectFromServer();
}

void MainWindow::on_pickUpButton_clicked()
{
    client->pickUpPhone();
    ui->hangUpButton->setEnabled(true);
    ui->dialButton->setEnabled(true);
    ui->pickUpButton->setEnabled(false);
}

void MainWindow::on_hangUpButton_clicked()
{
    client->hangUpPhone();
    ui->hangUpButton->setEnabled(false);
    ui->dialButton->setEnabled(false);
    ui->pickUpButton->setEnabled(true);
}

void MainWindow::on_dialButton_clicked()
{
    QString number = ui->numberLineEdit->text();
    client->dialNumber(number);
}

void MainWindow::on_sendTextMessage()
{
    QString text = ui->messageTextEdit->toPlainText();
    client->sendTextMessage(text);
}

void MainWindow::onTextMessageReceived(const QString &text)
{
    ui->messageFrom->setText(text);
}

void MainWindow::onPhoneStatusChanged(const QString &status)
{
    ui->phoneStatusLabel->setText(status);
}

