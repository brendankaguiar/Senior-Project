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


//Libraries and Header Files
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

//Global Variables
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
        avgTemp = 0,
        updateTime = 0,
        lastTemp = -10000,
        lastHum = -10000,
        lastWindSpeed = -10000,
        lastPressure = -10000,
        lastAqi = -10000;
QString windDirection;
QString GPSlocation;
QString CITYlocation;

int deviceID = 0;
int digit = 1;
int button = 100;
bool check = 0, Mcheck = 0, Fcheck = 0;
QDate startDate = QDate::currentDate();
QDate endDate = QDate::currentDate();
QDate downloadDate = QDate::currentDate();

QPen pen;
////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QtWidgets, QCustomPlot
/// Description: Initial setup of window, graphs and timer
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
   ui->statusbar->hide();
   QSharedPointer<QCPAxisTickerDateTime> dateTimeTicker(new QCPAxisTickerDateTime);
   ui->PlotTemperature->xAxis->setTicker(dateTimeTicker);
   dateTimeTicker->setDateTimeFormat("M/d/yyyy\nh:mm AP");
   ui->PlotTemperature->xAxis->setLabel("Date & Time");
   ui->PlotTemperature->yAxis->setLabel("Temperature °C");
   ui->PlotTemperature->xAxis->setPadding(10);
   ui->PlotTemperature->yAxis->setPadding(10);

   ui->PlotHumidity->xAxis->setTicker(dateTimeTicker);
   dateTimeTicker->setDateTimeFormat("M/d/yyyy\nh:mm AP");
   ui->PlotHumidity->xAxis->setLabel("Date & Time");
   ui->PlotHumidity->yAxis->setLabel("Humidity %");
   ui->PlotHumidity->xAxis->setPadding(10);
   ui->PlotHumidity->yAxis->setPadding(10);

   ui->PlotWindSpeedDirection->xAxis->setTicker(dateTimeTicker);
   dateTimeTicker->setDateTimeFormat("M/d/yyyy\nh:mm AP");
   ui->PlotWindSpeedDirection->xAxis->setLabel("Date & Time");
   ui->PlotWindSpeedDirection->yAxis->setLabel("Wind Speed MPH");
   ui->PlotWindSpeedDirection->xAxis->setPadding(10);
   ui->PlotWindSpeedDirection->yAxis->setPadding(10);

   ui->PlotPressure->xAxis->setTicker(dateTimeTicker);
   dateTimeTicker->setDateTimeFormat("M/d/yyyy\nh:mm AP");
   ui->PlotPressure->xAxis->setLabel("Date & Time");
   ui->PlotPressure->yAxis->setLabel("Pressure mbars");
   ui->PlotPressure->xAxis->setPadding(10);
   ui->PlotPressure->yAxis->setPadding(10);

   ui->PlotAirQuality->xAxis->setTicker(dateTimeTicker);
   dateTimeTicker->setDateTimeFormat("M/d/yyyy\nh:mm AP");
   ui->PlotAirQuality->xAxis->setLabel("Date & Time");
   ui->PlotAirQuality->yAxis->setLabel("Air Quality Index");
   ui->PlotAirQuality->xAxis->setPadding(10);
   ui->PlotAirQuality->yAxis->setPadding(10);

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
   //ui->PlotTemperature->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
   ui->PlotHumidity->graph(0)->setPen(QPen(Qt::blue));
   //ui->PlotHumidity->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
   ui->PlotWindSpeedDirection->graph(0)->setPen(QPen(Qt::blue));
   //ui->PlotWindSpeedDirection->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
   ui->PlotPressure->graph(0)->setPen(QPen(Qt::blue));
   //ui->PlotPressure->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
   ui->PlotAirQuality->graph(0)->setPen(QPen(Qt::blue));
   //ui->PlotAirQuality->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
   getHttp("https://flask-rews.herokuapp.com/devicedata/latest/" + QString::number(deviceID));
   qnam->setAutoDeleteReplies(true);

   ui->AboutFrame->setVisible(FALSE);
   ui->DeleteFrame->setVisible(FALSE);
   timerId = startTimer(5000);

}

//Default Qt Window Destructor
MainWindow::~MainWindow()
{
    delete ui;
}

////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QVector
/// Description: Adds points to graphs
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
/// Description: Clears Graphs
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
    maxTimestamp = 0;
}

////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QtWidgets, QCustomPlot, QVector
/// Description: Plots all graphs with data obtained from HTTP requests
///////////////////////////////////////////////////////////////
void MainWindow::plot()
{
    //ui->lcdNumber->display(qv_y.at(qv_y.length()-1));
    if(!qv_y2.isEmpty() || !qv_y3.isEmpty() || !qv_y4.isEmpty() || !qv_y5.isEmpty() || !qv_y6.isEmpty())
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
    }

        /*
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
    } */
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
    minTemp = ((minTemp*9)/5)+ 32;
    maxTemp = ((maxTemp*9)/5)+ 32;
    avgTemp = ((avgTemp*9)/5)+ 32;
    lastTemp = ((lastTemp*9/5)+32);
    while(i < qv_y2.length())
    {
        qv_y2.replace(i, (((qv_y2.at(i)*9)/5) + 32));
        i++;
    }

    ui->PlotTemperature->yAxis->setRange((minTemp-15.0), (maxTemp+15.0));
    ui->PlotTemperature->yAxis->setLabel("Temperature °F");
    plot();
}

////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QVector, QCustomPlot
///////////////////////////////////////////////////////////////
void MainWindow::convertC()
{
    int i = 0;
    minTemp = ((minTemp-32)*5)/9;
    maxTemp = ((maxTemp-32)*5)/9;
    avgTemp = ((avgTemp-32)*5)/9;
    lastTemp = ((lastTemp-32)*5)/9;
    while(i < qv_y2.length())
    {
        qv_y2.replace(i, (((qv_y2.at(i)-32)*5)/9));
        i++;
    }

    ui->PlotTemperature->yAxis->setRange((minTemp-15.0), (maxTemp+15.0));
    ui->PlotTemperature->yAxis->setLabel("Temperature °C");
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
    minWindSpeed = minWindSpeed/1.609;
    maxWindSpeed = maxWindSpeed/1.609;
    avgWindSpeed = avgWindSpeed/1.609;
    lastWindSpeed = lastWindSpeed/1.609;
    while(i < qv_y4.length())
    {
        qv_y4.replace(i, (qv_y4.at(i)/1.609));
        i++;
    }

    ui->PlotWindSpeedDirection->yAxis->setRange((minWindSpeed-5.0), (maxWindSpeed+5.0));
    ui->PlotWindSpeedDirection->yAxis->setLabel("Wind Speed MPH");
    plot();
}

