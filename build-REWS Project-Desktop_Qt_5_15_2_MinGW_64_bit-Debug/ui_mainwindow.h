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
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
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
    QLabel *HomeDate;
    QLabel *HomeHumidityVal;
    QLabel *HomeWindVal;
    QLabel *HomePressureVal;
    QLabel *HomeAQVal;
    QPushButton *UpdateHomepage;
    QLabel *HomeWindDir;
    QLabel *HomeHumidity_2;
    QFrame *frame_3;
    QFrame *frame_4;
    QFrame *frame_5;
    QFrame *frame_6;
    QFrame *frame_7;
    QLabel *HomeTime;
    QWidget *Humidity;
    QFrame *HumidityFrame1;
    QCustomPlot *PlotHumidity;
    QFrame *HumidityFrame2;
    QLabel *HumidityVal;
    QLabel *HumidityStats;
    QFrame *DateFrame;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_8;
    QLabel *From_2;
    QDateEdit *FirstDate_2;
    QLabel *To_2;
    QDateEdit *SecondDate_2;
    QLabel *HumidityUpdated;
    QWidget *Temperature;
    QFrame *TemperatureFrame1;
    QCustomPlot *PlotTemperature;
    QFrame *TemperatureFrame2;
    QLabel *TemperatureVal;
    QLabel *TemperatureStats;
    QFrame *DateSelector2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_6;
    QLabel *From;
    QDateEdit *FirstDate;
    QLabel *To;
    QDateEdit *SecondDate;
    QLabel *TemperatureUpdated;
    QWidget *Wind;
    QFrame *WindFrame2;
    QLabel *WindDirection;
    QLabel *WindVal;
    QLabel *WindStats;
    QFrame *DateSelector3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_9;
    QLabel *From_3;
    QDateEdit *FirstDate_3;
    QLabel *To_3;
    QDateEdit *SecondDate_3;
    QLabel *WindUpdated;
    QFrame *frame;
    QCustomPlot *PlotWindSpeedDirection;
    QWidget *Pressure;
    QFrame *frame_2;
    QCustomPlot *PlotPressure;
    QFrame *PressureFrame2;
    QLabel *PressureVal;
    QFrame *DateSelector4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_11;
    QLabel *From_4;
    QDateEdit *FirstDate_4;
    QLabel *To_4;
    QDateEdit *SecondDate_4;
    QLabel *PressureStats;
    QLabel *PressureUpdated;
    QWidget *AirQuality;
    QFrame *AQFrame1;
    QCustomPlot *PlotAirQuality;
    QFrame *AQFrame2;
    QLabel *AQVal;
    QLabel *AQState;
    QLabel *AQStats;
    QFrame *DateSelector5;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_12;
    QLabel *From_5;
    QDateEdit *FirstDate_5;
    QLabel *To_5;
    QDateEdit *SecondDate_5;
    QLabel *AQUpdated;
    QWidget *Settings;
    QPushButton *DeleteAll;
    QPushButton *DownloadAll;
    QPushButton *AboutButton;
    QFrame *AboutFrame;
    QLabel *AboutDetails;
    QPushButton *AboutClose;
    QPlainTextEdit *DebugBox;
    QPushButton *TempDebug;
    QPushButton *HumidityDebug;
    QPushButton *WindDebug;
    QPushButton *PressureDebug;
    QPushButton *AQDebug;
    QLabel *label;
    QFrame *DeleteFrame;
    QLabel *DeleteText;
    QPushButton *DeleteConfirm;
    QPushButton *DeleteDeny;
    QFrame *frame_8;
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
    QFrame *TemperatureOptions;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *CelciusButton;
    QRadioButton *FarenheitButton;
    QLabel *TemperatureTitle;
    QLabel *label_2;
    QFrame *frame_9;
    QLabel *GPS_Val;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1279, 639);
        MainWindow->setToolTipDuration(0);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow{\n"
"	background-color:   blue;  /*  Background window color   */ \n"
"}\n"
"\n"
" /* Main window color in center */ \n"
"QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{\n"
"	/*background-color: rgb(254,255,153);*/\n"
"	background-color: rgb(225,225,225);\n"
"	color:black;\n"
"}\n"
"\n"
"\n"
" /* Color the widgets so you can see them in the preview */ \n"
"QWidget{\n"
"	color: black;\n"
"	background-color:  rgb(182, 182, 182);\n"
"}\n"
"\n"
" /* Color the outer border  */ \n"
"QWidget#ThemeWidgetForm{\n"
"	/* background-color: red; */\n"
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
"Q"
                        "TabBar{\n"
"	color: black;  /*  Tab font color   */ \n"
"	min-width:5px;\n"
"}\n"
"\n"
"QTabBar::tab{\n"
"	background: rgb(180, 180, 180); /*  Tab background color   144*/ \n"
"	border: 1px solid black;\n"
"	padding: 10px;\n"
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
        QFont font;
        font.setPointSize(16);
        font.setBold(false);
        font.setItalic(false);
        tabWidget->setFont(font);
        tabWidget->setStyleSheet(QString::fromUtf8(""));
        Homepage = new QWidget();
        Homepage->setObjectName(QString::fromUtf8("Homepage"));
        Homepage->setStyleSheet(QString::fromUtf8(""));
        HTTPButton = new QPushButton(Homepage);
        HTTPButton->setObjectName(QString::fromUtf8("HTTPButton"));
        HTTPButton->setGeometry(QRect(30, 500, 201, 21));
        HomeTemp = new QLabel(Homepage);
        HomeTemp->setObjectName(QString::fromUtf8("HomeTemp"));
        HomeTemp->setGeometry(QRect(180, 95, 531, 251));
        QFont font1;
        font1.setPointSize(28);
        HomeTemp->setFont(font1);
        HomePressure = new QLabel(Homepage);
        HomePressure->setObjectName(QString::fromUtf8("HomePressure"));
        HomePressure->setGeometry(QRect(530, 305, 301, 181));
        QFont font2;
        font2.setPointSize(48);
        HomePressure->setFont(font2);
        HomeHumidity = new QLabel(Homepage);
        HomeHumidity->setObjectName(QString::fromUtf8("HomeHumidity"));
        HomeHumidity->setGeometry(QRect(530, 35, 301, 181));
        HomeHumidity->setFont(font2);
        HomeAQ = new QLabel(Homepage);
        HomeAQ->setObjectName(QString::fromUtf8("HomeAQ"));
        HomeAQ->setGeometry(QRect(890, 305, 301, 181));
        HomeAQ->setFont(font2);
        HomeWind = new QLabel(Homepage);
        HomeWind->setObjectName(QString::fromUtf8("HomeWind"));
        HomeWind->setGeometry(QRect(870, 35, 431, 181));
        HomeWind->setFont(font2);
        HomeDate = new QLabel(Homepage);
        HomeDate->setObjectName(QString::fromUtf8("HomeDate"));
        HomeDate->setGeometry(QRect(40, 395, 511, 71));
        QFont font3;
        font3.setPointSize(24);
        HomeDate->setFont(font3);
        HomeHumidityVal = new QLabel(Homepage);
        HomeHumidityVal->setObjectName(QString::fromUtf8("HomeHumidityVal"));
        HomeHumidityVal->setGeometry(QRect(620, 115, 141, 171));
        HomeHumidityVal->setFont(font1);
        HomeWindVal = new QLabel(Homepage);
        HomeWindVal->setObjectName(QString::fromUtf8("HomeWindVal"));
        HomeWindVal->setGeometry(QRect(980, 105, 231, 171));
        HomeWindVal->setFont(font1);
        HomePressureVal = new QLabel(Homepage);
        HomePressureVal->setObjectName(QString::fromUtf8("HomePressureVal"));
        HomePressureVal->setGeometry(QRect(550, 435, 261, 81));
        HomePressureVal->setFont(font1);
        HomeAQVal = new QLabel(Homepage);
        HomeAQVal->setObjectName(QString::fromUtf8("HomeAQVal"));
        HomeAQVal->setGeometry(QRect(910, 425, 251, 111));
        HomeAQVal->setFont(font1);
        HomeAQVal->setAlignment(Qt::AlignCenter);
        UpdateHomepage = new QPushButton(Homepage);
        UpdateHomepage->setObjectName(QString::fromUtf8("UpdateHomepage"));
        UpdateHomepage->setGeometry(QRect(290, 500, 221, 24));
        HomeWindDir = new QLabel(Homepage);
        HomeWindDir->setObjectName(QString::fromUtf8("HomeWindDir"));
        HomeWindDir->setGeometry(QRect(870, 195, 351, 81));
        HomeWindDir->setFont(font1);
        HomeHumidity_2 = new QLabel(Homepage);
        HomeHumidity_2->setObjectName(QString::fromUtf8("HomeHumidity_2"));
        HomeHumidity_2->setGeometry(QRect(40, 35, 421, 181));
        HomeHumidity_2->setFont(font2);
        frame_3 = new QFrame(Homepage);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setGeometry(QRect(20, 45, 431, 491));
        frame_3->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border: 2px solid black;\n"
"border-radius:20px;\n"
"background: rgb(215, 215, 215); /*185 */\n"
"}"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        frame_4 = new QFrame(Homepage);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setGeometry(QRect(500, 45, 321, 221));
        frame_4->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border: 2px solid black;\n"
"border-radius:20px;\n"
"background: rgb(215, 215, 215); /*185 */\n"
"}"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        frame_5 = new QFrame(Homepage);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setGeometry(QRect(860, 45, 371, 221));
        frame_5->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border: 2px solid black;\n"
"border-radius:20px;\n"
"background: rgb(215, 215, 215); /*185 */\n"
"}"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        frame_6 = new QFrame(Homepage);
        frame_6->setObjectName(QString::fromUtf8("frame_6"));
        frame_6->setGeometry(QRect(500, 335, 321, 201));
        frame_6->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border: 2px solid black;\n"
"border-radius:20px;\n"
"background: rgb(215, 215, 215); /*185 */\n"
"}"));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        frame_7 = new QFrame(Homepage);
        frame_7->setObjectName(QString::fromUtf8("frame_7"));
        frame_7->setGeometry(QRect(860, 335, 371, 201));
        frame_7->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border: 2px solid black;\n"
