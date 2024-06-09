#ifndef CHATSTAGEMESSAGE_H
#define CHATSTAGEMESSAGE_H

#include "stagemessage.h"

class ChatStageMessage : public StageMessage
{
public:
    explicit ChatStageMessage(ConnectInfo* pinfo, QObject *parent = nullptr);
    virtual const NetworkData& ToNetworkData();

    void ReposeRestart(bool isAgreeRestart);
    void RequestRestart();

private:
    NetworkData data;
};

#endif // CHATSTAGEMESSAGE_H
