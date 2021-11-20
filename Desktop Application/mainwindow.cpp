#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTimer>
#include <QtDebug>
#include <QGraphicsWidget>

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
   ui->plot->xAxis->setRange(0, 100);
   ui->plot->yAxis->setRange(0, 100);
   ui->plot->graph(0)->setPen(QPen(Qt::blue));
   ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
   timerId = startTimer(1000);
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
    addPoint(count,digit);
    count++;
    plot();
    //digit++;
}

void MainWindow::addPoint(double x, double y)
{
    qv_x.append(x);
    qv_y.append(y);
}

void MainWindow::clearData()
{
    qv_x.clear();
    qv_y.clear();
}

void MainWindow::plot()
{
    ui->plot->graph(0)->setData(qv_x,qv_y);
    ui->plot->replot();
    ui->plot->update();
}

void MainWindow::on_pushButton_2_clicked()
{
    clearData();
}

int MainWindow::newData()
{
    return rand() % 100;
}
