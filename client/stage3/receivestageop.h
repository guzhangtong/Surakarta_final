#ifndef RECEIVESTAGEOP_H
#define RECEIVESTAGEOP_H
#include "../connectinfo.h"
#include "../networkdata.h"
#include <QObject>

class ReceiveStageOp : public QObject
{
    Q_OBJECT
public:
    explicit ReceiveStageOp(QObject *parent = nullptr);
    bool ReviceData(SOCKET_INDEX socketIndex, const NetworkData& data);

private:
    virtual bool IsMyOp(const NetworkData& data) = 0;
    virtual void DoSomething(SOCKET_INDEX socketIndex, const NetworkData& data) = 0;

signals:
};

#endif // RECEIVESTAGEOP_H
