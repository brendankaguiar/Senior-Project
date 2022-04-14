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
        avgTemp = 0,
        updateTime = 0;
QString windDirection;
QString GPSlocation;
int digit = 1;
int button = 100;
bool check, Mcheck, Fcheck = 0;
QDate startDate = QDate::currentDate();
QDate endDate = QDate::currentDate();

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
   ui->PlotTemperature->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
   ui->PlotHumidity->graph(0)->setPen(QPen(Qt::blue));
   ui->PlotHumidity->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
   ui->PlotWindSpeedDirection->graph(0)->setPen(QPen(Qt::blue));
   ui->PlotWindSpeedDirection->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
   ui->PlotPressure->graph(0)->setPen(QPen(Qt::blue));
   ui->PlotPressure->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
   ui->PlotAirQuality->graph(0)->setPen(QPen(Qt::blue));
   ui->PlotAirQuality->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
   getHttp("https://flask-rews.herokuapp.com/devicedata/latest/0");
   qnam->setAutoDeleteReplies(true);

   ui->AboutFrame->setVisible(FALSE);
   ui->DeleteFrame->setVisible(FALSE);
   ui->HTTPButton->setVisible(FALSE);
   ui->UpdateHomepage->setVisible(FALSE);
   timerId = startTimer(11000);

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
    maxTimestamp = 0;
}

////////////////////////////////////////////////////////////////
/// Written By: Nicholas Ang
/// Dependencies: QtWidgets, QCustomPlot, QVector
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
    while(i < qv_y2.length())
    {
        qv_y2.replace(i, (((qv_y2.at(i)*9)/5) + 32));
        i++;
    }
    minTemp = ((minTemp*9)/5)+ 32;
    maxTemp = ((maxTemp*9)/5)+ 32;
    avgTemp = ((avgTemp*9)/5)+ 32;
    ui->PlotTemperature->yAxis->setRange((minTemp-5.0), (maxTemp+5.0));
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
    while(i < qv_y2.length())
    {
        qv_y2.replace(i, (((qv_y2.at(i)-32)*5)/9));
        i++;
    }
    minTemp = ((minTemp-32)*5)/9;
    maxTemp = ((maxTemp-32)*5)/9;
    avgTemp = ((avgTemp-32)*5)/9;
    ui->PlotTemperature->yAxis->setRange((minTemp-5.0), (maxTemp+5.0));
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
    while(i < qv_y4.length())
    {
        qv_y4.replace(i, (qv_y4.at(i)/1.609));
        i++;
    }
    minWindSpeed = minWindSpeed/1.609;
    maxWindSpeed = maxWindSpeed/1.609;
    avgWindSpeed = minWindSpeed/1.609;
    ui->PlotWindSpeedDirection->yAxis->setRange((minWindSpeed-5.0), (maxWindSpeed+5.0));
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
    minWindSpeed = minWindSpeed*1.609;
    maxWindSpeed = maxWindSpeed*1.609;
    avgWindSpeed = minWindSpeed*1.609;
    ui->PlotWindSpeedDirection->yAxis->setRange((minWindSpeed-5.0), (maxWindSpeed+5.0));
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
    minPressure = minPressure/100;
    maxPressure = maxPressure/100;
    avgPressure = minPressure/100;
    ui->PlotPressure->yAxis->setRange((minPressure-100.0), (maxPressure+100.0));
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
    minPressure = minPressure*100;
    maxPressure = maxPressure*100;
    avgPressure = minPressure*100;
    ui->PlotPressure->yAxis->setRange((minPressure-100.0), (maxPressure+100.0));
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
    check = checked;
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
    Mcheck = Mchecked;
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

