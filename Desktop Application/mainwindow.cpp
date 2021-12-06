#include "mainwindow.h"
#include "ui_mainwindow.h"
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

int count = 1;
int digit = 1;
int button = 100;
QPen pen;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      qnam(new QNetworkAccessManager)
{
   ui->setupUi(this);

   ui->HomepagePlot->addGraph();
   ui->PlotTemperature->addGraph();
   ui->PlotHumidity->addGraph();
   ui->PlotWindSpeedDirection->addGraph();
   ui->PlotPressure->addGraph();
   ui->PlotAirQuality->addGraph();

   ui->HomepagePlot->xAxis->setRange(0, 100);
   ui->HomepagePlot->yAxis->setRange(-50, 100);
   ui->PlotTemperature->xAxis->setRange(0, 100);
   ui->PlotTemperature->yAxis->setRange(-50, 100);
   ui->PlotHumidity->xAxis->setRange(0, 100);
   ui->PlotHumidity->yAxis->setRange(0, 100);
   ui->PlotWindSpeedDirection->xAxis->setRange(0, 100);
   ui->PlotWindSpeedDirection->yAxis->setRange(0, 30);
   ui->PlotPressure->xAxis->setRange(0, 100);
   ui->PlotPressure->yAxis->setRange(0, 1000);
   ui->PlotAirQuality->xAxis->setRange(0, 100);
   ui->PlotAirQuality->yAxis->setRange(0, 500);

   ui->HomepagePlot->graph(0)->setPen(QPen(Qt::blue));
   ui->HomepagePlot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addPoint(double x, double y, QVector<double> &xV, QVector<double> &yV)
{
    xV.begin();
    yV.begin();
    xV.append(x);
    yV.append(y);
}

void MainWindow::clearData()
{
    count = 1;
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

void MainWindow::plot()
{
    ui->HomepagePlot->graph(0)->setData(qv_x,qv_y);
    ui->PlotTemperature->graph(0)->setData(qv_x2,qv_y2);
    ui->PlotHumidity->graph(0)->setData(qv_x3,qv_y3);
    ui->PlotWindSpeedDirection->graph(0)->setData(qv_x4,qv_y4);
    ui->PlotPressure->graph(0)->setData(qv_x5,qv_y5);
    ui->PlotAirQuality->graph(0)->setData(qv_x6,qv_y6);

    ui->HomepagePlot->replot();
    ui->HomepagePlot->update();
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

    ui->lcdNumber->display(qv_y.at(qv_y.length()-1));
    ui->LCDTemperature->display(qv_y2.at(qv_y2.length()-1));
    ui->LCDHumidity->display(qv_y3.at(qv_y3.length()-1));
    ui->LCDWind->display(qv_y4.at(qv_y4.length()-1));
    ui->LCDPressure->display(qv_y5.at(qv_y5.length()-1));
    ui->LCDAirQuality->display(qv_y6.at(qv_y6.length()-1));
}

int MainWindow::newData()
{
    return rand() % 100;
}

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

void MainWindow::on_HTTPButton_clicked()
{
    QString url = ui->HTTPTextInput->toPlainText();
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
            double count = 1;


            clearData();
            for(QJsonArray::iterator record = jsonReply.begin(); record != jsonReply.end(); record++) {
                data = record->toObject();
//                qDebug() << data["winddirection"];
//                qDebug() << data["temperature"];
//                qDebug() << data["timestamp"];
                addPoint(count, data["temperature"].toDouble(), qv_x, qv_y);
                addPoint(count, data["temperature"].toDouble(), qv_x2, qv_y2);
                addPoint(count, data["humidity"].toDouble(), qv_x3, qv_y3);
                addPoint(count, data["windspeed"].toDouble(), qv_x4, qv_y4);
                addPoint(count, data["pressure"].toDouble(), qv_x5, qv_y5);
                addPoint(count, data["aqi"].toDouble(), qv_x6, qv_y6);
                qDebug() << qv_y;
                plot();
                count++;
            }
            reply->deleteLater();
        }
    );
    qnam->get(request);

}