////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QVector, QCustomPlot
///////////////////////////////////////////////////////////////
void MainWindow::convertKph()
{
    int i = 0;
    minWindSpeed = minWindSpeed*1.609;
    maxWindSpeed = maxWindSpeed*1.609;
    avgWindSpeed = avgWindSpeed*1.609;
    lastWindSpeed = lastWindSpeed*1.609;
    while(i < qv_y4.length())
    {
        qv_y4.replace(i, (qv_y4.at(i)*1.609));
        i++;
    }

    ui->PlotWindSpeedDirection->yAxis->setRange((minWindSpeed-5.0), (maxWindSpeed+5.0));
    ui->PlotWindSpeedDirection->yAxis->setLabel("Wind Speed KPH");
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
    minPressure = minPressure/100;
    maxPressure = maxPressure/100;
    avgPressure = avgPressure/100;
    lastPressure = lastPressure/100;
    while(i < qv_y5.length())
    {
        qv_y5.replace(i, (qv_y5.at(i)/100));
        i++;
    }

    ui->PlotPressure->yAxis->setRange((minPressure-1.0), (maxPressure+1.0));
    ui->PlotPressure->yAxis->setLabel("Pressure mbars");
    plot();
}

////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QVector, QCustomPlot
///////////////////////////////////////////////////////////////
void MainWindow::convertPas()
{
    int i = 0;
    minPressure = minPressure*100;
    maxPressure = maxPressure*100;
    avgPressure = avgPressure*100;
    lastPressure = lastPressure*100;
    while(i < qv_y5.length())
    {
        qv_y5.replace(i, (qv_y5.at(i)*100));
        i++;
    }

    ui->PlotPressure->yAxis->setRange((minPressure-100.0), (maxPressure+100.0));
    ui->PlotPressure->yAxis->setLabel("Pressure Pa");
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
    QString url = "https://flask-rews.herokuapp.com/devicedata/all/" + QString::number(deviceID) + "/2022_03_02";
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

            ui->PlotTemperature->yAxis->setRange((minTemp-15.0), (maxTemp+15.0));
            ui->PlotHumidity->yAxis->setRange(0, 100);
            ui->PlotWindSpeedDirection->yAxis->setRange((minWindSpeed-5.0), (maxWindSpeed+5.0));
            ui->PlotPressure->yAxis->setRange((minPressure-1.0), (maxPressure+1.0));
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
/// Description: Converts Pressure Units between mBars and Pascals
///////////////////////////////////////////////////////////////

void MainWindow::on_PascalButton_toggled(bool checked)
{
    check = checked;
    if(checked)
    {
        convertPas();
        //qDebug("converting to millibar");
    }
    else
    {

        convertMbars();
        //qDebug("converting to pascal");
    }
}

////////////////////////////////////////////////////////////////
/// Written By: Kenji Won
/// Dependencies: QtWidgets
/// Description: Converts Wind Speed Units between KPH and MPH
///////////////////////////////////////////////////////////////

void MainWindow::on_KPHButton_toggled(bool Mchecked)
{
    Mcheck = Mchecked;
    if(Mchecked)
    {
         convertKph();
         //qDebug("converting to mph");
    }
    else
    {
        convertMph();
        //qDebug("converting to kph");
    }
}

////////////////////////////////////////////////////////////////
/// Written By: Kenji Won
/// Dependencies: QtWidgets
/// Description: Converts Temperature Units between F and C
///////////////////////////////////////////////////////////////

void MainWindow::on_FarenheitButton_toggled(bool Fchecked)
{
    Fcheck = Fchecked;
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

////////////////////////////////////////////////////////////////
/// Written By: Kenji Won
/// Dependencies: QtWidgets
/// Description: Updates text for all sensor data on homepage
///////////////////////////////////////////////////////////////
//update homepage with data from graphs
void MainWindow::updateHomepage()
{
    //set the temp @ homescreen
    QString temp = "0";

    if(lastTemp == -10000)
    {
        temp = "0";
    }
    else
    {
        temp = QString::number(lastTemp);
    }
    if(ui->FarenheitButton->isChecked())
    {
        ui->HomeTemp->setText( temp.left(temp.indexOf(".") + 3) + " °F");
    }
    else
    {
        ui->HomeTemp->setText( temp.left(temp.indexOf(".") + 3) + " °C");
    }

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
    if(lastHum == -10000)
    {
        ui->HomeHumidityVal->setText("0%");
    }
    else
    {
        ui -> HomeHumidityVal->setText(QString::number(lastHum) + "%");
    }

    //update windspeed
    if(lastWindSpeed == -10000)
    {
        if(ui->MPHButton->isChecked())
        {
            ui -> HomeWindVal -> setText("0 MPH");
        }
        else
        {
            ui -> HomeWindVal -> setText("0 KM/H");
        }
        ui->HomeWindDir->setText("Direction: " + windDirection);
    }
    else
    {
        if(ui->MPHButton->isChecked())
        {
            ui -> HomeWindVal -> setText(QString::number(lastWindSpeed) + " MPH");
        }
        else
        {
            ui -> HomeWindVal -> setText(QString::number(lastWindSpeed) + " KM/H");
        }
        ui->HomeWindDir->setText("Direction: " + windDirection);
    }
    //update pressure
    if(lastPressure == -10000)
    {
        if(ui->MillibarsButton->isChecked())
        {
            ui -> HomePressureVal -> setText("0 mbars");
        }
        else
        {
            ui -> HomePressureVal -> setText("0 Pa");
        }
    }
    else
    {
        if(ui->MillibarsButton->isChecked())
        {
            ui -> HomePressureVal -> setText(QString::number(lastPressure) + " mbars");
        }
        else
        {
            ui -> HomePressureVal -> setText(QString::number(lastPressure) + " P");
        }
    }

    //update air quality
    int curAQ;
    if(lastAqi == -10000)
    {
        curAQ = 0;
    }
    else
    {
        curAQ = lastAqi;
    }
    if(curAQ > 301) { ui -> HomeAQVal -> setText(QString::number(curAQ) + "\nHazardous"); }
    else if (curAQ > 201) { ui -> HomeAQVal -> setText(QString::number(curAQ) + "\nVery Unhealthy"); }
    else if (curAQ > 201) { ui -> HomeAQVal -> setText(QString::number(curAQ) + "\nUnhealthy"); }
    else if (curAQ > 201) { ui -> HomeAQVal -> setText(QString::number(curAQ) + "\nUnhealthy for Senstive Groups"); }
    else if (curAQ > 201) { ui -> HomeAQVal -> setText(QString::number(curAQ) + "\nModerate"); }
    else { ui -> HomeAQVal -> setText(QString::number(curAQ) + "\nGood");}

}

////////////////////////////////////////////////////////////////
/// Written By: Kenji Won
/// Dependencies: QtWidgets
/// Description: Updates text for latest Hum data
///////////////////////////////////////////////////////////////
//update humidity page with data from graphs
void MainWindow::updateHumidity()
{
    QDateTime datetime = QDateTime::currentDateTime();
    QDateTime lastUpdatedDate = QDateTime::currentDateTime();
    if(maxTimestamp != 0)
    {
    lastUpdatedDate = QDateTime::fromSecsSinceEpoch(maxTimestamp);
    }
    if(lastHum == -10000)
    {
        ui->HumidityVal->setText("Current Humidity:\n0%");
    }
    else
    {
        ui -> HumidityVal->setText("Current Humidity: \n" + QString::number(lastHum) + "%");
    }
    ui -> HumidityUpdated -> setText("Last updated: " + lastUpdatedDate.toString("ddd MMM d h:mm:ss AP yyyy"));
    ui->HumidityStats->setText("24 hour average: " + QString::number(avgHum).left(QString::number(avgHum).indexOf(".")+3) + "%\nPast 24 hour high: " + QString::number(maxHum) + "%\nPast 24 hour low: " + QString::number(minHum) + "%");
}

////////////////////////////////////////////////////////////////
/// Written By: Kenji Won
/// Dependencies: QtWidgets
/// Description: Updates text for latest temp data
///////////////////////////////////////////////////////////////
//update temp page with data from graphs
void MainWindow::updateTemperature()
{
    QDateTime datetime = QDateTime::currentDateTime();
    QDateTime lastUpdatedDate = QDateTime::currentDateTime();
    if(maxTimestamp != 0)
    {
    lastUpdatedDate = QDateTime::fromSecsSinceEpoch(maxTimestamp);
    }
    QString temp;
    if(lastTemp == -10000)
    {
        temp = "0";
    }
    else
    {
        temp = QString::number(lastTemp);
    }
    if(ui->FarenheitButton->isChecked())
    {
        ui->TemperatureVal->setText("Current Temperature: \n" + temp.left(temp.indexOf(".") + 3) + " °F");
    }
    else
    {
        ui->TemperatureVal->setText("Current Temperature: \n" + temp.left(temp.indexOf(".") + 3) + " °C");
    }
    ui -> TemperatureUpdated -> setText("Last updated: " + lastUpdatedDate.toString("ddd MMM d h:mm:ss AP yyyy"));

    if(ui->FarenheitButton->isChecked())
    {
        ui->TemperatureStats->setText("24 hour average: " + QString::number(avgTemp).left(QString::number(avgTemp).indexOf(".")+3) + " °F\nPast 24 hour high: " + QString::number(maxTemp) + " °F\nPast 24 hour low: " + QString::number(minTemp) + " °F");
    }
    else
    {
        ui->TemperatureStats->setText("24 hour average: " +  QString::number(avgTemp).left(QString::number(avgTemp).indexOf(".")+3) + " °C\nPast 24 hour high: " + QString::number(maxTemp) + " °C\nPast 24 hour low: " + QString::number(minTemp) + " °C");
    }
}


////////////////////////////////////////////////////////////////
/// Written By: Kenji Won
/// Dependencies: QtWidgets
/// Description: Updates text for latest wind data
///////////////////////////////////////////////////////////////
//update wind page with data from graphs
void MainWindow::updateWind()
{
    QDateTime datetime = QDateTime::currentDateTime();
    QDateTime lastUpdatedDate = QDateTime::currentDateTime();
    if(maxTimestamp != 0)
    {
    lastUpdatedDate = QDateTime::fromSecsSinceEpoch(maxTimestamp);
    }
    if(lastWindSpeed != -10000)
    {
        if(ui->MPHButton->isChecked())
        {
            ui -> WindVal -> setText("Current Wind Speed: \n" + QString::number(lastWindSpeed) + " MPH");
        }
        else
        {
            ui -> WindVal -> setText("Current Wind Speed: \n" + QString::number(lastWindSpeed) + " KM/H");
        }
    }
    else
    {
        if(ui->MPHButton->isChecked())
        {
            ui -> WindVal -> setText("Current Wind Speed: \n0 MPH");
        }
        else
        {
            ui -> WindVal -> setText("Current Wind Speed: \n0 KM/H");
        }
    }
    ui -> WindDirection->setText("Current Wind Direction: "  + windDirection);
    ui -> WindUpdated -> setText("Last updated: " + lastUpdatedDate.toString("ddd MMM d h:mm:ss AP yyyy"));
    if(ui->MPHButton->isChecked())
        {
            ui->WindStats->setText("24 hour average: " + QString::number(avgWindSpeed).left(QString::number(avgWindSpeed).indexOf(".")+5) + " MPH\nPast 24 hour high: " + QString::number(maxWindSpeed) + " MPH\nPast 24 hour low: " + QString::number(minWindSpeed) + " MPH");
        }
        else
        {
            ui->WindStats->setText("24 hour average: " + QString::number(avgWindSpeed).left(QString::number(avgWindSpeed).indexOf(".")+5) + " KM/H\nPast 24 hour high: " + (QString::number(maxWindSpeed).left(QString::number(maxWindSpeed).indexOf(".")+5)) + " KM/H\nPast 24 hour low: " + QString::number(minWindSpeed) + " KM/H");
        }

}

////////////////////////////////////////////////////////////////
/// Written By: Kenji Won
/// Dependencies: QtWidgets
/// Description: Updates text for latest Pressure data
///////////////////////////////////////////////////////////////
//update pressure page with data from graphs
void MainWindow::updatePressure()
{
    QDateTime datetime = QDateTime::currentDateTime();
    QDateTime lastUpdatedDate = QDateTime::currentDateTime();
    if(maxTimestamp != 0)
    {
    lastUpdatedDate = QDateTime::fromSecsSinceEpoch(maxTimestamp);
    }
    if(lastPressure == -10000)
    {
        if(ui->MillibarsButton->isChecked())
        {
            ui -> PressureVal -> setText("Current Pressure: \n0 mbars");
        }
        else
        {
            ui -> PressureVal -> setText("Current Pressure: \n0 Pa");
        }
    }
    else
    {
        if(ui->MillibarsButton->isChecked())
        {
            ui -> PressureVal -> setText("Current Pressure: \n" + QString::number(lastPressure) + " mbars");
        }
        else
        {
            ui -> PressureVal -> setText("Current Pressure: \n" + QString::number(lastPressure) + " P");
        }
    }
    ui -> PressureUpdated -> setText("Last updated: " + lastUpdatedDate.toString("ddd MMM d h:mm:ss AP yyyy"));

    if(ui->MillibarsButton->isChecked())
    {
        ui->PressureStats->setText("24 hour average: " + QString::number(avgPressure).left(QString::number(avgPressure).indexOf(".")+6) + " mbar\nPast 24 hour high: " + QString::number(maxPressure) + " mbar\nPast 24 hour low: " + QString::number(minPressure) + " mbar");
    }
    else
    {
        ui->PressureStats->setText("24 hour average: " + QString::number(avgPressure).left(QString::number(avgPressure).indexOf(".")+8) + " Pa\nPast 24 hour high: " + QString::number(maxPressure) + " Pa\nPast 24 hour low: " + QString::number(minPressure) + " Pa");
    }

}

////////////////////////////////////////////////////////////////
/// Written By: Kenji Won
/// Dependencies: QtWidgets
/// Description: Updates text for latest AQI data
///////////////////////////////////////////////////////////////
//update aq page with data from graphs
void MainWindow::updateAQ()
{
    QDateTime datetime = QDateTime::currentDateTime();
    QDateTime lastUpdatedDate = QDateTime::currentDateTime();
    if(maxTimestamp != 0)
    {
    lastUpdatedDate = QDateTime::fromSecsSinceEpoch(maxTimestamp);
    }
    int curAQ;
    if(lastAqi == -10000)
    {
        curAQ = 0;
    }
    else
    {
        curAQ = lastAqi;
    }
    if(curAQ > 301)
    {
        ui -> AQVal -> setText("Current AQI: \n" + QString::number(curAQ));
        ui -> AQState -> setText("Hazardous");
    }
    else if (curAQ > 251)
    {
        ui -> AQVal -> setText("Current AQI: \n" + QString::number(curAQ));
        ui -> AQState -> setText("Very Unhealthy\n");
    }
    else if (curAQ > 201)
    {
        ui -> AQVal -> setText("Current AQI: \n" + QString::number(curAQ));
        ui -> AQState -> setText("Unhealthy\n");
    }
    else if (curAQ > 151)
    {
        ui -> AQVal -> setText("Current AQI: \n" + QString::number(curAQ));
        ui -> AQState -> setText("Poor\n");
    }
    else if (curAQ > 101)
    {
        ui -> AQVal -> setText("Current AQI: \n" + QString::number(curAQ));
        ui -> AQState -> setText("Moderate\n");
    }
    else
    {
        ui -> AQVal -> setText("Current AQI: \n" + QString::number(curAQ));
        ui -> AQState -> setText("Good\n");
    }
    ui -> AQUpdated -> setText("Last updated: " + lastUpdatedDate.toString("ddd MMM d h:mm:ss AP yyyy"));
    ui->AQStats->setText("24 hour average: " + QString::number(avgAqi).left(QString::number(avgAqi).indexOf(".")+3) + "\nPast 24 hour high: " + QString::number(maxAqi) + "\nPast 24 hour low: " + QString::number(minAqi));
}

////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QtWidgets
/// Description: Updates text for latest gps data
///////////////////////////////////////////////////////////////
void MainWindow::updateGPS()
{
    QDateTime lastUpdatedDate;
    lastUpdatedDate = QDateTime::fromSecsSinceEpoch(updateTime);
    if(updateTime != 0)
    {
        ui -> GPS_Val -> setText("Current Location: \nNear " + CITYlocation + "\n" + "Last Updated:\n" + lastUpdatedDate.toString("MM/dd/yyyy h:mm ap") + "\nLatitude/Longitude:\n" + GPSlocation);
    }
}

////////////////////////////////////////////////////////////////
/// Written By: Kenji Won
/// Dependencies: QtWidgets
/// Description: Sets background color of Temp tab based on current temp value
///////////////////////////////////////////////////////////////
//sets the background color based off temp
void MainWindow::setTempBG()
{
    double tempVal;
    if(lastTemp == -10000)
    {
        tempVal = 0;
    }
    else
    {
        tempVal = lastTemp;
    }
    if(!ui->FarenheitButton->isChecked()) { tempVal = (tempVal *9/5) + 32;} //if temp is in celcius convert it to farenheight for temp color
    if(tempVal > 100)
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(180, 76, 14);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(180, 76, 14);}");

    }
    else if( tempVal > 85)
    {//edited color
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(203, 179, 24);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(203, 179, 24);}");
    }
    else if( tempVal > 65)
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(89, 163, 202);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(89, 163, 202);}");
    }
    else if( tempVal > 45)
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(107, 197, 208);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(107, 197, 208);}");
    }
    else if( tempVal > 25)
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(93, 97, 175);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(93, 97, 175);}");
    }
    else if( tempVal > -10)
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(28, 56, 148);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(28, 56, 148);}");
    }
    else
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(225,225,225);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(225,225,225);}");
    }
}

