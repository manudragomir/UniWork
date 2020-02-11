/********************************************************************************
** Form generated from reading UI file 'SimulareLaborator.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMULARELABORATOR_H
#define UI_SIMULARELABORATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimulareLaboratorClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SimulareLaboratorClass)
    {
        if (SimulareLaboratorClass->objectName().isEmpty())
            SimulareLaboratorClass->setObjectName(QString::fromUtf8("SimulareLaboratorClass"));
        SimulareLaboratorClass->resize(600, 400);
        menuBar = new QMenuBar(SimulareLaboratorClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        SimulareLaboratorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SimulareLaboratorClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        SimulareLaboratorClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(SimulareLaboratorClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        SimulareLaboratorClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(SimulareLaboratorClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SimulareLaboratorClass->setStatusBar(statusBar);

        retranslateUi(SimulareLaboratorClass);

        QMetaObject::connectSlotsByName(SimulareLaboratorClass);
    } // setupUi

    void retranslateUi(QMainWindow *SimulareLaboratorClass)
    {
        SimulareLaboratorClass->setWindowTitle(QApplication::translate("SimulareLaboratorClass", "SimulareLaborator", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SimulareLaboratorClass: public Ui_SimulareLaboratorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMULARELABORATOR_H
