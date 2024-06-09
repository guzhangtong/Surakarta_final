#ifndef RESIGNSTAGEOP_H
#define RESIGNSTAGEOP_H

#include "serverreceivestageop.h"

class MainWindow;
class ResignStageOp : public ServerReceiveStageOp
{
public:
    explicit ResignStageOp(MainWindow *pserver, QObject *parent = nullptr);

public:
    virtual bool IsMyOp(const NetworkData& data);
    virtual void DoSomeThing(QTcpSocket* pcursocket, QTcpSocket*client1, QTcpSocket* client2, const NetworkData& data);

private:
    MainWindow* pmainwindow;
};

#endif // RESIGNSTAGEOP_H