////////////////////////////////////////////////////////////////
/// Written By: Kenji Won
/// Dependencies: QtWidgets
/// Description: Sets background color of Hum tab based on current Hum value
///////////////////////////////////////////////////////////////
//sets the background color based off humidity
void MainWindow::setHumidityBG()
{
    int humidVal;
    if(lastHum == -10000)
    {
        humidVal = 0;
    }
    else
    {
        humidVal = lastHum;
    }
    if(humidVal < 10)
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(135, 172, 216);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(135, 172, 216);}");
    }
    else if (humidVal < 20)
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(98, 142, 223);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(98, 142, 223);}");

    }
    else if (humidVal < 30)
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(84, 157, 240);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(84, 157, 240);}");
    }
    else if (humidVal < 40)
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(55, 130, 217);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(55, 130, 217);}");
    }
    else if (humidVal < 50)
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(64, 81, 202);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(64, 81, 202);}");
    }
    else if (humidVal < 60)
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(31, 45, 151);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(31, 45, 151);}");
    }
    else
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(17, 32, 141);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(17, 32, 141);}");
    }
}

////////////////////////////////////////////////////////////////
/// Written By: Kenji Won
/// Dependencies: QtWidgets
/// Description: Sets background color of Wind tab based on current Wind values
///////////////////////////////////////////////////////////////
//sets the background color based off wind
void MainWindow::setWindBG()
{
    double windVal;
    if(lastWindSpeed != -10000)
    {
        windVal = lastWindSpeed;
    }
    else
    {
        windVal = 0;
    }
    if(!(ui->MPHButton->isChecked()))
    {
        //convert km/h to m/h
        windVal = windVal/1.609344;
    }
    if(windVal < 3)
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(174, 194, 191);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(174, 194, 191);}");
    }
    else if (windVal < 7)
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(145, 205, 195);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(145, 205, 195);}");
    }
    else if (windVal < 12)
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(109, 151, 179);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(109, 151, 179);}");
    }
    else if (windVal < 18)
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(102,255,51);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(102,255,51);}");
    }
    else if (windVal < 24)
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(203,254,50);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(203,254,50);}");
    }
    else if (windVal < 31)
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(226,254,153);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(226,254,153);}");
    }
    else if (windVal < 38)
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(255,255,153);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(255,255,153);}");
    }
    else if (windVal < 46)
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(251,220,87);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(251,220,87);}");
    }
    else
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(255,154,101);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(255,154,101);}");
    }
}

