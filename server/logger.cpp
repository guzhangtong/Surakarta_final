#include "logger.h"

Logger::Logger() {
    // 获取当日日期
    QString currentDate = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    // 根据日期创建日志文件
    logFile.setFileName("logs/log_" + currentDate + ".txt");

    // 检查日志文件是否存在，如果不存在则创建
    if (!logFile.exists()) {
        QDir().mkpath("logs"); // 创建logs目录（如果不存在）
        logFile.open(QIODevice::WriteOnly | QIODevice::Text);
        logFile.close();
    }

    logFile.open(QIODevice::Append | QIODevice::Text);
    logStream.setDevice(&logFile);
}

Logger::~Logger() {
    logFile.close();
}

void Logger::log(QTcpSocket* client, NetworkData data) {
    // 获取当前时间
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");

    // 获取客户端的地址和端口号
    QString clientAddress = client->peerAddress().toString();
    quint16 clientPort = client->peerPort();

    // 获取op
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
        break;
    case OPCODE::RESIGN_OP:
        opString = "RESIGN_OP";
        break;
    case OPCODE::LEAVE_OP:
        opString = "LEAVE_OP";
        break;
    default:
        break;
    }

    // 组合为一个字符串
    QString clientInfo = QString("Client IP: %1, Port: %2")
                             .arg(clientAddress)
                             .arg(clientPort);

    // 组合输入的命令
    QString dataContent = opString + ' ' + data.data1 + ' ' + data.data2 + ' ' + data.data3;

    // 格式化日志信息
    QString logMessage = "[ " + currentTime + " ]" + " [ " + clientInfo + " ] " + dataContent + "\n";

    // 写入日志文件
    logStream << logMessage;
    logStream.flush(); // 确保日志信息即时写入文件
}
