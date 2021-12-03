/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *ThemeWidgetForm;
    QGridLayout *gridLayout_2;
    QTabWidget *tabWidget;
    QWidget *Homepage;
    QPushButton *pushButton;
    QLCDNumber *lcdNumber;
    QCustomPlot *plot;
    QPushButton *pushButton_2;
    QWidget *tab_3;
    QLCDNumber *lcdNumber_2;
    QCustomPlot *plot_2;
    QWidget *tab;
    QCustomPlot *plot_3;
    QLCDNumber *lcdNumber_3;
    QWidget *tab_5;
    QCustomPlot *plot_4;
    QLCDNumber *lcdNumber_4;
    QWidget *tab_4;
    QCustomPlot *plot_5;
    QLCDNumber *lcdNumber_5;
    QWidget *tab_2;
    QCustomPlot *plot_6;
    QLCDNumber *lcdNumber_6;
    QWidget *tab_6;
    QSlider *horizontalSlider;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QSlider *horizontalSlider_2;
    QSlider *horizontalSlider_3;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_17;
    QLineEdit *lineEdit_18;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1279, 620);
        MainWindow->setToolTipDuration(0);
        ThemeWidgetForm = new QWidget(MainWindow);
        ThemeWidgetForm->setObjectName(QString::fromUtf8("ThemeWidgetForm"));
        gridLayout_2 = new QGridLayout(ThemeWidgetForm);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tabWidget = new QTabWidget(ThemeWidgetForm);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        Homepage = new QWidget();
        Homepage->setObjectName(QString::fromUtf8("Homepage"));
        pushButton = new QPushButton(Homepage);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(100, 80, 75, 23));
        lcdNumber = new QLCDNumber(Homepage);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(880, 50, 231, 171));
        plot = new QCustomPlot(Homepage);
        plot->setObjectName(QString::fromUtf8("plot"));
        plot->setGeometry(QRect(40, 230, 441, 281));
        pushButton_2 = new QPushButton(Homepage);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(270, 80, 75, 23));
        tabWidget->addTab(Homepage, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        lcdNumber_2 = new QLCDNumber(tab_3);
        lcdNumber_2->setObjectName(QString::fromUtf8("lcdNumber_2"));
        lcdNumber_2->setGeometry(QRect(930, 80, 231, 171));
        plot_2 = new QCustomPlot(tab_3);
        plot_2->setObjectName(QString::fromUtf8("plot_2"));
        plot_2->setGeometry(QRect(50, 240, 441, 281));
        tabWidget->addTab(tab_3, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        plot_3 = new QCustomPlot(tab);
        plot_3->setObjectName(QString::fromUtf8("plot_3"));
        plot_3->setGeometry(QRect(30, 250, 441, 281));
        lcdNumber_3 = new QLCDNumber(tab);
        lcdNumber_3->setObjectName(QString::fromUtf8("lcdNumber_3"));
        lcdNumber_3->setGeometry(QRect(920, 50, 231, 171));
        tabWidget->addTab(tab, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        plot_4 = new QCustomPlot(tab_5);
        plot_4->setObjectName(QString::fromUtf8("plot_4"));
        plot_4->setGeometry(QRect(50, 240, 441, 281));
        lcdNumber_4 = new QLCDNumber(tab_5);
        lcdNumber_4->setObjectName(QString::fromUtf8("lcdNumber_4"));
        lcdNumber_4->setGeometry(QRect(900, 60, 231, 171));
        tabWidget->addTab(tab_5, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        plot_5 = new QCustomPlot(tab_4);
        plot_5->setObjectName(QString::fromUtf8("plot_5"));
        plot_5->setGeometry(QRect(40, 230, 441, 281));
        lcdNumber_5 = new QLCDNumber(tab_4);
        lcdNumber_5->setObjectName(QString::fromUtf8("lcdNumber_5"));
        lcdNumber_5->setGeometry(QRect(880, 40, 231, 171));
        tabWidget->addTab(tab_4, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        plot_6 = new QCustomPlot(tab_2);
        plot_6->setObjectName(QString::fromUtf8("plot_6"));
        plot_6->setGeometry(QRect(40, 230, 441, 281));
        lcdNumber_6 = new QLCDNumber(tab_2);
        lcdNumber_6->setObjectName(QString::fromUtf8("lcdNumber_6"));
        lcdNumber_6->setGeometry(QRect(880, 60, 231, 171));
        tabWidget->addTab(tab_2, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        horizontalSlider = new QSlider(tab_6);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(110, 60, 160, 22));
        horizontalSlider->setMaximum(1);
        horizontalSlider->setOrientation(Qt::Horizontal);
        lineEdit = new QLineEdit(tab_6);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(150, 20, 81, 20));
        lineEdit->setReadOnly(true);
        lineEdit_2 = new QLineEdit(tab_6);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(80, 90, 81, 20));
        lineEdit_2->setReadOnly(true);
        lineEdit_3 = new QLineEdit(tab_6);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(240, 90, 81, 20));
        lineEdit_4 = new QLineEdit(tab_6);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(510, 20, 131, 41));
        QFont font;
        font.setPointSize(20);
        lineEdit_4->setFont(font);
        lineEdit_4->setReadOnly(true);
        horizontalSlider_2 = new QSlider(tab_6);
        horizontalSlider_2->setObjectName(QString::fromUtf8("horizontalSlider_2"));
        horizontalSlider_2->setGeometry(QRect(110, 190, 160, 22));
        horizontalSlider_2->setMaximum(1);
        horizontalSlider_2->setOrientation(Qt::Horizontal);
        horizontalSlider_3 = new QSlider(tab_6);
        horizontalSlider_3->setObjectName(QString::fromUtf8("horizontalSlider_3"));
        horizontalSlider_3->setGeometry(QRect(110, 290, 160, 22));
        horizontalSlider_3->setMaximum(1);
        horizontalSlider_3->setOrientation(Qt::Horizontal);
        lineEdit_5 = new QLineEdit(tab_6);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(70, 220, 81, 20));
        lineEdit_5->setReadOnly(true);
        lineEdit_6 = new QLineEdit(tab_6);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(240, 220, 101, 20));
        lineEdit_6->setReadOnly(true);
        lineEdit_7 = new QLineEdit(tab_6);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
        lineEdit_7->setGeometry(QRect(240, 320, 81, 20));
        lineEdit_7->setReadOnly(true);
        lineEdit_8 = new QLineEdit(tab_6);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));
        lineEdit_8->setGeometry(QRect(80, 320, 81, 20));
        lineEdit_8->setReadOnly(true);
        lineEdit_17 = new QLineEdit(tab_6);
        lineEdit_17->setObjectName(QString::fromUtf8("lineEdit_17"));
        lineEdit_17->setGeometry(QRect(160, 150, 81, 20));
        lineEdit_17->setReadOnly(true);
        lineEdit_18 = new QLineEdit(tab_6);
        lineEdit_18->setObjectName(QString::fromUtf8("lineEdit_18"));
        lineEdit_18->setGeometry(QRect(160, 260, 81, 20));
        lineEdit_18->setReadOnly(true);
        tabWidget->addTab(tab_6, QString());

        gridLayout_2->addWidget(tabWidget, 0, 1, 1, 1);

        MainWindow->setCentralWidget(ThemeWidgetForm);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "REWS Desktop Visualizer", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Hello", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "clear", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Homepage), QCoreApplication::translate("MainWindow", "Homepage", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Temperature", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Humidity", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("MainWindow", "Wind Speed/Direction", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("MainWindow", "Pressure", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Air Quality", nullptr));
        lineEdit->setText(QCoreApplication::translate("MainWindow", "Temperature", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("MainWindow", "Celsius", nullptr));
        lineEdit_3->setText(QCoreApplication::translate("MainWindow", "Fahrenheit", nullptr));
        lineEdit_4->setText(QCoreApplication::translate("MainWindow", "SETTINGS", nullptr));
        lineEdit_5->setText(QCoreApplication::translate("MainWindow", "Miles Per Hour", nullptr));
        lineEdit_6->setText(QCoreApplication::translate("MainWindow", "Kilometer Per Hour", nullptr));
        lineEdit_7->setText(QCoreApplication::translate("MainWindow", "Pascals", nullptr));
        lineEdit_8->setText(QCoreApplication::translate("MainWindow", "Millibars", nullptr));
        lineEdit_17->setText(QCoreApplication::translate("MainWindow", "Wind Speed", nullptr));
        lineEdit_18->setText(QCoreApplication::translate("MainWindow", "Pressure", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QCoreApplication::translate("MainWindow", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
