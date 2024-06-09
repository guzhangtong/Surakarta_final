#include "readystageop.h"
#include "../mainwindow.h"

ReadyStageOp::ReadyStageOp(MainWindow *pserver, QObject *parent)
    : ServerReceiveStageOp{pserver, parent}
    , pmainwindow(pserver)
{}

bool ReadyStageOp::IsMyOp(const NetworkData &data)
{
    return data.op == OPCODE::READY_OP;
}

void ReadyStageOp::DoSomeThing(QTcpSocket* pcursocket, QTcpSocket*client1, QTcpSocket* client2, const NetworkData &data)
{
    if(pcursocket == client1 || client1 == nullptr)
    {
        NetworkData cmd = NetworkData(OPCODE::REJECT_OP, data.data1, "", "");
        if(data.data1.isEmpty()== true)
        {
            //error user name;
            this->SendToClient(pcursocket, cmd);
            this->pmainwindow->remove_client(pcursocket);
            return;
        }

        if (data.data2 == "NONE" ||  data.data2.isEmpty() == true)
        {
            //error color
            this->SendToClient(pcursocket, cmd);
            this->pmainwindow->remove_client(pcursocket);
            return;
        }

        if(data.data3.isEmpty() == true)
        {
            //error room number
            this->SendToClient(pcursocket, cmd);
            this->pmainwindow->remove_client(pcursocket);
            return;
        }

        this->pmainwindow->set_client1_color(data.data2);

        if(this->pmainwindow->get_client1_color() ==QString("BLACK"))
        {
            this->pmainwindow->set_socket_map(false, pcursocket);
        }
        else
        {
            this->pmainwindow->set_socket_map(true, pcursocket);
        }

        return;
    }

    if(pcursocket == client2 || client2 == nullptr)
    {
        NetworkData cmd = NetworkData(OPCODE::REJECT_OP, data.data1, "", "");
        if(data.data1.isEmpty()== true)
        {
            //error user name;
            this->SendToClient(pcursocket, cmd);
            this->pmainwindow->remove_client(pcursocket);
            return;
        }

        QString color1 = this->pmainwindow->get_client1_color();

        if(color1 == data.data2)
        {
            //error color
            this->SendToClient(pcursocket, cmd);
            this->pmainwindow->remove_client(pcursocket);
            return;
        }


        QString color2 = data.data2;
        if (data.data2 == "NONE" ||  data.data2.isEmpty() == true)
        {
            if(color1 == QString("WHITE"))
            {
                color2 = QString("BLACK");
            }
            else if(color1 == QString("BLACK"))
            {
                color2 = QString("WHITE");
            }
            else
            {
                //error color
                this->SendToClient(pcursocket, cmd);
                this->pmainwindow->remove_client(pcursocket);
                return;
            }
        }


        if(data.data3.isEmpty() == true)
        {
            //error room number
            this->SendToClient(pcursocket, cmd);
            this->pmainwindow->remove_client(pcursocket);
            return;
        }

        this->pmainwindow->set_client2_color(color2);
        if(this->pmainwindow->get_client2_color() ==QString("BLACK"))
        {
            this->pmainwindow->set_socket_map(false, pcursocket);
        }
        else
        {
            this->pmainwindow->set_socket_map(true, pcursocket);
        }

    }
    QString userName1 = this->pmainwindow->get_client1_name();
    QString userName2 = this->pmainwindow->get_client2_name();
    QString colorClient1 = this->pmainwindow->get_client1_color();
    QString colorClient2 = this->pmainwindow->get_client2_color();
    QString roomNum1;
    QString roomNum2;
    NetworkData readyClient1(OPCODE::READY_OP, userName2, colorClient1, roomNum1);
    NetworkData readyClient2(OPCODE::READY_OP, userName1, colorClient2, roomNum2);
    this->SendToClient(client1, readyClient1);
    this->SendToClient(client2, readyClient2);

    //begin to game,create board;
    this->pmainwindow->create_board();
}
