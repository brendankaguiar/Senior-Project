/************************************************
 * REWS Weather Station Visualizer
 * Written By: Nicholas Ang, Kenji Won, Dalton Tracy
 *
 * Framework dependencies:
 * QtWidgets, QMessageBox, QTimer, QtDebug, QGraphicsWidget,
 * QVector, QtNetwork, QUrl, QJsonValue, QJsonValueRef,
 * QJsonDocument, QJsonObject
 *
 * External Integrated Libraries:
 * QCustomPlot - qcustomplot.h, qcustomplot.cpp
 *
 * Contributions:
 * Nick - MainWindow, addPoint, clearData, plot, on_ChangeTemperature_sliderMoved, on_ChangePressure_sliderMoved,
 * on_ChangeWind_sliderMoved,convertF,convertC,convertMph,convertKph,convertMbars,convertPas, UI design
 * Kenji - on_HTTPButton_Clicked() and UI design
 * Dalton - on_HTTPButton_Clicked() function - 5 hours
 *
 * **********************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QMessageBox>
#include <QTimer>
#include <QtDebug>
#include <QGraphicsWidget>
#include <QVector>
#include <QtNetwork>
#include <QUrl>
#include <iostream>
#include <QJsonValue>
#include <QJsonValueRef>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCoreApplication>
#include <QStandardPaths>
#include <QDateTime>
#include <QDate>

double maxTemp = 0,
        minTemp = 0,
        maxHum = 0,
        minHum = 0,
        maxWindSpeed = 0,
        minWindSpeed = 0,
        maxPressure = 0,
        minPressure = 0,
        maxAqi = 0,
        minAqi = 0,
        maxTimestamp = 0,
        minTimestamp = 0,
        avgAqi = 0,
        avgHum = 0,
        avgWindSpeed = 0,
        avgPressure = 0,
        avgTemp = 0;
QString windDirection;
int digit = 1;
int button = 100;
QDate startDate;
QDate endDate;

QPen pen;
////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QtWidgets, QCustomPlot
///////////////////////////////////////////////////////////////
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    //,qnam(new QNetworkAccessManager)
{
   //qnam = new QNetworkAccessManager(this);
   ui->setupUi(this);
   //->HomepagePlot->addGraph();
   ui->PlotTemperature->addGraph();
   ui->PlotHumidity->addGraph();
   ui->PlotWindSpeedDirection->addGraph();
   ui->PlotPressure->addGraph();
   ui->PlotAirQuality->addGraph();

   //ui->HomepagePlot->xAxis->setRange(0, 100);
   //ui->HomepagePlot->yAxis->setRange(-5, 6); //in celsius
   ui->PlotTemperature->xAxis->setRange(0, 100);
   ui->PlotTemperature->yAxis->setRange(-50, 100);
   ui->PlotHumidity->xAxis->setRange(0, 1000);
   ui->PlotHumidity->yAxis->setRange(0, 1000);
   ui->PlotWindSpeedDirection->xAxis->setRange(0, 100);
   ui->PlotWindSpeedDirection->yAxis->setRange(0, 30);
   ui->PlotPressure->xAxis->setRange(0, 100);
   ui->PlotPressure->yAxis->setRange(0, 1000);
   ui->PlotAirQuality->xAxis->setRange(0, 100);
   ui->PlotAirQuality->yAxis->setRange(0, 500);

   //ui->HomepagePlot->graph(0)->setPen(QPen(Qt::blue));
   //ui->HomepagePlot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
   ui->PlotTemperature->graph(0)->setPen(QPen(Qt::blue));
   ui->PlotTemperature->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
   ui->PlotHumidity->graph(0)->setPen(QPen(Qt::blue));
   ui->PlotHumidity->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
   ui->PlotWindSpeedDirection->graph(0)->setPen(QPen(Qt::blue));
   ui->PlotWindSpeedDirection->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
   ui->PlotPressure->graph(0)->setPen(QPen(Qt::blue));
   ui->PlotPressure->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
   ui->PlotAirQuality->graph(0)->setPen(QPen(Qt::blue));
   ui->PlotAirQuality->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
   getHttp();
   qnam->setAutoDeleteReplies(true);

   timerId = startTimer(1000);

}

//Default Qt Window Destructor
MainWindow::~MainWindow()
{
    delete ui;
}

////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QVector
///////////////////////////////////////////////////////////////
void MainWindow::addPoint(double x, double y, QVector<double> &xV, QVector<double> &yV)
{
    xV.begin();
    yV.begin();
    xV.append(x);
    yV.append(y);
}

////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QVector
///////////////////////////////////////////////////////////////
void MainWindow::clearData()
{
    qv_x.clear();
    qv_y.clear();
    qv_x2.clear();
    qv_y2.clear();
    qv_x3.clear();
    qv_y3.clear();
    qv_x4.clear();
    qv_y4.clear();
    qv_x5.clear();
    qv_y5.clear();
    qv_x6.clear();
    qv_y6.clear();
}

////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QtWidgets, QCustomPlot, QVector
///////////////////////////////////////////////////////////////
void MainWindow::plot()
{
    //ui->lcdNumber->display(qv_y.at(qv_y.length()-1));
    if(!qv_y2.isEmpty() && !qv_y3.isEmpty() && !qv_y4.isEmpty() && !qv_y5.isEmpty() && !qv_y6.isEmpty())
    {
        //ui->HomepagePlot->graph(0)->setData(qv_x,qv_y);
        ui->PlotTemperature->graph(0)->setData(qv_x2,qv_y2);
        ui->PlotHumidity->graph(0)->setData(qv_x3,qv_y3);
        ui->PlotWindSpeedDirection->graph(0)->setData(qv_x4,qv_y4);
        ui->PlotPressure->graph(0)->setData(qv_x5,qv_y5);
        ui->PlotAirQuality->graph(0)->setData(qv_x6,qv_y6);

        //ui->HomepagePlot->replot();
        //ui->HomepagePlot->update();
        ui->PlotTemperature->replot();
        ui->PlotTemperature->update();
        ui->PlotHumidity->replot();
        ui->PlotHumidity->update();
        ui->PlotWindSpeedDirection->replot();
        ui->PlotWindSpeedDirection->update();
        ui->PlotPressure->replot();
        ui->PlotPressure->update();
        ui->PlotAirQuality->replot();
        ui->PlotAirQuality->update();

        ui->LCDTemperature->display(qv_y2.at(qv_y2.length()-1));
        ui->LCDHumidity->display(qv_y3.at(qv_y3.length()-1));
        ui->LCDWind->display(qv_y4.at(qv_y4.length()-1));
        ui->LCDPressure->display(qv_y5.at(qv_y5.length()-1));
        ui->LCDAirQuality->display(qv_y6.at(qv_y6.length()-1));
    }
    else
    {
        ui->LCDTemperature->display("0");
        ui->LCDHumidity->display("0");
        ui->LCDWind->display("0");
        ui->LCDPressure->display("0");
        ui->LCDAirQuality->display("0");
    }
}

int MainWindow::newData()
{
    return rand() % 100;
}

////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QtWidgets
///////////////////////////////////////////////////////////////
/*
void MainWindow::on_ChangeTemperature_sliderMoved(int position)
{
    if(position == 1)
    {
        convertF();
    }
    if(position == 0)
    {
        convertC();
    }
}
*/
////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QVector, QCustomPlot
///////////////////////////////////////////////////////////////
void MainWindow::convertF()
{
    int i = 0;
    while(i < qv_y2.length())
    {
        qv_y2.replace(i, (((qv_y2.at(i)*9)/5) + 32));
        i++;
    }
    plot();
}

