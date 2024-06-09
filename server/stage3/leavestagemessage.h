#ifndef LEAVESTAGEMESSAGE_H
#define LEAVESTAGEMESSAGE_H

#include "stagemessage.h"

class MainWindow;
class LeaveStageMessage : public StageMessage
{
public:
    explicit LeaveStageMessage( MainWindow* pmainwindow, QObject *parent = nullptr);

    virtual const NetworkData& ToNetworkData();

private:

    NetworkData data;
};

#endif // LEAVESTAGEMESSAGE_H
