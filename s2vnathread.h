#ifndef S2VNATHREAD_H
#define S2VNATHREAD_H

#include <QThread>
#include <QString>
#include <QTcpSocket>


class S2VNAThread : public QThread
{
    Q_OBJECT

public:
    S2VNAThread();

    void run();

    explicit S2VNAThread(QTcpSocket *socket);

    signals:
    void send(QString);
    private:
    QTcpSocket *_socket;
};

#endif // S2VNATHREAD_H
