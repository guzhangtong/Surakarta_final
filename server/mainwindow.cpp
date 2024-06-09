#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "./stage3/readystageop.h"
#include "./stage3/movestagemessage.h"
#include "./stage3/endstagemessage.h"
#include "./stage3/resignstageop.h"
#include "./stage3/leavestageop.h"
#include "./stage3/movestageop.h"
#include "./stage3/chatstageop.h"
#include "Board.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , rowString("ABCDEF")
    , colString("123456")
    , pboard(nullptr)
{
    ui->setupUi(this);

    server = new NetworkServer(this); // 创建一个服务器对象，其父对象为当前窗口

    // 定义定时器，用于处理计时工作
    timer_round = new QTimer;
    timer_step = new QTimer;
    connect(timer_step, SIGNAL(timeout()), this, SLOT(cut_time())); // 绑定倒计时函数

    // 创建 Logger 对象
    logger = new Logger;

    ui->ShowClient1->setReadOnly(true);
    ui->ShowClient2->setReadOnly(true);
    ui->receive_edit->setReadOnly(true);
    ui->time_edit->setReadOnly(true);

    connect(ui->PortButton, &QPushButton::clicked, this, &MainWindow::listen_port); // 开启服务器监听
    connect(ui->restart, &QPushButton::clicked, this, &MainWindow::restart_server); // 重启服务器
    connect(server, &NetworkServer::receive, this, &MainWindow::receive_from_client);
    // receive 是服务端收到消息后发出的信号，receive_from_client 是处理这个信号的槽函数

    pmoveStageMessage = new MoveStageMessage(this, this);
    pendStageMessage = new EndStageMessage(this, this);

    turnSocketMap.insert(true, nullptr);
    turnSocketMap.insert(false, nullptr);
    vecStageOp.push_back(new MoveStageOp(this, this));
    vecStageOp.push_back(new ReadyStageOp(this, this));
    vecStageOp.push_back(new ResignStageOp(this, this));
    vecStageOp.push_back(new LeaveStageOp(this, this));
    vecStageOp.push_back(new ChatStageOp(this, this));
}

MainWindow::~MainWindow() {
    delete ui;
    delete server;
}

void MainWindow::listen_port() {
    this->port = ui->PortEdit->text().toInt();
    server->listen(QHostAddress::Any, this->port);
    // 一行代码搞定监听，它会在所有 ip 地址上监听指定端口 port
    // 所谓监听，就是在网络上服务器要开始盯住某个端口，此时客户端可以通过这个端口和服务器取得联系
    // QHostAddress::Any 表示监听所有 ip 地址，在不考虑安全的情况下，这是一个比较方便的选择，你不用纠结为什么
    ui->PortButton->setEnabled(false);
    ui->PortEdit->setReadOnly(true);
    ui->PortEdit->setText("Listening...");
}

void MainWindow::remove_client(QTcpSocket* client) {
    if (client == client1) {
        client1->deleteLater();
        client1 = nullptr;
        ui->ShowClient1->setText("");
        if(this->get_client1_color() ==QString("BLACK"))
        {
            this->set_socket_map(false, nullptr);
        }
        else
        {
            this->set_socket_map(true, nullptr);
        }
    }
    else if (client == client2) {
        client2->deleteLater();
        client2 = nullptr;
        ui->ShowClient2->setText("");

        if(this->get_client2_color() ==QString("BLACK"))
        {
            this->set_socket_map(false, nullptr);
        }
        else
        {
            this->set_socket_map(true, nullptr);
        }
    }
    ui->receive_edit->setPlainText("");
    clients.remove(client);
}

