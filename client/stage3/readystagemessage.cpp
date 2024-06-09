#include "readystagemessage.h"
#include <QString>

ReadyStageMessage::ReadyStageMessage(const QString &userName, const QString &color, const QString &roomNum, ConnectInfo *pinfo, QObject *parent)
    : StageMessage{pinfo, parent}
    , data(OPCODE::READY_OP, userName, color, roomNum)
{}

const NetworkData& ReadyStageMessage::ToNetworkData()
{
    return this->data;
}
