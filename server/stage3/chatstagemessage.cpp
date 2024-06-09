#include "chatstagemessage.h"

ChatStageMessage::ChatStageMessage(MainWindow* pmain, QObject *parent)
    : StageMessage{pmain, parent}
    , data(OPCODE::CHAT_OP, QString(), QString(), QString())
{}

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
