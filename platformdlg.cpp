#include "platformdlg.h"
#include <QHeaderView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <logindlg.h>
#include <writeindlg.h>
#include<QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
platformDlg::platformDlg()
{

}

platformDlg::platformDlg(QString C)
{
    classID=C;
    reEnter=new QPushButton("重新登录");
    connect(reEnter,SIGNAL(clicked()),this,SLOT(goback()));
    writeIn=new QPushButton("新增记录");
    connect(writeIn,SIGNAL(clicked(bool)),this,SLOT(writeinslot()));
    QVBoxLayout* btnlayout=new QVBoxLayout;
    btnlayout->addWidget(reEnter);
    btnlayout->addWidget(writeIn);
    QHBoxLayout *layout=new QHBoxLayout(this);
    model=new QSqlTableModel;
    model->setTable(C);
    model->select();
    model->insertRecord(-1,QSqlRecord());
    view=new QTableView(this);
    view->setModel(model);
    view->resizeColumnsToContents();
    view->resizeRowsToContents();
    QHeaderView *header=view->horizontalHeader();
    header->setStretchLastSection(true);
    setMinimumWidth(300);
    setMinimumHeight(300);
    layout->addWidget(view);
    layout->addLayout(btnlayout);
}

void platformDlg::goback()
{
   loginDlg *logindlg=new loginDlg;
   logindlg->show();
   close();
}

void platformDlg::writeinslot()
{
    writeinDlg writeDlg;
    writeDlg.exec();
    if(writeDlg.result()==Accepted)
    {
        qDebug()<<"ok";
        QString q=QString("insert into %1 values('%2','%3','%4','%5')").arg(classID).arg(writeDlg.nameE->text()).arg(writeDlg.sexE->text()).arg(writeDlg.currE->text()).arg(writeDlg.gradE->text());
        QSqlQuery query;
        query.exec(q);
        QString q2=QString("select * from %1").arg(classID);
        query.exec(q2);
        query.last();
        qDebug()<<query.lastError().text();
        model->insertRecord(-1,query.record());
    }
    else
        qDebug()<<"not ok";
}
