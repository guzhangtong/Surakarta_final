#include "chatstagemessage.h"

ChatStageMessage::ChatStageMessage(ConnectInfo *pinfo, QObject *parent)
    : StageMessage{pinfo, parent}
    , data(OPCODE::CHAT_OP, "", "", "")
{}

void ChatStageMessage::ReposeRestart(bool isAgreeRestart)
{
    if(isAgreeRestart)
    {
        data.data1 = QString("1");
    }
    else
    {
        data.data1 = QString("0");
    }

    data.data3 = QString("2");
}
void ChatStageMessage::RequestRestart()
{
    data.data3 = QString("1");
}

const NetworkData& ChatStageMessage::ToNetworkData()
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
    return this->data;
}
