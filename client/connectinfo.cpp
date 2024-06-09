#include "connectinfo.h"
#include "networksocket.h"

// ConnectInfo 构造函数，初始化连接信息
ConnectInfo::ConnectInfo(QObject *parent, const QString &userName, const QString &color, const QString &ip, const QString &port)
    : QObject(parent)
    , userName(userName)
    , color(color)
    , roomNum("1")
    , ip(ip)
    , port(10086)
    , vecSocket{nullptr, nullptr}
{
    bool ok = false;
    int nport = port.toInt(&ok);
    if(ok)
    {
        this->port = nport; // 如果端口转换成功，则更新端口号
    }
}

// 获取用户名
QString ConnectInfo::GetUserName() const
{
    return this->userName;
}

// 获取颜色
QString ConnectInfo::GetColor() const
{
    return this->color;
}

// 获取IP地址
QString ConnectInfo::GetIp() const
{
    return this->ip;
}

// 获取端口号
int ConnectInfo::GetPort() const
{
    return this->port;
}

// 获取房间号
QString ConnectInfo::GetRoomNum() const
{
    return this->roomNum;
}

// 连接到服务器
void ConnectInfo::ConnectToServer(SOCKET_INDEX socketIndex)
{
    // 如果对应索引的Socket为空，则创建新的NetworkSocket对象
    if(vecSocket[socketIndex] == nullptr)
    {
        vecSocket[socketIndex] = new NetworkSocket(new QTcpSocket(this), this);
        connect(this->vecSocket[socketIndex]->base(),
                &QTcpSocket::connected ,
                this,
                &ConnectInfo::Connected);

        connect(this->vecSocket[socketIndex]->base(),
                &QTcpSocket::errorOccurred ,
                this,
                &ConnectInfo::hasConnectError);

        connect(this->vecSocket[socketIndex], &NetworkSocket::receive,
                this, &ConnectInfo::receiveMessage);

    }
    // 尝试连接到服务器
    vecSocket[socketIndex]->hello(this->ip, port);
    //this->vecSocket[HumenSocket_Index]->base()->waitForConnected(2000);

}

// 断开与服务器的连接
void ConnectInfo::DisconnectToServer(SOCKET_INDEX socketIndex)
{
    // 如果对应索引的Socket不为空，则执行bye操作
    if(this->vecSocket[socketIndex] != nullptr)
    {
        this->vecSocket[socketIndex]->bye();
    }
}

// 连接成功槽函数，发出hasConnected信号
void ConnectInfo::Connected()
{
    emit this->hasConnected();
}

// 连接错误槽函数，发出hasConnectError信号
void ConnectInfo::ConnectError(QAbstractSocket::SocketError error)
{
    emit this->hasConnectError();
}

void ConnectInfo::receiveMessage(NetworkData data)
{
    QObject *psend = this->sender();
    if(psend == this->vecSocket[HumenSocket_Index])
    {
        emit this->receive(HumenSocket_Index, data);
    }
    else if(psend == this->vecSocket[AISocket_Index])
    {
        emit this->receive(AISocket_Index, data);
    }
    else
    {
        emit this->receive(NoBadySocket, data);
    }

}

// 发送消息函数
void ConnectInfo::SendMessage(SOCKET_INDEX socketIndex, const NetworkData& sendData)
{
    // 如果对应索引的Socket不为空且索引有效，则发送数据
    if(this->vecSocket[socketIndex] != nullptr && socketIndex != NoBadySocket)
    {
        this->vecSocket[socketIndex]->send(sendData);
    }
}
