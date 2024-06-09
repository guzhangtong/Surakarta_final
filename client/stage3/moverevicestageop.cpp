#include "moverevicestageop.h"
#include "mainwindow.h"

MoveReviceStageOp::MoveReviceStageOp(MainWindow *pmain, QObject *parent)
    : ReceiveStageOp{parent}
    , pmainwindow(pmain)
{}


bool MoveReviceStageOp::IsMyOp(const NetworkData& data)
{
    return data.op == OPCODE::MOVE_OP;
}
void MoveReviceStageOp::DoSomething(SOCKET_INDEX socketIndex, const NetworkData& data)
{
    /*
     * use move_op data3 to sign the move_op selector;
     * if the data3 is "1" or "", mean move the stone;
     * so the data1 is first point of stone, for example "0,0"
     * the data2 is will move to point of stone; for example "1,1"
     *
     *  be unuse now
     * if the data3 is "2", mean select the stone;
     * so the data1 is selected point of stone; for example "0,0"
     *
     * if the data3 is "3", mean now is who is turn to move;
     * so the data1 is who will be move, "1" is white, "0" is black
     * the data2 is limit time;
     *
     *  be unuse now
     * if the data3 is "4", mean now is who is turn to move;
     * so the data1 is who will be move, "1" is white, "0" is black
     * the data2 is "";
    */
    if(data.data3 == QString("1") || data.data3.isEmpty()==true)
    {
        if(this->pmainwindow != nullptr)
        {
            QStringList fromPoints = data.data1.split(",");
            QStringList toPoints = data.data2.split(",");
            if(fromPoints.size() == 2 && toPoints.size() == 2)
            {
                QPoint fromPos(fromPoints[0].toInt(), fromPoints[1].toInt());
                QPoint toPos(toPoints[0].toInt(), toPoints[1].toInt());
                this->pmainwindow->MoveBoardStone(fromPos, toPos);
            }
        }
    }
    else if(data.data3 == QString("2"))
    {
        //be unuse now
        QStringList points = data.data1.split(",");
        if(points.size() == 2)
        {
            QPoint pos(points[0].toInt(), points[1].toInt());
            this->pmainwindow->ClickBoardStone(pos);
        }
    }
    else if(data.data3 == QString("3"))
    {
        int time = data.data2.toInt();
        if(data.data1 == QString("1"))
        {
            this->pmainwindow->ChangePlayTime(true, time);
        }
        else if(data.data1 == QString("0"))
        {
            this->pmainwindow->ChangePlayTime(false, time);
        }
    }
    else if(data.data3 == QString("4"))
    {
        //be unuse now
        // if(data.data1 == QString("1"))
        // {
        //     this->pmainwindow->ChangeRunTurn(true);
        // }
        // else if(data.data1 == QString("0"))
        // {
        //     this->pmainwindow->ChangeRunTurn(false);
        // }
    }
}