"border-radius:20px;\n"
"background: rgb(215, 215, 215); /*185 */\n"
"}"));
        frame_7->setFrameShape(QFrame::StyledPanel);
        frame_7->setFrameShadow(QFrame::Raised);
        HomeTime = new QLabel(Homepage);
        HomeTime->setObjectName(QString::fromUtf8("HomeTime"));
        HomeTime->setGeometry(QRect(60, 295, 501, 111));
        QFont font4;
        font4.setPointSize(64);
        HomeTime->setFont(font4);
        tabWidget->addTab(Homepage, QString());
        frame_7->raise();
        frame_6->raise();
        frame_5->raise();
        frame_4->raise();
        frame_3->raise();
        HTTPButton->raise();
        HomeTemp->raise();
        HomePressure->raise();
        HomeHumidity->raise();
        HomeAQ->raise();
        HomeWind->raise();
        HomeDate->raise();
        HomeHumidityVal->raise();
        HomeWindVal->raise();
        HomePressureVal->raise();
        HomeAQVal->raise();
        UpdateHomepage->raise();
        HomeWindDir->raise();
        HomeHumidity_2->raise();
        HomeTime->raise();
        Humidity = new QWidget();
        Humidity->setObjectName(QString::fromUtf8("Humidity"));
        HumidityFrame1 = new QFrame(Humidity);
        HumidityFrame1->setObjectName(QString::fromUtf8("HumidityFrame1"));
        HumidityFrame1->setGeometry(QRect(20, 50, 631, 481));
        HumidityFrame1->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border: 2px solid black;\n"
"background: rgb(215, 215, 215); /*185 */\n"
"border-radius:20px;\n"
"}"));
        HumidityFrame1->setFrameShape(QFrame::StyledPanel);
        HumidityFrame1->setFrameShadow(QFrame::Raised);
        PlotHumidity = new QCustomPlot(HumidityFrame1);
        PlotHumidity->setObjectName(QString::fromUtf8("PlotHumidity"));
        PlotHumidity->setGeometry(QRect(20, 20, 591, 441));
        PlotHumidity->setStyleSheet(QString::fromUtf8("QCustomPlot{\n"
"border-radius:20px;\n"
"}"));
        HumidityFrame2 = new QFrame(Humidity);
        HumidityFrame2->setObjectName(QString::fromUtf8("HumidityFrame2"));
        HumidityFrame2->setGeometry(QRect(690, 50, 551, 481));
        HumidityFrame2->setStyleSheet(QString::fromUtf8("QFrame#HumidityFrame2{\n"
"border: 2px solid black;\n"
"background: rgb(215, 215, 215); /*185 */\n"
"border-radius: 20px;\n"
"}\n"
"\n"
"QFrame{\n"
"	border-radius: 20px;\n"
"}"));
        HumidityFrame2->setFrameShape(QFrame::StyledPanel);
        HumidityFrame2->setFrameShadow(QFrame::Raised);
        HumidityVal = new QLabel(HumidityFrame2);
        HumidityVal->setObjectName(QString::fromUtf8("HumidityVal"));
        HumidityVal->setGeometry(QRect(40, -10, 941, 211));
        QFont font5;
        font5.setPointSize(36);
        HumidityVal->setFont(font5);
        HumidityVal->setScaledContents(false);
        HumidityStats = new QLabel(HumidityFrame2);
        HumidityStats->setObjectName(QString::fromUtf8("HumidityStats"));
        HumidityStats->setGeometry(QRect(40, 190, 471, 121));
        HumidityStats->setFont(font3);
        DateFrame = new QFrame(HumidityFrame2);
        DateFrame->setObjectName(QString::fromUtf8("DateFrame"));
        DateFrame->setGeometry(QRect(30, 380, 491, 81));
        DateFrame->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border: 1px solid black;\n"
