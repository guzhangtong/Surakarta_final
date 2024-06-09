#include "leavestagemessage.h"

LeaveStageMessage::LeaveStageMessage(MainWindow *pmainwindow, QObject *parent)
    : StageMessage{pmainwindow, parent}
    , data(OPCODE::LEAVE_OP, QString(), QString(), QString())
{}

const NetworkData& LeaveStageMessage::ToNetworkData()
{
    return this->data;
}
