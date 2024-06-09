#ifndef ENDSTAGEMESSAGE_H
#define ENDSTAGEMESSAGE_H

#include "stagemessage.h"
#include "../Board.h"

class MainWindow;
class EndStageMessage : public StageMessage

{
public:
    explicit EndStageMessage(MainWindow* pmain, QObject *parent = nullptr);
    virtual const NetworkData& ToNetworkData();

    void TimeoutEndGame(bool isWhiteTimeout);
    void EndGameReason(bool isWhiteLose, const SurakartaEndReason& reason);

private:
    NetworkData data;
};

#endif // ENDSTAGEMESSAGE_H
