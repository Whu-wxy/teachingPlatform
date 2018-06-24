#include "logindlg.h"
#include <QDebug>
#include <QMessageBox>
#include <QSqlResult>
#include <QDir>
#include <QSettings>
#include <QDoubleValidator>
loginDlg::loginDlg(QWidget *parent)
    : QDialog(parent)
{
    loginBtn=new QPushButton("注册");
    loginLabel=new QLabel("没有账号？立即注册");
    loginLabel->setAlignment(Qt::AlignHCenter);
    enterBtn=new QPushButton("登录");
    enterBtn->setDefault(true);
    enterLabel=new QLabel("已有账号？立即登录");
    enterLabel->setAlignment(Qt::AlignHCenter);
    numberLabel=new QLabel("账号：");
    numberEdit=new QLineEdit;

    passwordLabel1=new  QLabel("密码：");
    passwordEdit=new QLineEdit;
    passwordEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    savePWLabel=new QLabel("记住密码");
    savePW=new QCheckBox;
    passwordLabel2=new  QLabel("再次输入密码：");
    passwordCheckEdit=new QLineEdit;
    passwordCheckEdit->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    classLabel=new QLabel("班级：");
    classEdit=new QLineEdit;

    QVBoxLayout *mainL=new QVBoxLayout(this);
    QHBoxLayout *numberL=new QHBoxLayout;
    QHBoxLayout *passL1=new QHBoxLayout;
    QHBoxLayout *passL2=new QHBoxLayout;
    QHBoxLayout *btnL=new QHBoxLayout;
    QHBoxLayout *classL=new QHBoxLayout;
    QVBoxLayout *loginL=new QVBoxLayout;
    QVBoxLayout *enterL=new QVBoxLayout;
    numberL->addWidget(numberLabel);
    numberL->addWidget(numberEdit);
    passL1->addWidget(passwordLabel1);
    passL1->addWidget(passwordEdit);
    passL1->addWidget(savePWLabel);
    passL1->addWidget(savePW);
    passL2->addWidget(passwordLabel2);
    passL2->addWidget(passwordCheckEdit);
    passwordCheckEdit->hide();
    passwordLabel2->hide();
    classL->addWidget(classLabel);
    classL->addWidget(classEdit);
    classLabel->hide();
    classEdit->hide();
    loginL->addWidget(loginBtn);
    loginL->addWidget(loginLabel);
    enterL->addWidget(enterBtn);
    enterL->addWidget(enterLabel);
    btnL->addLayout(enterL);
    btnL->addLayout(loginL);

    mainL->addLayout(numberL);
    mainL->addLayout(passL1);
    mainL->addLayout(passL2);
    mainL->addLayout(classL);
    mainL->addLayout(btnL);
    mainL->addStretch();

    setMaximumWidth(300);
    setMinimumWidth(300);
    connect(enterBtn,SIGNAL(clicked(bool)),this,SLOT(checkEnter()));
    connect(loginBtn,SIGNAL(clicked(bool)),this,SLOT(change()));

    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    path=QDir::currentPath();
    path=path+"/TeachingDB.db";
    db.setDatabaseName(path);
    bool ok=db.open();
    if(ok==true)
        qDebug()<<"成功连接";
    path=QDir::currentPath()+"/config.ini";
    readINI("number");
    readINI("password");
    QSettings settings(path,QSettings::IniFormat);
    bool check=settings.value("Check").toBool();
    savePW->setChecked(check);
    numberEdit->setText(Number);
    if(check)
    passwordEdit->setText(PassWord);
    setMaximumHeight(120);
    setMinimumHeight(120);
}

loginDlg::~loginDlg()
{
    QSettings setting(path,QSettings::IniFormat);
    setting.setValue("Check",savePW->isChecked());
}

