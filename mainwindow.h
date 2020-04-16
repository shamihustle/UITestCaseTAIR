#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QValueAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QChartView>
#include <IProtocol.h>
#include <QTcpSocket>
#include <sockets2vna.h>
#include <scpicommands.h>
#include <scpiretrieval.h>
#include <QVector>
#include <QThread>
#include <threads2vna.h>

#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    IProtocol* protocol;

    QtCharts::QChartView *chartView;

    QtCharts::QChartView *view;

    QtCharts::QValueAxis *xAxis;  // Ось X

    QtCharts::QValueAxis*yAxis;  // Ось Y

    QPen graphicPen; // Перо для рисования графика

    QtCharts::QLineSeries *meas; // Точки измерений

    QtCharts::QChart *chart;

    QTimer deviceTimer;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    // Кнопка старт
    void on_pushButton_Start_clicked();

    // Установка настроек графика и осей
    void setChartSettings(QtCharts::QChartView *chartView);

    // Отрисовка графика
    // Принимает вектор частот и вектор данных из программы S2VNA
    void drawChart(QVector<double> freq, QVector<double> data);

    // Проверка на лишние символы в строке
    bool stringCheck(string string);

    // Проверка частоты
    bool frequencyChek(string freq);

    // Проверка полосы фильтра ПЧ
    bool filterBandCheck(string filterBand);

    // Проверка проверка колличества частотных точек
    bool numberOfPointsCheck(string numberOfPoints);

    // Изменене данных
    void DataChanges();

    // Изменение колличества точек по нажатию enter
    void enterPressedFrequencyPoint();

    // Изменение полосы филтра ПЧ по нажатию enter
    void enterPressedFilterStrip();

    // Изменение начальной частоты по нажатию enter
    void enterPressedStartFrequency();

    // Изменение конечной частоты по нажатию enter
    void enterPressedStopFrequency();

    // Установить значения частот
    void setFrequency(QVector<double> freq);

    // Установить значения измерений
    void setMeasurement(QVector<double> meas);

    // Отрисовать
    void draw(bool start);

    // Установить LineEdit в readOnly
    void setReadOnlyLineEdit(bool readOnly);

    // Измение надписи на кнопке старт
    void changeButtonStart(bool startChange);

private:

    Ui::MainWindow *ui;

    QThread * thread;

    ThreadS2VNA * _threadS2VNA;

    QVector<double> _frequency;

    QVector<double> _measurement;

signals:

     void startDraw();

     void boolChanged();

};



#endif // MAINWINDOW_H
