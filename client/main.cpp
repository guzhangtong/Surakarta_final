#include <QApplication>
#include "connectdialog.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle("cde");
    ConnectDialog connectDlg;
    int result =  connectDlg.exec();

    if(result == QDialog::Accepted)
    {
        MainWindow w(connectDlg.GetConnectInfo());
        w.show();
        return a.exec();
    }
    else
    {
        connectDlg.close();
        a.quit();
    }
    return 0;
}
