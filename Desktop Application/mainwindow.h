#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void addPoint(double x, double y,QVector<double> &xV, QVector<double> &yV);
    void clearData();
    void plot();
    int newData();
    void convertF();
    void convertC();
    void convertMph();
    void convertKph();
    void convertMbars();
    void convertPas();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_horizontalSlider_2_sliderMoved(int position);

    void on_horizontalSlider_3_sliderMoved(int position);

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    int timerId;
    void connectSignals();
    QVector<double> qvector_temp, qvector_humid, qvector_windspeed, qvector_pressure, qvector_aq;
    QVector<double> qv_x, qv_y, qv_x2, qv_y2,qv_x3, qv_y3,qv_x4, qv_y4,qv_x5, qv_y5,qv_x6, qv_y6;

protected:
    void timerEvent(QTimerEvent *event);

};
#endif // MAINWINDOW_H
