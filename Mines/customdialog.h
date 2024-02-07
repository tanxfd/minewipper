#ifndef CUSTOMDIALOG_H
#define CUSTOMDIALOG_H

#include <QObject>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QSpinBox>
#include "common.h"
#include "mainwindow.h"

class CustomDialog : public QDialog
{
    Q_OBJECT
public:

    QSpinBox *colspinbox;    //列分量框
    QSpinBox *rowspinbox;    //行分量框
    QSpinBox *minenumspinbox;//雷数分量框

    CustomDialog(QWidget *parent = 0);
    void readsettings();    //读自定义游戏设置文件
    void writesettings();   //写自定义游戏设置文件

signals:
    void signal_sendCustomset(int,int,int); //发送自定义游戏行，列，雷数的信号(signals)

public slots:
    void slot_accpetok();   //接收确定按钮的槽(slots:)

};

#endif // CUSTOMDIALOG_H
