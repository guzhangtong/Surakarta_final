#ifndef LEAVESTAGEMESSAGE_H
#define LEAVESTAGEMESSAGE_H

#include "stagemessage.h"

class LeaveStageMessage : public StageMessage
{
public:
    explicit LeaveStageMessage(ConnectInfo* pinfo, QObject *parent = nullptr);

    virtual const NetworkData& ToNetworkData();


private:
    NetworkData data;
};

#endif // LEAVESTAGEMESSAGE_H
