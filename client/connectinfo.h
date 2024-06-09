#ifndef CONNECTINFO_H
#define CONNECTINFO_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QAbstractSocket>
#include "networkdata.h"

enum SOCKET_INDEX{
    AISocket_Index = 0,
    HumenSocket_Index,
    NoBadySocket
};

class NetworkSocket;
class ConnectInfo : public QObject
{
    Q_OBJECT
public:
    ConnectInfo(QObject *parent,
                const QString& userName,
                const QString& color,
                const QString& ip,
                const QString& port);

    QString GetUserName() const;
    QString GetColor() const;
    QString GetIp() const;
    int GetPort() const;
    QString GetRoomNum() const;

public:
    void ConnectToServer(SOCKET_INDEX socketIndex);
    void DisconnectToServer(SOCKET_INDEX socketIndex);

    void SendMessage(SOCKET_INDEX socketIndex, const NetworkData& sendData);

public slots:
    void Connected();
    void ConnectError(QAbstractSocket::SocketError error);
    void receiveMessage(NetworkData data);


signals:
    void hasConnected();
    void hasConnectError();
    void receive(SOCKET_INDEX socketIndex, NetworkData data);

private:
    QString userName;
    QString color;
    QString roomNum;
    QString ip;
    int port;
    NetworkSocket* vecSocket[2]; //one AI, one humen;
};

#endif // CONNECTINFO_H
