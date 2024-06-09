#ifndef AIGAME_H
#define AIGAME_H
#include "Board.h"
class AIGame:public Board
{
    Q_OBJECT
public:

    bool ai_mode[2] = {false, false};

    AIGame(MoveStageMessage *pmsg = nullptr, QWidget *parent=0);
    MoveStageMessage *pmoveStageMsg{nullptr};
    QPoint AI_from,AI_to,AI_ID;
    // virtual void click(int id,int  row,int col);
    void AIgo();
    void getAllMove(QVector<Step *> &steps);
    void setAIMOVE();
    void fakeMove(Step* step);
    void unfakeMove(Step* step);
    int calcscore();
    int  getMaxScore(int level, int curMinScore);
    int  getMinScore(int level, int curMaxScore);
    Step* getBestMove();
    int _level;
    int flag_ifgo=0;
    void mouseReleaseEvent(QMouseEvent *ev);
private slots:
    void userChanged(bool user);
    void aiRunTimeOut();
};

#endif // AIGAME_H
