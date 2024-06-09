#include "movestagemessage.h"
#include "../mainwindow.h"

MoveStageMessage::MoveStageMessage(MainWindow* pmain, ConnectInfo *pinfo, QObject *parent)
    : StageMessage{pinfo, parent}
    , pmainwindow(pmain)
    , data(OPCODE::MOVE_OP, "", "", "")
{}

void MoveStageMessage::saveClickStonePoint(const QPoint& pt)
{
    this->clickPoint = pt;
}
void MoveStageMessage::clickStone()
{
    this->data.data3 = QString("2");
    QString pointStr = QString("%0,%1").arg(clickPoint.x()).arg(clickPoint.y());
    this->data.data1 = pointStr;
    this->data.data2 = QString();
}

void MoveStageMessage::saveMoveFromPoint(const QPoint& pt)
{
    this->fromPoint = pt;

}
void MoveStageMessage::saveMoveToPoint(const QPoint& pt)
{
    this->toPoint = pt;
}

void MoveStageMessage::moveStone()
{
    this->data.data1 = QString("%0,%1").arg(this->fromPoint.x()).arg(this->fromPoint.y());
    this->data.data2 = QString("%0,%1").arg(this->toPoint.x()).arg(this->toPoint.y());
    this->data.data3 = QString();
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
    return this->data;
}