////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QVector, QCustomPlot
///////////////////////////////////////////////////////////////
void MainWindow::convertC()
{
    int i = 0;
    while(i < qv_y2.length())
    {
        qv_y2.replace(i, (((qv_y2.at(i)-32)*5)/9));
        i++;
    }
    plot();
}

////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QtWidgets
///////////////////////////////////////////////////////////////
/*
void MainWindow::on_ChangeWind_sliderMoved(int position)
{
    if(position == 1)
    {
        convertKph();
    }
    if(position == 0)
    {
        convertMph();
    }
}
*/
////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QVector, QCustomPlot
///////////////////////////////////////////////////////////////
void MainWindow::convertMph()
{
    int i = 0;
    while(i < qv_y4.length())
    {
        qv_y4.replace(i, (qv_y4.at(i)/1.609));
        i++;
    }
    ui->PlotWindSpeedDirection->yAxis->setRangeUpper(30);
    plot();
}

////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QVector, QCustomPlot
///////////////////////////////////////////////////////////////
void MainWindow::convertKph()
{
    int i = 0;
    while(i < qv_y4.length())
    {
        qv_y4.replace(i, (qv_y4.at(i)*1.609));
        i++;
    }
    ui->PlotWindSpeedDirection->yAxis->setRangeUpper(50);
    plot();
}

////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QtWidgets
///////////////////////////////////////////////////////////////
/*
void MainWindow::on_ChangePressure_sliderMoved(int position)
{
    if(position == 1)
    {
        convertPas();
    }
    if(position == 0)
    {
        convertMbars();
    }
}
*/
////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QVector, QCustomPlot
///////////////////////////////////////////////////////////////
void MainWindow::convertMbars()
{
    int i = 0;
    while(i < qv_y5.length())
    {
        qv_y5.replace(i, (qv_y5.at(i)/100));
        i++;
    }
    ui->PlotPressure->yAxis->setRangeUpper(1000);
    plot();
}

////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QVector, QCustomPlot
///////////////////////////////////////////////////////////////
void MainWindow::convertPas()
{
    int i = 0;
    while(i < qv_y5.length())
    {
        qv_y5.replace(i, (qv_y5.at(i)*100));
        i++;
    }
    ui->PlotPressure->yAxis->setRangeUpper(100000);
    plot();
}

