#include "resignstageop.h"
#include "../mainwindow.h"

ResignStageOp::ResignStageOp(MainWindow *pserver, QObject *parent)
    : ServerReceiveStageOp{pserver, parent}
    , pmainwindow(pserver)
{}

bool ResignStageOp::IsMyOp(const NetworkData &data)
{
    return data.op == OPCODE::RESIGN_OP;
}

void ResignStageOp::DoSomeThing(QTcpSocket* pcursocket, QTcpSocket*client1, QTcpSocket* client2, const NetworkData &data)
{
    if(this->pmainwindow != nullptr && data.op == OPCODE::RESIGN_OP)
    {
        QTcpSocket*psocket = this->pmainwindow->get_socket_map(this->pmainwindow->get_is_white_turn());
        if(psocket == pcursocket)
        {
            //yes, RESIGN_OP msg is send on turn;
            this->pmainwindow->game_finish(this->pmainwindow->get_is_white_turn(), SurakartaEndReason::RESIGN);
        }
    }
}
