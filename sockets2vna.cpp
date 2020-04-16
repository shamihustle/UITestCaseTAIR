#include "sockets2vna.h"
#include <QTcpSocket>
#include <QVector>
#include <QDataStream>
#include <QEventLoop>
#include <QTimer>

// Конструктор
SocketS2VNA::SocketS2VNA()
{
    _socket = new QTcpSocket();
}


// Соедениение
bool SocketS2VNA::Connect(const QString& hostName, const quint16& port)
{
    _socket->connectToHost(hostName, port);

    if(_socket->waitForConnected(3000))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Получить данные
QVector<double> SocketS2VNA::DataRetrieval(const QString& request)
{
    _socket->write(request.toUtf8());

    _socket->waitForBytesWritten(500);

    _socket->waitForReadyRead(500);

    QString res;
    QStringList list;

    while (_socket->bytesAvailable())
    {
        QEventLoop loop;
        QTimer::singleShot(_socket->bytesAvailable() / 9, &loop, SLOT(quit()));

        loop.exec();
        res.append(_socket->readAll());
        list.append(res.split(QRegExp(",")));

    }

    return qstringToDoubleConverter(list);

}

// Отправить запрос
QString SocketS2VNA::SendRequest(const QString& request)
{
    QString result;

    _socket->write(request.toUtf8());

    if(!_socket->waitForBytesWritten())
    {
        throw std::runtime_error(_socket->errorString().toUtf8());
    }

    if(!_socket->waitForReadyRead())
    {
        throw std::runtime_error(_socket->errorString().toUtf8());
    }
    else
    {
        return result.append(_socket->readAll());
    }

}


// Отправить комманду
void SocketS2VNA::SendCommand(const QString &command)
{
    _socket->write(command.toUtf8());

    if(!_socket->waitForBytesWritten())
    {
        throw std::runtime_error(_socket->errorString().toUtf8());
    }
}

// Конвертер из QString в double
QVector<double> SocketS2VNA::qstringToDoubleConverter(QStringList stringList)
{

    QVector<double> result;
    bool ok = true;

    foreach (const QString &str, stringList)
        result << str.toDouble(&ok);

    for (int i = 0; i < result.size(); i++)
    {
        if(result[i] == 0)
            result.remove(i);
    }
    return result;
}


SocketS2VNA::~SocketS2VNA()
{
    delete _socket;
}

