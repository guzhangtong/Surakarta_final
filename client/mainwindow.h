#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Board.h"
#include <QTimer>
#include "AIGame.h"
#include "connectinfo.h"
#include <QVector>

namespace Ui {
class MainWindow;
}

class ReceiveStageOp;
class MoveStageMessage;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(ConnectInfo* pinfo, QWidget *parent = nullptr);
    ~MainWindow();

    void SetConnectInfo(ConnectInfo *pinfo);
    void SetBlackUserNameShow(const QString& name);
    void SetWhiteUserNameShow(const QString& name);
    void ChangeRunTurn(bool brun);
    bool GetIsWhiteTurn();
    void ChangePlayTime(bool isWhite, int time);
    void EndGameWhoLose(bool isWhite);

    void ClickBoardStone(const QPoint& pt);
    void MoveBoardStone(const QPoint& fromPt, const QPoint& toPt);
    void RestartGame(bool isRestart);

    QString EndGameResult(bool isWhiteWin);
    void SetThinkTime(bool isWhite, int time);

private slots:
    void AiPlayerConnected();
    void receiveMessage(SOCKET_INDEX socketIndex, NetworkData data);

    void chooseModel();
    void chooseModel_2();
    void chooseModel_3();
    void chooseModel_4();
    void slot_endGameBox();
    void endGameBox(QString msg);
    void undo();
    void gamePlayTimeout();
    void userChanged();
    void reset();
private:
    Ui::MainWindow *ui;
 //   Board* m_board{};
    AIGame* m_aigame{};
    QTimer gamePlayTimer;
    int user1Count = 10;
    int user2Count = 10;

    ConnectInfo *pconnectInfo;
    QVector<ReceiveStageOp*> vecReviceStageOp;
    MoveStageMessage *pmoveStageMessage{nullptr};
};

const int countdownSecs = 60;

#endif // MAINWINDOW_H
