/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
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
    QLCDNumber *lcdNumber;
    QCustomPlot *HomepagePlot;
    QPushButton *HTTPButton;
    QPlainTextEdit *HTTPTextInput;
    QLabel *EnterURLText;
    QWidget *Humidity;
    QCustomPlot *PlotHumidity;
    QLCDNumber *LCDHumidity;
    QWidget *Temperature;
    QLCDNumber *LCDTemperature;
    QCustomPlot *PlotTemperature;
    QLabel *label_10;
    QWidget *Wind;
    QCustomPlot *PlotWindSpeedDirection;
    QLCDNumber *LCDWind;
    QWidget *Pressure;
    QCustomPlot *PlotPressure;
    QLCDNumber *LCDPressure;
    QWidget *AirQuality;
    QCustomPlot *PlotAirQuality;
    QLCDNumber *LCDAirQuality;
    QWidget *Settings;
    QSlider *ChangeTemperature;
    QLineEdit *lineEdit_4;
    QSlider *ChangeWind;
    QSlider *ChangePressure;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1279, 620);
        MainWindow->setToolTipDuration(0);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow{\n"
"	background-color: rgb(185, 185, 185);  /*  Background window color   */ \n"
"}\n"
"\n"
" /* Window color  for all tabs */ \n"
"QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{\n"
"	background-color: rgb(225, 225, 225);\n"
"}\n"
"\n"
" /* Window color  for all tabs */ \n"
"QWidget{\n"
"	color: black;\n"
"	\n"
"	background-color: rgb(182, 182, 182);\n"
"}\n"
"\n"
"QTabWidget{\n"
"	font: 16pt \"Microsoft YaHei UI\"; /*  Tab font and size   */ \n"
"}\n"
"\n"
"QTabBar{\n"
"	color: black;  /*  Tab font color   */ \n"
"}\n"
"\n"
"QTabBar::tab{\n"
"	background: rgb(144, 144, 144); /*  Tab background color   */ \n"
"	border: 1px solid black;\n"
"	padding: 5px;\n"
"}\n"
"\n"
"QTabBar::tab:selected{\n"
"	background:rgb(230, 230, 230) ; /*  Selected tab background color   */ \n"
"}\n"
"\n"
"QTabBar::tab:hover{\n"
"	background:  rgb(168, 168, 168); /*  Selected tab background color   */ \n"
"}\n"
"\n"
"QTabWidget::tab-bar{\n"
"	"
                        "alignment: center /*  Allign the tabs to the center   */ \n"
"}\n"
"\n"
""));
        ThemeWidgetForm = new QWidget(MainWindow);
        ThemeWidgetForm->setObjectName(QString::fromUtf8("ThemeWidgetForm"));
        gridLayout_2 = new QGridLayout(ThemeWidgetForm);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tabWidget = new QTabWidget(ThemeWidgetForm);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setStyleSheet(QString::fromUtf8(""));
        Homepage = new QWidget();
        Homepage->setObjectName(QString::fromUtf8("Homepage"));
        lcdNumber = new QLCDNumber(Homepage);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(1000, 20, 231, 171));
        HomepagePlot = new QCustomPlot(Homepage);
        HomepagePlot->setObjectName(QString::fromUtf8("HomepagePlot"));
        HomepagePlot->setGeometry(QRect(40, 230, 441, 281));
        HTTPButton = new QPushButton(Homepage);
        HTTPButton->setObjectName(QString::fromUtf8("HTTPButton"));
        HTTPButton->setGeometry(QRect(170, 90, 80, 21));
        HTTPTextInput = new QPlainTextEdit(Homepage);
        HTTPTextInput->setObjectName(QString::fromUtf8("HTTPTextInput"));
        HTTPTextInput->setGeometry(QRect(130, 40, 201, 41));
        EnterURLText = new QLabel(Homepage);
        EnterURLText->setObjectName(QString::fromUtf8("EnterURLText"));
        EnterURLText->setGeometry(QRect(190, 20, 81, 16));
        tabWidget->addTab(Homepage, QString());
        Humidity = new QWidget();
        Humidity->setObjectName(QString::fromUtf8("Humidity"));
        PlotHumidity = new QCustomPlot(Humidity);
        PlotHumidity->setObjectName(QString::fromUtf8("PlotHumidity"));
        PlotHumidity->setGeometry(QRect(30, 250, 441, 281));
        LCDHumidity = new QLCDNumber(Humidity);
        LCDHumidity->setObjectName(QString::fromUtf8("LCDHumidity"));
        LCDHumidity->setGeometry(QRect(920, 50, 231, 171));
        tabWidget->addTab(Humidity, QString());
        Temperature = new QWidget();
        Temperature->setObjectName(QString::fromUtf8("Temperature"));
        LCDTemperature = new QLCDNumber(Temperature);
        LCDTemperature->setObjectName(QString::fromUtf8("LCDTemperature"));
        LCDTemperature->setGeometry(QRect(930, 80, 231, 171));
        PlotTemperature = new QCustomPlot(Temperature);
        PlotTemperature->setObjectName(QString::fromUtf8("PlotTemperature"));
        PlotTemperature->setGeometry(QRect(50, 240, 441, 281));
        label_10 = new QLabel(Temperature);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(40, 70, 511, 111));
        label_10->setScaledContents(false);
        tabWidget->addTab(Temperature, QString());
        Wind = new QWidget();
        Wind->setObjectName(QString::fromUtf8("Wind"));
        PlotWindSpeedDirection = new QCustomPlot(Wind);
        PlotWindSpeedDirection->setObjectName(QString::fromUtf8("PlotWindSpeedDirection"));
        PlotWindSpeedDirection->setGeometry(QRect(50, 240, 441, 281));
        LCDWind = new QLCDNumber(Wind);
        LCDWind->setObjectName(QString::fromUtf8("LCDWind"));
        LCDWind->setGeometry(QRect(900, 60, 231, 171));
        tabWidget->addTab(Wind, QString());
        Pressure = new QWidget();
        Pressure->setObjectName(QString::fromUtf8("Pressure"));
        PlotPressure = new QCustomPlot(Pressure);
        PlotPressure->setObjectName(QString::fromUtf8("PlotPressure"));
        PlotPressure->setGeometry(QRect(40, 230, 441, 281));
        LCDPressure = new QLCDNumber(Pressure);
        LCDPressure->setObjectName(QString::fromUtf8("LCDPressure"));
        LCDPressure->setGeometry(QRect(880, 40, 231, 171));
        tabWidget->addTab(Pressure, QString());
        AirQuality = new QWidget();
        AirQuality->setObjectName(QString::fromUtf8("AirQuality"));
        PlotAirQuality = new QCustomPlot(AirQuality);
        PlotAirQuality->setObjectName(QString::fromUtf8("PlotAirQuality"));
        PlotAirQuality->setGeometry(QRect(40, 230, 441, 281));
        PlotAirQuality->setStyleSheet(QString::fromUtf8(""));
        LCDAirQuality = new QLCDNumber(AirQuality);
        LCDAirQuality->setObjectName(QString::fromUtf8("LCDAirQuality"));
        LCDAirQuality->setGeometry(QRect(880, 60, 231, 171));
        tabWidget->addTab(AirQuality, QString());
        Settings = new QWidget();
        Settings->setObjectName(QString::fromUtf8("Settings"));
        ChangeTemperature = new QSlider(Settings);
        ChangeTemperature->setObjectName(QString::fromUtf8("ChangeTemperature"));
        ChangeTemperature->setGeometry(QRect(110, 60, 160, 22));
        ChangeTemperature->setMaximum(1);
        ChangeTemperature->setOrientation(Qt::Horizontal);
        lineEdit_4 = new QLineEdit(Settings);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(510, 20, 131, 41));
        QFont font;
        font.setPointSize(20);
        lineEdit_4->setFont(font);
        lineEdit_4->setReadOnly(true);
        ChangeWind = new QSlider(Settings);
        ChangeWind->setObjectName(QString::fromUtf8("ChangeWind"));
        ChangeWind->setGeometry(QRect(120, 160, 160, 22));
        ChangeWind->setMaximum(1);
        ChangeWind->setOrientation(Qt::Horizontal);
        ChangePressure = new QSlider(Settings);
        ChangePressure->setObjectName(QString::fromUtf8("ChangePressure"));
        ChangePressure->setGeometry(QRect(120, 260, 160, 22));
        ChangePressure->setMaximum(1);
        ChangePressure->setOrientation(Qt::Horizontal);
        label = new QLabel(Settings);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(160, 40, 71, 16));
        label_2 = new QLabel(Settings);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(100, 80, 41, 16));
        label_3 = new QLabel(Settings);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(240, 80, 61, 16));
        label_4 = new QLabel(Settings);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(160, 140, 71, 16));
        label_5 = new QLabel(Settings);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(80, 180, 121, 16));
        label_6 = new QLabel(Settings);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(210, 180, 141, 16));
        label_7 = new QLabel(Settings);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(160, 240, 71, 16));
        label_8 = new QLabel(Settings);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(100, 280, 49, 16));
        label_9 = new QLabel(Settings);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(260, 280, 51, 16));
        tabWidget->addTab(Settings, QString());

        gridLayout_2->addWidget(tabWidget, 0, 0, 1, 1);

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
        HTTPButton->setText(QCoreApplication::translate("MainWindow", "Send HTTP", nullptr));
        HTTPTextInput->setPlainText(QCoreApplication::translate("MainWindow", "https://www.qt.io/blog", nullptr));
        EnterURLText->setText(QCoreApplication::translate("MainWindow", "Enter URL", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Homepage), QCoreApplication::translate("MainWindow", "Homepage", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Humidity), QCoreApplication::translate("MainWindow", "Humidity", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Temperature", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Temperature), QCoreApplication::translate("MainWindow", "Temperature", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Wind), QCoreApplication::translate("MainWindow", "Wind Speed/Direction", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Pressure), QCoreApplication::translate("MainWindow", "Pressure", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(AirQuality), QCoreApplication::translate("MainWindow", "Air Quality", nullptr));
        lineEdit_4->setText(QCoreApplication::translate("MainWindow", "SETTINGS", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Temperature", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Celsius", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Fahrenheit", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Wind Speed", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Miles Per Hour (MPH)", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Kilometers Per Hour (KPH)", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Air Pressure", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Millibars", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Pascals", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Settings), QCoreApplication::translate("MainWindow", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
