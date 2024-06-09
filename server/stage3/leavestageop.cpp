#include "leavestageop.h"
#include "../mainwindow.h"
#include "../Board.h"
#include "./leavestagemessage.h"

LeaveStageOp::LeaveStageOp(MainWindow *pserver, QObject *parent)
    : ServerReceiveStageOp{pserver, parent}
    , pmainwindow(pserver)
{}

bool LeaveStageOp::IsMyOp(const NetworkData &data)
{
    return data.op == OPCODE::LEAVE_OP;
}

void LeaveStageOp::DoSomeThing(QTcpSocket* pcursocket, QTcpSocket*client1, QTcpSocket* client2, const NetworkData &data)
{
    if(client1 != nullptr && client2 != nullptr && data.op == OPCODE::LEAVE_OP)
    {
        if(pcursocket == client1)
        {
            if(this->pmainwindow != nullptr)
            {
                LeaveStageMessage msg(this->pmainwindow, this->pmainwindow);
                this->SendToClient(client2, msg.ToNetworkData());
            }
            else
            {
                LeaveStageMessage msg(this->pmainwindow, this->pmainwindow);
                this->SendToClient(client1, msg.ToNetworkData());
            }

        }


        if(this->pmainwindow != nullptr)
        {
            bool isWhiteLose = (this->pmainwindow->get_socket_map(true) == pcursocket);
            this->pmainwindow->remove_client(pcursocket);
            this->pmainwindow->game_finish(isWhiteLose, SurakartaEndReason::TIMEOUT);
        }
    }
}
