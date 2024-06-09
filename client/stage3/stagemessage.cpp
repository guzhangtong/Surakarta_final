#include "stagemessage.h"


StageMessage::StageMessage(ConnectInfo* pinfo, QObject *parent)
    : QObject{parent}
    , pconnectInfo(pinfo)
{}

void StageMessage::SendMessage(SOCKET_INDEX socketIndex)
{
    if(this->pconnectInfo != nullptr && socketIndex != NoBadySocket)
    {
        this->pconnectInfo->SendMessage(socketIndex, this->ToNetworkData());
    }
}
