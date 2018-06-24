#include "writeindlg.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
writeinDlg::writeinDlg()
{
     name=new QLabel("姓名");
     nameE=new QLineEdit;
     sex=new QLabel("性别");
     sexE=new QLineEdit;
     curr=new QLabel("课程");
     currE=new QLineEdit;
     grad=new QLabel("成绩");
     gradE=new QLineEdit;
     ok=new QPushButton("确认");
     cancel=new QPushButton("取消");
     connect(ok,SIGNAL(clicked(bool)),this,SLOT(onOK()));
     connect(cancel,SIGNAL(clicked(bool)),this,SLOT(onCancel()));
     QHBoxLayout *input1=new QHBoxLayout;
     QHBoxLayout *input2=new QHBoxLayout;
     QHBoxLayout *input3=new QHBoxLayout;
     QHBoxLayout *input4=new QHBoxLayout;
     QHBoxLayout *okcancel=new QHBoxLayout;
     QVBoxLayout *mainL=new QVBoxLayout(this);
     input1->addWidget(name);
     input1->addWidget(nameE);
     input2->addWidget(sex);
     input2->addWidget(sexE);
     input3->addWidget(curr);
     input3->addWidget(currE);
     input4->addWidget(grad);
     input4->addWidget(gradE);
     okcancel->addWidget(ok);
     okcancel->addWidget(cancel);
     mainL->addLayout(input1);
     mainL->addLayout(input2);
     mainL->addLayout(input3);
     mainL->addLayout(input4);
     mainL->addLayout(okcancel);
}

void writeinDlg::onOK()
{
    accept();
    close();
}

void writeinDlg::onCancel()
{
    reject();
    close();
}
