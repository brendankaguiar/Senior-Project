#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QJsonArray>

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
    void getHttp(QString http = "https://flask-rews.herokuapp.com/devicedata/all/0/latest");

private slots:

    //void on_ChangeTemperature_sliderMoved(int position);

    //void on_ChangeWind_sliderMoved(int position);

    //void on_ChangePressure_sliderMoved(int position);

    void on_HTTPButton_clicked();

    void on_PascalButton_toggled(bool checked);

    void on_KPHButton_toggled(bool checked);

    void on_FarenheitButton_toggled(bool checked);

    void on_pushButton_clicked();

    void on_tabWidget_currentChanged(int index);

    void updateHomepage();

    void updateHumidity();

    void updateTemperature();

    void updateWind();

    void updatePressure();

    void updateAQ();

    void updateGPS();

    void setTempBG();

    void setHumidityBG();

    void setWindBG();

    void setPressureBG();

    void setAQBG();

    void refreshCurrentTab();

    void downloadFile();

    void on_DownloadAll_clicked();

    void downloadFinished();

    QString requestUrl(QString type, QString date);

    void deleteAllData();

    void on_DeleteAll_clicked();

    void deleteFinished();

    QString getCurrentDate();

    QString getDate(QDate date);

    void getMinMaxAvg(QString sensor, QString date);

    void on_FirstDate_2_userDateChanged(const QDate &date);

    void on_SecondDate_2_userDateChanged(const QDate &date);

    void getHttpSensor(QString sensor, QString date);

    void multHttp(QString sensor);

    void on_AboutButton_clicked();

    void on_AboutClose_clicked();

    void on_DeleteConfirm_clicked();

    void on_DeleteDeny_clicked();

    void on_FirstDate_userDateChanged(const QDate &date);

    void on_SecondDate_userDateChanged(const QDate &date);

    void on_FirstDate_3_userDateChanged(const QDate &date);

    void on_SecondDate_3_userDateChanged(const QDate &date);

    void on_FirstDate_4_userDateChanged(const QDate &date);

    void on_SecondDate_4_userDateChanged(const QDate &date);

    void on_FirstDate_5_userDateChanged(const QDate &date);

    void on_SecondDate_5_userDateChanged(const QDate &date);

    void getGPSLocation();

    void on_TempDebug_clicked();

    void on_HumidityDebug_clicked();

    void on_WindDebug_clicked();

    void on_PressureDebug_clicked();

    void on_AQDebug_clicked();

    void on_MillibarsButton_toggled(bool checked);

private:
    Ui::MainWindow *ui;

    //void connectSignals();
    //QVector<double> qvector_temp, qvector_humid, qvector_windspeed, qvector_pressure, qvector_aq;
    QVector<double> qv_x, qv_y, qv_x2, qv_y2,qv_x3, qv_y3,qv_x4, qv_y4,qv_x5, qv_y5,qv_x6, qv_y6;

    //HTTP Networking variables for sending and receiving requests and replies.
    QNetworkRequest request;
    QNetworkAccessManager* qnam;
    QJsonArray jsonReply;

    int timerId;

protected:
    void timerEvent(QTimerEvent *event);
};
#endif // MAINWINDOW_H