void MainWindow::receive_from_client(QTcpSocket* client, NetworkData data) {
    // client 是发送消息的客户端，data 是消息内容
    // 以下代码首先处理客户端的连接和断开，然后处理从客户端收到的消息，显示在界面上并转发给另一个客户端
    // 你们在游戏里要做类似的事情，只不过处理不仅仅是显示，而是对应的游戏逻辑

    if (!clients.contains(client)) {
        if (clients.size() >= max_clients) {
            QMessageBox::warning(this, "Warning", "The server is full!");
            return;
        }
        clients.insert(client);
        if (!client1){
            client1 = client;
            name_1 = data.data1;
        }
        else if (!client2) {
            client2 = client;
            name_2 = data.data1;
        }

    }

    current_client = client;   // 记录当前发送指令的客户端，用于超时获取颜色
    logger->log(client, data); // 记录所有指令，发送指令的客户端以及data内容


    // if (data.op == OPCODE::LEAVE_OP) {
    //     remove_client(client);
    //     return;
    // }

    // 判断双方READY时是否为同一个颜色
    // if (data.op == OPCODE::READY_OP) {
    //     // 收集双方的执棋颜色
    //     if (data.data2 == "NONE"){
    //         if (color_1 == "" && color_2 == ""){
    //             data.data2 = "BLACK";
    //         } else if (color_1 == "BLACK" || color_2 == "BLACK") {
    //             data.data2 = "WHITE";
    //         } else if (color_1 == "WHITE" || color_2 == "WHITE") {
    //             data.data2 = "BLACK";
    //         }
    //     }
    //     if (client == client1) {
    //         color_1 = data.data2;
    //     }
    //     if (client == client2) {
    //         color_2 = data.data2;
    //     }

    //     qDebug() << color_1 << color_2;

    //     if (color_1 != "" && color_2 != ""){
    //         if (color_1 == color_2 && color_1 != "NONE"){
    //             // 若服务端判断客户端对局准备不合法，会向非法一方发送 REJECT_OP 拒绝连接
    //             color_1 = color_2 = "";
    //             NetworkData cmd = NetworkData(OPCODE::REJECT_OP, data.data1, "", "");
    //             send_to_client(current_client, cmd);
    //             return;
    //         } else if (color_1 == color_2 && color_1 == "NONE") {
    //             color_1 = "BLACK";
    //             color_2 = "WHITE";
    //         } else {
    //             if (color_1 == "WHITE") color_2 = "BLACK";
    //             else color_2 = "WHITE";

    //             if (color_2 == "WHITE") color_1 = "BLACK";
    //             else color_1 = "WHITE";
    //         }
    //     }

    // }

    // // 行棋合法性判断
    // if (data.op == OPCODE::MOVE_OP) {
    //     // 接收移动命令后关闭之前的倒计时，开始新的倒计时
    //     if (time_step == 0){
    //         // 倒计时结束 不进入更多个判断
    //         timer_step->stop();
    //         return;
    //     }
    //     timer_step->stop();
    //     time_step = max_step;
    //     timer_step->start(1000);

    //     // 获取当前执棋颜色
    //     QString win_color;
    //     if (current_client == client1) win_color = color_1;
    //     if (current_client == client2) win_color = color_2;



    //     //移动指令的构造 NetworkData(OPCODE::END_OP, "1", "2", "win_color");

    //     //     1-> MoveReason
    //     //     LEGAL,                     // unused
    //     //     LEGAL_CAPTURE_MOVE,        // capture a opponent's piece, and the move consists at least one corner loop
    //     //     LEGAL_NON_CAPTURE_MOVE,    // just as the name
    //     //     ILLIGAL,                   // unused
    //     //     NOT_PLAYER_TURN,           // move when it's not the player's turn.
    //     //     OUT_OF_BOARD,              // from or to position is out of board
    //     //     NOT_PIECE,                 // move a position that is not a piece
    //     //     NOT_PLAYER_PIECE,          // move a piece that is not the player's
    //     //     ILLIGAL_CAPTURE_MOVE,      // try to capture a opponent's piece, but the move can't consist any corner loop
    //     //     ILLIGAL_NON_CAPTURE_MOVE,  // otherwise
    //     //     GAME_ALREADY_END,          // unused
    //     //     GAME_NOT_START             // unused


    //     //     2-> EndReason
    //     //     NONE,          // not end
    //     //     STALEMATE,     // both players can't make more move
    //     //     CHECKMATE,     // one player's all pieces are captured
    //     //     TRAPPED,       // unused, one player's pieces are all trapped, no legal move can be made.
    //     //     RESIGN,        // one player resigns.
    //     //     TIMEOUT,       // one player's time is out.
    //     //     ILLIGAL_MOVE,  // one player makes an illegal move

    //     //  正常情况
    //     NetworkData cmd = NetworkData(OPCODE::MOVE_OP, "", "MoveReason", "EndReason");
    // }


    // 一方认输
    // if (data.op == OPCODE::RESIGN_OP) {
    //     QString win_color;
    //     if (client == client1) win_color = color_1;
    //     if (client == client2) win_color = color_2;
    //     NetworkData cmd = NetworkData(OPCODE::END_OP, "", "RESIGN", win_color);

    //     send_to_client(client1, cmd);
    //     send_to_client(client2, cmd);
    // }



    // 获取op
    QString opString;
    NetworkData printData  = data;
    switch(data.op) {
    case OPCODE::CHAT_OP:
        opString = "CHAT_OP";
        break;
    case OPCODE::READY_OP:
        opString = "READY_OP";
        break;
    case OPCODE::MOVE_OP:
        opString = "MOVE_OP";
        if(data.data3.isEmpty() || data.data3 == QString("1") )
        {
            QStringList fromPoints = data.data1.split(",");
            QStringList toPoints = data.data2.split(",");
            if(fromPoints.size() == 2 && toPoints.size() == 2)
            {
                QPoint fromPos(fromPoints[0].toInt(), fromPoints[1].toInt());
                QPoint toPos(toPoints[0].toInt(), toPoints[1].toInt());
                int row = 0;
                int col = 0;
                if(this->pboard->getRowCol(fromPos, row, col) == true)
                {
                    printData.data1 = QString() + this->rowString[row] + this->colString[col];
                }

                if(this->pboard->getRowCol(toPos, row, col) == true)
                {
                    printData.data2 = QString() + this->rowString[row] + this->colString[col];
                }
            }
        }
        break;
    case OPCODE::RESIGN_OP:
        opString = "RESIGN_OP";
        break;
    case OPCODE::LEAVE_OP:
        opString = "LEAVE_OP";
        break;
    case OPCODE::END_OP:
        opString = "END_OP";
        break;
    case OPCODE::REJECT_OP:
        opString = "REJECT_OP";
        break;
    default:
        opString = "UNKNOW_OP";
        break;
    }

    // 发送指令

    if (client == client1) {
        // if (client2)
        // {
        //     ui->ShowClient1->setText(opString + ' ' + data.data1 + ' ' + data.data2 + ' ' + data.data3);
        //     send_to_client(client2, data);
        // }

        ui->receive_edit->appendPlainText(QString("receive msg from ") + name_1 + QString(", msg is :  ") + opString + ' ' + printData.data1 + ' ' + printData.data2 + ' ' + printData.data3);
    }
    else if (client == client2) {
        // if (client1) {
        //     ui->ShowClient2->setText(opString + ' ' + data.data1 + ' ' + data.data2 + ' ' + data.data3);
        //     send_to_client(client1, data);
        // }
        ui->receive_edit->appendPlainText(QString("receive msg from ") + name_2 + QString(", msg is :  ") + opString + ' ' + printData.data1 + ' ' + printData.data2 + ' ' + printData.data3);
    }
    else
    {
        ui->receive_edit->appendPlainText(QString("receive msg error, from ") +  QString("Unknown client"));
        // QMessageBox::warning(this, "Warning", "Unknown client!");
    }


    for(auto& it : this->vecStageOp)
    {
        if(it->DoOp(current_client, client1, client2, data) == true)
        {
            break;
        }
    }
}