"background: rgb(210, 210, 210);\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(DateFrame);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_8 = new QLabel(DateFrame);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QFont font6;
        font6.setPointSize(10);
        label_8->setFont(font6);
        label_8->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border: 0px solid black;\n"
"background: rgb(210, 210, 210);\n"
"}"));

        horizontalLayout_2->addWidget(label_8);

        From_2 = new QLabel(DateFrame);
        From_2->setObjectName(QString::fromUtf8("From_2"));
        From_2->setFont(font6);
        From_2->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border: 0px solid black;\n"
"background: rgb(210, 210, 210);\n"
"}"));
        From_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(From_2);

        FirstDate_2 = new QDateEdit(DateFrame);
        FirstDate_2->setObjectName(QString::fromUtf8("FirstDate_2"));
        FirstDate_2->setSizeIncrement(QSize(2, 2));
        QFont font7;
        font7.setPointSize(12);
        FirstDate_2->setFont(font7);
        FirstDate_2->setStyleSheet(QString::fromUtf8("QDateEdit{\n"
"	background:white;\n"
"}"));
        FirstDate_2->setDateTime(QDateTime(QDate(2022, 1, 1), QTime(0, 0, 0)));
        FirstDate_2->setCalendarPopup(true);

        horizontalLayout_2->addWidget(FirstDate_2);

        To_2 = new QLabel(DateFrame);
        To_2->setObjectName(QString::fromUtf8("To_2"));
        To_2->setFont(font6);
        To_2->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border: 0px solid black;\n"
"background: rgb(210, 210, 210);\n"
"}"));
        To_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(To_2);

        SecondDate_2 = new QDateEdit(DateFrame);
        SecondDate_2->setObjectName(QString::fromUtf8("SecondDate_2"));
        SecondDate_2->setFont(font7);
        SecondDate_2->setStyleSheet(QString::fromUtf8("QDateEdit{\n"
"	background:white;\n"
"}"));
        SecondDate_2->setDateTime(QDateTime(QDate(2022, 1, 1), QTime(0, 0, 0)));
        SecondDate_2->setCalendarPopup(true);

        horizontalLayout_2->addWidget(SecondDate_2);

        HumidityUpdated = new QLabel(HumidityFrame2);
        HumidityUpdated->setObjectName(QString::fromUtf8("HumidityUpdated"));
        HumidityUpdated->setGeometry(QRect(50, 360, 461, 16));
        tabWidget->addTab(Humidity, QString());
        Temperature = new QWidget();
        Temperature->setObjectName(QString::fromUtf8("Temperature"));
        TemperatureFrame1 = new QFrame(Temperature);
        TemperatureFrame1->setObjectName(QString::fromUtf8("TemperatureFrame1"));
        TemperatureFrame1->setGeometry(QRect(20, 50, 631, 481));
        TemperatureFrame1->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border: 2px solid black;\n"
"background: rgb(215, 215, 215); /*185 */\n"
"border-radius:20px;\n"
"}"));
        TemperatureFrame1->setFrameShape(QFrame::StyledPanel);
        TemperatureFrame1->setFrameShadow(QFrame::Raised);
        PlotTemperature = new QCustomPlot(TemperatureFrame1);
        PlotTemperature->setObjectName(QString::fromUtf8("PlotTemperature"));
        PlotTemperature->setGeometry(QRect(20, 20, 591, 441));
        TemperatureFrame2 = new QFrame(Temperature);
        TemperatureFrame2->setObjectName(QString::fromUtf8("TemperatureFrame2"));
        TemperatureFrame2->setGeometry(QRect(690, 50, 551, 481));
        TemperatureFrame2->setStyleSheet(QString::fromUtf8("QFrame#TemperatureFrame2{\n"
"border: 2px solid black;\n"
"background: rgb(215, 215, 215); /*185 */\n"
"border-radius: 20px;\n"
"}\n"
"\n"
"QFrame{\n"
"	border-radius: 20px;\n"
"}"));
        TemperatureFrame2->setFrameShape(QFrame::StyledPanel);
        TemperatureFrame2->setFrameShadow(QFrame::Raised);
        TemperatureVal = new QLabel(TemperatureFrame2);
        TemperatureVal->setObjectName(QString::fromUtf8("TemperatureVal"));
        TemperatureVal->setGeometry(QRect(40, -10, 941, 211));
        TemperatureVal->setFont(font5);
        TemperatureVal->setScaledContents(false);
        TemperatureStats = new QLabel(TemperatureFrame2);
        TemperatureStats->setObjectName(QString::fromUtf8("TemperatureStats"));
        TemperatureStats->setGeometry(QRect(40, 190, 491, 121));
        TemperatureStats->setFont(font3);
        DateSelector2 = new QFrame(TemperatureFrame2);
        DateSelector2->setObjectName(QString::fromUtf8("DateSelector2"));
        DateSelector2->setGeometry(QRect(30, 380, 491, 81));
        DateSelector2->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border: 1px solid black;\n"
"background: rgb(210, 210, 210);\n"
"}"));
        horizontalLayout = new QHBoxLayout(DateSelector2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_6 = new QLabel(DateSelector2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font7);
        label_6->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border: 0px solid black;\n"
"background: rgb(210, 210, 210);\n"
"}"));

        horizontalLayout->addWidget(label_6);

        From = new QLabel(DateSelector2);
        From->setObjectName(QString::fromUtf8("From"));
        From->setFont(font7);
        From->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border: 0px solid black;\n"
"background: rgb(210, 210, 210);\n"
"}"));
        From->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(From);

        FirstDate = new QDateEdit(DateSelector2);
        FirstDate->setObjectName(QString::fromUtf8("FirstDate"));
        FirstDate->setFont(font7);
        FirstDate->setStyleSheet(QString::fromUtf8("QDateEdit{\n"
"	background:white;\n"
"}"));
        FirstDate->setDateTime(QDateTime(QDate(2022, 1, 1), QTime(0, 0, 0)));
        FirstDate->setCalendarPopup(true);

        horizontalLayout->addWidget(FirstDate);

        To = new QLabel(DateSelector2);
        To->setObjectName(QString::fromUtf8("To"));
        To->setFont(font7);
        To->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border: 0px solid black;\n"
