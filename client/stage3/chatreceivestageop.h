#ifndef CHATRECEIVESTAGEOP_H
#define CHATRECEIVESTAGEOP_H

#include "receivestageop.h"

class MainWindow;
class ChatReceiveStageOp : public ReceiveStageOp
{
public:
    explicit ChatReceiveStageOp(MainWindow* pmain, QObject *parent = nullptr);

private:
    virtual bool IsMyOp(const NetworkData& data);
    virtual void DoSomething(SOCKET_INDEX socketIndex, const NetworkData& data);
private:
    MainWindow *pmainwindow;
};

#endif // CHATRECEIVESTAGEOP_H
