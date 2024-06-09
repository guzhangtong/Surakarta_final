#include "connectdialog.h"
#include "ui_connectdialog.h"
#include <QMessageBox>

// 构造函数，初始化UI和设置背景图片
ConnectDialog::ConnectDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConnectDialog)
    , pconnectInfo(nullptr)
{
    ui->setupUi(this);
    this->setStyleSheet("QDialog{background-image:url(:/photo/mid2.jpg)}");
}

// 析构函数，释放UI资源
ConnectDialog::~ConnectDialog()
{
    delete ui;
}

// 获取连接信息
ConnectInfo* ConnectDialog::GetConnectInfo() const
{
    return this->pconnectInfo;
}

// 连接按钮点击槽函数
void ConnectDialog::onClickConnectSlot()
{
    // 如果连接信息为空，则创建新的连接信息对象
    if(this->pconnectInfo == nullptr)
    {
        ui->LabelUserName->text();
        QString color = ui->comboBoxColor->currentText();
        int indexCur = ui->comboBoxColor->currentIndex();
        // 如果颜色选择框的索引为0，则清空颜色字符串
        if(indexCur==0)
        {
            color = "";
        }
        // 创建新的连接信息对象，并连接信号和槽
        this->pconnectInfo = new ConnectInfo(
            this
            , ui->lineEditUserName->text()
            , color
            , ui->lineEditIp->text()
            , ui->lineEditPort->text()
            );
        connect(this->pconnectInfo, &ConnectInfo::hasConnected, this, &ConnectDialog::Connected);
        connect(this->pconnectInfo, &ConnectInfo::hasConnectError, this, &ConnectDialog::ConnectError);
    }
    // 调用连接函数，尝试连接到服务器
    this->pconnectInfo->ConnectToServer(HumenSocket_Index);
}

// 连接成功槽函数，关闭对话框
void ConnectDialog::Connected()
{
    QDialog::accept();
}

// 连接错误槽函数，显示错误信息并释放连接信息对象
void ConnectDialog::ConnectError()
{
    if(this->pconnectInfo != nullptr)
    {
        delete this->pconnectInfo;
        this->pconnectInfo = nullptr;
    }
    QMessageBox::warning(this, "error", "connect server error");
}

// 离线按钮点击槽函数，关闭对话框
void ConnectDialog::onClickOutlineSlot()
{
    QDialog::accept();
}
