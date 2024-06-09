#include "receivestageop.h"

ReceiveStageOp::ReceiveStageOp(QObject *parent)
    : QObject{parent}
{}

bool ReceiveStageOp::ReviceData(SOCKET_INDEX socketIndex, const NetworkData& data)
{
    if(this->IsMyOp(data) == true)
    {
        this->DoSomething(socketIndex, data);
        return true;
    }
    return false;
}
