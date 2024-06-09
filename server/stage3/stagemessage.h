#ifndef STAGEMESSAGE_H
#define STAGEMESSAGE_H

#include <QObject>
#include <QTcpSocket>
#include "../networkdata.h"

class MainWindow;
class QTcpSocket;
class StageMessage : public QObject
{
    Q_OBJECT
public:
    explicit StageMessage(MainWindow* pmain, QObject *parent = nullptr);

    QTcpSocket* GetSocket(bool isWhite);
    void SendMessage(QTcpSocket* psocket);

private:
    virtual const NetworkData& ToNetworkData() = 0;

signals:

private:
    MainWindow* pmainwindow;
};

#endif // STAGEMESSAGE_H
