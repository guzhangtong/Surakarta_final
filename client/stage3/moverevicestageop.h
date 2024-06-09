#ifndef MOVEREVICESTAGEOP_H
#define MOVEREVICESTAGEOP_H

#include "receivestageop.h"

class MainWindow;
class MoveReviceStageOp : public ReceiveStageOp
{
public:
    explicit MoveReviceStageOp(MainWindow* pmain, QObject *parent = nullptr);

private:
    virtual bool IsMyOp(const NetworkData& data);
    virtual void DoSomething(SOCKET_INDEX socketIndex, const NetworkData& data);
private:
    MainWindow *pmainwindow;
};

#endif // MOVEREVICESTAGEOP_H
