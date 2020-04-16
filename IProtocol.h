#ifndef IPROTOCOL_H
#define IPROTOCOL_H

#include <QString>

#include <QObject>


// Интерфейс протокола, который отвечает за связь
class IProtocol
{

public:

    // Подключение к программе S2VNA
    virtual bool Connect(const QString& hostName, const quint16& port) = 0 ;

    // Отправить команду программе
    virtual void SendCommand(const QString& command) = 0;

    // Отправить запрос
    // Ожидается какой-то ответ
    virtual QString SendRequest(const QString& request) = 0;

    // Получение данных
    virtual QVector<double> DataRetrieval(const QString& request) = 0;


    // Деструктор
    virtual ~IProtocol() = default;
};

#endif // IPROTOCOL_H