////////////////////////////////////////////////////////////////
/// Written By: Kenji Won
/// Dependencies: QtWidgets
/// Description: Sets background color of Pressure tab based on current pressure value
///////////////////////////////////////////////////////////////
//sets the background color based off pressure
void MainWindow::setPressureBG()
{
    double pressureVal;
    if(lastPressure != -10000)
    {
        pressureVal = lastPressure;
    }
    else
    {
        pressureVal = 0;
    }
    if(!ui->MillibarsButton->isChecked())
    {
        pressureVal = pressureVal/100;
    }
    if(pressureVal < 950)
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(70,117,235);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(70,117,235);}");
    }
    else if (pressureVal < 990)
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(117,151,235);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(117,151,235);}");
    }
    else if (pressureVal < 1020)
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(188,201,235);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(188,201,235);}");
    }
    else if (pressureVal < 1050)
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(235,188,194);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(235,188,194);}");
    }
    else
    {
       ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(235,106,125);}");
       ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(235,106,125);}");
    }
}

////////////////////////////////////////////////////////////////
/// Written By: Kenji Won
/// Dependencies: QtWidgets
/// Description: Sets background color of AQI tab based on current AQI value
///////////////////////////////////////////////////////////////
//sets the background color based off air quality (AQ)
void MainWindow::setAQBG()
{
    int curAQ;
    if(lastAqi == -10000)
    {
        curAQ = 0;
    }
    else
    {
        curAQ = lastAqi;
    }
    if(curAQ > 301)
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(125,75,89);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(125,75,89);}");
    }
    else if (curAQ > 201)
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(147,105,150);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(147,105,150);}");
    }
    else if (curAQ > 151)
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(255,102,102);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(255,102,102);}");
    }
    else if (curAQ > 101)
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(255,179,102);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(255,179,102);}");
    }
    else if (curAQ > 51)
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(255,255,179);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(255,255,179);}");
    }
    else
    {
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(116, 208, 116);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(116, 208, 116);}");
    }
}