////////////////////////////////////////////////////////////////
/// Written By: Kenji Won and Dalton Tracy
/// Dependencies: QString, QUrl, QNetworkAccessManager, QNetworkReply,
/// QByteArray, QJsonDocument, QJsonArray, QJssonObject
///////////////////////////////////////////////////////////////
void MainWindow::on_HTTPButton_clicked()
{
    qnam = new QNetworkAccessManager();
    //clearData();
    qnam->clearAccessCache();
    qnam->clearConnectionCache();
    QString url = "https://flask-rews.herokuapp.com/devicedata/all/0/2022_03_02";
    url.remove(QChar('"'));
    QUrl processedURL = url;
    qDebug() << "Sending request to: " << url;
    request.setUrl(processedURL);



    QObject::connect(qnam, &QNetworkAccessManager::finished,
        this, [=](QNetworkReply *reply) {
            if (reply->error()) {
                qDebug() << reply->errorString();
                return;
            }

            QByteArray buffer = reply->readAll();
            QJsonDocument jsonDoc(QJsonDocument::fromJson(buffer));
            QJsonArray jsonReply = jsonDoc.array();
            QJsonObject data = *new QJsonObject();

            /*double lastAQI = 0,
                    lastHum = 0,
                    lastWindSpeed = 0,
                    lastPressure = 0,
                    lastTemp = 0;*/

            for(QJsonArray::iterator record = jsonReply.begin(); record != jsonReply.end(); record++) {
                data = record->toObject();
                if(record == jsonReply.begin())
                {
                        minTimestamp = data["timestamp"].toDouble();
                }
 //                qDebug() << data["winddirection"];
                qDebug() << data["temperature"];
                //qDebug() << data["timestamp"];
                //addPoint(data["timestamp"].toDouble(), data["temperature"].toDouble(), qv_x, qv_y);
                addPoint(data["timestamp"].toDouble(), data["temperature"].toDouble(), qv_x2, qv_y2);
                addPoint(data["timestamp"].toDouble(), data["humidity"].toDouble(), qv_x3, qv_y3);
                addPoint(data["timestamp"].toDouble(), data["windspeed"].toDouble(), qv_x4, qv_y4);
                addPoint(data["timestamp"].toDouble(), data["pressure"].toDouble(), qv_x5, qv_y5);
                addPoint(data["timestamp"].toDouble(), data["aqi"].toDouble(), qv_x6, qv_y6);

                if(data["temperature"].toDouble() > maxTemp ) {
                    maxTemp = data["temperature"].toDouble();
                }else if(data["temperature"].toDouble() < minTemp) {
                    minTemp = data["temperature"].toDouble();
                }else if(data["humidity"].toDouble() > maxHum) {
                    maxHum = data["humidity"].toDouble();
                }else if(data["humidity"].toDouble() < minHum) {
                    minHum = data["humidity"].toDouble();
                }else if(data["windspeed"].toDouble() > maxWindSpeed) {
                    maxWindSpeed = data["windspeed"].toDouble();
                }else if(data["windspeed"].toDouble() < minWindSpeed) {
                    minWindSpeed = data["windspeed"].toDouble();
                }else if(data["pressure"].toDouble() > maxPressure) {
                    maxPressure = data["pressure"].toDouble();
                }else if(data["aqi"].toDouble() > maxAqi) {
                    maxAqi = data["aqi"].toDouble();
                }else if(data["aqi"].toDouble() < minAqi) {
                    minAqi = data["aqi"].toDouble();
                }else if(data["timestamp"].toDouble() > maxTimestamp) {
                    maxTimestamp = data["timestamp"].toDouble();
                }
                /*lastAQI = data["aqi"].toDouble();
                lastHum = data["humidity"].toDouble();
                lastWindSpeed = data["windspeed"].toDouble();
                lastPressure = data["pressure"].toDouble();
                lastTemp = data["temperature"].toDouble();*/
            }
            reply->deleteLater();

            //ui->HomepagePlot->yAxis->setRange(minTemp-5, maxTemp+5); //in celsius

            //ui->PlotTemperature->yAxis->rescale();
            //ui->PlotTemperature->yAxis->rescale();
            //ui->PlotHumidity->yAxis->rescale();
            //ui->PlotWindSpeedDirection->yAxis->rescale();
            //ui->PlotPressure->yAxis->rescale();
            //ui->PlotAirQuality->yAxis->rescale();
            qDebug() << minTemp;
            qDebug() << minHum;
            qDebug() <<minWindSpeed;
            qDebug() <<maxPressure;
            qDebug() <<minTimestamp;
            qDebug() <<minAqi;

            qDebug("\n");


            qDebug() << maxTemp;
            qDebug() << maxHum;
            qDebug() <<maxWindSpeed;
            qDebug() <<maxPressure;
            qDebug() <<maxAqi;
            qDebug() <<maxTimestamp;

            //ui->HomepagePlot->xAxis->setRange(minTimestamp, maxTimestamp); //in celsius
            ui->PlotTemperature->xAxis->setRange(minTimestamp, maxTimestamp);
            ui->PlotHumidity->xAxis->setRange(minTimestamp, maxTimestamp);
            ui->PlotWindSpeedDirection->xAxis->setRange(minTimestamp, maxTimestamp);
            ui->PlotPressure->xAxis->setRange(minTimestamp, maxTimestamp);
            ui->PlotAirQuality->xAxis->setRange(minTimestamp, maxTimestamp);

            ui->PlotTemperature->yAxis->setRange((minTemp-5.0), (maxTemp+5.0));
            ui->PlotHumidity->yAxis->setRange((minHum-5.0), (maxHum+5.0));
            ui->PlotWindSpeedDirection->yAxis->setRange((minWindSpeed-5.0), (maxWindSpeed+5.0));
            ui->PlotPressure->yAxis->setRange((minPressure-100.0), (maxPressure+100.0));
            ui->PlotAirQuality->yAxis->setRange((minAqi-5.0), (maxAqi+5.0));
            plot();

            //ui->AQIMeter->setValue(lastAQI);
        }
    );
    qnam->get(request);
}