void loginDlg::change()
{
         loginBtn->setText("返回");
         enterBtn->setText("确认");
         loginBtn->disconnect();
         enterBtn->disconnect();
         connect(enterBtn,SIGNAL(clicked(bool)),this,SLOT(checkLog()));
         connect(loginBtn,SIGNAL(clicked(bool)),this,SLOT(back()));

         passwordEdit->clear();
         numberEdit->clear();
         passwordLabel2->show();
         passwordCheckEdit->show();
         classLabel->show();
         classEdit->show();
         savePW->hide();
         savePWLabel->hide();

         setMaximumHeight(150);
         setMinimumHeight(150);
         setMaximumWidth(300);
         setMinimumWidth(300);
         loginLabel->hide();
         enterLabel->hide();
}

void loginDlg::checkLog()
{
    QSqlQuery query;
    query.exec("select * from Teacher where teacherID='"+numberEdit->text()+"'");

    if(numberEdit->text().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText("请输入账号！");
        msgBox.exec();
    }
    else if(passwordEdit->text().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText("请输入密码！");
        msgBox.exec();
    }
       else if(passwordCheckEdit->text().isEmpty())
        {
            QMessageBox msgBox;
            msgBox.setText("请再次输入密码！");
            msgBox.exec();
        }
    else if(classEdit->text().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText("请输入班级信息！");
        msgBox.exec();
    }

    else if(query.first()==true)
    {
        QMessageBox msgBox;
        msgBox.setText("账号已存在，请重新输入！");
        int rec=msgBox.exec();
        if(rec==1024)
        {
            numberEdit->clear();
            passwordEdit->clear();
            passwordCheckEdit->clear();
            classEdit->clear();
        }
    }
        else if(passwordEdit->text()==passwordCheckEdit->text())
        {
            QString q=QString("insert into Teacher values('%1','%2','%3')").arg(numberEdit->text()).arg(passwordEdit->text()).arg(classEdit->text());
            query.exec(q);
            QMessageBox msgBox;
            msgBox.setText("注册成功！");
            QString table=QString("create table %1 (姓名 char unique,性别 char,课程 char,成绩 int)").arg(classEdit->text());
            query.exec(table);
            int e=msgBox.exec();
            if(e==1024)
                back();
        }
}

void loginDlg::checkEnter()
{

    QSqlQuery query;
    query.exec("select password from Teacher where teacherID='"+numberEdit->text()+"'");

    if(query.first()==true&&!passwordEdit->text().isEmpty())
    {   
      if(query.value(0).toString()==passwordEdit->text())
       {
          query.exec("select class from Teacher where teacherID='"+numberEdit->text()+"'");
          query.first();
          QString C=query.value(0).toString();
        platform=new platformDlg(C);
        platform->show();
        writeINT("number",numberEdit->text());
        if(savePW->isChecked())
        {
            writeINT("password",passwordEdit->text());
            close();
        }
        else
        close();
       }
      else
       {
         QMessageBox msgBox;
          msgBox.setText("密码错误！");
         int rec=msgBox.exec();
         if(rec==1024)
             passwordEdit->clear();
        }
    }
    else if(passwordEdit->text().isEmpty())
    {
      QMessageBox msgbox;
      msgbox.setText("请输入密码");
      msgbox.exec();

    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("无此账号！");
        msgBox.exec();
    }

}

void loginDlg::back()
{
    loginBtn->setText("注册");
    enterBtn->setText("登录");
    loginBtn->disconnect();
    enterBtn->disconnect();
    connect(loginBtn,SIGNAL(clicked(bool)),this,SLOT(change()));
    connect(enterBtn,SIGNAL(clicked(bool)),this,SLOT(checkEnter()));
    loginLabel->show();
    enterLabel->show();
    passwordLabel2->hide();
    passwordCheckEdit->hide();
    savePW->show();
    savePWLabel->show();
    classEdit->hide();
    classLabel->hide();
    setMaximumHeight(120);
    setMinimumHeight(120);
    numberEdit->setText(Number);
    passwordEdit->setText(PassWord);
}

void loginDlg::readINI(QString key)
{
    QSettings setting(path,QSettings::IniFormat);
    if(key=="number")
    Number=setting.value(key).toString();
    else if(key=="password")
        PassWord=setting.value(key).toString();
}

void loginDlg::writeINT(QString key,QString value)
{
    path=QDir::currentPath();
    path=path+"/config.ini";
    QSettings setting(path,QSettings::IniFormat);
    setting.setValue(key,value);
}