////////////////////////////////////////////////////////////////
/// Written By: Kenji Won
/// Dependencies: QtWidgets
///////////////////////////////////////////////////////////////
//update the homepage
void MainWindow::on_pushButton_clicked()
{
    updateHomepage();
}

////////////////////////////////////////////////////////////////
/// Written By: Kenji Won
/// Dependencies: QtWidgets
/// Description: Refreshes tab with realtime data and adjusts graphs
///////////////////////////////////////////////////////////////
//Refreshes the tab with realtime data
void MainWindow::refreshCurrentTab()
{
    int index = ui->tabWidget->currentIndex();
    //0 - home, 1 - humidity, 2 - temp, 3 - wind, 4 - pressure, 5 - aq, 6 - settings
    if(index == 0)
    {
        updateHomepage();
        setTempBG();
    }
    else if(index == 1)
    {
        updateHumidity();
        setHumidityBG();
        ui->PlotHumidity->yAxis->setRange(0, 100);
        ui->PlotHumidity->xAxis->setRange(minTimestamp, maxTimestamp);
        plot();
    }
    else if(index == 2)
    {
        updateTemperature();
        setTempBG();
        ui->PlotTemperature->yAxis->setRange((minTemp-15), (maxTemp+15));
        ui->PlotTemperature->xAxis->setRange(minTimestamp, maxTimestamp);
        plot();
    }
    else if(index == 3)
    {
        updateWind();
        setWindBG();
        ui->PlotWindSpeedDirection->yAxis->setRange((minWindSpeed-5), (maxWindSpeed+5));
        ui->PlotWindSpeedDirection->xAxis->setRange(minTimestamp, maxTimestamp);
        plot();
    }
    else if(index == 4)
    {
        updatePressure();
        setPressureBG();
        if(check == 1)
        {
            ui->PlotPressure->yAxis->setRange((minPressure-100.0), (maxPressure+100.0));
        }
        else
        {
        ui->PlotPressure->yAxis->setRange((minPressure-1), (maxPressure+1));
        }
        ui->PlotPressure->xAxis->setRange(minTimestamp, maxTimestamp);
        plot();
    }
    else if(index == 5)
    {
        updateAQ();
        setAQBG();
        ui->PlotAirQuality->yAxis->setRange((minAqi-5), (maxAqi+5));
        ui->PlotAirQuality->xAxis->setRange(minTimestamp, maxTimestamp);
        plot();
    }
    else if(index == 6)
    {
        getGPSLocation();
        updateGPS();
        ui -> tabWidget -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(225,225,225);}");
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#ThemeWidgetForm{background-color: rgb(225,225,225);}");
    }
}

////////////////////////////////////////////////////////////////
/// Written By: Kenji Won
/// Dependencies: QtWidgets
/// Description: Gets data for corresponding sensor and tab to display to user
///////////////////////////////////////////////////////////////
//change color to default if user leave homepage or change color back if homepage is clicked on again
void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index == 0)
    {
        startDate = QDate::currentDate();
    }
    else if(index == 1)
    {
        getMinMaxAvg("humidity", getDate(QDate::currentDate()));
        getHttpSensor("humidity", getDate(QDate::currentDate()));
    }
    else if(index == 2)
    {
        getMinMaxAvg("temperature", getDate(QDate::currentDate()));
        getHttpSensor("temperature", getDate(QDate::currentDate()));
    }
    else if(index == 3)
    {
        getMinMaxAvg("windspeed", getDate(QDate::currentDate()));
        getHttpSensor("windspeed", getDate(QDate::currentDate()));
    }
    else if(index == 4)
    {
        getMinMaxAvg("pressure", getDate(QDate::currentDate()));
        getHttpSensor("pressure", getDate(QDate::currentDate()));
    }
    else if(index == 5)
    {
        getMinMaxAvg("aqi", getDate(QDate::currentDate()));
        getHttpSensor("aqi", getDate(QDate::currentDate()));
    }
    else
    {
        getGPSLocation();
    }
    refreshCurrentTab();
    ui->AboutFrame->setVisible(FALSE);
    ui->DeleteFrame->setVisible(FALSE);
}

