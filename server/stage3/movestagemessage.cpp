#include "movestagemessage.h"
#include "../mainwindow.h"


MoveStageMessage::MoveStageMessage(MainWindow *pmain, QObject *parent)
    : StageMessage{pmain, parent}
    , pmainwindow(pmain)
    , data(OPCODE::MOVE_OP, QString(), QString(), QString())
{}


void MoveStageMessage::thinkTimerToWho(bool isWhite, int time)
{
    if(isWhite)
    {
        this->data.data1 = QString("1");
    }
    else
    {
        this->data.data1 = QString("0");
    }
    this->data.data2 = QString::number(time);
    this->data.data3 = QString("3");
}

void MoveStageMessage::turnToWho(bool isWhite)
{
    if(isWhite)
    {
        this->data.data1 = QString("1");        
    }
    else
    {
        this->data.data1 = QString("0");
    }
    this->data.data2 = QString();
    this->data.data3 = QString("4");
}

void MoveStageMessage::clickStone(bool isWhite, const QPoint& pt)
{
    if(this->pmainwindow->get_is_white_turn() == isWhite)
    {
        this->data.data3 = QString("2");
        QString pointStr = QString("%0,%1").arg(pt.x()).arg(pt.y());
        this->data.data1 = pointStr;
    }
}

const NetworkData& MoveStageMessage::ToNetworkData()
{
    /*
     * use move_op data3 to sign the move_op selector;
     * if the data3 is "1" or "", mean move the stone;
     * so the data1 is first point of stone, for example "0,0"
     * the data2 is will move to point of stone; for example "1,1"
     *
     *be unuse now
     * if the data3 is "2", mean select the stone;
     * so the data1 is selected point of stone; for example "0,0"
     *
     * if the data3 is "3", mean now is who is turn to move;
     * so the data1 is who will be move, "1" is white, "0" is black
     * the data2 is limit time;
     *
     *be unuse now
     * if the data3 is "4", mean now is who is turn to move;
     * so the data1 is who will be move, "1" is white, "0" is black
     * the data2 is "";
    */

    return data;
}
