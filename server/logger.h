#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDir>
#include <networkserver.h>

class Logger {
public:
    Logger(); // 构造函数
    ~Logger(); // 析构函数

    void log(QTcpSocket* client, NetworkData data); // 记录日志信息的函数

private:
    QFile logFile;
    QTextStream logStream;
};

#endif // LOGGER_H