////////////////////////////////////////////////////////////////
/// Written By: Kenji Won and Dalton Tracy
/// Dependencies: QString, QUrl, QNetworkAccessManager, QNetworkReply,
/// QByteArray, QJsonDocument, QJsonArray, QJssonObject, QDateTime
/// Description: Initial startup HTTP request. Gets all data for current date
/// to show data on homepage and all tabs
///////////////////////////////////////////////////////////////
void MainWindow::getHttp(QString http)
{
    QString date = getDate(QDate::currentDate());
    //QString date = "2022_03_04";
    QString url = requestUrl("all/", date);
    qnam = new QNetworkAccessManager();
    clearData();
    qnam->clearAccessCache();
    qnam->clearConnectionCache();
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

                windDirection = data["winddirection"].toString();
                if(data["timestamp"].toDouble() > maxTimestamp) {
                    maxTimestamp = data["timestamp"].toDouble();
                }
                /*lastAQI = data["aqi"].toDouble();
                lastHum = data["humidity"].toDouble();
                lastWindSpeed = data["windspeed"].toDouble();
                lastPressure = data["pressure"].toDouble();
                lastTemp = data["temperature"].toDouble();*/

            }
            reply->deleteLater();
            if(!qv_y2.isEmpty())
            {
            lastTemp = qv_y2.at(qv_y2.length()-1);
            lastHum = qv_y3.at(qv_y3.length()-1);
            lastWindSpeed = qv_y4.at(qv_y4.length()-1);
            lastPressure = qv_y5.at(qv_y5.length()-1);
            lastAqi = qv_y6.at(qv_y6.length()-1);
            }
            //ui->HomepagePlot->xAxis->setRange(minTimestamp, maxTimestamp); //in celsius
            ui->PlotTemperature->xAxis->setRange(minTimestamp, maxTimestamp);
            ui->PlotHumidity->xAxis->setRange(minTimestamp, maxTimestamp);
            ui->PlotWindSpeedDirection->xAxis->setRange(minTimestamp, maxTimestamp);
            ui->PlotPressure->xAxis->setRange(minTimestamp, maxTimestamp);
            ui->PlotAirQuality->xAxis->setRange(minTimestamp, maxTimestamp);

            //ui->HomepagePlot->yAxis->setRange(minTemp-5, maxTemp+5); //in celsius
            ui->PlotTemperature->yAxis->setRange((minTemp-15), (maxTemp+15));
            ui->PlotHumidity->yAxis->setRange(0, 100);
            ui->PlotWindSpeedDirection->yAxis->setRange((minWindSpeed-5), (maxWindSpeed+5));
            ui->PlotPressure->yAxis->setRange((minPressure-1), (maxPressure+1));
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
            if(check == 1)
            {
                convertPas();
                ui->PlotPressure->yAxis->setRange((minPressure-100.0), (maxPressure+100.0));
            }
            if(Mcheck == 1)
            {
                convertKph();
            }
            if(Fcheck == 1)
            {
                convertF();
            }
            plot();
            updateHomepage();
            //ui->AQIMeter->setValue(lastAQI);
        }
    );
    updateHomepage();
    qnam->get(request);
}

////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QString, QUrl, QNetworkAccessManager, QNetworkReply
/// Description: Sends HTTP request for all sensor data for a user set date
///////////////////////////////////////////////////////////////
void MainWindow::downloadFile()
{
    qnam = new QNetworkAccessManager();
    //QString downloadUrl = "https://flask-rews.herokuapp.com/devicedata/all/" + QString::number(deviceID) + "/2022_02_16";
    QString downloadUrl = requestUrl("all/", getDate(downloadDate));
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

//Download button
void MainWindow::on_DownloadAll_clicked()
{
    downloadFile();
}

////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QString, QUrl, QNetworkAccessManager, QNetworkReply,
/// QFile
/// Description: Writes data from reply to file
///////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QString
/// Description: Formats string for url
///////////////////////////////////////////////////////////////
QString MainWindow::requestUrl(QString type, QString date)
{
    QString defaultString = "https://flask-rews.herokuapp.com/devicedata/";
    QString deviceNum = (QString::number(deviceID) + "/");
    QString url;
    QString temp;
    url = defaultString.append(type);
    temp = url.append(deviceNum);
    url = temp.append(date);
    return url;
}

////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QString, QUrl, QNetworkAccessManager, QNetworkReply
/// Description: When called, sends request to HTTP Get to delete all data
///////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QString, QUrl, QNetworkAccessManager, QNetworkReply
/// Description: When called, reads HTTP requests reply and clears all data
///////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////////
/// Written By: Kenji Won
/// Dependencies: QDateTime
/// Description: UI element to show delete information window
///////////////////////////////////////////////////////////////
void MainWindow::on_DeleteAll_clicked()
{
    ui->AboutFrame->setVisible(FALSE);
    if(ui->DeleteFrame->isVisible()) { ui->DeleteFrame->setVisible(FALSE); }
    else { ui->DeleteFrame->setVisible(TRUE); }
    ui->DeleteText->setText("Are you sure you wish to delete all data?\nThis process is irreversible");
}

////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QDateTime
/// Description: Gets current date and formats it in string for url
///////////////////////////////////////////////////////////////
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
            dateS = QString::number(year) + "_0" + QString::number(month) + "_" + QString::number(day);
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

////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QDateTime
/// Description: Gets date selected from the user and formats
///  it in string for url
///////////////////////////////////////////////////////////////
QString MainWindow::getDate(QDate date)
{
    int day,month,year;
    QString dateS;
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
            dateS = QString::number(year) + "_0" + QString::number(month) + "_" + QString::number(day);
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

////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QString, QUrl, QNetworkAccessManager, QNetworkReply,
/// QByteArray, QJsonDocument, QJsonArray, QJssonObject
/// Description: Gets the min, max, avg over 24 hours from the webserver
/// using HTTP Get requests. Min, max, avg is used to set graph ranges and
/// display to user
///////////////////////////////////////////////////////////////
void MainWindow::getMinMaxAvg(QString sensor, QString date)
{
    QString pr = "stats/";
    //QString date = getCurrentDate();
    //QString url = requestUrl(pr.append(sensor.append("/")), date);
    QString url = requestUrl("stats/" + sensor + "/", date);
    qnam = new QNetworkAccessManager();
    url.remove(QChar('"'));
    QUrl processedURL = url;
    qDebug() << "Sending request to: " << url;
    request.setUrl(processedURL);
    qDebug() << sensor;
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



            qDebug() << buffer;
            for(QJsonArray::iterator record = jsonReply.begin(); record != jsonReply.end(); record++) {
                data = record->toObject();
                qDebug() << sensor;
                if(sensor == "temperature")
                {
                    if(!data["min"].isNull())
                    {
                    minTemp = data["min"].toDouble();
                    maxTemp = data["max"].toDouble();
                    avgTemp = data["average"].toDouble();
                    }
                }
                else if(sensor == "humidity")
                {
                    if(!data["min"].isNull())
                    {
                    minHum = data["min"].toDouble();
                    maxHum = data["max"].toDouble();
                    avgHum = data["average"].toDouble();
                    }
                }
                else if(sensor == "windspeed")
                {
                    if(!data["min"].isNull())
                    {
                    minWindSpeed = data["min"].toDouble();
                    maxWindSpeed = data["max"].toDouble();
                    avgWindSpeed = data["average"].toDouble();
                    }
                }
                else if(sensor == "pressure")
                {
                    if(!data["min"].isNull())
                    {
                    minPressure = data["min"].toDouble();
                    maxPressure = data["max"].toDouble();
                    avgPressure = data["average"].toDouble();
                    }
                }
                else if(sensor == "aqi")
                {
                    if(!data["min"].isNull())
                    {
                    minAqi = data["min"].toDouble();
                    maxAqi = data["max"].toDouble();
                    avgAqi = data["average"].toDouble();
                    }
                }
            }

            reply->deleteLater();
    });
    qnam->get(request);
}

