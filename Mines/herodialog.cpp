#include "herodialog.h"

HeroDialog::HeroDialog(QWidget *parent) : QDialog(parent)
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

void HeroDialog::readsettings()    //读英雄榜数据
{
    QSettings *sets = new QSettings("../herodialog.ini", QSettings::IniFormat, this);
    sets->beginGroup("herosrecord");
    QString low_t = sets->value("low", "999").toString();
    QString medium_t = sets->value("medium", "999").toString();
    QString height_t = sets->value("high", "999").toString();
    sets->endGroup();

    lowrecordtimelabel->setText(low_t);
    mediumrecordtimelabel->setText(medium_t);
    heightrecordtimelabel->setText(height_t);

    sets->beginGroup("herosname");
    QString low_n = sets->value("low", "charnanme").toString();
    QString medium_n = sets->value("medium", "charnanme").toString();
    QString height_n = sets->value("high", "charnanme").toString();
    sets->endGroup();

    lowrecordnamelabel->setText(low_n);
    mediumrecordnamelabel->setText(medium_n);
    heightrecordnamelabel->setText(height_n);
}

void HeroDialog::writesettings()
{
    QSettings *sets = new QSettings("../herodialog.ini", QSettings::IniFormat, this);
    sets->beginGroup("herosrecord");
    sets->setValue("low", lowrecordtimelabel->text());
    sets->setValue("medium", mediumrecordtimelabel->text());
    sets->setValue("high", heightrecordtimelabel->text());
    sets->endGroup();

    sets->beginGroup("herosname");
    sets->setValue("low", lowrecordnamelabel->text());
    sets->setValue("medium", mediumrecordnamelabel->text());
    sets->setValue("high", heightrecordnamelabel->text());
    sets->endGroup();
}

void HeroDialog::init_herorecord() //初始化英雄榜数据
{


    this->writesettings();
}

void HeroDialog::slot_reset()  	//重新设置英雄榜数据槽(slots:)
{
    this->init_herorecord();
}

