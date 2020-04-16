#include "scpiretrieval.h"
#include <sockets2vna.h>
#include <QString>
#include <QVector>
#include <QEventLoop>
#include <QTimer>


SCPIRetrieval::SCPIRetrieval(IProtocol *protocol)
{
    _protocol = protocol;
}

// Получение значений частоты
QVector<double> SCPIRetrieval::FrequencyRetrieval(const int &channel)
{
    QString retrieval = "SENS" + QString::number(channel) + ":FREQuency:DATA?\n";

    return _protocol->DataRetrieval(retrieval);
}

// Получение значений графика из программы
QVector<double> SCPIRetrieval::MeasurementRetrieval(const int &channel)
{
    QString retrieval = "CALC" + QString::number(channel) + ":DATA:FDAT?\n";

    return  _protocol->DataRetrieval(retrieval);
}

// Запуск измерений и ожидание завершения
bool SCPIRetrieval::DataScaning()
{
    try
    {
        _protocol->SendCommand(":TRIG:SOUR BUS\n");
        _protocol->SendCommand(":TRIG:SING\n");
        QString ans = _protocol->SendRequest("*OPC?\n");
        if (ans == "1\n")
            return true;
        else return false;
    }
    catch (std::exception &exception)
    {
        throw std::runtime_error("Timeout exceeded");
    }
}

SCPIRetrieval::~SCPIRetrieval()
{

};
