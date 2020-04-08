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

    QtCharts::QLineSeries *measurement; // Точки измерений


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    // Кнопка старт
    void on_pushButton_Start_clicked();

    // Установка настроек графика и осей
    void SetChartSettings(QtCharts::QChartView *chartView);

    // Отрисовка графика
    // Принимает вектор частот и вектор данных из программы S2VNA
    void DrawChart(QVector<double> freq, QVector<double> data);

    // Проверка на лишние символы в строке
    bool StringCheck(string string);

    // Проверка частоты
    bool FrequencyChek(string freq);

    // Проверка полосы фильтра ПЧ
    bool FilterBandCheck(string filterBand);

    // Проверка проверка колличества частотных точек
    bool NumberOfPointsCheck(string numberOfPoints);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
