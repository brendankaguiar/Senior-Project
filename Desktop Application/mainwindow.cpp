
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QValueAxis>
#include <QtWidgets/QGridLayout>
#include <QTime>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTimer>
#include <QtDebug>
#include "timer.h"
#include <QGraphicsWidget>

int digit = 1;
int button = 100;
QPen pen;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
   ui->setupUi(this);

   ui->plot->addGraph();
   ui->plot->xAxis->setRange(0, 20);
   ui->plot->yAxis->setRange(0, 20);
   ui->plot->graph(0)->setPen(QPen(Qt::blue));
   //ui->plot->graph()->setPen(pen);
   ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
  // ui->plot->graph(0)->setLineStyle(QCPGraph::);
   timerId = startTimer(1000);
   /*QChartView *chartView;

   QChart *chart = new QChart();
   chart->legend()->hide();
   QLineSeries *series = new QLineSeries(chart);
   chart->addSeries(series);
   chart->createDefaultAxes();
   chart->setTitle("Simple line chart example");
   chart->axisX()->setRange(0,10);
   chart->axisY()->setRange(0,10);
   //QString name("Series ");
    series->append(0.5,0.5);
    //chart->addSeries(series);
    //![5]
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->gridLayout_3->addWidget(chartView, 1, 2);
    m_charts << chartView;
    digit = 0;
    if(digit < 1000)
    {
    delay(1000);
    digit++;
    ui->lcdNumber->display(digit);
    //timerId = startTimer(1000);
    updateLineChart(series);
    }*/


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    //QMessageBox::information(this,"Download Data", "File Type:");
    digit = 0;
    ui->lcdNumber_2->display(button = button + 100);

}

void MainWindow::timerEvent(QTimerEvent *event)
{
    qDebug() << "Update...";
    ui->lcdNumber->display(++digit);
    addPoint(digit,digit);
    plot();
}

/*QChart *MainWindow::createLineChart() const
{
    QChart *chart = new QChart();
    chart->setTitle("Line chart");

    QString name("Series ");
    QLineSeries *series = new QLineSeries(chart);
            series->append(digit,digit);
                        series->append(digit+1,digit+1);
                                    series->append(digit+2,digit+2);
                                                series->append(digit+3,digit+3);
                                                            series->append(digit+4,digit+4);

        chart->addSeries(series);

    return chart;
}*/

/*void MainWindow::updateLineChart(QLineSeries *series)
{
    series->append(digit,digit);
}*/

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

