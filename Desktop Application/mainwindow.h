#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QLineSeries>

QT_BEGIN_NAMESPACE
class QChartView;
class QChart;
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void addPoint(double x, double y);
    void clearData();
    void plot();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    int timerId;
    //QChart *createLineChart() const;
    //QList<QChartView *> m_charts;
    //void updateLineChart(QLineSeries *series);
    void connectSignals();
    QVector<double> qv_x, qv_y;

protected:
    void timerEvent(QTimerEvent *event);

};
#endif // MAINWINDOW_H
