#include "movestageop.h"
#include "../mainwindow.h"
#include <QStringList>
#include <QPoint>

MoveStageOp::MoveStageOp(MainWindow *pserver, QObject *parent)
    : ServerReceiveStageOp{pserver, parent}
    , pmainwindow(pserver)
{}

bool MoveStageOp::IsMyOp(const NetworkData& data)
{
    return data.op == OPCODE::MOVE_OP;
}
void MoveStageOp::DoSomeThing(QTcpSocket* pcursocket, QTcpSocket*client1, QTcpSocket* client2, const NetworkData& data)
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
                bool isRight = false;
                isRight = this->pmainwindow->move_board_stone(fromPos, toPos);

                if(isRight)
                {
                    //is right, to send to other client;
                    if(pcursocket == client1)
                    {
                        this->pmainwindow->send_to_client(client2, data);
                    }
                    else
                    {
                        this->pmainwindow->send_to_client(client1, data);
                    }
                }
            }
        }
    }
    else if(data.data3 == QString("2"))
    {
        //be unuse now
        if(this->pmainwindow != nullptr)
        {
            QStringList points = data.data1.split(",");
            if(points.size() == 2)
            {
                QPoint pos(points[0].toInt(), points[1].toInt());
                this->pmainwindow->click_board_stone(pos);
                //is right, to send to other client;
                if(pcursocket == client1)
                {
                    this->pmainwindow->send_to_client(client2, data);
                }
                else
                {
                    this->pmainwindow->send_to_client(client1, data);
                }
            }
        }
    }
    else if(data.data3 == QString("3"))
    {
        //is send to client, server no unuse;
        ;
    }

}
