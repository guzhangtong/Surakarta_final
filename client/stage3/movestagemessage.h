#ifndef MOVESTAGEMESSAGE_H
#define MOVESTAGEMESSAGE_H

#include "stagemessage.h"

class MainWindow;
class MoveStageMessage : public StageMessage
{
public:
    explicit MoveStageMessage(MainWindow* pmain, ConnectInfo *pinfo, QObject *parent = nullptr);
    virtual const NetworkData& ToNetworkData();

    void saveClickStonePoint(const QPoint& pt);
    void clickStone();
    void saveMoveFromPoint(const QPoint& pt);
    void saveMoveToPoint(const QPoint& pt);
    void moveStone();

private:
    MainWindow* pmainwindow;
    NetworkData data;
    QPoint clickPoint;
    QPoint fromPoint;
    QPoint toPoint;
};

#endif // MOVESTAGEMESSAGE_H
