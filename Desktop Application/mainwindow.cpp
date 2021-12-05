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
   ui->HomepagePlot->yAxis->setRange(0, 100);
   ui->PlotTemperature->xAxis->setRange(0, 100);
   ui->PlotTemperature->yAxis->setRange(0, 100);
   ui->PlotHumidity->xAxis->setRange(0, 100);
   ui->PlotHumidity->yAxis->setRange(0, 100);
   ui->PlotWindSpeedDirection->xAxis->setRange(0, 100);
   ui->PlotWindSpeedDirection->yAxis->setRange(0, 100);
   ui->PlotPressure->xAxis->setRange(0, 100);
   ui->PlotPressure->yAxis->setRange(0, 100);
   ui->PlotAirQuality->xAxis->setRange(0, 100);
   ui->PlotAirQuality->yAxis->setRange(0, 100);

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
    xV.append(x);
    yV.append(y);
}

void MainWindow::clearData()
{
    qv_x.clear();
    qv_y.clear();
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

}

int MainWindow::newData()
{
    return rand() % 100;
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
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
    while(i < qvector_temp.length())
    {
        qvector_temp.replace(i, (((qvector_temp.at(i)*9)/5) + 32));
        i++;
    }
}

void MainWindow::convertC()
{
    int i = 0;
    while(i < qvector_temp.length())
    {
        qvector_temp.replace(i, (((qvector_temp.at(i)-32)*5)/9));
        i++;
    }
}


void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
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
    while(i < qvector_windspeed.length())
    {
        qvector_windspeed.replace(i, (qvector_windspeed.at(i)/1.609));
        i++;
    }
}

void MainWindow::convertKph()
{
    int i = 0;
    while(i < qvector_windspeed.length())
    {
        qvector_windspeed.replace(i, (qvector_windspeed.at(i)*1.609));
        i++;
    }
}

void MainWindow::on_horizontalSlider_3_sliderMoved(int position)
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
    while(i < qvector_pressure.length())
    {
        qvector_pressure.replace(i, (qvector_pressure.at(i)/100));
        i++;
    }
}

void MainWindow::convertPas()
{
    int i = 0;
    while(i < qvector_pressure.length())
    {
        qvector_pressure.replace(i, (qvector_pressure.at(i)*100));
        i++;
    }
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
            qDebug() << buffer;
            QJsonDocument jsonDoc(QJsonDocument::fromJson(buffer));
            QJsonArray jsonReply = jsonDoc.array();
            QJsonObject data = jsonReply[0].toObject();

            qDebug() << data;
            qDebug() << data["temperature"];
            reply->deleteLater();
        }
    );
    qnam->get(request);

}

