#include "customdialog.h"

CustomDialog::CustomDialog(QWidget *parent)
{
    this->setWindowTitle("自定义数据");
    QLabel *colLabel = new QLabel("列数");
    QLabel *rowLabel = new QLabel("行数");
    QLabel *minenumLabel = new QLabel("雷数");

    colspinbox = new QSpinBox;    //列分量框
    rowspinbox = new QSpinBox;    //行分量框
    minenumspinbox = new QSpinBox;//雷数分量框

    colspinbox->setRange(9, 99);
    colspinbox->setSingleStep(1);
    colspinbox->setValue(9);
    rowspinbox->setRange(9, 99);
    rowspinbox->setSingleStep(1);
    rowspinbox->setValue(9);

    minenumspinbox->setRange(1, 999);
    minenumspinbox->setSingleStep(5);
    minenumspinbox->setValue(10);
    QPushButton *customButton = new QPushButton("确定");

    QGridLayout *glayout = new QGridLayout(this);
    glayout->addWidget(rowLabel, 0, 0, Qt::AlignCenter);
    glayout->addWidget(rowspinbox, 0 ,1, Qt::AlignCenter);
    glayout->addWidget(colLabel, 1, 0, Qt::AlignCenter);

    glayout->addWidget(colspinbox, 1, 1, Qt::AlignCenter);
    glayout->addWidget(minenumLabel, 2, 0, Qt::AlignCenter);
    glayout->addWidget(minenumspinbox, 2, 1, Qt::AlignCenter);
    glayout->addWidget(customButton, 3, 0, 1, 3, Qt::AlignCenter);

    this->setFixedSize(120, 162);
    this->connect(customButton, SIGNAL(clicked(bool)), this, SLOT(slot_accpetok()));

}

void CustomDialog::readsettings()    //读自定义游戏设置文件
{

    QSettings *settings = new QSettings("../customdialog.ini", QSettings::IniFormat, this);
    settings->beginGroup("CustomGame");
    int col = settings->value("Custom_col", 9).toInt();
    int row = settings->value("Custom_row", 9).toInt();
    int minenum = settings->value("Custom_minenum", 10).toInt();
    settings->endGroup();

    colspinbox->setValue(col);
    rowspinbox->setValue(row);
    minenumspinbox->setValue(minenum);
}

void CustomDialog::writesettings()   //写自定义游戏设置文件
{
    QSettings *settings = new QSettings("../customdialog.ini", QSettings::IniFormat, this);
    settings->beginGroup("CustomGame");
    settings->setValue("Custom_col",colspinbox->value());
    settings->setValue("Custom_row",rowspinbox->value());
    settings->setValue("Custom_minenum",minenumspinbox->value());
    settings->endGroup();
}

void CustomDialog::slot_accpetok()   //接收确定按钮的槽(slots:)
{
    int col = colspinbox->value();
    int row = rowspinbox->value();
    int minenums = minenumspinbox->value();

    emit this->signal_sendCustomset(col, row, minenums);
    this->writesettings();
    this->close();
}
