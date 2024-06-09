#ifndef SERVERRECEIVESTAGEOP_H
#define SERVERRECEIVESTAGEOP_H

#include "../networkdata.h"
#include <QObject>
#include <QTcpSocket>

class MainWindow;
class ServerReceiveStageOp : public QObject
{
    Q_OBJECT
public:
    explicit ServerReceiveStageOp(MainWindow *pserver, QObject *parent = nullptr);

    void SendToClient(QTcpSocket* another, NetworkData data);
    bool DoOp(QTcpSocket* pcursocket, QTcpSocket*client1, QTcpSocket* client2, const NetworkData& data);

public:
    virtual bool IsMyOp(const NetworkData& data) = 0;
    virtual void DoSomeThing(QTcpSocket* pcursocket, QTcpSocket*client1, QTcpSocket* client2, const NetworkData& data) = 0;

signals:

private:
    MainWindow *psocketServer;
};

#endif // SERVERRECEIVESTAGEOP_H
