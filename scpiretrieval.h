#ifndef SCPIRETRIEVAL_H
#define SCPIRETRIEVAL_H

#include <sockets2vna.h>
#include <QString>
#include <QVector>

// Класс SCPI запросов
class SCPIRetrieval
{

IProtocol* _protocol;

public:

    // Конструктор
    // Принимает протокол
    SCPIRetrieval(IProtocol* protocol);

    // Получение значений графика из программы
    QVector<double> MeasurementRetrieval(const int &channel);

    // Получение значений частоты
    QVector<double> FrequencyRetrieval(const int &channel);

    // Запусr измерений и ожидание завершения
    bool DataScaning();

    ~SCPIRetrieval();
};

#endif // SCPIRETRIEVAL_H
