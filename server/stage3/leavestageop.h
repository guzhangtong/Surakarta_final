#ifndef LEAVESTAGEOP_H
#define LEAVESTAGEOP_H

#include "serverreceivestageop.h"

class MainWindow;
class LeaveStageOp : public ServerReceiveStageOp
{
public:
    explicit LeaveStageOp(MainWindow *pserver, QObject *parent = nullptr);

public:
    virtual bool IsMyOp(const NetworkData& data);
    virtual void DoSomeThing(QTcpSocket* pcursocket, QTcpSocket*client1, QTcpSocket* client2, const NetworkData& data);

private:
    MainWindow* pmainwindow;
};

#endif // LEAVESTAGEOP_H
