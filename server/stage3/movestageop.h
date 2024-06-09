#ifndef MOVESTAGEOP_H
#define MOVESTAGEOP_H

#include "serverreceivestageop.h"

class MoveStageOp : public ServerReceiveStageOp
{
public:
    explicit MoveStageOp(MainWindow *pserver, QObject *parent = nullptr);

public:
    virtual bool IsMyOp(const NetworkData& data);
    virtual void DoSomeThing(QTcpSocket* pcursocket, QTcpSocket*client1, QTcpSocket* client2, const NetworkData& data);

private:
    MainWindow* pmainwindow;
};

#endif // MOVESTAGEOP_H
