#ifndef BOARD_H
#define BOARD_H
#include <QWidget>
#include "qtimer.h"
#include "stone.h"
#include "QPoint"
#include <QVector>
#include <QMap>
#include <QMainWindow>
#include <qpushbutton.h>
#include "step.h"



enum class SurakartaIllegalMoveReason : int {
    LEGAL,                     // unused
    LEGAL_CAPTURE_MOVE,        // capture a opponent's piece, and the move consists at least one corner loop
    LEGAL_NON_CAPTURE_MOVE,    // just as the name
    ILLIGAL,                   // unused
    NOT_PLAYER_TURN,           // unused, move when it's not the player's turn.
    OUT_OF_BOARD,              // from or to position is out of board
    NOT_PIECE,                 // move a position that is not a piece
    NOT_PLAYER_PIECE,          // move a piece that is not the player's
    ILLIGAL_CAPTURE_MOVE,      // try to capture a opponent's piece, but the move can't consist any corner loop
    ILLIGAL_NON_CAPTURE_MOVE,  // otherwise
    GAME_ALREADY_END,          // unused
    GAME_NOT_START             // unused
};

enum class SurakartaEndReason : int {
    NONE,          // not end
    STALEMATE,     // both players can't make more move
    CHECKMATE,     // one player's all pieces are captured
    TRAPPED,       // unused, one player's pieces are all trapped, no legal move can be made.
    RESIGN,        // unused, one player resigns.
    TIMEOUT,       // unused, one player's time is out.
    ILLIGAL_MOVE,  // one player makes an illegal move
};

using PieceColorMemoryType = int;
enum class PieceColor : PieceColorMemoryType
{
    BLACK,
    WHITE,
    NONE,
    UNKNOWN
};

class MoveStageMessage;
class EndStageMessage;
class Board:public QWidget
{
    Q_OBJECT
public:
    explicit Board(MoveStageMessage*pmoveStageMsg, EndStageMessage* pendStageMsg, QWidget *parent=0);
    QVector<Stone> _s;
    QVector<Stone> _s_back;
    QVector<Stone> _s_reset;
    QVector<Step*> _steps;
    int _select=-1;
    int step=-1;
    int clickPosRow,clickPosCol;
    bool selectPos=false;
    bool bTurn;
    bool nearDeath_1=false;
    bool nearDeath_2=false;

    QMap<bool, int> mapThinkTime;
    QTimer thinkPlayTimer;

    int can_go_x[40],can_go_y[40];
    QPoint center(int row,int col);//返回棋子坐标
    QPoint center(int id);//返回棋子坐标
    void moveStone(int moveid, int killid, int row, int col);
    void moveStone(int moveid, int row, int col);
    bool getRowCol(QPoint pt,int& x,int& y);
    void drawStone( QPainter& painter,int id);
    void paintEvent(QPaintEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    bool canMovel(int moveid,int x,int y,int killid);
    void saveStep(int moveid, int killid, int row, int col, QVector<Step*>& steps);
    void reliveStone(int id);
    void killStone(int id);
    void undo();
    bool getUser1(){return bTurn;}
    void reset();
    bool click(int id,int  row,int col);
    bool click(QPoint pt);

    void setTurn(bool b);
    void GameFinish(bool isWhiteLose, SurakartaEndReason reason);

private slots:
    void ThinkTimeTimeOut();
    void SyncTurnTimeOut();
    void GameFinishSlot(bool isWhiteLose);


signals:
    void sig_userChanged();
    void sig_finish(bool user1);

protected:
    void copyStone(QVector<Stone>&s1,QVector<Stone>&s2);
    void init();

private:
    MoveStageMessage* pmoveStageMessage{nullptr};
    EndStageMessage* pendStageMessage{nullptr};
};

const int BOARD_GRAD_SIZE=6;//棋盘大小
const int bianyuan=100;
const int CHESS_SIZE=15;//棋子大小
const int MARK_SIZE=10;
const int BLOCK_SIZE=40;//格子大小
const int POS_OFFSET=BLOCK_SIZE*0.6;//模糊度
const int THINK_TIME=60;

#endif // BOARD_H
