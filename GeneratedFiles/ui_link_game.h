/********************************************************************************
** Form generated from reading UI file 'link_game.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LINK_GAME_H
#define UI_LINK_GAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Link_GameClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Link_GameClass)
    {
        if (Link_GameClass->objectName().isEmpty())
            Link_GameClass->setObjectName(QStringLiteral("Link_GameClass"));
        Link_GameClass->resize(600, 400);
        menuBar = new QMenuBar(Link_GameClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        Link_GameClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Link_GameClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Link_GameClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Link_GameClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Link_GameClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Link_GameClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Link_GameClass->setStatusBar(statusBar);

        retranslateUi(Link_GameClass);

        QMetaObject::connectSlotsByName(Link_GameClass);
    } // setupUi

    void retranslateUi(QMainWindow *Link_GameClass)
    {
        Link_GameClass->setWindowTitle(QApplication::translate("Link_GameClass", "Link_Game", 0));
    } // retranslateUi

};

namespace Ui {
    class Link_GameClass: public Ui_Link_GameClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LINK_GAME_H
