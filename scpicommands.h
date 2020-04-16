#ifndef SCPICOMMANDS_H
#define SCPICOMMANDS_H

#include <QString>
#include <QVector>


using namespace std;


// Класс SCPI комманд
class SCPICommands
{
public:

    // Назначение колличества рабочих точек
    QString static SetNumberOfPoints(const int &channel, const int &numberOfPoints);

    // Назначение полосы филтра ПЧ
    QString static SetFilterBand(const int &channel, const int &filterBand);

    // Назначение начальной частоты
    QString static SetStartFrequency(const int &channel, const double &startFrequency);

    // Назначение конечной частоты
    QString static SetStopFrequency(const int &channel, const double &stopFrequency);

    // Выбор измеряемого параметра графика
    QString static SelectionMeasuredParameter(const int &channel, const int &chart, const QString &parameter);


};

#endif // SCPICOMMANDS_H