//update homepage with data from graphs
void MainWindow::updateHomepage()
{
    //set the temp @ homescreen
    QString temp;

    if(qv_y2.isEmpty())
    {
        temp = "0";
    }
    else
    {
        temp = QString::number(qv_y2.at(qv_y2.length()-1));
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
    if(datetime.time().toString().leftRef(2).toInt() > 12)
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
        ui->HomeWindDir->setText("Direction: " + windDirection);
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
        ui->HomeWindDir->setText("Direction: " + windDirection);
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

//update humidity page with data from graphs
void MainWindow::updateHumidity()
{
    QDateTime datetime = QDateTime::currentDateTime();
    if(qv_y3.isEmpty())
    {
        ui->HumidityVal->setText("Current Humidity: 0%");
    }
    else
    {
        ui -> HumidityVal->setText("Current Humidity: \n" + QString::number(qv_y3.at(qv_y3.length()-1)) + "%");
    }
    ui -> HumidityUpdated -> setText("Last updated: " + datetime.toString());
    ui->HumidityStats->setText("24 hour average: " + QString::number(avgHum).left(QString::number(avgHum).indexOf(".")+3) + "%\nPast 24 hour high: " + QString::number(maxHum) + "%\nPast 24 hour low: " + QString::number(minHum) + "%");
}

//update temp page with data from graphs
void MainWindow::updateTemperature()
{
    QDateTime datetime = QDateTime::currentDateTime();
    QString temp;
    if(qv_y2.isEmpty())
    {
        temp = "0";
    }
    else
    {
        temp = QString::number(qv_y2.at(qv_y2.length()-1));
    }
    if(ui->FarenheitButton->isChecked())
    {
        ui->TemperatureVal->setText("Current Temperature: \n" + temp.left(temp.indexOf(".") + 3) + " °F");
    }
    else
    {
        ui->TemperatureVal->setText("Current Temperature: \n" + temp.left(temp.indexOf(".") + 3) + " °C");
    }
    ui -> TemperatureUpdated -> setText("Last updated: " + datetime.toString());

    if(ui->FarenheitButton->isChecked())
    {
        ui->TemperatureStats->setText("24 hour average: " + QString::number(avgTemp).left(QString::number(avgTemp).indexOf(".")+3) + " °F\nPast 24 hour high: " + QString::number(maxTemp) + " °F\nPast 24 hour low: " + QString::number(minTemp) + " °F");
    }
    else
    {
        ui->TemperatureStats->setText("24 hour average: " +  QString::number(avgTemp).left(QString::number(avgTemp).indexOf(".")+3) + " °C\nPast 24 hour high: " + QString::number(maxTemp) + " °C\nPast 24 hour low: " + QString::number(minTemp) + " °C");
    }
}



//update wind page with data from graphs
void MainWindow::updateWind()
{
    QDateTime datetime = QDateTime::currentDateTime();
    if(!qv_y4.isEmpty())
    {
        if(ui->MPHButton->isChecked())
        {
            ui -> WindVal -> setText("Current Wind Speed: \n" + QString::number(qv_y4.at(qv_y4.length()-1)) + " MPH");
        }
        else
        {
            ui -> WindVal -> setText("Current Wind Speed: \n" + QString::number(qv_y4.at(qv_y4.length()-1)) + " KM/H");
        }
    }
    ui -> WindDirection->setText("Current Wind Direction: "  + windDirection);
    ui -> WindUpdated -> setText("Last updated: " + datetime.toString());
    if(ui->MPHButton->isChecked())
        {
            ui->WindStats->setText("24 hour average: " + QString::number(avgWindSpeed).left(QString::number(avgWindSpeed).indexOf(".")+3) + " MPH\nPast 24 hour high: " + QString::number(maxWindSpeed) + " MPH\nPast 24 hour low: " + QString::number(minWindSpeed) + " MPH");
        }
        else
        {
            ui->WindStats->setText("24 hour average: " + QString::number(avgWindSpeed).left(QString::number(avgWindSpeed).indexOf(".")+3) + " KM/H\nPast 24 hour high: " + QString::number(maxWindSpeed) + " KM/H\nPast 24 hour low: " + QString::number(minWindSpeed) + " KM/H");
        }

}


//update pressure page with data from graphs
void MainWindow::updatePressure()
{
    QDateTime datetime = QDateTime::currentDateTime();
    if(qv_y5.isEmpty())
    {
        if(ui->MillibarsButton->isChecked())
        {
            ui -> PressureVal -> setText("0 mbars");
        }
        else
        {
            ui -> PressureVal -> setText("0 P");
        }
    }
    else
    {
        if(ui->MillibarsButton->isChecked())
        {
            ui -> PressureVal -> setText("Current Pressure: \n" + QString::number(qv_y5.at(qv_y5.length()-1)) + " mbars");
        }
        else
        {
            ui -> PressureVal -> setText("Current Pressure: \n" + QString::number(qv_y5.at(qv_y5.length()-1)) + " P");
        }
    }
    ui -> PressureUpdated -> setText("Last updated: " + datetime.toString());

    if(ui->MillibarsButton->isChecked())
    {
        ui->PressureStats->setText("24 hour average: " + QString::number(avgPressure).left(QString::number(avgPressure).indexOf(".")+3) + " mbar\nPast 24 hour high: " + QString::number(maxPressure) + " mbar\nPast 24 hour low: " + QString::number(minPressure) + " mbar");
    }
    else
    {
        ui->PressureStats->setText("24 hour average: " + QString::number(avgPressure).left(QString::number(avgPressure).indexOf(".")+3) + " Pa\nPast 24 hour high: " + QString::number(maxPressure) + " Pa\nPast 24 hour low: " + QString::number(minPressure) + " Pa");
    }

}

//update aq page with data from graphs
void MainWindow::updateAQ()
{
    QDateTime datetime = QDateTime::currentDateTime();
    int curAQ;
    if(qv_y6.isEmpty())
    {
        curAQ = 0;
    }
    else
    {
        curAQ = qv_y6.at(qv_y6.length()-1);
    }
    if(curAQ > 301)
    {
        ui -> AQVal -> setText("Current AQI: \n" + QString::number(curAQ));
        ui -> AQState -> setText("Hazardous");
    }
    else if (curAQ > 201)
    {
        ui -> AQVal -> setText("Current AQI: \n" + QString::number(curAQ));
        ui -> AQState -> setText("Very Unhealthy");
    }
    else if (curAQ > 201)
    {
        ui -> AQVal -> setText("Current AQI: \n" + QString::number(curAQ));
        ui -> AQState -> setText("Unhealthy");
    }
    else if (curAQ > 201)
    {
        ui -> AQVal -> setText("Current AQI: \n" + QString::number(curAQ));
        ui -> AQState -> setText("Unhealthy for Senstive Groups");
    }
    else if (curAQ > 201)
    {
        ui -> AQVal -> setText("Current AQI: \n" + QString::number(curAQ));
        ui -> AQState -> setText("Moderate");
    }
    else
    {
        ui -> AQVal -> setText("Current AQI: \n" + QString::number(curAQ));
        ui -> AQState -> setText("Good");
    }
    ui -> AQUpdated -> setText("Last updated: " + datetime.toString());
     ui->AQStats->setText("24 hour average: " + QString::number(avgAqi).left(QString::number(avgAqi).indexOf(".")+3) + "\nPast 24 hour high: " + QString::number(maxAqi) + "\nPast 24 hour low: " + QString::number(minAqi));
}

void MainWindow::updateGPS()
{
    QDateTime lastUpdatedDate;
    lastUpdatedDate = QDateTime::fromSecsSinceEpoch(updateTime);
    if(updateTime != 0)
    {
        ui -> GPS_Val -> setText("Current Location: \nNear " + GPSlocation + "\n" + "Last Updated:\n" + lastUpdatedDate.toString("MM/dd/yyyy h:mm ap"));
    }
}

//sets the background color based off temp
void MainWindow::setTempBG()
{
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

//sets the background color based off humidity
void MainWindow::setHumidityBG()
{
    int humidVal;
    if(qv_y3.isEmpty())
    {
        humidVal = 0;
    }
    else
    {
        humidVal = (qv_y3.at(qv_y3.length()-1));
    }
    if(humidVal < 10) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(152,192,240);}"); }
    else if (humidVal < 20) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(117,177,240);}"); }
    else if (humidVal < 30) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(103,167,240);}"); }
    else if (humidVal < 40) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(95,162,240);}"); }
    else if (humidVal < 50) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(84,154,240);}"); }
    else if (humidVal < 60) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(86,152,239);}"); }
    else { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(20,124,235);}"); }
}