"background: rgb(210, 210, 210);\n"
"}"));
        To->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(To);

        SecondDate = new QDateEdit(DateSelector2);
        SecondDate->setObjectName(QString::fromUtf8("SecondDate"));
        SecondDate->setFont(font7);
        SecondDate->setStyleSheet(QString::fromUtf8("QDateEdit{\n"
"	background:white;\n"
"}"));
        SecondDate->setDateTime(QDateTime(QDate(2022, 1, 1), QTime(0, 0, 0)));
        SecondDate->setCalendarPopup(true);

        horizontalLayout->addWidget(SecondDate);

        TemperatureUpdated = new QLabel(TemperatureFrame2);
        TemperatureUpdated->setObjectName(QString::fromUtf8("TemperatureUpdated"));
        TemperatureUpdated->setGeometry(QRect(50, 360, 461, 16));
        tabWidget->addTab(Temperature, QString());
        Wind = new QWidget();
        Wind->setObjectName(QString::fromUtf8("Wind"));
        WindFrame2 = new QFrame(Wind);
        WindFrame2->setObjectName(QString::fromUtf8("WindFrame2"));
        WindFrame2->setGeometry(QRect(690, 50, 551, 481));
        WindFrame2->setStyleSheet(QString::fromUtf8("QFrame#WindFrame2{\n"
"border: 2px solid black;\n"
"background: rgb(215, 215, 215); /*185 */\n"
"border-radius: 20px;\n"
"}\n"
"\n"
"QFrame{\n"
"	border-radius: 20px;\n"
"}"));
        WindFrame2->setFrameShape(QFrame::StyledPanel);
        WindFrame2->setFrameShadow(QFrame::Raised);
        WindDirection = new QLabel(WindFrame2);
        WindDirection->setObjectName(QString::fromUtf8("WindDirection"));
        WindDirection->setGeometry(QRect(-10, 200, 501, 221));
        WindDirection->setFont(font3);
        WindDirection->setStyleSheet(QString::fromUtf8("QLabel{\n"
"background:transparent;\n"
"}"));
        WindDirection->setAlignment(Qt::AlignCenter);
        WindVal = new QLabel(WindFrame2);
        WindVal->setObjectName(QString::fromUtf8("WindVal"));
        WindVal->setGeometry(QRect(40, -20, 941, 211));
        WindVal->setFont(font5);
        WindVal->setScaledContents(false);
        WindStats = new QLabel(WindFrame2);
        WindStats->setObjectName(QString::fromUtf8("WindStats"));
        WindStats->setGeometry(QRect(40, 160, 501, 121));
        WindStats->setFont(font3);
        WindStats->setStyleSheet(QString::fromUtf8("QLabel{\n"
"background:transparent;\n"
"}"));
        DateSelector3 = new QFrame(WindFrame2);
        DateSelector3->setObjectName(QString::fromUtf8("DateSelector3"));
        DateSelector3->setGeometry(QRect(30, 380, 491, 81));
        DateSelector3->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border: 1px solid black;\n"
"background: rgb(210, 210, 210);\n"
"}"));
        horizontalLayout_3 = new QHBoxLayout(DateSelector3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_9 = new QLabel(DateSelector3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font7);
        label_9->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border: 0px solid black;\n"
"background: rgb(210, 210, 210);\n"
"}"));

        horizontalLayout_3->addWidget(label_9);

        From_3 = new QLabel(DateSelector3);
        From_3->setObjectName(QString::fromUtf8("From_3"));
        From_3->setFont(font7);
        From_3->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border: 0px solid black;\n"
"background: rgb(210, 210, 210);\n"
"}"));
        From_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(From_3);

        FirstDate_3 = new QDateEdit(DateSelector3);
        FirstDate_3->setObjectName(QString::fromUtf8("FirstDate_3"));
        FirstDate_3->setFont(font7);
        FirstDate_3->setStyleSheet(QString::fromUtf8("QDateEdit{\n"
"	background:white;\n"
"}"));
        FirstDate_3->setDateTime(QDateTime(QDate(2022, 1, 1), QTime(0, 0, 0)));
        FirstDate_3->setCalendarPopup(true);

        horizontalLayout_3->addWidget(FirstDate_3);

        To_3 = new QLabel(DateSelector3);
        To_3->setObjectName(QString::fromUtf8("To_3"));
        To_3->setFont(font7);
        To_3->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border: 0px solid black;\n"
"background: rgb(210, 210, 210);\n"
"}"));
        To_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(To_3);

        SecondDate_3 = new QDateEdit(DateSelector3);
        SecondDate_3->setObjectName(QString::fromUtf8("SecondDate_3"));
        SecondDate_3->setFont(font7);
        SecondDate_3->setStyleSheet(QString::fromUtf8("QDateEdit{\n"
"	background:white;\n"
"}"));
        SecondDate_3->setDateTime(QDateTime(QDate(2022, 1, 1), QTime(0, 0, 0)));
        SecondDate_3->setCalendarPopup(true);

        horizontalLayout_3->addWidget(SecondDate_3);

        WindUpdated = new QLabel(WindFrame2);
        WindUpdated->setObjectName(QString::fromUtf8("WindUpdated"));
        WindUpdated->setGeometry(QRect(50, 360, 371, 16));
        frame = new QFrame(Wind);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(20, 50, 631, 481));
        frame->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border:2px solid black;\n"
"background: rgb(215, 215, 215); /*185 */\n"
"border-radius: 20px;\n"
"}"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        PlotWindSpeedDirection = new QCustomPlot(frame);
        PlotWindSpeedDirection->setObjectName(QString::fromUtf8("PlotWindSpeedDirection"));
        PlotWindSpeedDirection->setGeometry(QRect(20, 20, 591, 441));
        tabWidget->addTab(Wind, QString());
        Pressure = new QWidget();
        Pressure->setObjectName(QString::fromUtf8("Pressure"));
        frame_2 = new QFrame(Pressure);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(20, 50, 631, 481));
        frame_2->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border:2px solid black;\n"
"background: rgb(215, 215, 215); /*185 */\n"
"border-radius: 20px;\n"
"}"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        PlotPressure = new QCustomPlot(frame_2);
        PlotPressure->setObjectName(QString::fromUtf8("PlotPressure"));
        PlotPressure->setGeometry(QRect(20, 20, 591, 441));
        PressureFrame2 = new QFrame(Pressure);
        PressureFrame2->setObjectName(QString::fromUtf8("PressureFrame2"));
        PressureFrame2->setGeometry(QRect(690, 50, 551, 481));
        PressureFrame2->setStyleSheet(QString::fromUtf8("QFrame#PressureFrame2{\n"
"border: 2px solid black;\n"
"background: rgb(215, 215, 215); /*185 */\n"
"border-radius: 20px;\n"
"}\n"
"\n"
"QFrame{\n"
"	border-radius: 20px;\n"
"}"));
        PressureFrame2->setFrameShape(QFrame::StyledPanel);
        PressureFrame2->setFrameShadow(QFrame::Raised);
        PressureVal = new QLabel(PressureFrame2);
        PressureVal->setObjectName(QString::fromUtf8("PressureVal"));
        PressureVal->setGeometry(QRect(40, -10, 941, 211));
        PressureVal->setFont(font5);
        PressureVal->setScaledContents(false);
        DateSelector4 = new QFrame(PressureFrame2);
        DateSelector4->setObjectName(QString::fromUtf8("DateSelector4"));
        DateSelector4->setGeometry(QRect(30, 380, 491, 81));
        DateSelector4->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border: 1px solid black;\n"
