#ifndef READYSTAGEMESSAGE_H
#define READYSTAGEMESSAGE_H

#include "stagemessage.h"

class ReadyStageMessage : public StageMessage
{
public:
    explicit ReadyStageMessage(const QString& userName, const QString& color, const QString& roomNum, ConnectInfo *pinfo, QObject *parent = nullptr);
    virtual const NetworkData& ToNetworkData();


private:
    NetworkData data;
};

#endif // READYSTAGEMESSAGE_H