////////////////////////////////////////////////////////////////
/// Written By: Kenji Won
/// Dependencies: QtWidgets
///////////////////////////////////////////////////////////////

void MainWindow::on_MillibarsButton_toggled(bool checked)
{
    if(checked)
    {
        convertMbars();
        //qDebug("converting to millibar");
    }
    else
    {
        convertPas();
        //qDebug("converting to pascal");
    }
}

////////////////////////////////////////////////////////////////
/// Written By: Kenji Won
/// Dependencies: QtWidgets
///////////////////////////////////////////////////////////////

void MainWindow::on_MPHButton_toggled(bool Mchecked)
{
    if(Mchecked)
    {
        convertMph();
         //qDebug("converting to mph");
    }
    else
    {
        convertKph();
        //qDebug("converting to kph");
    }
}

////////////////////////////////////////////////////////////////
/// Written By: Kenji Won
/// Dependencies: QtWidgets
///////////////////////////////////////////////////////////////

void MainWindow::on_FarenheitButton_toggled(bool Fchecked)
{
    if(Fchecked)
    {
        convertF();
        //qDebug("converting to f");
    }
    else
    {
        convertC();
        //qDebug("converting to c");
    }
}

//update homepage with data from graphs
void MainWindow::updateHomepage()
{
    //set the temp @ homescreen
    QString temp;
    double tempVal;
    if(qv_y2.isEmpty())
    {
        temp = "0";
        tempVal = 0;
    }
    else
    {
        temp = QString::number(qv_y2.at(qv_y2.length()-1));
        tempVal = (qv_y2.at(qv_y2.length()-1));
    }
    if(ui->FarenheitButton->isChecked())
    {
        ui->HomeTemp->setText( temp.left(temp.indexOf(".") + 3) + " °F");
    }
    else
    {
        ui->HomeTemp->setText( temp.left(temp.indexOf(".") + 3) + " °C");
        tempVal = (tempVal *9/5) + 32;
    }
    //set the background color based on temperature
    //, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings
    if(tempVal > 100) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage {background-color: rgb(255,86,1);}"); }
    else if( tempVal > 85) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage{background-color: rgb(253,200,36);}"); }
    else if( tempVal > 65) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage{background-color: rgb(247,255,144);}"); }
    else if( tempVal > 45) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage{background-color: rgb(186,255,236);}"); }
    else if( tempVal > 25) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage{background-color: rgb(144,242,255);}"); }
    else if( tempVal > -10) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage{background-color: rgb(40,114,213);}"); }
    else { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity{background-color: rgb(225,225,225);}"); }

    //set the time and date @ homescreen
    QDateTime datetime = QDateTime::currentDateTime();
    //ui->HomeTime->setText(datetime.time().toString()); //24 hour time
    //12 hour time
    if(datetime.time().toString().left(2).toInt() > 12)
    {
        ui->HomeTime->setText(QString::number(datetime.time().toString().left(2).toInt()-12) + datetime.time().toString().mid(2,3) + " PM");
    }
    else
    {
        ui->HomeTime->setText(datetime.time().toString().left(5) + " AM");
    }
    ui->HomeDate->setText(QLocale().toString(datetime.date(),QLocale::LongFormat));

    //update humidity
    if(qv_y3.isEmpty())
    {
        ui->HomeHumidityVal->setText("0%");
    }
    else
    {
        ui -> HomeHumidityVal->setText(QString::number(qv_y3.at(qv_y3.length()-1)) + "%");
    }

    //update windspeed
    if(qv_y4.isEmpty())
    {
    if(ui->MPHButton->isChecked())
    {
        ui -> HomeWindVal -> setText("0 MPH");
    }
    else
    {
        ui -> HomeWindVal -> setText("0 KM/H");
    }
    }
    else
    {
        if(ui->MPHButton->isChecked())
        {
            ui -> HomeWindVal -> setText(QString::number(qv_y4.at(qv_y4.length()-1)) + " MPH");
        }
        else
        {
            ui -> HomeWindVal -> setText(QString::number(qv_y4.at(qv_y4.length()-1)) + " KM/H");
        }
    }
    //update pressure
    if(qv_y5.isEmpty())
    {
        if(ui->MillibarsButton->isChecked())
        {
            ui -> HomePressureVal -> setText("0 mbars");
        }
        else
        {
            ui -> HomePressureVal -> setText("0 P");
        }
    }
    else
    {
        if(ui->MillibarsButton->isChecked())
        {
            ui -> HomePressureVal -> setText(QString::number(qv_y5.at(qv_y5.length()-1)) + " mbars");
        }
        else
        {
            ui -> HomePressureVal -> setText(QString::number(qv_y5.at(qv_y5.length()-1)) + " P");
        }
    }

    //update air quality
    int curAQ;
    if(qv_y6.isEmpty())
    {
        curAQ = 0;
    }
    else
    {
        curAQ = qv_y6.at(qv_y6.length()-1);
    }
    if(curAQ > 301) { ui -> HomeAQVal -> setText(QString::number(curAQ) + "\nHazardous"); }
    else if (curAQ > 201) { ui -> HomeAQVal -> setText(QString::number(curAQ) + "\nVery Unhealthy"); }
    else if (curAQ > 201) { ui -> HomeAQVal -> setText(QString::number(curAQ) + "\nUnhealthy"); }
    else if (curAQ > 201) { ui -> HomeAQVal -> setText(QString::number(curAQ) + "\nUnhealthy for Senstive Groups"); }
    else if (curAQ > 201) { ui -> HomeAQVal -> setText(QString::number(curAQ) + "\nModerate"); }
    else { ui -> HomeAQVal -> setText(QString::number(curAQ) + "\nGood");}

}

//update the homepage
void MainWindow::on_pushButton_clicked()
{
    updateHomepage();
}

//change color to default if user leave homepage or change color back if homepage is clicked on again
void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(ui->tabWidget->currentIndex() == 0)
    {
        updateHomepage();
        double tempVal;
        if(qv_y2.isEmpty())
        {
            tempVal = 0;
        }
        else
        {
            tempVal = (qv_y2.at(qv_y2.length()-1));
        }
        if(!ui->FarenheitButton->isChecked()) { tempVal = (tempVal *9/5) + 32;} //if temp is in celcius convert it to farenheight for temp color
        if(tempVal > 100) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(255,86,1);}"); }
        else if( tempVal > 85) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(253,200,36);}"); }
        else if( tempVal > 65) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(247,255,144);}"); }
        else if( tempVal > 45) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(186,255,236);}"); }
        else if( tempVal > 25) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(144,242,255);}"); }
        else if( tempVal > -10) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(40,114,213);}"); }
        else { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(225,225,225);}"); }
    }
    else
    {
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(225,225,225);}");
    }
}

