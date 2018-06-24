#ifndef WRITEINDLG_H
#define WRITEINDLG_H

#include<QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDialog>
class writeinDlg : public QDialog
{
    Q_OBJECT
public:
    writeinDlg();

public:
    QPushButton *ok;
    QPushButton *cancel;
    QLabel *name;
    QLineEdit *nameE;
    QLabel *sex;
    QLineEdit *sexE;
    QLabel *curr;
    QLineEdit *currE;
    QLabel *grad;
    QLineEdit *gradE;

public slots:
    void onOK();
    void onCancel();

};

#endif // WRITEINDLG_H
