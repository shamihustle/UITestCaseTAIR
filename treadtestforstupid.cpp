
#include "treadtestforstupid.h"

#include <sockets2vna.h>
#include <SCPIRetrieval.h>

TreadTestForStupid::TreadTestForStupid() :
    _frequencyPoint(""), _filterStrip(""),
    _startFrequency("") , _stopFrequency("")
{
     _protocol = new SocketS2VNA();
}

bool TreadTestForStupid::running() const
{
    return _running;
}

QString TreadTestForStupid::frequencyPoint() const
{
    return _frequencyPoint;
}

QString TreadTestForStupid::filterStrip() const
{
    return _filterStrip;
}

QString TreadTestForStupid::startFrequency() const
{
    return _startFrequency;
}

QString TreadTestForStupid::stopFrequency() const
{
    return _stopFrequency;
}

QVector<double> TreadTestForStupid::Frequency() const
{
    return _frequency;
}

QVector<double> TreadTestForStupid::Measurement() const
{
    return _measurement;
}

void TreadTestForStupid::run()
{
    _protocol->SendCommand(_frequencyPoint);
    _protocol->SendCommand(_filterStrip);
    _protocol->SendCommand(_startFrequency);
    _protocol->SendCommand(_stopFrequency);

    SCPIRetrieval retrieval(_protocol);

    retrieval.DataScaning();
    _frequency = retrieval.FrequencyRetrieval(1);
    _measurement = retrieval.MeasurementRetrieval(1);
    for (int i = 0; i < _measurement.size(); i++)
    {
        if(_measurement[i] == 0)
            _measurement.remove(i);
    }

}

void TreadTestForStupid::setRunning(bool running)
{
    if (_running == running)
        return;

    _running = running;
    emit runningChanged(running);
}

void TreadTestForStupid::setFrequencyPoint(QString frequencyPoint)
{
    if (_frequencyPoint == frequencyPoint)
        return;

    _frequencyPoint = frequencyPoint;
    emit frequencyPointChanged(frequencyPoint);
}

void TreadTestForStupid::setFilterStrip(QString filterStrip)
{
    if (_filterStrip == filterStrip)
        return;

    _filterStrip = filterStrip;
    emit filterStripChanged(filterStrip);
}

void TreadTestForStupid::setStartFrequency(QString startFrequency)
{
    if (_startFrequency == startFrequency)
        return;

    _startFrequency = startFrequency;
    emit startFrequencyChanged(startFrequency);
}

void TreadTestForStupid::setStopFrequency(QString stopFrequency)
{
    if (_stopFrequency == stopFrequency)
        return;

    _stopFrequency = stopFrequency;
    emit stopFrequencyChanged(stopFrequency);
}