const QString& MainWindow::get_client1_name()
{
    return this->name_1;
}

const QString& MainWindow::get_client2_name()
{
    return this->name_2;
}

const QString& MainWindow::get_client1_color()
{
    return this->color_1;
}

const QString& MainWindow::get_client2_color()
{
    return this->color_2;
}

void  MainWindow::set_client1_color(const QString& color)
{
    this->color_1 = color;
}

void  MainWindow::set_client2_color(const QString& color)
{
    this->color_2 = color;
}
void MainWindow::create_board()
{
    if(this->pboard == nullptr)
    {
        this->pboard = new Board(this->pmoveStageMessage, this->pendStageMessage, this);
        this->pboard->hide();
        qDebug()<< "MainWindow::create_board() " << "create board";
    }
    else
    {
        this->pboard->reset();
        qDebug() << "MainWindow::create_board() " << "reset board";
    }
}

bool MainWindow::get_is_white_turn()
{
    if(this->pboard != nullptr)
    {
        return this->pboard->bTurn;
    }

    return false;
}

void MainWindow::set_socket_map(bool isWhite, QTcpSocket* psocket)
{
    this->turnSocketMap[isWhite] = psocket;
}
QTcpSocket* MainWindow::get_socket_map(bool isWhite)
{
    return this->turnSocketMap[isWhite];
}

void MainWindow::game_finish(bool isWhiteLose, SurakartaEndReason reason)
{
    if(this->pboard != nullptr)
    {
        this->pboard->GameFinish(isWhiteLose, reason);
    }
}

void MainWindow::click_board_stone(const QPoint& pt)
{
    if(this->pboard != nullptr)
    {
        this->pboard->click(pt);
    }
}

bool MainWindow::move_board_stone(const QPoint& fromPt, const QPoint& toPt)
{
    bool canMove = false;
    if(this->pboard != nullptr)
    {
        this->pboard->click(fromPt);
        canMove = this->pboard->click(toPt);
    }

    return canMove;
}

