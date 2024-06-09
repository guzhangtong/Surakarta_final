#include "serverreceivestageop.h"
#include "../mainwindow.h"
ServerReceiveStageOp::ServerReceiveStageOp(MainWindow *pserver, QObject *parent)
    : QObject{parent}
    , psocketServer(pserver)
{

}

void ServerReceiveStageOp::SendToClient(QTcpSocket* another, NetworkData data)
{
    if(this->psocketServer != nullptr)
    {
        this->psocketServer->send_to_client(another, data);
    }
}

bool ServerReceiveStageOp::DoOp(QTcpSocket* pcursocket, QTcpSocket*client1, QTcpSocket* client2, const NetworkData &data)
{
    if(this->IsMyOp(data))
    {
        this->DoSomeThing(pcursocket, client1, client2, data);
        return true;
    }
    return false;
}
