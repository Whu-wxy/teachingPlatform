#ifndef LOGINDLG_H
#define LOGINDLG_H

#include <QDialog>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QtSql>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <platformdlg.h>
#include <QCheckBox>
class loginDlg : public QDialog
{
    Q_OBJECT

public:
    loginDlg(QWidget *parent = 0);
    ~loginDlg();
    void readINI(QString);
    void writeINT(QString,QString);
    QString path;


private:
    QPushButton *loginBtn;
    QLabel *loginLabel;
    QPushButton *enterBtn;
    QLabel *enterLabel;
    QLabel *numberLabel;
    QLineEdit *numberEdit;
    QLabel *passwordLabel1;
    QLineEdit *passwordEdit;
    QLabel *passwordLabel2;
    QLineEdit *passwordCheckEdit;
    QLabel *classLabel;
    QLineEdit *classEdit;
    platformDlg *platform;
    QLabel *savePWLabel;
    QCheckBox *savePW;

    QString Number;
    QString PassWord;



public slots:
    void change();
    void checkLog();
    void checkEnter();
    void back();

};

#endif // LOGINDLG_H