"background: rgb(210, 210, 210);\n"
"}"));
        horizontalLayout_4 = new QHBoxLayout(DateSelector4);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_11 = new QLabel(DateSelector4);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFont(font7);
        label_11->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border: 0px solid black;\n"
"background: rgb(210, 210, 210);\n"
"}"));

        horizontalLayout_4->addWidget(label_11);

        From_4 = new QLabel(DateSelector4);
        From_4->setObjectName(QString::fromUtf8("From_4"));
        From_4->setFont(font7);
        From_4->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border: 0px solid black;\n"
"background: rgb(210, 210, 210);\n"
"}"));
        From_4->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(From_4);

        FirstDate_4 = new QDateEdit(DateSelector4);
        FirstDate_4->setObjectName(QString::fromUtf8("FirstDate_4"));
        FirstDate_4->setFont(font7);
        FirstDate_4->setStyleSheet(QString::fromUtf8("QDateEdit{\n"
"	background:white;\n"
"}"));
        FirstDate_4->setDateTime(QDateTime(QDate(2022, 1, 1), QTime(0, 0, 0)));
        FirstDate_4->setCalendarPopup(true);

        horizontalLayout_4->addWidget(FirstDate_4);

        To_4 = new QLabel(DateSelector4);
        To_4->setObjectName(QString::fromUtf8("To_4"));
        To_4->setFont(font7);
        To_4->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border: 0px solid black;\n"
"background: rgb(210, 210, 210);\n"
"}"));
        To_4->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(To_4);

        SecondDate_4 = new QDateEdit(DateSelector4);
        SecondDate_4->setObjectName(QString::fromUtf8("SecondDate_4"));
        SecondDate_4->setFont(font7);
        SecondDate_4->setStyleSheet(QString::fromUtf8("QDateEdit{\n"
"	background:white;\n"
"}"));
        SecondDate_4->setDateTime(QDateTime(QDate(2022, 1, 1), QTime(0, 0, 0)));
        SecondDate_4->setCalendarPopup(true);

        horizontalLayout_4->addWidget(SecondDate_4);

        PressureStats = new QLabel(PressureFrame2);
        PressureStats->setObjectName(QString::fromUtf8("PressureStats"));
        PressureStats->setGeometry(QRect(40, 190, 501, 121));
        PressureStats->setFont(font3);
        PressureUpdated = new QLabel(PressureFrame2);
        PressureUpdated->setObjectName(QString::fromUtf8("PressureUpdated"));
        PressureUpdated->setGeometry(QRect(50, 360, 451, 16));
        tabWidget->addTab(Pressure, QString());
        AirQuality = new QWidget();
        AirQuality->setObjectName(QString::fromUtf8("AirQuality"));
        AQFrame1 = new QFrame(AirQuality);
        AQFrame1->setObjectName(QString::fromUtf8("AQFrame1"));
        AQFrame1->setGeometry(QRect(20, 50, 631, 481));
        AQFrame1->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border:2px solid black;\n"
"background: rgb(215, 215, 215); /*185 */\n"
"border-radius: 20px;\n"
"}"));
        AQFrame1->setFrameShape(QFrame::StyledPanel);
        AQFrame1->setFrameShadow(QFrame::Raised);
        PlotAirQuality = new QCustomPlot(AQFrame1);
        PlotAirQuality->setObjectName(QString::fromUtf8("PlotAirQuality"));
        PlotAirQuality->setGeometry(QRect(20, 20, 591, 441));
        PlotAirQuality->setStyleSheet(QString::fromUtf8(""));
        AQFrame2 = new QFrame(AirQuality);
        AQFrame2->setObjectName(QString::fromUtf8("AQFrame2"));
        AQFrame2->setGeometry(QRect(690, 50, 551, 481));
        AQFrame2->setStyleSheet(QString::fromUtf8("QFrame#AQFrame2{\n"
"border: 2px solid black;\n"
"background: rgb(215, 215, 215); /*185 */\n"
"border-radius: 20px;\n"
"}\n"
"\n"
"QFrame{\n"
"	border-radius: 20px;\n"
"}"));
        AQFrame2->setFrameShape(QFrame::StyledPanel);
        AQFrame2->setFrameShadow(QFrame::Raised);
        AQVal = new QLabel(AQFrame2);
        AQVal->setObjectName(QString::fromUtf8("AQVal"));
        AQVal->setGeometry(QRect(40, -20, 391, 211));
        AQVal->setFont(font5);
        AQVal->setScaledContents(false);
        AQState = new QLabel(AQFrame2);
        AQState->setObjectName(QString::fromUtf8("AQState"));
        AQState->setGeometry(QRect(320, -50, 391, 211));
        AQState->setFont(font5);
        AQState->setStyleSheet(QString::fromUtf8("QLabel{\n"
"background:transparent;\n"
"}"));
        AQStats = new QLabel(AQFrame2);
        AQStats->setObjectName(QString::fromUtf8("AQStats"));
        AQStats->setGeometry(QRect(40, 190, 491, 121));
        AQStats->setFont(font3);
        AQStats->setStyleSheet(QString::fromUtf8("QLabel{\n"
"background:transparent;\n"
"}"));
        DateSelector5 = new QFrame(AQFrame2);
        DateSelector5->setObjectName(QString::fromUtf8("DateSelector5"));
        DateSelector5->setGeometry(QRect(30, 380, 491, 81));
        DateSelector5->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border: 1px solid black;\n"
"background: rgb(210, 210, 210);\n"
"}"));
        horizontalLayout_5 = new QHBoxLayout(DateSelector5);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_12 = new QLabel(DateSelector5);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font7);
        label_12->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border: 0px solid black;\n"
"background: rgb(210, 210, 210);\n"
"}"));

        horizontalLayout_5->addWidget(label_12);

        From_5 = new QLabel(DateSelector5);
        From_5->setObjectName(QString::fromUtf8("From_5"));
        From_5->setFont(font7);
        From_5->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border: 0px solid black;\n"
