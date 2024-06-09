#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "./stage3/readystagemessage.h"
#include "./stage3/readyrevicestageop.h"
#include "./stage3/moverevicestageop.h"
#include "./stage3/endrevicestageop.h"
#include "./stage3/resignstagemessage.h"
#include "./stage3/leavestagemessage.h"
#include "./stage3/movestagemessage.h"
#include "./stage3/chatstagemessage.h"
#include "./stage3/chatreceivestageop.h"
#include <QMessageBox>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QDebug>

MainWindow::MainWindow(ConnectInfo *pinfo, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pconnectInfo(nullptr)
{
    ui->setupUi(this);
    ui->lcdNumber_2->display(QString::number(countdownSecs));
    ui->lcdNumber->display(QString::number(countdownSecs));
    ui->stackedWidget->setCurrentIndex(0);
    this->SetConnectInfo(pinfo);
    if(this->pconnectInfo != nullptr)
    {
        this->pmoveStageMessage = new MoveStageMessage(this, this->pconnectInfo, this);
    }

    m_aigame = new AIGame(this->pmoveStageMessage, this);
    //this->setStyleSheet("QMainWindow {background-color:rgb(7, 9, 4)}");
    this->setStyleSheet("QMainWindow {background-image:url(:/photo/back2.png)}");
    // 设置窗口固定大小
    setFixedSize(700,500); // 设置窗口宽度为800像素，高度为600像素
    // 禁用窗口的大小调整功能
    setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint); // 禁止用户调整窗口大小
    ui->gridLayout_2->addWidget(m_aigame);
    ui->pushButton->setStyleSheet("position: absolute; top: 100px; left: 100px; width: 100px; height: 50px;");
    ui->pushButton_2->setStyleSheet("position:absolute; top: 100px; left: 100px; width: 100px; height: 50px;");
    ui->pushButton_3->setStyleSheet("position: absolute; top: 100px; left:100px; width: 100px; height: 50px;");
    ui->pushButton_4->setStyleSheet("position: absolute; top: 100px; left: 100px; width: 100px; height: 50px;");
    connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::chooseModel);//human vs human
    connect(ui->pushButton_2,&QPushButton::clicked,this,&MainWindow::chooseModel_2);//human vs AI
    connect(ui->pushButton_3,&QPushButton::clicked,this,&MainWindow::chooseModel_3);
    connect(ui->pushButton_4,&QPushButton::clicked,this,&MainWindow::chooseModel_4);
    connect(ui->loseBtn_1,&QPushButton::clicked,this,&MainWindow::slot_endGameBox);
    connect(ui->loseBtn_2,&QPushButton::clicked,this,&MainWindow::slot_endGameBox);
    connect(ui->undoBtn_1,&QPushButton::clicked,this,&MainWindow::undo);
    connect(ui->undoBtn_2,&QPushButton::clicked,this,&MainWindow::undo);
    connect(&gamePlayTimer,&QTimer::timeout,this,&MainWindow::gamePlayTimeout);
    connect(m_aigame,&Board::sig_userChanged,this,&MainWindow::userChanged);
    connect(m_aigame,&Board::sig_finish,[=](bool user1){
        QString msg = this->EndGameResult(!user1);
        // if(user1){
        //     msg = "用户1输了\n游戏结束，您想要做什么？";
        // }else {
        //     msg = "用户2输了\n游戏结束，您想要做什么？";
        // }
        msg += QString("\n游戏结束，您想要做什么？");
        endGameBox(msg);
    });


    vecReviceStageOp.push_back(new ReadyReviceStageOp(this, this));
    vecReviceStageOp.push_back(new MoveReviceStageOp(this, this));
    vecReviceStageOp.push_back(new EndReviceStageOp(this, this));
    vecReviceStageOp.push_back(new ChatReceiveStageOp(this, this));
}

MainWindow::~MainWindow()
{
    LeaveStageMessage msg(this->pconnectInfo);
    if(this->pconnectInfo != nullptr)
    {
        this->pconnectInfo->SendMessage(HumenSocket_Index, msg.ToNetworkData());
    }

    delete ui;
}

void MainWindow::SetConnectInfo(ConnectInfo *pinfo)
{
    this->pconnectInfo = pinfo;
    if(this->pconnectInfo != nullptr)
    {
        this->pconnectInfo->setParent(this);
        connect(this->pconnectInfo, &ConnectInfo::receive, this, &MainWindow::receiveMessage);

    }
}

void MainWindow::SetBlackUserNameShow(const QString& name)
{
    ui->labelUserBlack->setText(name);
}
void MainWindow::SetWhiteUserNameShow(const QString& name)
{
    ui->labelUserWhite->setText(name);
}

