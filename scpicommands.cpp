#include "scpicommands.h"
#include <QTcpSocket>
#include <QString>
#include <QVector>

using namespace std;

// Колличество точек измерения
QString SCPICommands::SetNumberOfPoints(const int &channel, const int &numberOfPoints)
{
    return "SENS" + QString::number(channel) + ":SWE:POIN " + QString::number(numberOfPoints) + "\n";
}

// Определяет ПЧ
QString SCPICommands::SetFilterBand(const int &channel, const int &filterBand)
{
    return "SENS" + QString::number(channel) + ":BAND " + QString::number(filterBand) + "\n";
}

// Устанавлваем начальную частоту
QString SCPICommands::SetStartFrequency(const int &channel, const double &startFrequency)
{
    return "SENS" + QString::number(channel) + ":FREQ:STAR " + QString::number(startFrequency) + "GHZ\n";
}

// Установка конечной частоты
QString SCPICommands::SetStopFrequency(const int &channel, const double &stopFrequency)
{
    return "SENS" + QString::number(channel) + ":FREQ:STOP " + QString::number(stopFrequency) + "GHZ\n";
}

// Выбор измеряемого параметра графика
QString SCPICommands::SelectionMeasuredParameter(const int &channel, const int &chart, const QString &parameter)
{
    return "CALC" + QString::number(channel) + ":PAR" + QString::number(chart) + ":DEF " + parameter + "\n";
}