////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QString, QUrl, QNetworkAccessManager, QNetworkReply,
/// QByteArray, QJsonDocument, QJsonArray, QJssonObject
/// Description: Gets the data from a specific sensor on a specific date,
/// default date is current date. Uses HTTP Get Requests
///////////////////////////////////////////////////////////////
void MainWindow::getHttpSensor(QString sensor, QString date)
{
    getMinMaxAvg(sensor, date);
    //QString date = getCurrentDate();
    QString url = requestUrl("sensor/" + sensor + "/", date);
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
                if(sensor == "temperature")
                {
                    addPoint(data["timestamp"].toDouble(), data["temperature"].toDouble(), qv_x2, qv_y2);
                }
                else if(sensor == "humidity")
                {
                    addPoint(data["timestamp"].toDouble(), data["humidity"].toDouble(), qv_x3, qv_y3);
                }
                else if(sensor == "windspeed")
                {
                    addPoint(data["timestamp"].toDouble(), data["windspeed"].toDouble(), qv_x4, qv_y4);
                    windDirection = data["winddirection"].toString();
                }
                else if(sensor == "pressure")
                {
                    addPoint(data["timestamp"].toDouble(), data["pressure"].toDouble(), qv_x5, qv_y5);
                }
                else if(sensor == "aqi")
                {
                    addPoint(data["timestamp"].toDouble(), data["aqi"].toDouble(), qv_x6, qv_y6);
                }

                if(data["timestamp"].toDouble() > maxTimestamp)
                {
                     maxTimestamp = data["timestamp"].toDouble();
                }
            }
            reply->deleteLater();

            if(sensor == "temperature")
            {
                if(!qv_y2.isEmpty())
                {
                lastTemp = qv_y2.at(qv_y2.length()-1);
                }
                ui->PlotTemperature->yAxis->setRange((minTemp-15), (maxTemp+15));
                ui->PlotTemperature->xAxis->setRange(minTimestamp, maxTimestamp);
            }
            else if(sensor == "humidity")
            {
                if(!qv_y3.isEmpty())
                {
                lastHum = qv_y3.at(qv_y3.length()-1);
                }
                ui->PlotHumidity->yAxis->setRange(0, 100);
                ui->PlotHumidity->xAxis->setRange(minTimestamp, maxTimestamp);
            }
            else if(sensor == "windspeed")
            {
                    if(!qv_y4.isEmpty())
                    {
                lastWindSpeed = qv_y4.at(qv_y4.length()-1);
                    }
                ui->PlotWindSpeedDirection->yAxis->setRange((minWindSpeed-5), (maxWindSpeed+5));
                ui->PlotWindSpeedDirection->xAxis->setRange(minTimestamp, maxTimestamp);
            }
            else if(sensor == "pressure")
            {
                        if(!qv_y5.isEmpty())
                        {
                lastPressure = qv_y5.at(qv_y5.length()-1);
                        }
                ui->PlotPressure->yAxis->setRange((minPressure-1), (maxPressure+1));
                ui->PlotPressure->xAxis->setRange(minTimestamp, maxTimestamp);
            }
            else if(sensor == "aqi")
            {
                            if(!qv_y6.isEmpty())
                            {
                lastAqi = qv_y6.at(qv_y6.length()-1);
                            }
                ui->PlotAirQuality->yAxis->setRange((minAqi-5), (maxAqi+5));
                ui->PlotAirQuality->xAxis->setRange(minTimestamp, maxTimestamp);
            }

            if(check == 1)
            {
                convertPas();
                ui->PlotPressure->yAxis->setRange((minPressure-100.0), (maxPressure+100.0));
            }
            if(Mcheck == 1)
            {
                convertKph();
            }
            if(Fcheck == 1)
            {
                convertF();
            }

            plot();

        }
    );
    qnam->get(request);

}

