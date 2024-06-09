#ifndef CHATSTAGEOP_H
#define CHATSTAGEOP_H

#include "serverreceivestageop.h"

class MainWindow;
class ChatStageOp : public ServerReceiveStageOp
{
public:
    explicit ChatStageOp(MainWindow *pserver, QObject *parent = nullptr);

public:
    virtual bool IsMyOp(const NetworkData& data);
    virtual void DoSomeThing(QTcpSocket* pcursocket, QTcpSocket*client1, QTcpSocket* client2, const NetworkData& data);

private:
    MainWindow* pmainwindow;
};

#endif // CHATSTAGEOP_H
