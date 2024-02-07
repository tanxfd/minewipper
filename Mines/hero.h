#ifndef HERO_H
#define HERO_H

#include <QMainWindow>
#include <QApplication>
#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QSettings>
#include "mainwindow.h"
class hero : public QDialog
{
    Q_OBJECT
public:
    explicit hero(QDialog *parent = 0);
    QLabel *lowrecordtimelabel;     //初级纪录时间
    QLabel *mediumrecordtimelabel;  //中级纪录时间
    QLabel *heightrecordtimelabel;  //高级纪录时间
    QLabel *lowrecordnamelabel;     //初级纪录姓名
    QLabel *mediumrecordnamelabel;  //中级纪录姓名
    QLabel *heightrecordnamelabel;  //高级纪录姓名

    void readsettings();    //读英雄榜数据
    void writesettings();	//将英雄榜数据写入文件
    void init_herorecord(); //初始化英雄榜数据
signals:

public slots:
    void slot_reset();  	//重新设置英雄榜数据槽(slots:)
};

#endif // HERO_H