//sets the background color based off wind
void MainWindow::setWindBG()
{
    double windVal = 0;
    if(!qv_y4.isEmpty())
    {
        windVal = (qv_y4.at(qv_y4.length()-1));;
    }
    if(!(ui->MPHButton->isChecked()))
    {
        //convert km/h to m/h
        windVal = windVal/1.609344;
    }
    if(windVal < 3) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(103,203,255);}"); }
    else if (windVal < 7) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(120,207,193);}"); }
    else if (windVal < 12) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(0,228,1);}"); }
    else if (windVal < 18) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(102,255,51);}"); }
    else if (windVal < 24) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(203,254,50);}"); }
    else if (windVal < 31) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(226,254,153);}"); }
    else if (windVal < 38) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(255,255,153);}"); }
    else if (windVal < 46) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(251,220,87);}"); }
    else { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(255,154,101);}"); }
}

//sets the background color based off pressure
void MainWindow::setPressureBG()
{
    double pressureVal = 0;
    if(!qv_y5.isEmpty())
    {
        pressureVal = (qv_y5.at(qv_y5.length()-1));
    }
    if(!ui->MillibarsButton->isChecked())
    {
        pressureVal = pressureVal/100;
    }
    if(pressureVal < 950) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(70,117,235);}"); }
    else if (pressureVal < 990) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(117,151,235);}"); }
    else if (pressureVal < 1020) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(188,201,235);}"); }
    else if (pressureVal < 1050) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(235,188,194);}"); }
    else { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(235,106,125);}"); }
}

