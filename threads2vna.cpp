#include "threads2vna.h"
#include <sockets2vna.h>
#include <SCPIRetrieval.h>
#include "scpicommands.h"
#include <QTcpSocket>
#include <QVector>
#include <QMessageBox>
#include <QEventLoop>
#include <QTimer>

ThreadS2VNA::ThreadS2VNA(QObject *parent) :
    QObject(parent), _frequencyPoint("SENS1:SWE:POIN 201\n"), _filterStrip("SENS1:BAND 10000\n"),
    _startFrequency("SENS1:FREQ:STAR 0.0001GHZ\n"), _stopFrequency("SENS1:FREQ:STOP 9GHZ\n")
{
    _protocol = new SocketS2VNA();

    retrieval = new SCPIRetrieval(_protocol);
    _running = false;
}

bool ThreadS2VNA::running() const
{
    return _running;
}

QString ThreadS2VNA::frequencyPoint() const
{
    return _frequencyPoint;
}

QString ThreadS2VNA::filterStrip() const
{
    return _filterStrip;
}

QString ThreadS2VNA::startFrequency() const
{
    return _startFrequency;
}

QString ThreadS2VNA::stopFrequency() const
{
    return _stopFrequency;
}

QVector<double> ThreadS2VNA::Frequency() const
{
    return _frequency;
}

QVector<double> ThreadS2VNA::Measurement() const
{
    return _measurement;
}

void ThreadS2VNA::run()
{

    if(!_protocol->Connect("localhost", 5025))
    {
        setRunning(false);
        return;
    }

    _protocol->SendCommand(_frequencyPoint);
    _protocol->SendCommand(_filterStrip);
    _protocol->SendCommand(_startFrequency);
    _protocol->SendCommand(_stopFrequency);

    updateData();

    while(_running)
    {
        // проверяю есть ли изменения в данных
        if (_frequency != _newFrequency && _measurement != _newMeasurement)
        {
            // присваиваю новые значения
            _frequency = _newFrequency;
            _measurement = _newMeasurement;

            // передаю значения , что бы их можно было забрать
            emit sendFrequency(_frequency);
            emit sendMeasurement(_measurement);
            emit startDraw(true);
        }
        _sleep(1000);
    }
    emit finished();
}

void ThreadS2VNA::setRunning(bool running)
{
    if (_running == running)
        return;

    _running = running;
    emit runningChanged(running);
}

void ThreadS2VNA::setFrequencyPoint(QString frequencyPoint)
{
    if (_frequencyPoint == frequencyPoint)
        return;

    _frequencyPoint = frequencyPoint;
    _protocol->SendCommand(_frequencyPoint);

    updateData();

    emit frequencyPointChanged(frequencyPoint);
}

void ThreadS2VNA::setFilterStrip(QString filterStrip)
{
    if (_filterStrip == filterStrip)
        return;
    _filterStrip = filterStrip;
    _protocol->SendCommand(_filterStrip);

    updateData();

    emit filterStripChanged(filterStrip);
}

void ThreadS2VNA::setStartFrequency(QString startFrequency)
{
    if (_startFrequency == startFrequency)
        return;

    _startFrequency = startFrequency;
    _protocol->SendCommand(_startFrequency);

    updateData();

    emit startFrequencyChanged(startFrequency);
}

void ThreadS2VNA::setStopFrequency(QString stopFrequency)
{
    if (_stopFrequency == stopFrequency)
        return;

    _stopFrequency = stopFrequency;
    _protocol->SendCommand(_stopFrequency);

    updateData();

    emit stopFrequencyChanged(stopFrequency);
}

void ThreadS2VNA::updateData()
{
    if (retrieval->DataScaning())
    {
        _newMeasurement = retrieval->MeasurementRetrieval(1);

        _newFrequency = retrieval->FrequencyRetrieval(1);
    }
}



