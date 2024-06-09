#include "resignstagemessage.h"

ResignStageMessage::ResignStageMessage(ConnectInfo *pinfo, QObject *parent)
    : StageMessage{pinfo, parent}
    , data(OPCODE::RESIGN_OP, "", "", "")
{}

const NetworkData& ResignStageMessage::ToNetworkData()
{
    return this->data;
}
