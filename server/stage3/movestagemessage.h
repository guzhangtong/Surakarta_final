#ifndef MOVESTAGEMESSAGE_H
#define MOVESTAGEMESSAGE_H

#include "stagemessage.h"

class MainWindow;
class QTcpSocket;
class MoveStageMessage : public StageMessage
{
public:
    explicit MoveStageMessage(MainWindow* pmain, QObject *parent = nullptr);
    virtual const NetworkData& ToNetworkData();

public:
    void thinkTimerToWho(bool isWhite, int time);
    void turnToWho(bool isWhite);
    void clickStone(bool isWhite, const QPoint& pt);

private:
    MainWindow* pmainwindow;
    NetworkData data;
};

#endif // MOVESTAGEMESSAGE_H
