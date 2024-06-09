#ifndef READYSTAGEOP_H
#define READYSTAGEOP_H

#include "serverreceivestageop.h"

class MainWindow;
class ReadyStageOp : public ServerReceiveStageOp
{
public:
    explicit ReadyStageOp(MainWindow *pserver, QObject *parent = nullptr);


public:
    virtual bool IsMyOp(const NetworkData& data);
    virtual void DoSomeThing(QTcpSocket* pcursocket, QTcpSocket*client1, QTcpSocket* client2, const NetworkData& data);

private:
    MainWindow* pmainwindow;
};

#endif // READYSTAGEOP_H