void MainWindow::getHttp(QString http)
{
    QString date = getCurrentDate();
    QString url = requestUrl("all/", date);
    qnam = new QNetworkAccessManager();
    clearData();
    qnam->clearAccessCache();
    qnam->clearConnectionCache();
    ui->LoadingScreen->setVisible(TRUE);
    //QString url = http;
    url.remove(QChar('"'));
    QUrl processedURL = url;
    qDebug() << "Sending request to: " << url;
    request.setUrl(processedURL);
    QObject::connect(qnam, &QNetworkAccessManager::finished,
        this, [=](QNetworkReply *reply) {
            if (reply->error()) {
                qDebug() << reply->errorString();
                return;
            }

            QByteArray buffer = reply->readAll();
            QJsonDocument jsonDoc(QJsonDocument::fromJson(buffer));
            QJsonArray jsonReply = jsonDoc.array();
            QJsonObject data = *new QJsonObject();

            /*double lastAQI = 0,
                    lastHum = 0,
                    lastWindSpeed = 0,
                    lastPressure = 0,
                    lastTemp = 0;*/

            //qDebug() << buffer;

            ui->LoadingBar->setValue(50);
            for(QJsonArray::iterator record = jsonReply.begin(); record != jsonReply.end(); record++) {
                data = record->toObject();
                if(record == jsonReply.begin()){
                    minTimestamp = data["timestamp"].toDouble();
                }
 //                qDebug() << data["winddirection"];
                // qDebug() << data["temperature"];
                //qDebug() << data["timestamp"];
                //addPoint(data["timestamp"].toDouble(), data["temperature"].toDouble(), qv_x, qv_y);
                addPoint(data["timestamp"].toDouble(), data["temperature"].toDouble(), qv_x2, qv_y2);
                addPoint(data["timestamp"].toDouble(), data["humidity"].toDouble(), qv_x3, qv_y3);
                addPoint(data["timestamp"].toDouble(), data["windspeed"].toDouble(), qv_x4, qv_y4);
                addPoint(data["timestamp"].toDouble(), data["pressure"].toDouble(), qv_x5, qv_y5);
                addPoint(data["timestamp"].toDouble(), data["aqi"].toDouble(), qv_x6, qv_y6);

                if(data["temperature"].toDouble() > maxTemp) {
                    maxTemp = data["temperature"].toDouble();
                }else if(data["temperature"].toDouble() < minTemp) {
                    minTemp = data["temperature"].toDouble();
                }else if(data["humidity"].toDouble() > maxHum) {
                    maxHum = data["humidity"].toDouble();
                }else if(data["humidity"].toDouble() < minHum) {
                    minHum = data["humidity"].toDouble();
                }else if(data["windspeed"].toDouble() > maxWindSpeed) {
                    maxWindSpeed = data["windspeed"].toDouble();
                }else if(data["windspeed"].toDouble() < minWindSpeed) {
                    minWindSpeed = data["windspeed"].toDouble();
                }else if(data["pressure"].toDouble() > maxPressure) {
                    maxPressure = data["pressure"].toDouble();
                }else if(data["aqi"].toDouble() > maxAqi) {
                    maxAqi = data["aqi"].toDouble();
                }else if(data["aqi"].toDouble() < minAqi) {
                    minAqi = data["aqi"].toDouble();
                }else if(data["timestamp"].toDouble() > maxTimestamp) {
                    maxTimestamp = data["timestamp"].toDouble();
                }
                /*lastAQI = data["aqi"].toDouble();
                lastHum = data["humidity"].toDouble();
                lastWindSpeed = data["windspeed"].toDouble();
                lastPressure = data["pressure"].toDouble();
                lastTemp = data["temperature"].toDouble();*/

            }
            ui->LoadingBar->setValue(90);
            reply->deleteLater();

            //ui->HomepagePlot->xAxis->setRange(minTimestamp, maxTimestamp); //in celsius
            ui->PlotTemperature->xAxis->setRange(minTimestamp, maxTimestamp);
            ui->PlotHumidity->xAxis->setRange(minTimestamp, maxTimestamp);
            ui->PlotWindSpeedDirection->xAxis->setRange(minTimestamp, maxTimestamp);
            ui->PlotPressure->xAxis->setRange(minTimestamp, maxTimestamp);
            ui->PlotAirQuality->xAxis->setRange(minTimestamp, maxTimestamp);

            //ui->HomepagePlot->yAxis->setRange(minTemp-5, maxTemp+5); //in celsius
            ui->PlotTemperature->yAxis->setRange((minTemp-5), (maxTemp+5));
            ui->PlotHumidity->yAxis->setRange((minHum-5), (maxHum+5));
            ui->PlotWindSpeedDirection->yAxis->setRange((minWindSpeed-5), (maxWindSpeed+5));
            ui->PlotPressure->yAxis->setRange((minPressure-100), (maxPressure+100));
            ui->PlotAirQuality->yAxis->setRange((minAqi-5), (maxAqi+5));

            qDebug() << minTemp;
            qDebug() << minHum;
            qDebug() <<minWindSpeed;
            qDebug() <<maxPressure;
            qDebug() <<minAqi;
            qDebug() <<minTimestamp;

            qDebug("\n");

            qDebug() << maxTemp;
            qDebug() << maxHum;
            qDebug() <<maxWindSpeed;
            qDebug() <<maxPressure;
            qDebug() <<maxAqi;
            qDebug() <<maxTimestamp;
            plot();
            updateHomepage();
            //ui->AQIMeter->setValue(lastAQI);
        }
    );
    updateHomepage();
    ui->LoadingBar->setValue(100);
    qnam->get(request);
    ui->LoadingScreen->setVisible(FALSE);
    }

