/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pickUpButton;
    QPushButton *hangUpButton;
    QTextEdit *messageTextEdit;
    QLabel *phoneStatusLabel;
    QLineEdit *numberLineEdit;
    QPushButton *dialButton;
    QLabel *messageFrom;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *clientNumber;
    QLabel *label_4;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(412, 384);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        pickUpButton = new QPushButton(centralWidget);
        pickUpButton->setObjectName("pickUpButton");
        pickUpButton->setGeometry(QRect(270, 10, 121, 30));
        hangUpButton = new QPushButton(centralWidget);
        hangUpButton->setObjectName("hangUpButton");
        hangUpButton->setGeometry(QRect(20, 10, 141, 30));
        messageTextEdit = new QTextEdit(centralWidget);
        messageTextEdit->setObjectName("messageTextEdit");
        messageTextEdit->setGeometry(QRect(20, 190, 371, 91));
        phoneStatusLabel = new QLabel(centralWidget);
        phoneStatusLabel->setObjectName("phoneStatusLabel");
        phoneStatusLabel->setGeometry(QRect(270, 130, 91, 16));
        numberLineEdit = new QLineEdit(centralWidget);
        numberLineEdit->setObjectName("numberLineEdit");
        numberLineEdit->setGeometry(QRect(20, 80, 211, 31));
        dialButton = new QPushButton(centralWidget);
        dialButton->setObjectName("dialButton");
        dialButton->setGeometry(QRect(270, 60, 121, 30));
        messageFrom = new QLabel(centralWidget);
        messageFrom->setObjectName("messageFrom");
        messageFrom->setGeometry(QRect(20, 290, 361, 81));
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 160, 151, 20));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(270, 100, 51, 20));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 120, 91, 20));
        clientNumber = new QLabel(centralWidget);
        clientNumber->setObjectName("clientNumber");
        clientNumber->setGeometry(QRect(110, 120, 141, 20));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(20, 50, 211, 20));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Mini-ATS Client", nullptr));
        pickUpButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\267\321\217\321\202\321\214 \321\202\321\200\321\203\320\261\320\272\321\203", nullptr));
        hangUpButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\273\320\276\320\266\320\270\321\202\321\214 \321\202\321\200\321\203\320\261\320\272\321\203", nullptr));
        phoneStatusLabel->setText(QCoreApplication::translate("MainWindow", "Phone Status", nullptr));
        numberLineEdit->setText(QString());
        dialButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\267\320\262\320\276\320\275\320\270\321\202\321\214", nullptr));
        messageFrom->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\265:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\241\321\202\320\260\321\202\321\203\321\201:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\222\320\260\321\210 \320\275\320\276\320\274\320\265\321\200:", nullptr));
        clientNumber->setText(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\275\320\276\320\274\320\265\321\200 \321\201\320\276\320\261\320\265\321\201\320\265\320\264\320\275\320\270\320\272\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
