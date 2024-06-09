#ifndef READYREVICESTAGEOP_H
#define READYREVICESTAGEOP_H

#include "receivestageop.h"

class MainWindow;
class ReadyReviceStageOp : public ReceiveStageOp
{
public:
    explicit ReadyReviceStageOp(MainWindow* pmain, QObject *parent = nullptr);

private:
    virtual bool IsMyOp(const NetworkData& data);
    virtual void DoSomething(SOCKET_INDEX socketIndex, const NetworkData& data);

private:
    MainWindow *pmainwindow;
};

#endif // READYREVICESTAGEOP_H