void MainWindow::downloadFile()
{
    qnam = new QNetworkAccessManager();
    //QString downloadUrl = "https://flask-rews.herokuapp.com/devicedata/all/0/2022_02_16";
    QString downloadUrl = requestUrl("sensor/temperature/", "2022_02_17");
    qnam->clearAccessCache();
    qnam->clearConnectionCache();
    QString url = downloadUrl;
    url.remove(QChar('"'));
    QUrl processedURL = url;
    qDebug() << "Sending request to: " << url;
    request.setUrl(processedURL);

    QNetworkReply *reply = qnam->get(request);
    connect(reply, SIGNAL(finished()), this, SLOT(downloadFinished()));

}

void MainWindow::on_DownloadAll_clicked()
{

    downloadFile();
}

void MainWindow::downloadFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

        if (reply)
        {
            if (reply->error() == QNetworkReply::NoError)
            {
                QString downloadPath = (QString)QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
                QString userFilename = QFileDialog::getSaveFileName(this, tr("Save File as"), downloadPath, (" txt file (*.txt)"));
                QFile file(userFilename);
                if(file.open(QIODevice::WriteOnly))
                {
                        file.write(reply->readAll());
                        qDebug() << "Download Successful";
                }
            }
            reply->deleteLater();
        }
        else
        {
            qDebug() << "Error downloading file";
        }
}

QString MainWindow::requestUrl(QString type, QString date)
{
    QString defaultString = "https://flask-rews.herokuapp.com/devicedata/";
    QString deviceNum = "0/";
    QString url;
    QString temp;
    url = defaultString.append(type);
    temp = url.append(deviceNum);
    url = temp.append(date);
    return url;
}

void MainWindow::deleteAllData()
{
    qnam = new QNetworkAccessManager();
    QString downloadUrl = "https://flask-rews.herokuapp.com/devicedata/delete";
    qnam->clearAccessCache();
    qnam->clearConnectionCache();
    QString url = downloadUrl;
    url.remove(QChar('"'));
    QUrl processedURL = url;
    qDebug() << "Sending request to: " << url;
    request.setUrl(processedURL);
    QNetworkReply *reply = qnam->get(request);
    QObject::connect(reply, SIGNAL(finished()), this, SLOT(deleteFinished()));
}

void MainWindow::deleteFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());

        if (reply)
        {
            if (reply->error() == QNetworkReply::NoError)
            {
                        clearData();
                        qDebug() << "Delete Successful";
            }
            reply->deleteLater();
        }
        else
        {
            qDebug() << "Error deleting all data";
        }

}

void MainWindow::on_DeleteAll_clicked()
{
    deleteAllData();
}

QString MainWindow::getCurrentDate()
{
    int day,month,year;
    QString dateS;
    QDate date = QDate::currentDate();
    day = date.day();
    month = date.month();
    year = date.year();
    if(month > 0 && month < 10)
    {
        if(day > 0 && day < 10)
        {
            dateS = QString::number(year) + "_0" + QString::number(month) + "_0" + QString::number(day);
        }
        else
        {
            dateS = QString::number(year) + "_0" + QString::number(month) + "_0" + QString::number(day);
        }
    }
    else
    {
        if(day > 0 && day < 10)
        {
            dateS = QString::number(year) + "_" + QString::number(month) + "_0" + QString::number(day);
        }
        else
        {
            dateS = QString::number(year) + "_" + QString::number(month) + "_" + QString::number(day);
        }
    }
    return dateS;
}