"background: rgb(210, 210, 210);\n"
"}"));
        From_5->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(From_5);

        FirstDate_5 = new QDateEdit(DateSelector5);
        FirstDate_5->setObjectName(QString::fromUtf8("FirstDate_5"));
        FirstDate_5->setSizeIncrement(QSize(10, 10));
        FirstDate_5->setBaseSize(QSize(10, 10));
        FirstDate_5->setFont(font7);
        FirstDate_5->setStyleSheet(QString::fromUtf8("QDateEdit{\n"
"	background:white;\n"
"}"));
        FirstDate_5->setDateTime(QDateTime(QDate(2022, 1, 1), QTime(0, 0, 0)));
        FirstDate_5->setCalendarPopup(true);

        horizontalLayout_5->addWidget(FirstDate_5);

        To_5 = new QLabel(DateSelector5);
        To_5->setObjectName(QString::fromUtf8("To_5"));
        To_5->setFont(font7);
        To_5->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border: 0px solid black;\n"
"background: rgb(210, 210, 210);\n"
"}"));
        To_5->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(To_5);

        SecondDate_5 = new QDateEdit(DateSelector5);
        SecondDate_5->setObjectName(QString::fromUtf8("SecondDate_5"));
        SecondDate_5->setFont(font7);
        SecondDate_5->setStyleSheet(QString::fromUtf8("QDateEdit{\n"
"	background:white;\n"
"}"));
        SecondDate_5->setDateTime(QDateTime(QDate(2022, 1, 1), QTime(0, 0, 0)));
        SecondDate_5->setCalendarPopup(true);

        horizontalLayout_5->addWidget(SecondDate_5);

        AQUpdated = new QLabel(AQFrame2);
        AQUpdated->setObjectName(QString::fromUtf8("AQUpdated"));
        AQUpdated->setGeometry(QRect(50, 360, 451, 16));
        tabWidget->addTab(AirQuality, QString());
        Settings = new QWidget();
        Settings->setObjectName(QString::fromUtf8("Settings"));
        DeleteAll = new QPushButton(Settings);
        DeleteAll->setObjectName(QString::fromUtf8("DeleteAll"));
        DeleteAll->setGeometry(QRect(1120, 510, 121, 41));
        DownloadAll = new QPushButton(Settings);
        DownloadAll->setObjectName(QString::fromUtf8("DownloadAll"));
        DownloadAll->setGeometry(QRect(980, 510, 121, 41));
        AboutButton = new QPushButton(Settings);
        AboutButton->setObjectName(QString::fromUtf8("AboutButton"));
        AboutButton->setGeometry(QRect(0, 530, 80, 24));
        QFont font8;
        font8.setUnderline(true);
        AboutButton->setFont(font8);
        AboutButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	color:blue;\n"
"	background:transparent;\n"
"}"));
        AboutFrame = new QFrame(Settings);
        AboutFrame->setObjectName(QString::fromUtf8("AboutFrame"));
        AboutFrame->setGeometry(QRect(560, 80, 601, 371));
        AboutFrame->setAutoFillBackground(false);
        AboutFrame->setStyleSheet(QString::fromUtf8("QFrame{\n"
"	background: rgb(236,235,242);\n"
"	border: 1px solid black;\n"
"}"));
        AboutFrame->setFrameShape(QFrame::StyledPanel);
        AboutFrame->setFrameShadow(QFrame::Raised);
        AboutDetails = new QLabel(AboutFrame);
        AboutDetails->setObjectName(QString::fromUtf8("AboutDetails"));
        AboutDetails->setGeometry(QRect(30, 20, 511, 271));
        AboutDetails->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	border: 0px;\n"
"}"));
        AboutDetails->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        AboutClose = new QPushButton(AboutFrame);
        AboutClose->setObjectName(QString::fromUtf8("AboutClose"));
        AboutClose->setGeometry(QRect(270, 330, 80, 24));
        DebugBox = new QPlainTextEdit(AboutFrame);
        DebugBox->setObjectName(QString::fromUtf8("DebugBox"));
        DebugBox->setGeometry(QRect(260, 190, 101, 70));
        TempDebug = new QPushButton(AboutFrame);
        TempDebug->setObjectName(QString::fromUtf8("TempDebug"));
        TempDebug->setGeometry(QRect(50, 280, 80, 24));
        HumidityDebug = new QPushButton(AboutFrame);
        HumidityDebug->setObjectName(QString::fromUtf8("HumidityDebug"));
        HumidityDebug->setGeometry(QRect(160, 280, 80, 24));
        WindDebug = new QPushButton(AboutFrame);
        WindDebug->setObjectName(QString::fromUtf8("WindDebug"));
        WindDebug->setGeometry(QRect(270, 280, 80, 24));
        PressureDebug = new QPushButton(AboutFrame);
        PressureDebug->setObjectName(QString::fromUtf8("PressureDebug"));
        PressureDebug->setGeometry(QRect(380, 280, 80, 24));
        AQDebug = new QPushButton(AboutFrame);
        AQDebug->setObjectName(QString::fromUtf8("AQDebug"));
        AQDebug->setGeometry(QRect(490, 280, 80, 24));
        label = new QLabel(AboutFrame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(260, 170, 101, 20));
        DeleteFrame = new QFrame(Settings);
        DeleteFrame->setObjectName(QString::fromUtf8("DeleteFrame"));
        DeleteFrame->setGeometry(QRect(560, 80, 601, 371));
        DeleteFrame->setAutoFillBackground(false);
        DeleteFrame->setStyleSheet(QString::fromUtf8("QFrame{\n"
"	background: rgb(236,235,242);\n"
"	border: 1px solid black;\n"
"}"));
        DeleteFrame->setFrameShape(QFrame::StyledPanel);
        DeleteFrame->setFrameShadow(QFrame::Raised);
        DeleteText = new QLabel(DeleteFrame);
        DeleteText->setObjectName(QString::fromUtf8("DeleteText"));
        DeleteText->setGeometry(QRect(30, 20, 511, 271));
        QFont font9;
        font9.setPointSize(20);
        DeleteText->setFont(font9);
        DeleteText->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	border: 0px;\n"
