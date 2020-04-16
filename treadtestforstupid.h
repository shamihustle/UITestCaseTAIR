#ifndef TREADTESTFORSTUPID_H
#define TREADTESTFORSTUPID_H

#include <QThread>
#include <IProtocol.h>


class TreadTestForStupid : public QThread
{
    QString _frequencyPoint;

    QString _filterStrip;

    QString _startFrequency;

    QString _stopFrequency;

    QVector<double> _frequency;

    QVector<double> _measurement;

    bool _running;

    IProtocol* _protocol;

public:
    explicit TreadTestForStupid();

    bool running() const;

    QString frequencyPoint() const;

    QString filterStrip() const;

    QString startFrequency() const;

    QString stopFrequency() const;

    QVector<double> Frequency()const;

    QVector<double> Measurement() const;



signals:
     void finished();

     void runningChanged(bool running);

     void frequencyPointChanged(QString frequencyPoint);

     void filterStripChanged(QString filterStrip);

     void startFrequencyChanged(QString startFrequency);

     void stopFrequencyChanged(QString stopFrequency);

public slots:
     void run() override; // Метод с полезной нагрузкой, который может выполняться в цикле

     void setRunning(bool running);

     void setFrequencyPoint(QString frequencyPoint);

     void setFilterStrip(QString filterStrip);

     void setStartFrequency(QString startFrequency);

     void setStopFrequency(QString stopFrequency);

};

#endif // TREADTESTFORSTUPID_H
