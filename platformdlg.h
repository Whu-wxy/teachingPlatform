#ifndef PLATFORMDLG_H
#define PLATFORMDLG_H

#include <QDialog>
#include<QSqlDatabase>
#include<QSqlQuery>
#include <QTableView>
#include <QSqlTableModel>
#include <QtSql>
#include <QPushButton>
class platformDlg : public QDialog
{
    Q_OBJECT
public:
    platformDlg();
    platformDlg(QString);

private:
    QString classID;
    QSqlTableModel *model;
    QTableView *view;
    QPushButton *reEnter;
    QPushButton *writeIn;

public slots:
    void goback();
    void writeinslot();


};

#endif // PLATFORMDLG_H
