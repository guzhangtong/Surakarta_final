#include "endstagemessage.h"
#include "../Board.h"

EndStageMessage::EndStageMessage(MainWindow *pmain, QObject *parent)
    : StageMessage{pmain, parent}
    , data(OPCODE::END_OP, QString(), QString(), QString())
{}

void EndStageMessage::TimeoutEndGame(bool isWhiteTimeout)
{
    data.data1 = QString();
    int reason = static_cast<int>(SurakartaEndReason::TIMEOUT);
    data.data2 = QString::number(reason);
    PieceColor timeoutColor = PieceColor::NONE;
    if(isWhiteTimeout)
    {
        timeoutColor = PieceColor::WHITE;
    }
    else
    {
        timeoutColor = PieceColor::BLACK;
    }
    int ntimeoutColor = static_cast<int>(timeoutColor);
    data.data3 = QString::number(ntimeoutColor);
}

void EndStageMessage::EndGameReason(bool isWhiteLose, const SurakartaEndReason& reason)
{
    data.data1 = QString();
    int nreason = static_cast<int>(reason);
    data.data2 = QString::number(nreason);
    PieceColor loserColor = PieceColor::NONE;
    if(isWhiteLose)
    {
        loserColor = PieceColor::WHITE;
    }
    else
    {
        loserColor = PieceColor::BLACK;
    }
    int nloserColor = static_cast<int>(loserColor);
    data.data3 = QString::number(nloserColor);
}

const NetworkData& EndStageMessage::ToNetworkData()
{
    /*
     *
     *     ---SurakartaIllegalMoveReason Item---
     *     0:LEGAL,                     // unused
     *     1:LEGAL_CAPTURE_MOVE,        // capture a opponent's piece, and the move consists at least one corner loop
     *     2:LEGAL_NON_CAPTURE_MOVE,    // just as the name
     *     3:ILLIGAL,                   // unused
     *     4:NOT_PLAYER_TURN,           // move when it's not the player's turn.
     *     5:OUT_OF_BOARD,              // from or to position is out of board
     *     6:NOT_PIECE,                 // move a position that is not a piece
     *     7:NOT_PLAYER_PIECE,          // move a piece that is not the player's
     *     8:ILLIGAL_CAPTURE_MOVE,      // try to capture a opponent's piece, but the move can't consist any corner loop
     *     9:ILLIGAL_NON_CAPTURE_MOVE,  // otherwise
     *     10:GAME_ALREADY_END,          // unused
     *     11:GAME_NOT_START             // unused
     *
     *     ---SurakartaEndReason Item---
     *     0:NONE,          // not end
     *     1:STALEMATE,     // both players can't make more move
     *     2:CHECKMATE,     // one player's all pieces are captured
     *     3:TRAPPED,       // unused, one player's pieces are all trapped, no legal move can be made.
     *     4:RESIGN,        // one player resigns.
     *     5:TIMEOUT,       // one player's time is out.
     *     6:ILLIGAL_MOVE,  // one player makes an illegal move
     *
     *     ---PieceColor Item---
     *     0:BLACK,
     *     1:WHITE,
     *     2:NONE,
     *     3:UNKNOWN
     *
     *     data1:   if data2 is "6" of the SurakartaEndReason Item be mean ILLIGAL_MOVE, the data1 is one of the SurakartaIllegalMoveReason Item,
     *              or data2 is other of the SurakartaEndReason Item,  thie data1 is "";
     *     data2 is one of the SurakartaEndReason Item, if data2 is the "1" be mean STALEMATE, is "6" be mean  ILLIGAL_MOVE
     *     data3 is one of the SurakartaEndReason Item,
     */
    return data;
}
