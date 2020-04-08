#ifndef SOCKETS2VNA_H
#define SOCKETS2VNA_H

#include <IProtocol.h>
#include <QTcpSocket>
#include <QString>
#include <QVector>

// Класс обмена информацией с программой S2VNA через Socket
class SocketS2VNA : public IProtocol
{
private:

    QTcpSocket* _socket;

    QVector<double> qstringToDoubleConverter(QStringList stringList);

public:

    //Конструктор
    SocketS2VNA();

    //Подключение к программе S2VNA
    bool Connect(const QString& hostName, const quint16 &port) override;

    //Отправить команду программе
    void SendCommand(const QString& command) override;

    //Отправить запрос
    //Ожидается какой-то ответ
    QString SendRequest(const QString& request) override;

    // Получение данных
    QVector<double> DataRetrieval(const QString& request);

    ~SocketS2VNA();
};

#endif // SOCKETS2VNA_H
