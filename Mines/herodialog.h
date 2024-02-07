#ifndef HERODIALOG_H
#define HERODIALOG_H

#include <QDialog>
#include <QGridLayout>
#include <QSettings>
#include <QLabel>

#include "common.h"
#include "mainwindow.h"


class HeroDialog : public QDialog
{

public:
    explicit HeroDialog(QObject *parent = 0);

    QLabel *lowrecordtimelabel;     //初级纪录时间
    QLabel *mediumrecordtimelabel;  //中级纪录时间
    QLabel *heightrecordtimelabel;  //高级纪录时间
    QLabel *lowrecordnamelabel;     //初级纪录姓名
    QLabel *mediumrecordnamelabel;  //中级纪录姓名
    QLabel *heightrecordnamelabel;  //高级纪录姓名



    void readsettings();    //读英雄榜数据
    void writesettings();	//将英雄榜数据写入文件

    void init_herorecord(); //初始化英雄榜数据
public slots:
    void slot_reset();  	//重新设置英雄榜数据槽(slots:)
};

#endif // HERODIALOG_H
