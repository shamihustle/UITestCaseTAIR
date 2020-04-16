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

// Проверка на отсутсвие лишних символов
bool MainWindow::stringCheck(string string)
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
bool MainWindow::frequencyChek(string freq)
{
    if(QString::fromStdString(freq).toDouble() > 9.0 || QString::fromStdString(freq).toDouble() < 0.0 || !stringCheck(freq))
        return false;
    else
        return true;
}

// Проверка полосы филтра ПЧ
bool MainWindow::filterBandCheck(string filterBand)
{
    if(QString::fromStdString(filterBand).toInt() < 10  || !stringCheck(filterBand))
        return false;
    else
        return true;
}

// Проверка колличества чатотных точек
bool MainWindow::numberOfPointsCheck(string numberOfPoints)
{
    if(QString::fromStdString(numberOfPoints).toInt() < 0  || !stringCheck(numberOfPoints))
        return false;
    else
        return true;
}