"}"));
        DeleteText->setAlignment(Qt::AlignCenter);
        DeleteConfirm = new QPushButton(DeleteFrame);
        DeleteConfirm->setObjectName(QString::fromUtf8("DeleteConfirm"));
        DeleteConfirm->setGeometry(QRect(360, 310, 221, 51));
        DeleteDeny = new QPushButton(DeleteFrame);
        DeleteDeny->setObjectName(QString::fromUtf8("DeleteDeny"));
        DeleteDeny->setGeometry(QRect(20, 310, 221, 51));
        frame_8 = new QFrame(Settings);
        frame_8->setObjectName(QString::fromUtf8("frame_8"));
        frame_8->setGeometry(QRect(110, 90, 371, 371));
        frame_8->setStyleSheet(QString::fromUtf8("QFrame#frame_8{\n"
"border: 2px solid black;\n"
"border-radius:20px;\n"
"background: rgb(215, 215, 215); /*185 */\n"
"}"));
        frame_8->setFrameShape(QFrame::StyledPanel);
        frame_8->setFrameShadow(QFrame::Raised);
        SettingsOptions = new QFrame(frame_8);
        SettingsOptions->setObjectName(QString::fromUtf8("SettingsOptions"));
        SettingsOptions->setGeometry(QRect(0, 120, 371, 241));
        formLayout = new QFormLayout(SettingsOptions);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        AirTitle = new QLabel(SettingsOptions);
        AirTitle->setObjectName(QString::fromUtf8("AirTitle"));
        QFont font10;
        font10.setPointSize(16);
        AirTitle->setFont(font10);

        formLayout->setWidget(0, QFormLayout::LabelRole, AirTitle);

        verticalFrame = new QFrame(SettingsOptions);
        verticalFrame->setObjectName(QString::fromUtf8("verticalFrame"));
        verticalLayout = new QVBoxLayout(verticalFrame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        MillibarsButton = new QRadioButton(verticalFrame);
        MillibarsButton->setObjectName(QString::fromUtf8("MillibarsButton"));
        QFont font11;
        font11.setPointSize(11);
        MillibarsButton->setFont(font11);
        MillibarsButton->setChecked(true);

        verticalLayout->addWidget(MillibarsButton);

        PascalButton = new QRadioButton(verticalFrame);
        PascalButton->setObjectName(QString::fromUtf8("PascalButton"));
        PascalButton->setFont(font11);

        verticalLayout->addWidget(PascalButton);


        formLayout->setWidget(0, QFormLayout::FieldRole, verticalFrame);

        WindTitle = new QLabel(SettingsOptions);
        WindTitle->setObjectName(QString::fromUtf8("WindTitle"));
        WindTitle->setFont(font10);

        formLayout->setWidget(1, QFormLayout::LabelRole, WindTitle);

        WindOptions = new QFrame(SettingsOptions);
        WindOptions->setObjectName(QString::fromUtf8("WindOptions"));
        verticalLayout_2 = new QVBoxLayout(WindOptions);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        MPHButton = new QRadioButton(WindOptions);
        MPHButton->setObjectName(QString::fromUtf8("MPHButton"));
        MPHButton->setFont(font11);
        MPHButton->setChecked(true);

        verticalLayout_2->addWidget(MPHButton);

        KPHButton = new QRadioButton(WindOptions);
        KPHButton->setObjectName(QString::fromUtf8("KPHButton"));
        KPHButton->setFont(font11);

        verticalLayout_2->addWidget(KPHButton);


        formLayout->setWidget(1, QFormLayout::FieldRole, WindOptions);

        TemperatureOptions = new QFrame(SettingsOptions);
        TemperatureOptions->setObjectName(QString::fromUtf8("TemperatureOptions"));
        verticalLayout_3 = new QVBoxLayout(TemperatureOptions);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        CelciusButton = new QRadioButton(TemperatureOptions);
        CelciusButton->setObjectName(QString::fromUtf8("CelciusButton"));
        CelciusButton->setFont(font11);
        CelciusButton->setChecked(true);

        verticalLayout_3->addWidget(CelciusButton);

        FarenheitButton = new QRadioButton(TemperatureOptions);
        FarenheitButton->setObjectName(QString::fromUtf8("FarenheitButton"));
        FarenheitButton->setFont(font11);
        FarenheitButton->setChecked(false);

        verticalLayout_3->addWidget(FarenheitButton);


        formLayout->setWidget(2, QFormLayout::FieldRole, TemperatureOptions);

        TemperatureTitle = new QLabel(SettingsOptions);
        TemperatureTitle->setObjectName(QString::fromUtf8("TemperatureTitle"));
        TemperatureTitle->setFont(font10);

        formLayout->setWidget(2, QFormLayout::LabelRole, TemperatureTitle);

        label_2 = new QLabel(frame_8);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(90, -30, 181, 181));
        label_2->setFont(font5);
        frame_9 = new QFrame(Settings);
        frame_9->setObjectName(QString::fromUtf8("frame_9"));
        frame_9->setGeometry(QRect(620, 90, 481, 271));
        frame_9->setStyleSheet(QString::fromUtf8("QFrame#frame_9{\n"
"border: 2px solid black;\n"
"border-radius:20px;\n"
"background: rgb(215, 215, 215); /*185 */\n"
"}"));
        frame_9->setFrameShape(QFrame::StyledPanel);
        frame_9->setFrameShadow(QFrame::Raised);
        GPS_Val = new QLabel(frame_9);
        GPS_Val->setObjectName(QString::fromUtf8("GPS_Val"));
        GPS_Val->setGeometry(QRect(-110, -100, 681, 451));
        GPS_Val->setFont(font9);
        GPS_Val->setLayoutDirection(Qt::LeftToRight);
        GPS_Val->setScaledContents(false);
        GPS_Val->setAlignment(Qt::AlignCenter);
        tabWidget->addTab(Settings, QString());
        frame_8->raise();
        DeleteFrame->raise();
        AboutFrame->raise();
        DeleteAll->raise();
        DownloadAll->raise();
        AboutButton->raise();
        frame_9->raise();

        gridLayout_2->addWidget(tabWidget, 1, 0, 1, 1);

        MainWindow->setCentralWidget(ThemeWidgetForm);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "REWS Desktop Visualizer", nullptr));
        HTTPButton->setText(QCoreApplication::translate("MainWindow", "Start (now automatic on startup)", nullptr));
        HomeTemp->setText(QCoreApplication::translate("MainWindow", "18 \302\260C", nullptr));
        HomePressure->setText(QCoreApplication::translate("MainWindow", "Pressure", nullptr));
        HomeHumidity->setText(QCoreApplication::translate("MainWindow", "Humidity", nullptr));
        HomeAQ->setText(QCoreApplication::translate("MainWindow", "Air Quality", nullptr));
        HomeWind->setText(QCoreApplication::translate("MainWindow", "Wind Speed", nullptr));
        HomeDate->setText(QCoreApplication::translate("MainWindow", "Friday, Feburary 18th, 2022", nullptr));
        HomeHumidityVal->setText(QCoreApplication::translate("MainWindow", "34%", nullptr));
        HomeWindVal->setText(QCoreApplication::translate("MainWindow", "5 MPH", nullptr));
        HomePressureVal->setText(QCoreApplication::translate("MainWindow", "1000 mbar", nullptr));
        HomeAQVal->setText(QCoreApplication::translate("MainWindow", "18\n"
"Excellent", nullptr));
        UpdateHomepage->setText(QCoreApplication::translate("MainWindow", "Update Homepage (temp debugging)", nullptr));
        HomeWindDir->setText(QCoreApplication::translate("MainWindow", "Direction: ", nullptr));
        HomeHumidity_2->setText(QCoreApplication::translate("MainWindow", "Temperature", nullptr));
        HomeTime->setText(QCoreApplication::translate("MainWindow", "00:00 AM", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Homepage), QCoreApplication::translate("MainWindow", "Homepage", nullptr));
        HumidityVal->setText(QCoreApplication::translate("MainWindow", "Current Humidity:", nullptr));
        HumidityStats->setText(QCoreApplication::translate("MainWindow", "24 hour average: #%\n"
"Past 24 hour high: #%\n"
"Past 24 hour low: #%", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Select graphing date range", nullptr));
        From_2->setText(QCoreApplication::translate("MainWindow", "from", nullptr));
        To_2->setText(QCoreApplication::translate("MainWindow", "to", nullptr));
        HumidityUpdated->setText(QCoreApplication::translate("MainWindow", "Last Updated: 1:00 PM 2/18/22", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Humidity), QCoreApplication::translate("MainWindow", "Humidity", nullptr));
        TemperatureVal->setText(QCoreApplication::translate("MainWindow", "Current Temperature:", nullptr));
        TemperatureStats->setText(QCoreApplication::translate("MainWindow", "24 hour average: #\302\272C\n"
"Past 24 hour high: #\302\272C\n"
"Past 24 hour low: #\302\272C", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Select graphing date range", nullptr));
        From->setText(QCoreApplication::translate("MainWindow", "from", nullptr));
        To->setText(QCoreApplication::translate("MainWindow", "to", nullptr));
        TemperatureUpdated->setText(QCoreApplication::translate("MainWindow", "Last Updated: 1:00 PM 2/18/22", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Temperature), QCoreApplication::translate("MainWindow", "Temperature", nullptr));
        WindDirection->setText(QCoreApplication::translate("MainWindow", "Current Wind Direction:\n"
"", nullptr));
        WindVal->setText(QCoreApplication::translate("MainWindow", "Current Wind Speed:", nullptr));
        WindStats->setText(QCoreApplication::translate("MainWindow", "24 hour average: #MPH\n"
"Past 24 hour high: #MPH\n"
"Past 24 hour low: #MPH", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Select graphing date range", nullptr));
        From_3->setText(QCoreApplication::translate("MainWindow", "from", nullptr));
        To_3->setText(QCoreApplication::translate("MainWindow", "to", nullptr));
        WindUpdated->setText(QCoreApplication::translate("MainWindow", "Last Updated: 1:00 PM 2/18/22", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Wind), QCoreApplication::translate("MainWindow", "Wind Speed/Direction", nullptr));
        PressureVal->setText(QCoreApplication::translate("MainWindow", "Current Pressure:", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Select graphing date range", nullptr));
        From_4->setText(QCoreApplication::translate("MainWindow", "from", nullptr));
        To_4->setText(QCoreApplication::translate("MainWindow", "to", nullptr));
        PressureStats->setText(QCoreApplication::translate("MainWindow", "24 hour average: #mbars\n"
"Past 24 hour high: #mbars\n"
"Past 24 hour low: #mbars", nullptr));
        PressureUpdated->setText(QCoreApplication::translate("MainWindow", "Last Updated: 1:00 PM 2/18/22", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Pressure), QCoreApplication::translate("MainWindow", "Pressure", nullptr));
        AQVal->setText(QCoreApplication::translate("MainWindow", "Current AQI:", nullptr));
        AQState->setText(QCoreApplication::translate("MainWindow", "Excellent", nullptr));
        AQStats->setText(QCoreApplication::translate("MainWindow", "24 hour average: #\n"
"Past 24 hour high: #\n"
"Past 24 hour low: #", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Select graphing date range", nullptr));
        From_5->setText(QCoreApplication::translate("MainWindow", "from", nullptr));
        To_5->setText(QCoreApplication::translate("MainWindow", "to", nullptr));
        AQUpdated->setText(QCoreApplication::translate("MainWindow", "Last Updated: 1:00 PM 2/18/22", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(AirQuality), QCoreApplication::translate("MainWindow", "Air Quality", nullptr));
        DeleteAll->setText(QCoreApplication::translate("MainWindow", "DELETE ALL DATA", nullptr));
        DownloadAll->setText(QCoreApplication::translate("MainWindow", "Download all data", nullptr));
        AboutButton->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        AboutDetails->setText(QCoreApplication::translate("MainWindow", "Cool about page\n"
"We made this thing", nullptr));
        AboutClose->setText(QCoreApplication::translate("MainWindow", "Close About", nullptr));
        DebugBox->setPlainText(QCoreApplication::translate("MainWindow", "0", nullptr));
        TempDebug->setText(QCoreApplication::translate("MainWindow", "Update Temp", nullptr));
        HumidityDebug->setText(QCoreApplication::translate("MainWindow", "Update Humid", nullptr));
        WindDebug->setText(QCoreApplication::translate("MainWindow", "Update Wind", nullptr));
        PressureDebug->setText(QCoreApplication::translate("MainWindow", "Update Pressure", nullptr));
        AQDebug->setText(QCoreApplication::translate("MainWindow", "Update AQ", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Enter Value", nullptr));
        DeleteText->setText(QCoreApplication::translate("MainWindow", "Are you sure you wish to delete all data?\n"
"This process is irreversible ", nullptr));
        DeleteConfirm->setText(QCoreApplication::translate("MainWindow", "Yes, Delete All Data Permanently", nullptr));
        DeleteDeny->setText(QCoreApplication::translate("MainWindow", "No, go back and do not delete data", nullptr));
        AirTitle->setText(QCoreApplication::translate("MainWindow", "Air Pressure", nullptr));
        MillibarsButton->setText(QCoreApplication::translate("MainWindow", "Millibars", nullptr));
        PascalButton->setText(QCoreApplication::translate("MainWindow", "Pascals", nullptr));
        WindTitle->setText(QCoreApplication::translate("MainWindow", "Wind Speed", nullptr));
        MPHButton->setText(QCoreApplication::translate("MainWindow", "Miles Per Hour (MPH)", nullptr));
        KPHButton->setText(QCoreApplication::translate("MainWindow", "Kilometers Per Hour (KPH)", nullptr));
        CelciusButton->setText(QCoreApplication::translate("MainWindow", "Celsius", nullptr));
        FarenheitButton->setText(QCoreApplication::translate("MainWindow", "Farenheight ", nullptr));
        TemperatureTitle->setText(QCoreApplication::translate("MainWindow", "Temperature", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        GPS_Val->setText(QCoreApplication::translate("MainWindow", "Current Location:\n"
"\n"
"Last updated:\n"
"\n"
"Latitude/Longitude:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(Settings), QCoreApplication::translate("MainWindow", "Settings", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