bool MainWindow::restart_game()
{
    if(this->pboard != nullptr)
    {
        this->pboard->reset();
    }
}

void MainWindow::send_to_client(QTcpSocket* another, NetworkData data) {
    // 发送消息给一个客户端，这个程序里实际上做的事情是转发消息
    if(another != nullptr)
    {
        this->server->send(another, data);

        QString opString;
        switch(data.op) {
        case OPCODE::CHAT_OP:
            opString = "CHAT_OP";
            break;
        case OPCODE::READY_OP:
            opString = "READY_OP";
            break;
        case OPCODE::MOVE_OP:
            opString = "MOVE_OP";
            if(data.data3.isEmpty() || data.data3 == QString("1") )
            {
                QStringList fromPoints = data.data1.split(",");
                QStringList toPoints = data.data2.split(",");
                if(fromPoints.size() == 2 && toPoints.size() == 2)
                {
                    QPoint fromPos(fromPoints[0].toInt(), fromPoints[1].toInt());
                    QPoint toPos(toPoints[0].toInt(), toPoints[1].toInt());
                    int row = 0;
                    int col = 0;
                    if(this->pboard->getRowCol(fromPos, row, col) == true)
                    {
                        data.data1 = QString() + this->rowString[row] + this->colString[col];
                    }

                    if(this->pboard->getRowCol(toPos, row, col) == true)
                    {
                        data.data2 = QString() + this->rowString[row] + this->colString[col];
                    }
                }
            }
            break;
        case OPCODE::RESIGN_OP:
            opString = "RESIGN_OP";
            break;
        case OPCODE::LEAVE_OP:
            opString = "LEAVE_OP";
            break;
        case OPCODE::END_OP:
            opString = "END_OP";
            break;
        case OPCODE::REJECT_OP:
            opString = "REJECT_OP";
            break;
        default:
            opString = "UNKNOW_OP";
            break;
        }

        if (another == client1) {
            // if (client2)
            // {
            //     ui->ShowClient1->setText(opString + ' ' + data.data1 + ' ' + data.data2 + ' ' + data.data3);
            //     send_to_client(client2, data);
            // }
            if(data.op != OPCODE::MOVE_OP || (data.op == OPCODE::MOVE_OP && data.data3 != QString("3")))
            {
                ui->receive_edit->appendPlainText(QString("send msg to ") + name_1 + QString(", msg is :  ") + opString + ' ' + data.data1 + ' ' + data.data2 + ' ' + data.data3);
            }
        }
        else if (another == client2) {
            // if (client1) {
            //     ui->ShowClient2->setText(opString + ' ' + data.data1 + ' ' + data.data2 + ' ' + data.data3);
            //     send_to_client(client1, data);
            // }
            if(data.op != OPCODE::MOVE_OP || (data.op == OPCODE::MOVE_OP && data.data3 != QString("3")))
            {
                ui->receive_edit->appendPlainText(QString("send msg to ") + name_2 + QString(", msg is :  ") + opString + ' ' + data.data1 + ' ' + data.data2 + ' ' + data.data3);
            }
        }
    }
}

void MainWindow::restart_server() {
    // 如果你要重启服务器，就像其他 QObject 一样，你需要 disconnect 再 connect 回来一些信号槽
    server->close();
    clients.clear();
    client1 = nullptr;
    client2 = nullptr;

    this->set_socket_map(true, nullptr);
    this->set_socket_map(false, nullptr);

    disconnect(server, &NetworkServer::receive, this, &MainWindow::receive_from_client);
    delete server;
    server = new NetworkServer(this);
    ui->PortButton->setEnabled(true);
    ui->PortEdit->setReadOnly(false);
    ui->PortEdit->setText(QString::number(this->port));
    ui->ShowClient1->setText("");
    ui->ShowClient2->setText("");
    ui->receive_edit->clear();
    connect(server, &NetworkServer::receive, this, &MainWindow::receive_from_client);

}

void MainWindow::cut_time()
{
    // 显示回合倒计时，并让time_step自减
    ui->time_edit->setPlainText(QString::number(time_step) + 's');

    if (time_step > 0){
        time_step -= 1;
    } else {
        QString win_color;
        if (current_client == client1) win_color = color_1;
        if (current_client == client2) win_color = color_2;
        NetworkData cmd = NetworkData(OPCODE::END_OP, "", "TIMEOUT", win_color);

        send_to_client(client1, cmd);
        send_to_client(client2, cmd);
        timer_step->stop();
    }
}
