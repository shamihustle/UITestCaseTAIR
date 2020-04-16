#ifndef THREADS2VNA_H
#define THREADS2VNA_H

#include <QObject>
#include <IProtocol.h>
#include <QVector>
#include <SCPIRetrieval.h>

class ThreadS2VNA : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)

    Q_PROPERTY(QString frequencyPoint READ frequencyPoint WRITE setFrequencyPoint NOTIFY frequencyPointChanged)

    Q_PROPERTY(QString filterStrip READ filterStrip WRITE setFilterStrip NOTIFY filterStripChanged)

    Q_PROPERTY(QString startFrequency READ startFrequency WRITE setStartFrequency NOTIFY startFrequencyChanged)

    Q_PROPERTY(QString stopFrequency READ stopFrequency WRITE setStopFrequency NOTIFY stopFrequencyChanged)

    QString _frequencyPoint;

    QString _filterStrip;

    QString _startFrequency;

    QString _stopFrequency;

    QVector<double> _frequency;

    QVector<double> _measurement;

    QVector<double> _newFrequency;

    QVector<double> _newMeasurement;

    SCPIRetrieval *retrieval;

    bool _running;

    IProtocol* _protocol;

    QTcpSocket * _socket;

public:
    // Конструктор
    explicit ThreadS2VNA(QObject *parent = 0);

    // Запуск потока
    bool running() const;

    // Колличество точек
    QString frequencyPoint() const;

    // Полоса фильтра ПЧ
    QString filterStrip() const;

    // Начальная частота
    QString startFrequency() const;

    // Конечная частоты
    QString stopFrequency() const;

    // Частоты
    QVector<double> Frequency()const;

    // Данные графика
    QVector<double> Measurement() const;

signals:
     void finished();

     // Изменения
     void runningChanged(bool running);

     // Изменения колличества  точек
     void frequencyPointChanged(QString frequencyPoint);

     // Изменения полосы филтра ПЧ
     void filterStripChanged(QString filterStrip);

     // Изменения начальной частоты
     void startFrequencyChanged(QString startFrequency);

     // Изменения конечной частоты
     void stopFrequencyChanged(QString stopFrequency);

     // Установить значение частоты
     void sendFrequency(QVector<double>);

     // Установить значения измерений
     void sendMeasurement(QVector<double>);

     // Отрисовать новые данные
     void startDraw(bool);


public slots:
     // Метод с полезной нагрузкой, который может выполняться в цикле
     void run();

     // Запустить или остановить поток
     void setRunning(bool running);

     // Установить заначения колличества точек
     void setFrequencyPoint(QString frequencyPoint);

     // Установить полосу филтра ПЧ
     void setFilterStrip(QString filterStrip);

     // Установить начальную чатсоту
     void setStartFrequency(QString startFrequency);

     // Установить конечную частоту
     void setStopFrequency(QString stopFrequency);

     // Обновить данные частоты и измерений
     void updateData();

};

#endif // THREADS2VNA_H
