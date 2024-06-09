#include "chatreceivestageop.h"
#include "../mainwindow.h"

ChatReceiveStageOp::ChatReceiveStageOp(MainWindow *pmain, QObject *parent)
    : ReceiveStageOp{parent}
    , pmainwindow(pmain)
{}


bool ChatReceiveStageOp::IsMyOp(const NetworkData& data)
{
    return data.op == OPCODE::CHAT_OP;
}
void ChatReceiveStageOp::DoSomething(SOCKET_INDEX socketIndex, const NetworkData& data)
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
            if(this->pmainwindow != nullptr)
                this->pmainwindow->RestartGame(true);

        }
        else if(data.data1 == QString("0"))
        {
            if(this->pmainwindow != nullptr)
                this->pmainwindow->RestartGame(false);
        }
    }
}