void MainWindow::ChangeRunTurn(bool brun)
{
    if(this->m_aigame != nullptr)
    {
        bool bChange = this->m_aigame->bTurn != brun;
        bool srcTurn = this->m_aigame->bTurn;
        this->m_aigame->setTurn(brun);
        if(bChange)
        {
            emit this->m_aigame->sig_userChanged(srcTurn);
        }
    }
}

bool MainWindow::GetIsWhiteTurn()
{
    if(this->m_aigame != nullptr)
    {
        return this->m_aigame->bTurn;
    }
    return false;
}

void MainWindow::ChangePlayTime(bool isWhite, int time)
{
    if(isWhite){
        user1Count = time;
        ui->lcdNumber_2->display(QString::number(countdownSecs));
        ui->lcdNumber->display(user1Count);        
    }else {
        user2Count = time;
        ui->lcdNumber->display(QString::number(countdownSecs));
        ui->lcdNumber_2->display(user2Count);
    }

    this->SetThinkTime(isWhite, 60-time);
}

void MainWindow::EndGameWhoLose(bool isWhite)
{
    if(this->m_aigame != nullptr)
    {
        emit this->m_aigame->sig_finish(isWhite);
    }
}

void MainWindow::ClickBoardStone(const QPoint& pt)
{
    if(this->m_aigame != nullptr)
    {
        this->m_aigame->click(pt);
    }
}

void MainWindow::MoveBoardStone(const QPoint& fromPt, const QPoint& toPt)
{
    //NOBadySocket
    if(this->m_aigame != nullptr)
    {
        this->m_aigame->click(fromPt, NoBadySocket);
        this->m_aigame->click(toPt, NoBadySocket);
    }
}

void MainWindow::RestartGame(bool isRestart)
{
    if(isRestart)
        this->reset();
    else
        exit(0);
}

QString MainWindow::EndGameResult(bool isWhiteWin)
{
    if(this->m_aigame != nullptr)
    {
        return this->m_aigame->EndGameResult(isWhiteWin);
    }
    return QString();
}
void MainWindow::SetThinkTime(bool isWhite, int time)
{
    if(this->m_aigame != nullptr)
    {
        this->m_aigame->SetThinkTime(isWhite, time);
    }
}

void MainWindow::receiveMessage(SOCKET_INDEX socketIndex, NetworkData data)
{
    for(auto& it : this->vecReviceStageOp)
    {
        if(it->ReviceData(socketIndex, data) == true)
        {
            break;
        }
    }
}

void MainWindow::AiPlayerConnected()
{
    if(this->pconnectInfo != nullptr)
    {
        ReadyStageMessage aiMsg(
            QString("AiPlayer"),
            this->pconnectInfo->GetColor()== QString("BLACK") ? QString("WHITE") : QString("BLACK"),
            this->pconnectInfo->GetRoomNum() ,
            this->pconnectInfo
            );

        this->pconnectInfo->SendMessage(AISocket_Index, aiMsg.ToNetworkData());

        this->reset();
    }
}

