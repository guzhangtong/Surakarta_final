#include "readyrevicestageop.h"
#include "../mainwindow.h"

ReadyReviceStageOp::ReadyReviceStageOp(MainWindow* pmain, QObject *parent)
    : ReceiveStageOp{parent}
    , pmainwindow(pmain)
{}

bool ReadyReviceStageOp::IsMyOp(const NetworkData& data)
{
    return data.op == OPCODE::READY_OP;
}
void ReadyReviceStageOp::DoSomething(SOCKET_INDEX socketIndex, const NetworkData& data)
{
    if(data.data2 == QString("BLACK"))
    {
        // this->pmainwindow->SetWhiteUserNameShow(data.data1);
    }
    else
    {
        // this->pmainwindow->SetBlackUserNameShow(data.data1);
    }

    if(socketIndex == HumenSocket_Index)
    {
        ;
    }
}
