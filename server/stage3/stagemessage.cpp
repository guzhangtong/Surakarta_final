#include "stagemessage.h"
#include "../mainwindow.h"

StageMessage::StageMessage(MainWindow *pmain, QObject *parent)
    : QObject{parent}
    , pmainwindow(pmain)
{}


QTcpSocket* StageMessage::GetSocket(bool isWhite)
{
    if(this->pmainwindow != nullptr)
    {
        return this->pmainwindow->get_socket_map(isWhite);
    }

    return nullptr;
}

void StageMessage::SendMessage(QTcpSocket* psocket)
{
    if(this->pmainwindow != nullptr && psocket !=nullptr)
    {
        this->pmainwindow->send_to_client(psocket, this->ToNetworkData());
    }
}
