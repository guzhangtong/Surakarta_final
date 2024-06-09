#ifndef ENDREVICESTAGEOP_H
#define ENDREVICESTAGEOP_H

#include "receivestageop.h"

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

class MainWindow;
class EndReviceStageOp : public ReceiveStageOp
{
public:
    explicit EndReviceStageOp(MainWindow* pmain, QObject *parent = nullptr);

private:
    virtual bool IsMyOp(const NetworkData& data);
    virtual void DoSomething(SOCKET_INDEX socketIndex, const NetworkData& data);
private:
    MainWindow *pmainwindow;
};

#endif // ENDREVICESTAGEOP_H
