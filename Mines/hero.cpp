#include "hero.h"

hero::hero(QDialog *parent) : QDialog(parent)
{
    this->setWindowTitle("排行榜");

    lowrecordtimelabel = new QLabel;     //初级纪录时间
    mediumrecordtimelabel = new QLabel;  //中级纪录时间
    heightrecordtimelabel = new QLabel;  //高级纪录时间
    lowrecordnamelabel = new QLabel;     //初级纪录姓名
    mediumrecordnamelabel = new QLabel;  //中级纪录姓名
    heightrecordnamelabel = new QLabel;  //高级纪录姓名

    QLabel *low_diff = new QLabel("低级");
    QLabel *medium_diff = new QLabel("中级");
    QLabel *high_diff = new QLabel("高级");
    QPushButton *resetbutton = new QPushButton("重置排行榜");
    QGridLayout *glayout = new QGridLayout(this);

    glayout->addWidget(low_diff, 0, 0);
    glayout->addWidget(lowrecordtimelabel, 0, 1);
    glayout->addWidget(lowrecordnamelabel, 0, 2);
    glayout->addWidget(medium_diff, 1, 0);
    glayout->addWidget(mediumrecordtimelabel, 1, 1);

    glayout->addWidget(mediumrecordnamelabel, 1, 2);
    glayout->addWidget(high_diff, 2, 0);
    glayout->addWidget(heightrecordtimelabel, 2, 1);
    glayout->addWidget(heightrecordnamelabel, 2, 2);
    glayout->addWidget(resetbutton, 3, 0, 1, 3, Qt::AlignCenter);

    this->readsettings();
    this->connect(resetbutton, SIGNAL(clicked(bool)), this, SLOT(slot_reset()));
}
void hero::readsettings()    //读英雄榜数据
{
    QSettings *sets = new QSettings("../herodialog.ini", QSettings::IniFormat, this);
    sets->beginGroup("low");
    QString low_t = sets->value("low_R", "999").toString();
    QString low_n = sets->value("low_N", "charnanme").toString();
    sets->endGroup();

    lowrecordtimelabel->setText(low_t);
    lowrecordnamelabel->setText(low_n);

    sets->beginGroup("medium");
    QString medium_t = sets->value("medium_R", "999").toString();
    QString medium_n = sets->value("medium_N", "charnanme").toString();
    sets->endGroup();

    mediumrecordtimelabel->setText(medium_t);
    mediumrecordnamelabel->setText(medium_n);

    sets->beginGroup("high");
    QString height_t = sets->value("high_R", "999").toString();
    QString height_n = sets->value("high_N", "charnanme").toString();
    sets->endGroup();

    heightrecordtimelabel->setText(height_t);
    heightrecordnamelabel->setText(height_n);
}
void hero::writesettings()	//将英雄榜数据写入文件
{
    QSettings *sets = new QSettings("../herodialog.ini", QSettings::IniFormat, this);
    sets->beginGroup("low");
    sets->setValue("low_R", lowrecordtimelabel->text());
    sets->setValue("low_N", lowrecordnamelabel->text());
    sets->endGroup();

    sets->beginGroup("medium");
    sets->setValue("medium_R", mediumrecordtimelabel->text());
    sets->setValue("medium_N", mediumrecordnamelabel->text());
    sets->endGroup();

    sets->beginGroup("high");
    sets->setValue("high_R", heightrecordtimelabel->text());
    sets->setValue("high_N", heightrecordnamelabel->text());
    sets->endGroup();
}
void hero::init_herorecord() //初始化英雄榜数据
{
    QSettings *sets = new QSettings("../herodialog.ini", QSettings::IniFormat, this);
    sets->beginGroup("low");
    sets->setValue("low_R", lowrecordtimelabel->text());
    sets->setValue("low_N", lowrecordnamelabel->text());
    sets->endGroup();

    sets->beginGroup("medium");
    sets->setValue("medium_R", mediumrecordtimelabel->text());
    sets->setValue("medium_N", mediumrecordnamelabel->text());
    sets->endGroup();

    sets->beginGroup("high");
    sets->setValue("high_R", heightrecordtimelabel->text());
    sets->setValue("high_N", heightrecordnamelabel->text());
    sets->endGroup();
}
void hero::slot_reset()
{
    lowrecordtimelabel->setText("999");
    lowrecordnamelabel->setText("charname");
    mediumrecordtimelabel->setText("999");
    mediumrecordnamelabel->setText("charname");
    heightrecordtimelabel->setText("999");
    heightrecordnamelabel->setText("charname");
}
