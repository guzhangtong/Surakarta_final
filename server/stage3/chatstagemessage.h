#ifndef CHATSTAGEMESSAGE_H
#define CHATSTAGEMESSAGE_H

#include "stagemessage.h"

class MainWindow;
class ChatStageMessage : public StageMessage
{
public:
    explicit ChatStageMessage(MainWindow* pmain, QObject *parent = nullptr);

    virtual const NetworkData& ToNetworkData();

private:
    NetworkData data;
};

#endif // CHATSTAGEMESSAGE_H
