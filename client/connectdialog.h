#ifndef CONNECTDIALOG_H
#define CONNECTDIALOG_H

#include "connectinfo.h"
#include <QDialog>

namespace Ui {
class ConnectDialog;
}

class ConnectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectDialog(QWidget *parent = nullptr);
    ~ConnectDialog();

    ConnectInfo* GetConnectInfo() const;

private:
    void Connected();
    void ConnectError();

protected slots:
    void onClickConnectSlot();
    void onClickOutlineSlot();

private:
    Ui::ConnectDialog *ui;
    ConnectInfo *pconnectInfo;
};

#endif // CONNECTDIALOG_H