void MainWindow::getMinMaxAvg(QString sensor)
{
    QString date = getCurrentDate();
    QString url = requestUrl(sensor, date);
    qnam = new QNetworkAccessManager();
    url.remove(QChar('"'));
    QUrl processedURL = url;
    qDebug() << "Sending request to: " << url;
    request.setUrl(processedURL);
    QObject::connect(qnam, &QNetworkAccessManager::finished,
        this, [=](QNetworkReply *reply) {
            if (reply->error()) {
                qDebug() << reply->errorString();
                return;
            }

            QByteArray buffer = reply->readAll();
            QJsonDocument jsonDoc(QJsonDocument::fromJson(buffer));
            QJsonArray jsonReply = jsonDoc.array();
            QJsonObject data = *new QJsonObject();



            //qDebug() << buffer;

            ui->LoadingBar->setValue(50);
            for(QJsonArray::iterator record = jsonReply.begin(); record != jsonReply.end(); record++) {
                data = record->toObject();
                if(sensor == "temperature")
                {
                    minTemp = data["min"].toDouble();
                    maxTemp = data["max"].toDouble();
                    avgTemp = data["average"].toDouble();
                }
                else if(sensor == "humidity")
                {
                    minHum = data["min"].toDouble();
                    maxHum = data["max"].toDouble();
                    avgHum = data["average"].toDouble();
                }
                else if(sensor == "windspeed")
                {
                    minWindSpeed = data["min"].toDouble();
                    maxWindSpeed = data["max"].toDouble();
                    avgWindSpeed = data["average"].toDouble();
                }
                else if(sensor == "pressure")
                {
                    minPressure = data["min"].toDouble();
                    maxPressure = data["max"].toDouble();
                    avgPressure = data["average"].toDouble();
                }
                else if(sensor == "aqi")
                {
                    minAqi = data["min"].toDouble();
                    maxAqi = data["max"].toDouble();
                    avgAqi = data["average"].toDouble();
                }
            }
            reply->deleteLater();
    });
    qnam->get(request);
}

void MainWindow::on_FirstDate_2_userDateChanged(const QDate &date)
{
    //Humidity Tab date boxes
    startDate = date;
}


void MainWindow::on_SecondDate_2_userDateChanged(const QDate &date)
{
    //Humidity Tab date boxes
    endDate = date;
}

void MainWindow::getHttpMultidate()
{
    //QDate tempDate = startDate;
    //Only do up to one year for now
    if(startDate.year() == endDate.year())
    {
        if(startDate.month() == endDate.month())
        {
            while(startDate.day() <= endDate.day())
            {
                //getHttp(tempDate);
                //tempDate.setDate(tempDate.day()+1);
            }
        }
        else if(startDate.month() < endDate.month())
        {

        }
    }
}

void MainWindow::getHttpTemp()
{
    getMinMaxAvg("temperature");
    QString date = getCurrentDate();
    QString url = requestUrl("temperature/", date);
    qnam = new QNetworkAccessManager();
    clearData();
    qnam->clearAccessCache();
    qnam->clearConnectionCache();
    url.remove(QChar('"'));
    QUrl processedURL = url;
    qDebug() << "Sending request to: " << url;
    request.setUrl(processedURL);
    QObject::connect(qnam, &QNetworkAccessManager::finished,
        this, [=](QNetworkReply *reply) {
            if (reply->error()) {
                qDebug() << reply->errorString();
                return;
            }

            QByteArray buffer = reply->readAll();
            QJsonDocument jsonDoc(QJsonDocument::fromJson(buffer));
            QJsonArray jsonReply = jsonDoc.array();
            QJsonObject data = *new QJsonObject();

            for(QJsonArray::iterator record = jsonReply.begin(); record != jsonReply.end(); record++) {
                data = record->toObject();
                if(record == jsonReply.begin()){
                    minTimestamp = data["timestamp"].toDouble();
                }
                addPoint(data["timestamp"].toDouble(), data["temperature"].toDouble(), qv_x2, qv_y2);
            }
            reply->deleteLater();

            ui->PlotTemperature->yAxis->setRange((minTemp-5), (maxTemp+5));

            ui->PlotTemperature->xAxis->setRange(minTimestamp, maxTimestamp);

            plot();
        }
    );
    updateHomepage();
    qnam->get(request);
}

void MainWindow::getHttpHum()
{
    getMinMaxAvg("humidity");
    QString date = getCurrentDate();
    QString url = requestUrl("humidity/", date);
    qnam = new QNetworkAccessManager();
    clearData();
    qnam->clearAccessCache();
    qnam->clearConnectionCache();
    url.remove(QChar('"'));
    QUrl processedURL = url;
    qDebug() << "Sending request to: " << url;
    request.setUrl(processedURL);
    QObject::connect(qnam, &QNetworkAccessManager::finished,
        this, [=](QNetworkReply *reply) {
            if (reply->error()) {
                qDebug() << reply->errorString();
                return;
            }

            QByteArray buffer = reply->readAll();
            QJsonDocument jsonDoc(QJsonDocument::fromJson(buffer));
            QJsonArray jsonReply = jsonDoc.array();
            QJsonObject data = *new QJsonObject();

            for(QJsonArray::iterator record = jsonReply.begin(); record != jsonReply.end(); record++) {
                data = record->toObject();
                if(record == jsonReply.begin()){
                    minTimestamp = data["timestamp"].toDouble();
                }
                addPoint(data["timestamp"].toDouble(), data["humidity"].toDouble(), qv_x3, qv_y3);
            }
            reply->deleteLater();

            ui->PlotHumidity->yAxis->setRange((minHum-5), (maxHum+5));

            ui->PlotHumidity->xAxis->setRange(minTimestamp, maxTimestamp);

            plot();
        }
    );
    updateHomepage();
    qnam->get(request);
}