void MainWindow::chooseModel()
{
    qDebug() << "enter human vs human";
    this->m_aigame->ai_mode[0] = false;
    this->m_aigame->ai_mode[1] = false;

    //此处应该切换到不同界面，等stage3联网做完再实现
    if(this->pconnectInfo != nullptr)
    {
        ReadyStageMessage msg(
            this->pconnectInfo->GetUserName(),
            this->pconnectInfo->GetColor(),
            this->pconnectInfo->GetRoomNum(),
            this->pconnectInfo
            );
        this->pconnectInfo->SendMessage(HumenSocket_Index, msg.ToNetworkData());

        if(this->pconnectInfo->GetColor()== QString("BLACK"))
        {
            this->SetBlackUserNameShow(this->pconnectInfo->GetUserName());
        }
        else
        {
            this->SetWhiteUserNameShow(this->pconnectInfo->GetUserName());
        }
    }
    else
    {
        this->reset();
    }
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::chooseModel_2() {

    qDebug() << "enter human vs AI";


    //此处应该切换到不同界面，等stage3联网做完再实现
    if(this->pconnectInfo != nullptr)
    {
        ReadyStageMessage msg(
            this->pconnectInfo->GetUserName(),
            this->pconnectInfo->GetColor(),
            this->pconnectInfo->GetRoomNum(),
            this->pconnectInfo
            );
        this->pconnectInfo->SendMessage(HumenSocket_Index, msg.ToNetworkData());

        //for AI socket
        this->pconnectInfo->ConnectToServer(AISocket_Index);
        connect(this->pconnectInfo, &ConnectInfo::hasConnected, this, &MainWindow::AiPlayerConnected);

        if(this->pconnectInfo->GetColor() == QString("BLACK"))
        {
            this->m_aigame->ai_mode[0] = false;
            this->m_aigame->ai_mode[1] = true;
        }
        else
        {
            this->m_aigame->ai_mode[0] = true;
            this->m_aigame->ai_mode[1] = false;
        }
    }
    else
    {
        this->m_aigame->ai_mode[0] = false;
        this->m_aigame->ai_mode[1] = true;
        this->reset();
    }
    ui->stackedWidget->setCurrentIndex(1);    
}

void MainWindow::chooseModel_3() {
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::chooseModel_4() {
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::slot_endGameBox()
{
    if(this->pconnectInfo != nullptr)
    {
        ResignStageMessage resignMsg(this->pconnectInfo);
        this->pconnectInfo->SendMessage(HumenSocket_Index, resignMsg.ToNetworkData());
    }
    else
    {
        QObject *obj = sender();
        QString msg;
        if(obj == ui->loseBtn_1){
            msg = "用户1输了\n游戏结束，您想要做什么？";
        }else {
            msg = "用户2输了\n游戏结束，您想要做什么？";
        }
        endGameBox(msg);
    }
}

void MainWindow::undo()
{
    //悔棋
    m_aigame->undo();
}



//用户切换
void MainWindow::userChanged()
{
    if(this->pconnectInfo == nullptr)
    {
        //online game, do not start timer;
        if(!gamePlayTimer.isActive())
            gamePlayTimer.start(1*1000);
    }

    if(m_aigame->getUser1()){
        user2Count = countdownSecs;
    }else {
        user1Count = countdownSecs;
    }

}

void MainWindow::reset()
{
    m_aigame->reset();
    ui->lcdNumber_2->display(QString::number(countdownSecs));
    ui->lcdNumber->display(QString::number(countdownSecs));
    user1Count = countdownSecs;
    user2Count = countdownSecs;
}

void MainWindow::gamePlayTimeout()
{
    if(m_aigame->getUser1()){
        user1Count -=1;
        ui->lcdNumber_2->display(QString::number(countdownSecs));
        ui->lcdNumber->display(user1Count);
        this->SetThinkTime(m_aigame->getUser1(), user1Count);
    }else {
        user2Count -=1;
        ui->lcdNumber->display(QString::number(countdownSecs));
        ui->lcdNumber_2->display(user2Count);
        this->SetThinkTime(m_aigame->getUser1(), user2Count);
    }


    if(user1Count <=0 ) {
        QString msg = this->EndGameResult(false);
        msg += "\n游戏结束，您想要做什么？";
        endGameBox(msg);
    }else if(user2Count <=  0) {
        QString msg = this->EndGameResult(true);
        msg += "\n游戏结束，您想要做什么？";
        endGameBox(msg);
    }
}


void MainWindow::endGameBox(QString msg)
{
    QObject* obj = sender();
    gamePlayTimer.stop();

    // 创建一个消息框
    QMessageBox endGameBox;
    endGameBox.setText(msg);

    // 创建自定义按钮
    QPushButton *restartButton = new QPushButton("重新开始");
    QPushButton *exitButton = new QPushButton("结束游戏");

    // 将自定义按钮添加到消息框
    endGameBox.addButton(restartButton, QMessageBox::ActionRole);
    endGameBox.addButton(exitButton, QMessageBox::RejectRole);

    // 由于我们添加了自定义按钮，所以不使用标准按钮
    endGameBox.setStandardButtons(QMessageBox::NoButton);

    // 连接按钮的clicked信号到槽函数
    connect(restartButton, &QPushButton::clicked, this, [this, &endGameBox]() {
        // 用户点击了“重新开始”按钮
        endGameBox.close(); // 关闭消息框
        if(this->pconnectInfo == nullptr)
        {
            reset();
        }
        else
        {
            ChatStageMessage msg(this->pconnectInfo, this);
            msg.RequestRestart();
            msg.SendMessage(HumenSocket_Index);
            msg.ReposeRestart(true);
            msg.SendMessage(HumenSocket_Index);
        }

    });

    connect(exitButton, &QPushButton::clicked, this, [this, &endGameBox]() {
        // 用户点击了“结束游戏”按钮
        endGameBox.close(); // 关闭消息框
        if(this->pconnectInfo == nullptr)
        {
            //outline,only exit ;
            exit(0);
        }
        else
        {
            ChatStageMessage msg(this->pconnectInfo, this);
            msg.ReposeRestart(false);
            msg.SendMessage(HumenSocket_Index);
        }
    });

    // 显示消息框
    endGameBox.exec();
}






