#ifndef STAGEMESSAGE_H
#define STAGEMESSAGE_H

#include <QObject>
#include "../networkdata.h"
#include "../connectinfo.h"

class ConnectInfo;
class StageMessage : public QObject
{
    Q_OBJECT
public:
    explicit StageMessage(ConnectInfo* pinfo, QObject *parent = nullptr);
    void SendMessage(SOCKET_INDEX socketIndex);

    virtual const NetworkData& ToNetworkData() = 0;

signals:

private:
    ConnectInfo* pconnectInfo;
};

#endif // STAGEMESSAGE_H
