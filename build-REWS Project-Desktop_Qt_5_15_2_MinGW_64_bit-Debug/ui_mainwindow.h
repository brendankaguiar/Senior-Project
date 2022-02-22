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
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
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
    QPushButton *HTTPButton;
    QLabel *HomeTemp;
    QLabel *HomePressure;
    QLabel *HomeHumidity;
    QLabel *HomeAQ;
    QLabel *HomeWind;
    QLabel *HomeTime;
    QLabel *HomeDate;
    QLabel *HomeHumidityVal;
    QLabel *HomeWindVal;
    QLabel *HomePressureVal;
    QLabel *HomeAQVal;
    QPushButton *pushButton;
    QWidget *Humidity;
    QCustomPlot *PlotHumidity;
    QLCDNumber *LCDHumidity;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *DateSelector_2;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_2;
    QLabel *From_2;
    QDateEdit *FirstDate_2;
    QLabel *To_2;
    QDateEdit *SecondDate_2;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QWidget *Temperature;
    QLCDNumber *LCDTemperature;
    QCustomPlot *PlotTemperature;
    QLabel *label_10;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *DateSelector;
    QLabel *label_6;
    QHBoxLayout *horizontalLayout;
    QLabel *From;
    QDateEdit *FirstDate;
    QLabel *To;
    QDateEdit *SecondDate;
    QLabel *label_3;
    QLabel *label_5;
    QWidget *Wind;
    QCustomPlot *PlotWindSpeedDirection;
    QLCDNumber *LCDWind;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *DateSelector_3;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout_3;
    QLabel *From_3;
    QDateEdit *FirstDate_3;
    QLabel *To_3;
    QDateEdit *SecondDate_3;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_19;
    QWidget *Pressure;
    QCustomPlot *PlotPressure;
    QLCDNumber *LCDPressure;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *DateSelector_4;
    QLabel *label_11;
    QHBoxLayout *horizontalLayout_4;
    QLabel *From_4;
    QDateEdit *FirstDate_4;
    QLabel *To_4;
    QDateEdit *SecondDate_4;
    QLabel *label_20;
    QLabel *label_21;
    QLabel *label_22;
    QWidget *AirQuality;
    QCustomPlot *PlotAirQuality;
    QLCDNumber *LCDAirQuality;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *DateSelector_5;
    QLabel *label_12;
    QHBoxLayout *horizontalLayout_5;
    QLabel *From_5;
    QDateEdit *FirstDate_5;
    QLabel *To_5;
    QDateEdit *SecondDate_5;
    QLabel *label_23;
    QLabel *label_24;
    QLabel *label_25;
    QLabel *label_2;
    QWidget *Settings;
    QLineEdit *SettingsTitle;
    QFrame *SettingsOptions;
    QFormLayout *formLayout;
    QLabel *AirTitle;
    QFrame *verticalFrame;
    QVBoxLayout *verticalLayout;
    QRadioButton *MillibarsButton;
    QRadioButton *PascalButton;
    QLabel *WindTitle;
    QFrame *WindOptions;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *MPHButton;
    QRadioButton *KPHButton;
    QLabel *TemperatureTitle;
    QFrame *TemperatureOptions;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *CelciusButton;
    QRadioButton *FarenheitButton;
    QPushButton *DeleteAll;
    QPushButton *DownloadAll;
    QPushButton *AboutButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1279, 620);
        MainWindow->setToolTipDuration(0);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow{\n"
"	background-color:   rgb(185, 185, 185);  /*  Background window color   */ \n"
"}\n"
"\n"
" /* Main window color in center */ \n"
"QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{\n"
"	/*background-color: rgb(254,255,153);*/\n"
"	background-color: rgb(225,225,225);\n"
"}\n"
"\n"
" /* Color the widgets so you can see them in the preview */ \n"
"QWidget{\n"
"	color: black;\n"
"	background-color:  rgb(182, 182, 182);\n"
"}\n"
"\n"
" /* Remove the background on the radio button widgets */ \n"
"QRadioButton{\n"
"	color: black;\n"
"	background-color: none\n"
"}\n"
"\n"
" /* Remove the background on the VBoxes */ \n"
"QFrame{\n"
" 	background-color: none\n"
"}\n"
"QTabWidget{\n"
"	font: 16pt \"Microsoft YaHei UI\"; /*  Tab font and size   */ \n"
"}\n"
"\n"
"QTabWidget::pane{\n"
"	color:red;\n"
"}\n"
"\n"
"QTabBar{\n"
"	color: black;  /*  Tab font color   */ \n"
"}\n"
"\n"
"QTabBar::tab{\n"
"	background: rgb(144, 144, 144); "
                        "/*  Tab background color   */ \n"
"	border: 1px solid black;\n"
"	padding: 5px;\n"
"}\n"
"\n"
"QTabBar::tab:selected{\n"
"	background:rgb(230, 230, 230) ; /*  Selected tab background color   */ \n"
"}\n"
"\n"
"QTabBar::tab:hover{\n"
"	background:  rgb(168, 168, 168); /*  Hovered tab background color   */ \n"
"}\n"
"\n"
"QTabWidget::tab-bar{\n"
"	alignment: center /*  Allign the tabs to the center   */ \n"
"}\n"
"\n"
""));
        MainWindow->setAnimated(true);
        ThemeWidgetForm = new QWidget(MainWindow);
        ThemeWidgetForm->setObjectName(QString::fromUtf8("ThemeWidgetForm"));
        ThemeWidgetForm->setEnabled(true);
        gridLayout_2 = new QGridLayout(ThemeWidgetForm);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        tabWidget = new QTabWidget(ThemeWidgetForm);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setStyleSheet(QString::fromUtf8(""));
        Homepage = new QWidget();
        Homepage->setObjectName(QString::fromUtf8("Homepage"));
        HTTPButton = new QPushButton(Homepage);
        HTTPButton->setObjectName(QString::fromUtf8("HTTPButton"));
        HTTPButton->setGeometry(QRect(30, 500, 80, 21));
        HomeTemp = new QLabel(Homepage);
        HomeTemp->setObjectName(QString::fromUtf8("HomeTemp"));
        HomeTemp->setGeometry(QRect(60, 30, 531, 251));
        QFont font;
        font.setPointSize(72);
        HomeTemp->setFont(font);
        HomePressure = new QLabel(Homepage);
        HomePressure->setObjectName(QString::fromUtf8("HomePressure"));
        HomePressure->setGeometry(QRect(560, 230, 301, 181));
        QFont font1;
        font1.setPointSize(48);
        HomePressure->setFont(font1);
        HomeHumidity = new QLabel(Homepage);
        HomeHumidity->setObjectName(QString::fromUtf8("HomeHumidity"));
        HomeHumidity->setGeometry(QRect(560, 20, 301, 181));
        HomeHumidity->setFont(font1);
        HomeAQ = new QLabel(Homepage);
        HomeAQ->setObjectName(QString::fromUtf8("HomeAQ"));
        HomeAQ->setGeometry(QRect(900, 230, 301, 181));
        HomeAQ->setFont(font1);
        HomeWind = new QLabel(Homepage);
        HomeWind->setObjectName(QString::fromUtf8("HomeWind"));
        HomeWind->setGeometry(QRect(900, 20, 431, 181));
        HomeWind->setFont(font1);
        HomeTime = new QLabel(Homepage);
        HomeTime->setObjectName(QString::fromUtf8("HomeTime"));
        HomeTime->setGeometry(QRect(40, 320, 501, 111));
        HomeTime->setFont(font);
        HomeDate = new QLabel(Homepage);
        HomeDate->setObjectName(QString::fromUtf8("HomeDate"));
        HomeDate->setGeometry(QRect(40, 400, 511, 71));
        QFont font2;
        font2.setPointSize(28);
        HomeDate->setFont(font2);
        HomeHumidityVal = new QLabel(Homepage);
        HomeHumidityVal->setObjectName(QString::fromUtf8("HomeHumidityVal"));
        HomeHumidityVal->setGeometry(QRect(630, 120, 141, 171));
        HomeHumidityVal->setFont(font2);
        HomeWindVal = new QLabel(Homepage);
        HomeWindVal->setObjectName(QString::fromUtf8("HomeWindVal"));
        HomeWindVal->setGeometry(QRect(980, 120, 231, 171));
        HomeWindVal->setFont(font2);
        HomePressureVal = new QLabel(Homepage);
        HomePressureVal->setObjectName(QString::fromUtf8("HomePressureVal"));
        HomePressureVal->setGeometry(QRect(600, 370, 261, 81));
        HomePressureVal->setFont(font2);
        HomeAQVal = new QLabel(Homepage);
        HomeAQVal->setObjectName(QString::fromUtf8("HomeAQVal"));
        HomeAQVal->setGeometry(QRect(900, 370, 251, 111));
        HomeAQVal->setFont(font2);
        HomeAQVal->setAlignment(Qt::AlignCenter);
        pushButton = new QPushButton(Homepage);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(290, 500, 80, 24));
        tabWidget->addTab(Homepage, QString());
        Humidity = new QWidget();
        Humidity->setObjectName(QString::fromUtf8("Humidity"));
        PlotHumidity = new QCustomPlot(Humidity);
        PlotHumidity->setObjectName(QString::fromUtf8("PlotHumidity"));
        PlotHumidity->setGeometry(QRect(270, 230, 441, 281));
        LCDHumidity = new QLCDNumber(Humidity);
        LCDHumidity->setObjectName(QString::fromUtf8("LCDHumidity"));
        LCDHumidity->setGeometry(QRect(410, 30, 231, 171));
        verticalLayoutWidget_2 = new QWidget(Humidity);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(40, 430, 231, 78));
        DateSelector_2 = new QVBoxLayout(verticalLayoutWidget_2);
        DateSelector_2->setObjectName(QString::fromUtf8("DateSelector_2"));
        DateSelector_2->setContentsMargins(0, 0, 0, 0);
        label_8 = new QLabel(verticalLayoutWidget_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QFont font3;
        font3.setPointSize(12);
        label_8->setFont(font3);

        DateSelector_2->addWidget(label_8);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        From_2 = new QLabel(verticalLayoutWidget_2);
        From_2->setObjectName(QString::fromUtf8("From_2"));
        From_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(From_2);

        FirstDate_2 = new QDateEdit(verticalLayoutWidget_2);
        FirstDate_2->setObjectName(QString::fromUtf8("FirstDate_2"));

        horizontalLayout_2->addWidget(FirstDate_2);

        To_2 = new QLabel(verticalLayoutWidget_2);
        To_2->setObjectName(QString::fromUtf8("To_2"));
        To_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(To_2);

        SecondDate_2 = new QDateEdit(verticalLayoutWidget_2);
        SecondDate_2->setObjectName(QString::fromUtf8("SecondDate_2"));

        horizontalLayout_2->addWidget(SecondDate_2);


        DateSelector_2->addLayout(horizontalLayout_2);

        label_13 = new QLabel(Humidity);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 10, 941, 211));
        QFont font4;
        font4.setPointSize(36);
        label_13->setFont(font4);
        label_13->setScaledContents(false);
        label_14 = new QLabel(Humidity);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(810, 320, 341, 121));
        QFont font5;
        font5.setPointSize(24);
        label_14->setFont(font5);
        label_15 = new QLabel(Humidity);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(0, 520, 211, 16));
        tabWidget->addTab(Humidity, QString());
        Temperature = new QWidget();
        Temperature->setObjectName(QString::fromUtf8("Temperature"));
        LCDTemperature = new QLCDNumber(Temperature);
        LCDTemperature->setObjectName(QString::fromUtf8("LCDTemperature"));
        LCDTemperature->setGeometry(QRect(500, 10, 231, 171));
        PlotTemperature = new QCustomPlot(Temperature);
        PlotTemperature->setObjectName(QString::fromUtf8("PlotTemperature"));
        PlotTemperature->setGeometry(QRect(360, 210, 441, 281));
        label_10 = new QLabel(Temperature);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(50, -10, 941, 211));
        label_10->setFont(font4);
        label_10->setScaledContents(false);
        verticalLayoutWidget = new QWidget(Temperature);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(100, 410, 231, 78));
        DateSelector = new QVBoxLayout(verticalLayoutWidget);
        DateSelector->setObjectName(QString::fromUtf8("DateSelector"));
        DateSelector->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(verticalLayoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font3);

        DateSelector->addWidget(label_6);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        From = new QLabel(verticalLayoutWidget);
        From->setObjectName(QString::fromUtf8("From"));
        From->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(From);

        FirstDate = new QDateEdit(verticalLayoutWidget);
        FirstDate->setObjectName(QString::fromUtf8("FirstDate"));

        horizontalLayout->addWidget(FirstDate);

        To = new QLabel(verticalLayoutWidget);
        To->setObjectName(QString::fromUtf8("To"));
        To->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(To);

        SecondDate = new QDateEdit(verticalLayoutWidget);
        SecondDate->setObjectName(QString::fromUtf8("SecondDate"));

        horizontalLayout->addWidget(SecondDate);


        DateSelector->addLayout(horizontalLayout);

        label_3 = new QLabel(Temperature);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(0, 520, 211, 16));
        label_5 = new QLabel(Temperature);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(860, 280, 341, 121));
        label_5->setFont(font5);
        tabWidget->addTab(Temperature, QString());
        Wind = new QWidget();
        Wind->setObjectName(QString::fromUtf8("Wind"));
        PlotWindSpeedDirection = new QCustomPlot(Wind);
        PlotWindSpeedDirection->setObjectName(QString::fromUtf8("PlotWindSpeedDirection"));
        PlotWindSpeedDirection->setGeometry(QRect(310, 250, 441, 281));
        LCDWind = new QLCDNumber(Wind);
        LCDWind->setObjectName(QString::fromUtf8("LCDWind"));
        LCDWind->setGeometry(QRect(480, 40, 231, 171));
        verticalLayoutWidget_3 = new QWidget(Wind);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(60, 440, 231, 78));
        DateSelector_3 = new QVBoxLayout(verticalLayoutWidget_3);
        DateSelector_3->setObjectName(QString::fromUtf8("DateSelector_3"));
        DateSelector_3->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(verticalLayoutWidget_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font3);

        DateSelector_3->addWidget(label_9);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        From_3 = new QLabel(verticalLayoutWidget_3);
        From_3->setObjectName(QString::fromUtf8("From_3"));
        From_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(From_3);

        FirstDate_3 = new QDateEdit(verticalLayoutWidget_3);
        FirstDate_3->setObjectName(QString::fromUtf8("FirstDate_3"));

        horizontalLayout_3->addWidget(FirstDate_3);

        To_3 = new QLabel(verticalLayoutWidget_3);
        To_3->setObjectName(QString::fromUtf8("To_3"));
        To_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(To_3);

        SecondDate_3 = new QDateEdit(verticalLayoutWidget_3);
        SecondDate_3->setObjectName(QString::fromUtf8("SecondDate_3"));

        horizontalLayout_3->addWidget(SecondDate_3);


        DateSelector_3->addLayout(horizontalLayout_3);

        label_16 = new QLabel(Wind);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(30, 20, 941, 211));
        label_16->setFont(font4);
        label_16->setScaledContents(false);
        label_17 = new QLabel(Wind);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(860, 350, 361, 121));
        label_17->setFont(font5);
        label_18 = new QLabel(Wind);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(0, 520, 211, 16));
        label_19 = new QLabel(Wind);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(840, 210, 361, 121));
        label_19->setFont(font5);
        label_19->setAlignment(Qt::AlignCenter);
        tabWidget->addTab(Wind, QString());
        Pressure = new QWidget();
        Pressure->setObjectName(QString::fromUtf8("Pressure"));
        PlotPressure = new QCustomPlot(Pressure);
        PlotPressure->setObjectName(QString::fromUtf8("PlotPressure"));
        PlotPressure->setGeometry(QRect(290, 240, 441, 281));
        LCDPressure = new QLCDNumber(Pressure);
        LCDPressure->setObjectName(QString::fromUtf8("LCDPressure"));
        LCDPressure->setGeometry(QRect(390, 40, 231, 171));
        verticalLayoutWidget_4 = new QWidget(Pressure);
        verticalLayoutWidget_4->setObjectName(QString::fromUtf8("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(40, 440, 231, 78));
        DateSelector_4 = new QVBoxLayout(verticalLayoutWidget_4);
        DateSelector_4->setObjectName(QString::fromUtf8("DateSelector_4"));
        DateSelector_4->setContentsMargins(0, 0, 0, 0);
        label_11 = new QLabel(verticalLayoutWidget_4);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFont(font3);

        DateSelector_4->addWidget(label_11);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        From_4 = new QLabel(verticalLayoutWidget_4);
        From_4->setObjectName(QString::fromUtf8("From_4"));
        From_4->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(From_4);

        FirstDate_4 = new QDateEdit(verticalLayoutWidget_4);
        FirstDate_4->setObjectName(QString::fromUtf8("FirstDate_4"));

        horizontalLayout_4->addWidget(FirstDate_4);

        To_4 = new QLabel(verticalLayoutWidget_4);
        To_4->setObjectName(QString::fromUtf8("To_4"));
        To_4->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(To_4);

        SecondDate_4 = new QDateEdit(verticalLayoutWidget_4);
        SecondDate_4->setObjectName(QString::fromUtf8("SecondDate_4"));

        horizontalLayout_4->addWidget(SecondDate_4);


        DateSelector_4->addLayout(horizontalLayout_4);

        label_20 = new QLabel(Pressure);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(0, 520, 211, 16));
        label_21 = new QLabel(Pressure);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(10, 20, 941, 211));
        label_21->setFont(font4);
        label_21->setScaledContents(false);
        label_22 = new QLabel(Pressure);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(820, 360, 381, 121));
        label_22->setFont(font5);
        tabWidget->addTab(Pressure, QString());
        AirQuality = new QWidget();
        AirQuality->setObjectName(QString::fromUtf8("AirQuality"));
        PlotAirQuality = new QCustomPlot(AirQuality);
        PlotAirQuality->setObjectName(QString::fromUtf8("PlotAirQuality"));
        PlotAirQuality->setGeometry(QRect(320, 240, 441, 281));
        PlotAirQuality->setStyleSheet(QString::fromUtf8(""));
        LCDAirQuality = new QLCDNumber(AirQuality);
        LCDAirQuality->setObjectName(QString::fromUtf8("LCDAirQuality"));
        LCDAirQuality->setGeometry(QRect(460, 40, 231, 171));
        verticalLayoutWidget_5 = new QWidget(AirQuality);
        verticalLayoutWidget_5->setObjectName(QString::fromUtf8("verticalLayoutWidget_5"));
        verticalLayoutWidget_5->setGeometry(QRect(70, 440, 231, 78));
        DateSelector_5 = new QVBoxLayout(verticalLayoutWidget_5);
        DateSelector_5->setObjectName(QString::fromUtf8("DateSelector_5"));
        DateSelector_5->setContentsMargins(0, 0, 0, 0);
        label_12 = new QLabel(verticalLayoutWidget_5);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font3);

        DateSelector_5->addWidget(label_12);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        From_5 = new QLabel(verticalLayoutWidget_5);
        From_5->setObjectName(QString::fromUtf8("From_5"));
        From_5->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(From_5);

        FirstDate_5 = new QDateEdit(verticalLayoutWidget_5);
        FirstDate_5->setObjectName(QString::fromUtf8("FirstDate_5"));

        horizontalLayout_5->addWidget(FirstDate_5);

        To_5 = new QLabel(verticalLayoutWidget_5);
        To_5->setObjectName(QString::fromUtf8("To_5"));
        To_5->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(To_5);

        SecondDate_5 = new QDateEdit(verticalLayoutWidget_5);
        SecondDate_5->setObjectName(QString::fromUtf8("SecondDate_5"));

        horizontalLayout_5->addWidget(SecondDate_5);


        DateSelector_5->addLayout(horizontalLayout_5);

        label_23 = new QLabel(AirQuality);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(60, 30, 391, 211));
        label_23->setFont(font4);
        label_23->setScaledContents(false);
        label_24 = new QLabel(AirQuality);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(0, 520, 211, 16));
        label_25 = new QLabel(AirQuality);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(860, 330, 381, 121));
        label_25->setFont(font5);
        label_2 = new QLabel(AirQuality);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(920, 200, 191, 161));
        label_2->setFont(font5);
        tabWidget->addTab(AirQuality, QString());
        Settings = new QWidget();
        Settings->setObjectName(QString::fromUtf8("Settings"));
        SettingsTitle = new QLineEdit(Settings);
        SettingsTitle->setObjectName(QString::fromUtf8("SettingsTitle"));
        SettingsTitle->setGeometry(QRect(510, 20, 131, 41));
        QFont font6;
        font6.setPointSize(20);
        SettingsTitle->setFont(font6);
        SettingsTitle->setReadOnly(true);
        SettingsOptions = new QFrame(Settings);
        SettingsOptions->setObjectName(QString::fromUtf8("SettingsOptions"));
        SettingsOptions->setGeometry(QRect(120, 100, 371, 211));
        formLayout = new QFormLayout(SettingsOptions);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        AirTitle = new QLabel(SettingsOptions);
        AirTitle->setObjectName(QString::fromUtf8("AirTitle"));
        QFont font7;
        font7.setPointSize(16);
        AirTitle->setFont(font7);

        formLayout->setWidget(0, QFormLayout::LabelRole, AirTitle);

        verticalFrame = new QFrame(SettingsOptions);
        verticalFrame->setObjectName(QString::fromUtf8("verticalFrame"));
        verticalLayout = new QVBoxLayout(verticalFrame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        MillibarsButton = new QRadioButton(verticalFrame);
        MillibarsButton->setObjectName(QString::fromUtf8("MillibarsButton"));
        QFont font8;
        font8.setPointSize(11);
        MillibarsButton->setFont(font8);
        MillibarsButton->setChecked(true);

        verticalLayout->addWidget(MillibarsButton);

        PascalButton = new QRadioButton(verticalFrame);
        PascalButton->setObjectName(QString::fromUtf8("PascalButton"));
        PascalButton->setFont(font8);

        verticalLayout->addWidget(PascalButton);


        formLayout->setWidget(0, QFormLayout::FieldRole, verticalFrame);

        WindTitle = new QLabel(SettingsOptions);
        WindTitle->setObjectName(QString::fromUtf8("WindTitle"));
        WindTitle->setFont(font7);

        formLayout->setWidget(1, QFormLayout::LabelRole, WindTitle);

        WindOptions = new QFrame(SettingsOptions);
        WindOptions->setObjectName(QString::fromUtf8("WindOptions"));
        verticalLayout_2 = new QVBoxLayout(WindOptions);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        MPHButton = new QRadioButton(WindOptions);
        MPHButton->setObjectName(QString::fromUtf8("MPHButton"));
        MPHButton->setFont(font8);
        MPHButton->setChecked(true);

        verticalLayout_2->addWidget(MPHButton);

        KPHButton = new QRadioButton(WindOptions);
        KPHButton->setObjectName(QString::fromUtf8("KPHButton"));
        KPHButton->setFont(font8);

        verticalLayout_2->addWidget(KPHButton);


        formLayout->setWidget(1, QFormLayout::FieldRole, WindOptions);

        TemperatureTitle = new QLabel(SettingsOptions);
        TemperatureTitle->setObjectName(QString::fromUtf8("TemperatureTitle"));
        TemperatureTitle->setFont(font7);

        formLayout->setWidget(2, QFormLayout::LabelRole, TemperatureTitle);

        TemperatureOptions = new QFrame(SettingsOptions);
        TemperatureOptions->setObjectName(QString::fromUtf8("TemperatureOptions"));
        verticalLayout_3 = new QVBoxLayout(TemperatureOptions);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        CelciusButton = new QRadioButton(TemperatureOptions);
        CelciusButton->setObjectName(QString::fromUtf8("CelciusButton"));
        CelciusButton->setFont(font8);
        CelciusButton->setChecked(true);

        verticalLayout_3->addWidget(CelciusButton);

        FarenheitButton = new QRadioButton(TemperatureOptions);
        FarenheitButton->setObjectName(QString::fromUtf8("FarenheitButton"));
        FarenheitButton->setFont(font8);
        FarenheitButton->setChecked(false);

        verticalLayout_3->addWidget(FarenheitButton);


        formLayout->setWidget(2, QFormLayout::FieldRole, TemperatureOptions);

        DeleteAll = new QPushButton(Settings);
        DeleteAll->setObjectName(QString::fromUtf8("DeleteAll"));
        DeleteAll->setGeometry(QRect(1120, 490, 121, 41));
        DownloadAll = new QPushButton(Settings);
        DownloadAll->setObjectName(QString::fromUtf8("DownloadAll"));
        DownloadAll->setGeometry(QRect(890, 180, 121, 41));
        AboutButton = new QPushButton(Settings);
        AboutButton->setObjectName(QString::fromUtf8("AboutButton"));
        AboutButton->setGeometry(QRect(10, 510, 80, 24));
        QFont font9;
        font9.setUnderline(true);
        AboutButton->setFont(font9);
        AboutButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	color:blue;\n"
"	background:transparent;\n"
"}"));
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
        HTTPButton->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        HomeTemp->setText(QCoreApplication::translate("MainWindow", "18 \302\260C", nullptr));
        HomePressure->setText(QCoreApplication::translate("MainWindow", "Pressure", nullptr));
        HomeHumidity->setText(QCoreApplication::translate("MainWindow", "Humidity", nullptr));
        HomeAQ->setText(QCoreApplication::translate("MainWindow", "Air Quality", nullptr));
        HomeWind->setText(QCoreApplication::translate("MainWindow", "Wind Speed", nullptr));
        HomeTime->setText(QCoreApplication::translate("MainWindow", "00:00 AM", nullptr));
        HomeDate->setText(QCoreApplication::translate("MainWindow", "Friday, Feburary 18th, 2022", nullptr));
        HomeHumidityVal->setText(QCoreApplication::translate("MainWindow", "34%", nullptr));
        HomeWindVal->setText(QCoreApplication::translate("MainWindow", "5 MPH\n"
"NNW", nullptr));
        HomePressureVal->setText(QCoreApplication::translate("MainWindow", "1000 mbar", nullptr));
        HomeAQVal->setText(QCoreApplication::translate("MainWindow", "18\n"
"Excellent", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Homepage), QCoreApplication::translate("MainWindow", "Homepage", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Select Graphing Date Range", nullptr));
        From_2->setText(QCoreApplication::translate("MainWindow", "From", nullptr));
        To_2->setText(QCoreApplication::translate("MainWindow", "to", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Current Humidity                     %", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "24 hour average: #%\n"
"Past 24 hour high: #%\n"
"Past 24 hour low: #%", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Last Updated: 1:00 PM 2/18/22", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Humidity), QCoreApplication::translate("MainWindow", "Humidity", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Current Temperature                     \302\272C", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Select Graphing Date Range", nullptr));
        From->setText(QCoreApplication::translate("MainWindow", "From", nullptr));
        To->setText(QCoreApplication::translate("MainWindow", "to", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Last Updated: 1:00 PM 2/18/22", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "24 hour average: #\302\272C\n"
"Past 24 hour high: #\302\272C\n"
"Past 24 hour low: #\302\272C", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Temperature), QCoreApplication::translate("MainWindow", "Temperature", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Select Graphing Date Range", nullptr));
        From_3->setText(QCoreApplication::translate("MainWindow", "From", nullptr));
        To_3->setText(QCoreApplication::translate("MainWindow", "to", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Current Wind Speed                     MPH", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "24 hour average: #MPH\n"
"Past 24 hour high: #MPH\n"
"Past 24 hour low: #MPH", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "Last Updated: 1:00 PM 2/18/22", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "Current Wind Direction:\n"
"NNW", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Wind), QCoreApplication::translate("MainWindow", "Wind Speed/Direction", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Select Graphing Date Range", nullptr));
        From_4->setText(QCoreApplication::translate("MainWindow", "From", nullptr));
        To_4->setText(QCoreApplication::translate("MainWindow", "to", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "Last Updated: 1:00 PM 2/18/22", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "Current Pressure                     mbars", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "24 hour average: #mbars\n"
"Past 24 hour high: #mbars\n"
"Past 24 hour low: #mbars", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Pressure), QCoreApplication::translate("MainWindow", "Pressure", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Select Graphing Date Range", nullptr));
        From_5->setText(QCoreApplication::translate("MainWindow", "From", nullptr));
        To_5->setText(QCoreApplication::translate("MainWindow", "to", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "Current AQI Level", nullptr));
        label_24->setText(QCoreApplication::translate("MainWindow", "Last Updated: 1:00 PM 2/18/22", nullptr));
        label_25->setText(QCoreApplication::translate("MainWindow", "24 hour average: #\n"
"Past 24 hour high: #\n"
"Past 24 hour low: #", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Excellent", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(AirQuality), QCoreApplication::translate("MainWindow", "Air Quality", nullptr));
        SettingsTitle->setText(QCoreApplication::translate("MainWindow", "SETTINGS", nullptr));
        AirTitle->setText(QCoreApplication::translate("MainWindow", "Air Pressure", nullptr));
        MillibarsButton->setText(QCoreApplication::translate("MainWindow", "Millibars", nullptr));
        PascalButton->setText(QCoreApplication::translate("MainWindow", "Pascals", nullptr));
        WindTitle->setText(QCoreApplication::translate("MainWindow", "Wind Speed", nullptr));
        MPHButton->setText(QCoreApplication::translate("MainWindow", "Miles Per Hour (MPH)", nullptr));
        KPHButton->setText(QCoreApplication::translate("MainWindow", "Kilometers Per Hour (KPH)", nullptr));
        TemperatureTitle->setText(QCoreApplication::translate("MainWindow", "Temperature", nullptr));
        CelciusButton->setText(QCoreApplication::translate("MainWindow", "Celsius", nullptr));
        FarenheitButton->setText(QCoreApplication::translate("MainWindow", "Farenheight ", nullptr));
        DeleteAll->setText(QCoreApplication::translate("MainWindow", "DELETE ALL DATA", nullptr));
        DownloadAll->setText(QCoreApplication::translate("MainWindow", "Download all data", nullptr));
        AboutButton->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Settings), QCoreApplication::translate("MainWindow", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
