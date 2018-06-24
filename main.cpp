#include "logindlg.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    loginDlg w;

        QFile qssFile(".:/res.qrs/theme.qss");
        qssFile.open(QFile::ReadOnly);
        QString qss;
        if(qssFile.isOpen())
        {

            qss = QLatin1String(qssFile.readAll());

            w.setStyleSheet(qss);

            qssFile.close();
}
    w.show();

    return a.exec();
}
