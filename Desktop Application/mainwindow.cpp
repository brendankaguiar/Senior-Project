#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTimer>
#include <QtDebug>
#include <QGraphicsWidget>
#include <QVector>

int count = 1;
int digit = 1;
int button = 100;
QPen pen;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
   ui->setupUi(this);

   ui->plot->addGraph();
   ui->plot_2->addGraph();
   ui->plot_3->addGraph();
   ui->plot_4->addGraph();
   ui->plot_5->addGraph();
   ui->plot_6->addGraph();

   ui->plot->xAxis->setRange(0, 100);
   ui->plot->yAxis->setRange(0, 100);
   ui->plot_2->xAxis->setRange(0, 100);
   ui->plot_2->yAxis->setRange(0, 100);
   ui->plot_3->xAxis->setRange(0, 100);
   ui->plot_3->yAxis->setRange(0, 100);
   ui->plot_4->xAxis->setRange(0, 100);
   ui->plot_4->yAxis->setRange(0, 100);
   ui->plot_5->xAxis->setRange(0, 100);
   ui->plot_5->yAxis->setRange(0, 100);
   ui->plot_6->xAxis->setRange(0, 100);
   ui->plot_6->yAxis->setRange(0, 100);

   ui->plot->graph(0)->setPen(QPen(Qt::blue));
   ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
   ui->plot_2->graph(0)->setPen(QPen(Qt::blue));
   ui->plot_2->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
   ui->plot_3->graph(0)->setPen(QPen(Qt::blue));
   ui->plot_3->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
   ui->plot_4->graph(0)->setPen(QPen(Qt::blue));
   ui->plot_4->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
   ui->plot_5->graph(0)->setPen(QPen(Qt::blue));
   ui->plot_5->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
   ui->plot_6->graph(0)->setPen(QPen(Qt::blue));
   ui->plot_6->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);

   timerId = startTimer(1000);
   qvector_temp.append(23.5);
   qDebug() <<  "Test Temp: " << qvector_temp.at(0);
   qvector_windspeed.append(73.2);
   qDebug() <<  "Test Temp: " << qvector_windspeed.at(0);
   qvector_pressure.append(732.54);
   qDebug() <<  "Test Temp: " << qvector_pressure.at(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    //QMessageBox::information(this,"Download Data", "File Type:");
    count = 1;
    ui->lcdNumber_2->display(button = button + 100);

}

void MainWindow::timerEvent(QTimerEvent *event)
{
    digit = newData();
    qDebug() << "Update...";
    ui->lcdNumber->display(digit);
    addPoint(count,digit, qv_x,qv_y);
    addPoint(count,digit, qv_x2,qv_y2);
    addPoint(count,digit, qv_x3,qv_y3);
    addPoint(count,digit, qv_x4,qv_y4);
    addPoint(count,digit, qv_x5,qv_y5);
    addPoint(count,digit, qv_x6,qv_y6);
    count++;
    plot();
    qDebug() << "Test Temp: " << qvector_temp.at(0);
    qDebug() << "Test Wind Speed: " << qvector_windspeed.at(0);
    qDebug() << "Test Pressure: " << qvector_pressure.at(0);
    //digit++;
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
    ui->plot->graph(0)->setData(qv_x,qv_y);
    ui->plot_2->graph(0)->setData(qv_x2,qv_y2);
    ui->plot_3->graph(0)->setData(qv_x3,qv_y3);
    ui->plot_4->graph(0)->setData(qv_x4,qv_y4);
    ui->plot_5->graph(0)->setData(qv_x5,qv_y5);
    ui->plot_6->graph(0)->setData(qv_x6,qv_y6);
    ui->plot->replot();
    ui->plot->update();
    ui->plot_2->replot();
    ui->plot_2->update();
    ui->plot_3->replot();
    ui->plot_3->update();
    ui->plot_4->replot();
    ui->plot_4->update();
    ui->plot_5->replot();
    ui->plot_5->update();
    ui->plot_6->replot();
    ui->plot_6->update();

}

void MainWindow::on_pushButton_2_clicked()
{
    clearData();
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