void MainWindow::getHttpWindSpeedDirection()
{
    getMinMaxAvg("windspeed");
    QString date = getCurrentDate();
    QString url = requestUrl("windspeed/", date);
    qnam = new QNetworkAccessManager();
    clearData();
    qnam->clearAccessCache();
    qnam->clearConnectionCache();
    url.remove(QChar('"'));
    QUrl processedURL = url;
    qDebug() << "Sending request to: " << url;
    request.setUrl(processedURL);
    QObject::connect(qnam, &QNetworkAccessManager::finished,
        this, [=](QNetworkReply *reply) {
            if (reply->error()) {
                qDebug() << reply->errorString();
                return;
            }

            QByteArray buffer = reply->readAll();
            QJsonDocument jsonDoc(QJsonDocument::fromJson(buffer));
            QJsonArray jsonReply = jsonDoc.array();
            QJsonObject data = *new QJsonObject();

            for(QJsonArray::iterator record = jsonReply.begin(); record != jsonReply.end(); record++) {
                data = record->toObject();
                if(record == jsonReply.begin()){
                    minTimestamp = data["timestamp"].toDouble();
                }
                addPoint(data["timestamp"].toDouble(), data["windspeed"].toDouble(), qv_x4, qv_y4);
                windDirection = data["winddirection"].toString();
            }
            reply->deleteLater();

            ui->PlotWindSpeedDirection->yAxis->setRange((minWindSpeed-5), (maxWindSpeed+5));

            ui->PlotWindSpeedDirection->xAxis->setRange(minTimestamp, maxTimestamp);

            plot();
        }
    );
    updateHomepage();
    qnam->get(request);
}

void MainWindow::getHttpPressure()
{
    getMinMaxAvg("pressure");
    QString date = getCurrentDate();
    QString url = requestUrl("pressure/", date);
    qnam = new QNetworkAccessManager();
    clearData();
    qnam->clearAccessCache();
    qnam->clearConnectionCache();
    url.remove(QChar('"'));
    QUrl processedURL = url;
    qDebug() << "Sending request to: " << url;
    request.setUrl(processedURL);
    QObject::connect(qnam, &QNetworkAccessManager::finished,
        this, [=](QNetworkReply *reply) {
            if (reply->error()) {
                qDebug() << reply->errorString();
                return;
            }

            QByteArray buffer = reply->readAll();
            QJsonDocument jsonDoc(QJsonDocument::fromJson(buffer));
            QJsonArray jsonReply = jsonDoc.array();
            QJsonObject data = *new QJsonObject();

            for(QJsonArray::iterator record = jsonReply.begin(); record != jsonReply.end(); record++) {
                data = record->toObject();
                if(record == jsonReply.begin()){
                    minTimestamp = data["timestamp"].toDouble();
                }
                addPoint(data["timestamp"].toDouble(), data["pressure"].toDouble(), qv_x5, qv_y5);
            }
            reply->deleteLater();

            ui->PlotPressure->yAxis->setRange((minPressure-100), (maxPressure+100));

            ui->PlotPressure->xAxis->setRange(minTimestamp, maxTimestamp);

            plot();
        }
    );
    updateHomepage();
    qnam->get(request);
}

void MainWindow::getHttpAqi()
{
    getMinMaxAvg("aqi");
    QString date = getCurrentDate();
    QString url = requestUrl("aqi/", date);
    qnam = new QNetworkAccessManager();
    clearData();
    qnam->clearAccessCache();
    qnam->clearConnectionCache();
    url.remove(QChar('"'));
    QUrl processedURL = url;
    qDebug() << "Sending request to: " << url;
    request.setUrl(processedURL);
    QObject::connect(qnam, &QNetworkAccessManager::finished,
        this, [=](QNetworkReply *reply) {
            if (reply->error()) {
                qDebug() << reply->errorString();
                return;
            }

            QByteArray buffer = reply->readAll();
            QJsonDocument jsonDoc(QJsonDocument::fromJson(buffer));
            QJsonArray jsonReply = jsonDoc.array();
            QJsonObject data = *new QJsonObject();

            for(QJsonArray::iterator record = jsonReply.begin(); record != jsonReply.end(); record++) {
                data = record->toObject();
                if(record == jsonReply.begin()){
                    minTimestamp = data["timestamp"].toDouble();
                }
                addPoint(data["timestamp"].toDouble(), data["aqi"].toDouble(), qv_x6, qv_y6);
            }
            reply->deleteLater();

            ui->PlotAirQuality->yAxis->setRange((minAqi-5), (maxAqi+5));

            ui->PlotAirQuality->xAxis->setRange(minTimestamp, maxTimestamp);

            plot();
        }
    );
    updateHomepage();
    qnam->get(request);
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    updateHomepage();
}
