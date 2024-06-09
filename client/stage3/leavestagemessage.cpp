#include "leavestagemessage.h"

LeaveStageMessage::LeaveStageMessage(ConnectInfo *pinfo, QObject *parent)
    : StageMessage{pinfo, parent}
    , data(OPCODE::LEAVE_OP, "", "", "")
{}

const NetworkData& LeaveStageMessage::ToNetworkData()
{
    return this->data;
}
