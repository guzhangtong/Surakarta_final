#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Board.h"
#include <QMainWindow>
#include <QSet>
#include <networkdata.h>
#include <networkserver.h>
#include <QMessageBox>
#include <QTimer>
#include <logger.h>
#include <QVector>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class ServerReceiveStageOp;
class Board;
class MoveStageMessage;
class EndStageMessage;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    int port = 10086;
    const int max_clients = 2;
    const int max_round = 40, max_step = 3;
    int time_round, time_step;
    QString name_1 = "", name_2 = "";
    QString color_1 = "", color_2 = "";
    Ui::MainWindow *ui;
    QSet<QTcpSocket*> clients;
    NetworkServer* server = nullptr;
    QTcpSocket* client1 = nullptr;
    QTcpSocket* client2 = nullptr;
    QTcpSocket* current_client = nullptr;
    QTimer* timer_round = nullptr;
    QTimer* timer_step = nullptr;
    Logger *logger; // 日志模块
    const QString rowString;
    const QString colString;

    QVector<ServerReceiveStageOp*> vecStageOp;
    Board *pboard;
    QMap<bool, QTcpSocket*> turnSocketMap;//use be divide the black socket and white socket;
    MoveStageMessage *pmoveStageMessage{nullptr};
    EndStageMessage *pendStageMessage{nullptr};

public:
    const QString& get_client1_name();
    const QString& get_client2_name();

    const QString& get_client1_color();
    const QString& get_client2_color();
    void set_client1_color(const QString& color);
    void set_client2_color(const QString& color);
    void create_board();

    bool get_is_white_turn();

    void set_socket_map(bool isWhite, QTcpSocket* psocket);
    QTcpSocket* get_socket_map(bool isWhite);
    void game_finish(bool isWhiteLose, SurakartaEndReason reason);
    void click_board_stone(const QPoint& pt);
    bool move_board_stone(const QPoint& fromPt, const QPoint& toPt);
    bool restart_game();

    void send_to_client(QTcpSocket* another, NetworkData data);
    void remove_client(QTcpSocket* client);

private slots:
    void listen_port();

    void restart_server();

    void receive_from_client(QTcpSocket* client, NetworkData data);

    void cut_time();
};
#endif // MAINWINDOW_H
