/********************************************************************************
** Form generated from reading UI file 'QtGuiApplication5.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGUIAPPLICATION5_H
#define UI_QTGUIAPPLICATION5_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtGuiApplication5Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtGuiApplication5Class)
    {
        if (QtGuiApplication5Class->objectName().isEmpty())
            QtGuiApplication5Class->setObjectName(QString::fromUtf8("QtGuiApplication5Class"));
        QtGuiApplication5Class->resize(600, 400);
        menuBar = new QMenuBar(QtGuiApplication5Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        QtGuiApplication5Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtGuiApplication5Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QtGuiApplication5Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(QtGuiApplication5Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QtGuiApplication5Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QtGuiApplication5Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QtGuiApplication5Class->setStatusBar(statusBar);

        retranslateUi(QtGuiApplication5Class);

        QMetaObject::connectSlotsByName(QtGuiApplication5Class);
    } // setupUi

    void retranslateUi(QMainWindow *QtGuiApplication5Class)
    {
        QtGuiApplication5Class->setWindowTitle(QApplication::translate("QtGuiApplication5Class", "QtGuiApplication5", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtGuiApplication5Class: public Ui_QtGuiApplication5Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGUIAPPLICATION5_H
