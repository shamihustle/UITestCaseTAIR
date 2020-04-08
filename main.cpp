#include "mainwindow.h"

#include <QApplication>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QChart>
#include <QChartView>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    return a.exec();
}

// Отрисовка графика
// Принимает вектор частот и вектор данных из программы S2VNA
void MainWindow::DrawChart(QVector<double> freq, QVector<double> data)
{
    chartView->chart()->removeAxis(xAxis);
    chartView->chart()->removeAxis(yAxis);


    xAxis->setRange(freq.first(), freq.back());
    yAxis->setRange(*min_element(data.begin(),data.end()), *max_element(data.begin(),data.end()));

    measurement->clear();

    for(int i = 0; i < data.size(); i++)
    {
        *measurement << QPointF(freq[i], data[i]);
    }

    chartView->chart()->addSeries(measurement);         // Добавить на график


    chartView->chart()->setAxisX(xAxis, measurement);   // Назначить ось xAxis, осью X для measurement
    chartView->chart()->setAxisY(yAxis, measurement);   // Назначить ось yAxis, осью Y для measurement
}

// Установка настроенк для графиков QrCharts
void MainWindow::SetChartSettings(QtCharts::QChartView *chartView)
{
    xAxis = new QtCharts::QValueAxis;
    xAxis->setRange(0, 9000000000);
    xAxis->setTitleText(tr("Frequency"));
    xAxis->setTitleBrush(Qt::gray);
    xAxis->setLabelsColor(Qt::gray);

    yAxis = new QtCharts::QValueAxis;
    yAxis->setRange(-50, 50)     ;
    yAxis->setTitleText(tr("Values"));
    yAxis->setTitleBrush(Qt::gray);
    yAxis->setLabelsColor(Qt::gray);


    graphicPen.setWidthF(0.5f);   // Установить ширину линии
    graphicPen.setBrush(Qt::yellow);

    measurement = new QtCharts::QLineSeries;
    measurement->setName("Measurement");
    measurement->setPen(graphicPen);
    measurement->setUseOpenGL(true);

    chartView->chart()->setTheme(QtCharts::QChart::ChartThemeDark);

    chartView->chart()->setAxisX(xAxis);   // Назначить ось xAxis, осью X для measurement
    chartView->chart()->setAxisY(yAxis);   // Назначить ось yAxis, осью Y для measurement

}

// Проверка на отсутсвие лишних символов
bool MainWindow::StringCheck(string string)
{
    char* endPtr;

    strtof(string.data(), &endPtr);

    if(*endPtr)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Проверка частоты
bool MainWindow::FrequencyChek(string freq)
{
    if(QString::fromStdString(freq).toDouble() > 9.0 || QString::fromStdString(freq).toDouble() < 0.0 || !StringCheck(freq))
        return false;
    else
        return true;
}

// Проверка полосы филтра ПЧ
bool MainWindow::FilterBandCheck(string filterBand)
{
    if(QString::fromStdString(filterBand).toInt() < 10  || !StringCheck(filterBand))
        return false;
    else
        return true;
}

// Проверка колличества чатотных точек
bool MainWindow::NumberOfPointsCheck(string numberOfPoints)
{
    if(QString::fromStdString(numberOfPoints).toInt() < 0  || !StringCheck(numberOfPoints))
        return false;
    else
        return true;
}
