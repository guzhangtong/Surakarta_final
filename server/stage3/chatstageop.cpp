#include "chatstageop.h"
#include "../mainwindow.h"

ChatStageOp::ChatStageOp(MainWindow *pserver, QObject *parent)
    : ServerReceiveStageOp{pserver, parent}
    , pmainwindow(pserver)
{}

bool ChatStageOp::IsMyOp(const NetworkData &data)
{
    return data.op == OPCODE::CHAT_OP;
}

void ChatStageOp::DoSomeThing(QTcpSocket* pcursocket, QTcpSocket*client1, QTcpSocket* client2, const NetworkData &data)
{
    /*
     *use the chat op to restart game;
     *if the data3 is "1",mean request restart game;
     *then the data1 is "" and the data2 is ""
     *
     *if  the data3 is "2",mean repose is agree restart game
     *then the data1 is "" or "0" to reject restart , or "1" to agree restart game
     *and the data2 is ""
    */

    if(data.data3 == QString("2"))
    {
        if(data.data1 == QString("1"))
        {
            //restart game;
            if(this->pmainwindow != nullptr)
                this->pmainwindow->restart_game();

        }
        else if(data.data1 == QString("0"))
        {
            ;
        }
    }

    if(pcursocket == client1)
    {
        if(this->pmainwindow != nullptr)
            this->pmainwindow->send_to_client(client2, data);
    }
    else
    {
        if(this->pmainwindow != nullptr)
            this->pmainwindow->send_to_client(client1, data);
    }
}
