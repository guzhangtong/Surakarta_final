#ifndef RESIGNSTAGEMESSAGE_H
#define RESIGNSTAGEMESSAGE_H

#include "stagemessage.h"

class ResignStageMessage : public StageMessage
{
public:
    explicit ResignStageMessage(ConnectInfo *pinfo, QObject *parent = nullptr);
    virtual const NetworkData& ToNetworkData();


private:
    NetworkData data;
};

#endif // RESIGNSTAGEMESSAGE_H