//sets the background color based off air quality (AQ)
void MainWindow::setAQBG()
{
    int curAQ;
    if(qv_y6.isEmpty())
    {
        curAQ = 0;
    }
    else
    {
        curAQ = qv_y6.at(qv_y6.length()-1);
    }
    if(curAQ > 301) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(125,75,89);}"); }
    else if (curAQ > 201) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(147,105,150);}"); }
    else if (curAQ > 201) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(255,102,102);}"); }
    else if (curAQ > 201) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(255,179,102);}"); }
    else if (curAQ > 201) { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(255,255,179);}"); }
    else { ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(87,217,87);}"); }
}

//update the homepage
void MainWindow::on_pushButton_clicked()
{
    updateHomepage();
}

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
        ui->PlotHumidity->yAxis->setRange((minHum-5), (maxHum+5));
        ui->PlotHumidity->xAxis->setRange(minTimestamp, maxTimestamp);
        plot();
    }
    else if(index == 2)
    {
        updateTemperature();
        setTempBG();
        ui->PlotTemperature->yAxis->setRange((minTemp-5), (maxTemp+5));
        ui->PlotTemperature->xAxis->setRange(minTimestamp, maxTimestamp);
        plot();
    }
    else if(index == 3)
    {
        updateWind();
        setWindBG();
        ui->PlotTemperature->yAxis->setRange((minWindSpeed-5), (maxWindSpeed+5));
        ui->PlotTemperature->xAxis->setRange(minTimestamp, maxTimestamp);
        plot();
    }
    else if(index == 4)
    {
        updatePressure();
        setPressureBG();
        ui->PlotTemperature->yAxis->setRange((minPressure-100), (maxPressure+100));
        ui->PlotTemperature->xAxis->setRange(minTimestamp, maxTimestamp);
        plot();
    }
    else if(index == 5)
    {
        updateAQ();
        setAQBG();
        ui->PlotTemperature->yAxis->setRange((minAqi-5), (maxAqi+5));
        ui->PlotTemperature->xAxis->setRange(minTimestamp, maxTimestamp);
        plot();
    }
    else if(index == 6)
    {
        getGPSLocation();
        updateGPS();
        ui -> ThemeWidgetForm -> setStyleSheet("QWidget#Homepage, QWidget#Humidity, QWidget#Temperature, QWidget#Wind, QWidget#Pressure, QWidget#AirQuality, QWidget#Settings{background-color: rgb(225,225,225);}");
    }
}
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
    }
    else if(index == 2)
    {
        getMinMaxAvg("temperature", getDate(QDate::currentDate()));
    }
    else if(index == 3)
    {
        getMinMaxAvg("windspeed", getDate(QDate::currentDate()));
    }
    else if(index == 4)
    {
        getMinMaxAvg("pressure", getDate(QDate::currentDate()));
    }
    else if(index == 5)
    {
        getMinMaxAvg("aqi", getDate(QDate::currentDate()));
    }
    else
    {
        getGPSLocation();
    }
    refreshCurrentTab();
    ui->AboutFrame->setVisible(FALSE);
    ui->DeleteFrame->setVisible(FALSE);
}

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
            if(check == 1)
            {
                convertPas();
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

void MainWindow::downloadFile()
{
    qnam = new QNetworkAccessManager();
    //QString downloadUrl = "https://flask-rews.herokuapp.com/devicedata/all/0/2022_02_16";
    QString downloadUrl = requestUrl("all/", getDate(QDate::currentDate()));
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
    ui->AboutFrame->setVisible(FALSE);
    if(ui->DeleteFrame->isVisible()) { ui->DeleteFrame->setVisible(FALSE); }
    else { ui->DeleteFrame->setVisible(TRUE); }
    ui->DeleteText->setText("Are you sure you wish to delete all data?\nThis process is irreversible");
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
                ui->PlotTemperature->yAxis->setRange((minTemp-5), (maxTemp+5));
                ui->PlotTemperature->xAxis->setRange(minTimestamp, maxTimestamp);
            }
            else if(sensor == "humidity")
            {
                ui->PlotHumidity->yAxis->setRange((minHum-5), (maxHum+5));
                ui->PlotHumidity->xAxis->setRange(minTimestamp, maxTimestamp);
            }
            else if(sensor == "windspeed")
            {
                ui->PlotWindSpeedDirection->yAxis->setRange((minWindSpeed-5), (maxWindSpeed+5));
                ui->PlotWindSpeedDirection->xAxis->setRange(minTimestamp, maxTimestamp);
            }
            else if(sensor == "pressure")
            {
                ui->PlotPressure->yAxis->setRange((minPressure-100), (maxPressure+100));
                ui->PlotPressure->xAxis->setRange(minTimestamp, maxTimestamp);
            }
            else if(sensor == "aqi")
            {
                ui->PlotAirQuality->yAxis->setRange((minAqi-5), (maxAqi+5));
                ui->PlotAirQuality->xAxis->setRange(minTimestamp, maxTimestamp);
            }

            if(check == 1)
            {
                convertPas();
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
                    ui->PlotTemperature->yAxis->setRange((minTemp-5), (maxTemp+5));

                    ui->PlotTemperature->xAxis->setRange(minTimestamp, maxTimestamp);
                }
                else if(sensor == "humidity")
                {
                    ui->PlotHumidity->yAxis->setRange((minHum-5), (maxHum+5));

                    ui->PlotHumidity->xAxis->setRange(minTimestamp, maxTimestamp);
                }
                else if(sensor == "windspeed")
                {
                    ui->PlotWindSpeedDirection->yAxis->setRange((minWindSpeed-5), (maxWindSpeed+5));

                    ui->PlotWindSpeedDirection->xAxis->setRange(minTimestamp, maxTimestamp);
                }
                else if(sensor == "pressure")
                {
                    ui->PlotPressure->yAxis->setRange((minPressure-100), (maxPressure+100));

                    ui->PlotPressure->xAxis->setRange(minTimestamp, maxTimestamp);
                }
                else if(sensor == "aqi")
                {
                    ui->PlotAirQuality->yAxis->setRange((minAqi-5), (maxAqi+5));

                    ui->PlotAirQuality->xAxis->setRange(minTimestamp, maxTimestamp);
                }

                if(check == 1)
                {
                    convertPas();
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
        tempdate = tempdate.addDays(1);
        tday = getDate(tempdate);
    }
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    refreshCurrentTab();
    if(startDate == QDate::currentDate())
    {
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


void MainWindow::on_DeleteConfirm_clicked()
{
    deleteAllData();
    ui->DeleteText->setText("All data has been deleted");
}


void MainWindow::on_DeleteDeny_clicked()
{
    ui->DeleteFrame->setVisible(FALSE);
}

void MainWindow::on_FirstDate_2_userDateChanged(const QDate &date)
{
    //Humidity Tab date boxes
    startDate = date;
    clearData();
    minTimestamp = 0;
    maxTimestamp = 0;
    getHttpSensor("humidity" ,getDate(date));
}


void MainWindow::on_SecondDate_2_userDateChanged(const QDate &date)
{
    //Humidity Tab date boxes
    endDate = date;
    multHttp("humidity");
}

void MainWindow::on_FirstDate_userDateChanged(const QDate &date)
{
    startDate = date;
    clearData();
    minTimestamp = 0;
    maxTimestamp = 0;
    getHttpSensor("temperature", getDate(date));
    //plot();
}


void MainWindow::on_SecondDate_userDateChanged(const QDate &date)
{
    endDate = date;
    multHttp("temperature");
}


void MainWindow::on_FirstDate_3_userDateChanged(const QDate &date)
{
    startDate = date;
    clearData();
    minTimestamp = 0;
    maxTimestamp = 0;
    getHttpSensor("windspeed", getDate(date));
}


void MainWindow::on_SecondDate_3_userDateChanged(const QDate &date)
{
    endDate = date;
    multHttp("windspeed");
}


void MainWindow::on_FirstDate_4_userDateChanged(const QDate &date)
{
    startDate = date;
    clearData();
    minTimestamp = 0;
    maxTimestamp = 0;
    getHttpSensor("pressure", getDate(date));
}


void MainWindow::on_SecondDate_4_userDateChanged(const QDate &date)
{
    endDate = date;
    multHttp("pressure");
}


void MainWindow::on_FirstDate_5_userDateChanged(const QDate &date)
{
    startDate = date;
    clearData();
    minTimestamp = 0;
    maxTimestamp = 0;
    getHttpSensor("aqi", getDate(date));
}


void MainWindow::on_SecondDate_5_userDateChanged(const QDate &date)
{
    endDate = date;
    multHttp("aqi");
}

void MainWindow::getGPSLocation()
{
    QString url = "https://flask-rews.herokuapp.com/devicedata/metadata/location/0";
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
                GPSlocation = data["location"].toString();
                updateTime = data["lastupdated"].toDouble();
                }
            }

            reply->deleteLater();
    });
    qnam->get(request);
}

void MainWindow::on_TempDebug_clicked()
{
    double value = ui->DebugBox->toPlainText().toDouble();
    addPoint(QDateTime::currentMSecsSinceEpoch(), value, qv_x2, qv_y2);
    plot();
}


void MainWindow::on_HumidityDebug_clicked()
{
    double value = ui->DebugBox->toPlainText().toDouble();
    addPoint(QDateTime::currentMSecsSinceEpoch(), value, qv_x3, qv_y3);
    plot();
}


void MainWindow::on_WindDebug_clicked()
{
    double value = ui->DebugBox->toPlainText().toDouble();
    addPoint(QDateTime::currentMSecsSinceEpoch(), value, qv_x4, qv_y4);
    plot();
}


void MainWindow::on_PressureDebug_clicked()
{
    double value = ui->DebugBox->toPlainText().toDouble();
    addPoint(QDateTime::currentMSecsSinceEpoch(), value, qv_x5, qv_y5);
    plot();
}


void MainWindow::on_AQDebug_clicked()
{
    double value = ui->DebugBox->toPlainText().toDouble();
    addPoint(QDateTime::currentMSecsSinceEpoch(), value, qv_x6, qv_y6);
    plot();
}