////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QString, QUrl, QNetworkAccessManager, QNetworkReply,
/// QByteArray, QJsonDocument, QJsonArray, QJssonObject
/// Description: Iterates over the dates selected by user and gets data
/// for the sensor over these dates to plot on graph. Uses HTTP Get request
///////////////////////////////////////////////////////////////
void MainWindow::multHttp(QString sensor)
{
    clearData();
    QDate tempdate = startDate;
    QString tday = getDate(tempdate);
    while(tempdate.day() <= endDate.day() && tempdate.month() <= endDate.month() && tempdate.year() == endDate.year())
    {
        getMinMaxAvg(sensor, tday);
        //QString date = getCurrentDate();
        QString url = requestUrl(("sensor/" + sensor + "/"), tday);
        qnam = new QNetworkAccessManager();
        //clearData();
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

                    if(sensor == "temperature")
                    {
                        addPoint(data["timestamp"].toDouble(), data[sensor].toDouble(), qv_x2, qv_y2);
                    }
                    else if(sensor == "humidity")
                    {
                        addPoint(data["timestamp"].toDouble(), data[sensor].toDouble(), qv_x3, qv_y3);
                    }
                    else if(sensor == "windspeed")
                    {
                        addPoint(data["timestamp"].toDouble(), data[sensor].toDouble(), qv_x4, qv_y4);
                        windDirection = data["winddirection"].toString();
                    }
                    else if(sensor == "pressure")
                    {
                        addPoint(data["timestamp"].toDouble(), data[sensor].toDouble(), qv_x5, qv_y5);
                    }
                    else if(sensor == "aqi")
                    {
                        addPoint(data["timestamp"].toDouble(), data[sensor].toDouble(), qv_x6, qv_y6);
                    }



                    if(data["timestamp"].toDouble() > maxTimestamp)
                    {
                         maxTimestamp = data["timestamp"].toDouble();
                    }
                }
                reply->deleteLater();
                if(sensor == "temperature")
                {
                    if(!qv_y2.isEmpty())
                    {
                    lastTemp = qv_y2.at(qv_y2.length()-1);
                    }
                    ui->PlotTemperature->yAxis->setRange((minTemp-15), (maxTemp+15));

                    ui->PlotTemperature->xAxis->setRange(minTimestamp, maxTimestamp);
                }
                else if(sensor == "humidity")
                {
                        if(!qv_y3.isEmpty())
                        {
                    lastHum = qv_y3.at(qv_y3.length()-1);
                        }
                    ui->PlotHumidity->yAxis->setRange(0, 100);

                    ui->PlotHumidity->xAxis->setRange(minTimestamp, maxTimestamp);
                }
                else if(sensor == "windspeed")
                {
                        if(!qv_y4.isEmpty())
                        {
                    lastWindSpeed = qv_y4.at(qv_y4.length()-1);
                        }
                    ui->PlotWindSpeedDirection->yAxis->setRange((minWindSpeed-5), (maxWindSpeed+5));

                    ui->PlotWindSpeedDirection->xAxis->setRange(minTimestamp, maxTimestamp);
                }
                else if(sensor == "pressure")
                {
                            if(!qv_y5.isEmpty())
                            {
                    lastPressure = qv_y5.at(qv_y5.length()-1);
                            }
                    ui->PlotPressure->yAxis->setRange((minPressure-1), (maxPressure+1));

                    ui->PlotPressure->xAxis->setRange(minTimestamp, maxTimestamp);
                }
                else if(sensor == "aqi")
                {
                                if(!qv_y6.isEmpty())
                                {
                    lastAqi = qv_y6.at(qv_y6.length()-1);
                                }
                    ui->PlotAirQuality->yAxis->setRange((minAqi-5), (maxAqi+5));

                    ui->PlotAirQuality->xAxis->setRange(minTimestamp, maxTimestamp);
                }

                plot();
            }
        );
        qnam->get(request);
        tempdate = tempdate.addDays(1);
        tday = getDate(tempdate);
    }
    if(check == 1)
    {
        convertPas();
        ui->PlotPressure->yAxis->setRange((minPressure-100.0), (maxPressure+100.0));
    }
    if(Mcheck == 1)
    {
        convertKph();
    }
    if(Fcheck == 1)
    {
        convertF();
    }
}

//Updating current page with realtime data
void MainWindow::timerEvent(QTimerEvent *event)
{
    refreshCurrentTab();
    if(startDate == QDate::currentDate())
    {
        getMinMaxAvg("humidity", getDate(QDate::currentDate()));
        getMinMaxAvg("temperature", getDate(QDate::currentDate()));
        getMinMaxAvg("windspeed", getDate(QDate::currentDate()));
        getMinMaxAvg("pressure", getDate(QDate::currentDate()));
        getMinMaxAvg("aqi", getDate(QDate::currentDate()));
        getHttp();
    }
}

//toggles the about page visibility
void MainWindow::on_AboutButton_clicked()
{
    ui->DeleteFrame->setVisible(FALSE);
    if(ui->AboutFrame->isVisible()) { ui->AboutFrame->setVisible(FALSE); }
    else { ui->AboutFrame->setVisible(TRUE); }
}

//closes the about page
void MainWindow::on_AboutClose_clicked()
{
    ui->AboutFrame->setVisible(FALSE);
}

//Delete Data Button
void MainWindow::on_DeleteConfirm_clicked()
{
    deleteAllData();
    ui->DeleteText->setText("All data has been deleted");
}

//Cancel Delete Data button
void MainWindow::on_DeleteDeny_clicked()
{
    ui->DeleteFrame->setVisible(FALSE);
}

//Start Date Humidity
void MainWindow::on_FirstDate_2_userDateChanged(const QDate &date)
{
    //Humidity Tab date boxes
    startDate = date;
    clearData();
    minTimestamp = 0;
    maxTimestamp = 0;
    getHttpSensor("humidity" ,getDate(date));
}

//End Date Humidity
void MainWindow::on_SecondDate_2_userDateChanged(const QDate &date)
{
    //Humidity Tab date boxes
    endDate = date;
    multHttp("humidity");
}

//Start Date Temperature
void MainWindow::on_FirstDate_userDateChanged(const QDate &date)
{
    startDate = date;
    clearData();
    minTimestamp = 0;
    maxTimestamp = 0;
    getHttpSensor("temperature", getDate(date));
}

//End Date Temperature
void MainWindow::on_SecondDate_userDateChanged(const QDate &date)
{
    endDate = date;
    multHttp("temperature");
}

//Start Date WindSpeed
void MainWindow::on_FirstDate_3_userDateChanged(const QDate &date)
{
    startDate = date;
    clearData();
    minTimestamp = 0;
    maxTimestamp = 0;
    getHttpSensor("windspeed", getDate(date));
}

//End Date WindSpeed
void MainWindow::on_SecondDate_3_userDateChanged(const QDate &date)
{
    endDate = date;
    multHttp("windspeed");
}

//End Date Pressure
void MainWindow::on_FirstDate_4_userDateChanged(const QDate &date)
{
    startDate = date;
    clearData();
    minTimestamp = 0;
    maxTimestamp = 0;
    getHttpSensor("pressure", getDate(date));
}

//End Date Pressure
void MainWindow::on_SecondDate_4_userDateChanged(const QDate &date)
{
    endDate = date;
    multHttp("pressure");
}

//Start Date AQI
void MainWindow::on_FirstDate_5_userDateChanged(const QDate &date)
{
    startDate = date;
    clearData();
    minTimestamp = 0;
    maxTimestamp = 0;
    getHttpSensor("aqi", getDate(date));
}

//End date AQI
void MainWindow::on_SecondDate_5_userDateChanged(const QDate &date)
{
    endDate = date;
    multHttp("aqi");
}


////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QString, QUrl, QNetworkAccessManager, QNetworkReply,
/// QByteArray, QJsonDocument, QJsonArray, QJssonObject
/// Description: Uses GET HTTP request to get data on city, last updated
///  time, and latitude/longitude
///////////////////////////////////////////////////////////////
void MainWindow::getGPSLocation()
{
    QString url = "https://flask-rews.herokuapp.com/devicedata/metadata/location/"  + QString::number(deviceID);
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



            qDebug() << buffer;
            for(QJsonArray::iterator record = jsonReply.begin(); record != jsonReply.end(); record++) {
                data = record->toObject();
                if(!data["location"].isNull() && updateTime != data["lastupdated"].toDouble())
                {
                CITYlocation = data["city"].toString();
                updateTime = data["lastupdated"].toDouble();
                GPSlocation = data["location"].toString();
                }
            }

            reply->deleteLater();
    });
    qnam->get(request);
}


//Sets download date to whatever user selected
void MainWindow::on_DownloadDate_userDateChanged(const QDate &date)
{
    downloadDate = date;
}

