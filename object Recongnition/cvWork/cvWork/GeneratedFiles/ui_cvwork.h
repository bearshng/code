/********************************************************************************
** Form generated from reading UI file 'cvwork.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CVWORK_H
#define UI_CVWORK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cvWorkClass
{
public:
    QAction *actionOpen;
    QAction *actionExtract;
    QAction *actionTrain;
    QAction *actionExtract_2;
    QWidget *centralWidget;
    QPushButton *surfBtn;
    QPushButton *siftBtn;
    QLabel *imageLabel;
    QLabel *topLabel;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *cvWorkClass)
    {
        if (cvWorkClass->objectName().isEmpty())
            cvWorkClass->setObjectName(QStringLiteral("cvWorkClass"));
        cvWorkClass->resize(721, 529);
        cvWorkClass->setStyleSheet(QStringLiteral("background-color: rgb(175,213,239);"));
        actionOpen = new QAction(cvWorkClass);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionExtract = new QAction(cvWorkClass);
        actionExtract->setObjectName(QStringLiteral("actionExtract"));
        actionTrain = new QAction(cvWorkClass);
        actionTrain->setObjectName(QStringLiteral("actionTrain"));
        actionExtract_2 = new QAction(cvWorkClass);
        actionExtract_2->setObjectName(QStringLiteral("actionExtract_2"));
        centralWidget = new QWidget(cvWorkClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        surfBtn = new QPushButton(centralWidget);
        surfBtn->setObjectName(QStringLiteral("surfBtn"));
        surfBtn->setGeometry(QRect(120, 440, 75, 23));
        surfBtn->setStyleSheet(QStringLiteral("border-radius:5px;"));
        surfBtn->setAutoDefault(false);
        surfBtn->setDefault(false);
        surfBtn->setFlat(false);
        siftBtn = new QPushButton(centralWidget);
        siftBtn->setObjectName(QStringLiteral("siftBtn"));
        siftBtn->setGeometry(QRect(350, 440, 75, 23));
        siftBtn->setStyleSheet(QLatin1String("border-radius:5px;\n"
""));
        siftBtn->setFlat(false);
        imageLabel = new QLabel(centralWidget);
        imageLabel->setObjectName(QStringLiteral("imageLabel"));
        imageLabel->setGeometry(QRect(10, 20, 441, 411));
        imageLabel->setStyleSheet(QLatin1String("border:1px dashed gray;\n"
"height:400px;"));
        imageLabel->setAlignment(Qt::AlignCenter);
        topLabel = new QLabel(centralWidget);
        topLabel->setObjectName(QStringLiteral("topLabel"));
        topLabel->setGeometry(QRect(460, 20, 241, 411));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        topLabel->setFont(font);
        topLabel->setStyleSheet(QLatin1String("border:1px dashed gray;\n"
"height:400px;"));
        topLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        cvWorkClass->setCentralWidget(centralWidget);
        surfBtn->raise();
        imageLabel->raise();
        siftBtn->raise();
        topLabel->raise();
        menuBar = new QMenuBar(cvWorkClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 721, 23));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        cvWorkClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(cvWorkClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        cvWorkClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(cvWorkClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        cvWorkClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);

        retranslateUi(cvWorkClass);

        QMetaObject::connectSlotsByName(cvWorkClass);
    } // setupUi

    void retranslateUi(QMainWindow *cvWorkClass)
    {
        cvWorkClass->setWindowTitle(QApplication::translate("cvWorkClass", "\347\256\200\345\215\225\347\211\251\344\275\223\350\257\206\345\210\253\345\267\245\345\205\267", 0));
        actionOpen->setText(QApplication::translate("cvWorkClass", "\346\211\223\345\274\200", 0));
        actionExtract->setText(QApplication::translate("cvWorkClass", "\346\217\220\345\217\226", 0));
        actionTrain->setText(QApplication::translate("cvWorkClass", "\350\256\255\347\273\203", 0));
        actionExtract_2->setText(QApplication::translate("cvWorkClass", "\346\217\220\345\217\226", 0));
        surfBtn->setText(QApplication::translate("cvWorkClass", "SURF\347\256\227\345\255\220", 0));
        siftBtn->setText(QApplication::translate("cvWorkClass", "SIFT\347\256\227\345\255\220", 0));
        imageLabel->setText(QString());
        topLabel->setText(QString());
        menuFile->setTitle(QApplication::translate("cvWorkClass", "\346\226\207\344\273\266", 0));
    } // retranslateUi

};

namespace Ui {
    class cvWorkClass: public Ui_cvWorkClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CVWORK_H
