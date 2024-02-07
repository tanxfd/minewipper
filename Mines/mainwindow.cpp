#include "mainwindow.h"
#include "common.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),centralGet(0), mineView(0), mineScene(0), mineLCD(0), secondLCD(0), rabbitButton(0), m_timer(0)
{
    this->setWindowTitle("Mines");
    this->setWindowIcon(QIcon(":/images/icon.png"));
    this->CreatAction();
    this->CreatMenu();

    this->slot_newgame();

}

void MainWindow::CreatAction()
{
    newAction = new QAction("新建", this);
    this->connect(newAction, SIGNAL(triggered()), this, SLOT(slot_newgame()));
    lowAction = new QAction("低级", this);
    lowAction->setCheckable(true);
    lowAction->setChecked(true);

    mediumAction = new QAction("中级", this);
    mediumAction->setCheckable(true);
    highAction = new QAction("高级", this);
    highAction->setCheckable(true);
    customAction = new QAction("自定义", this);
    customAction->setCheckable(true);

    QActionGroup *actionGroup = new QActionGroup(this);
    actionGroup->addAction(lowAction);
    actionGroup->addAction(mediumAction);
    actionGroup->addAction(highAction);
    actionGroup->addAction(customAction);
    this->connect(actionGroup, SIGNAL(triggered(QAction*)), this, SLOT(slot_newgamebydiff(QAction*)));

    colorAction = new QAction("颜色", this);
    colorAction->setCheckable(true);
    this->connect(colorAction, SIGNAL(triggered(bool)), this, SLOT(slot_colorAction()));

    soundAction = new QAction("声音", this);
    soundAction->setCheckable(true);
    this->connect(soundAction, SIGNAL(triggered(bool)), this, SLOT(slot_soundAction()));

    heroAction = new QAction("排行榜", this);
    heroAction->setCheckable(true);
    this->connect(heroAction, SIGNAL(triggered(bool)), this, SLOT(slot_displayhero()));

    aboutAction = new QAction("版本", this);
    aboutAction->setCheckable(true);
    this->connect(aboutAction, SIGNAL(triggered(bool)), this, SLOT(slot_about()));

    exitAction = new QAction("退出", this);
    exitAction->setCheckable(true);
    this->connect(exitAction, SIGNAL(triggered(bool)), this, SLOT(close()));
}

void MainWindow::CreatMenu()
{
    QMenuBar *menu_bar = this->menuBar();
    QMenu *file_menu = menu_bar->addMenu("开始");
    QMenu *help_menu = menu_bar->addMenu("帮助");
    file_menu->addAction(newAction);
    file_menu->addSeparator();

    file_menu->addAction(lowAction);
    file_menu->addAction(mediumAction);
    file_menu->addAction(highAction);
    file_menu->addAction(customAction);
    file_menu->addSeparator();

    file_menu->addAction(colorAction);
    file_menu->addAction(soundAction);
    file_menu->addAction(heroAction);
    file_menu->addSeparator();

    help_menu->addAction(aboutAction);
    help_menu->addAction(exitAction);
}

void MainWindow::readSetting()
{
    QSettings *sets = new QSettings("../minedialog.ini", QSettings::IniFormat, this);

    sets->beginGroup("rowcolmine");
    int diff = sets->value("diff", 0).toInt();
    int row = sets->value("row", 10).toInt();
    int col = sets->value("col", 10).toInt();
    int mine = sets->value("mine", 9).toInt();
    sets->endGroup();
    mineScene->m_crrentlevel = diff;
    mineScene->m_scenerow = row;
    mineScene->m_scenecol = col;
    mineScene->m_minesum = mine;
}

void MainWindow::writeSetting()
{
    QSettings *sets = new QSettings("../minedialog.ini", QSettings::IniFormat, this);

    sets->beginGroup("rowcolmine");
    sets->setValue("diff", mineScene->m_crrentlevel);
    sets->setValue("row", mineScene->m_scenerow);
    sets->setValue("col", mineScene->m_scenecol);
    sets->setValue("mine", mineScene->m_minesum);
    sets->endGroup();

}

void MainWindow::slot_newgame()
{
    centralGet->deleteLater();
    mineView->deleteLater();
    mineScene->deleteLater();
    mineLCD->deleteLater();

    secondLCD->deleteLater();
    rabbitButton->deleteLater();
    m_timer->deleteLater();
    centralGet = new QWidget(this);

    QPalette LCDpale;
    LCDpale.setColor(QPalette::Normal, QPalette::WindowText, Qt::black);
    mineLCD = new QLCDNumber(centralGet);
    mineLCD->setPalette(LCDpale);
    mineLCD->setDigitCount(3);

    secondLCD = new QLCDNumber(centralGet);
    secondLCD->setPalette(LCDpale);
    secondLCD->setDigitCount(3);

    rabbitButton = new QPushButton(centralGet);
    this->connect(rabbitButton, SIGNAL(clicked(bool)), this, SLOT(slot_newgame()));
    rabbitButton->setIcon(QIcon(":/images/rabbit_nor.png"));

    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(mineLCD);
    hlayout->addStretch();
    hlayout->addWidget(rabbitButton);
    hlayout->addStretch();
    hlayout->addWidget(secondLCD);

    mineView = new QGraphicsView(centralGet);
    mineScene = new MineScene;
    mineView->setScene(mineScene);
    this->readSetting();

    QVBoxLayout *vlayout = new QVBoxLayout(centralGet);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(mineView);
    this->setCentralWidget(centralGet);

    this->connect(mineScene, SIGNAL(sig_scenenewGame()), this, SLOT(slot_newgame()));
    this->connect(mineScene, SIGNAL(sig_scenedisplayMineNum(int)), this, SLOT(slot_displayminenums(int)));
    this->connect(mineScene, SIGNAL(sig_successPassGame()), this, SLOT(slot_heroupdate()));

    mineScene->setSceneRect(0, 0, mineScene->m_scenerow * COMMON::MAPWIDTH, mineScene->m_scenecol * COMMON::MAPHEIGHT + 70);
    mineView->setFixedSize(mineScene->m_scenerow * COMMON::MAPWIDTH + 5, mineScene->m_scenecol * COMMON::MAPHEIGHT + 75);
    this->setFixedSize(mineScene->m_scenerow * COMMON::MAPWIDTH + 25, mineScene->m_scenecol * COMMON::MAPHEIGHT + 75);

    if (mineScene->m_crrentlevel == COMMON::LOW_DIFF)
        lowAction->setChecked(true);
    else if (mineScene->m_crrentlevel == COMMON::MEDIUM_DIFF)
        mediumAction->setChecked(true);
    else if (mineScene->m_crrentlevel == COMMON::HIGH_DIFF)
        highAction->setChecked(true);
    else if (mineScene->m_crrentlevel == COMMON::CUSTOM_DIFF)
        customAction->setChecked(true);

    m_time = 0;
    mineLCD->display(mineScene->m_minesum);
    secondLCD->display(m_time);

    m_timer = new QTimer(this);
    this->connect(m_timer, SIGNAL(timeout()), this, SLOT(slot_dispalytimes()));
    m_timer->start(1000);
    mineScene->initscene();

}

void MainWindow::slot_newgamebydiff(QAction *actions)
{
    if (actions == lowAction)
    {
        mineScene->m_crrentlevel = COMMON::LOW_DIFF;
        mineScene->m_scenecol = COMMON::LOW_ROW_COL;
        mineScene->m_scenerow = COMMON::LOW_ROW_COL;
        mineScene->m_minesum = COMMON::LOW_MINENUMS;
    }
    else if (actions == mediumAction)
    {
        mineScene->m_crrentlevel = COMMON::MEDIUM_DIFF;
        mineScene->m_scenecol = COMMON::MEDIUM_ROW_COL;
        mineScene->m_scenerow = COMMON::MEDIUM_ROW_COL;
        mineScene->m_minesum = COMMON::MEDIUM_MINENUMS;
    }
    else if (actions == highAction)
    {
        mineScene->m_crrentlevel = COMMON::HIGH_DIFF;
        mineScene->m_scenecol = COMMON::HIGH_ROW;
        mineScene->m_scenerow = COMMON::HIGH_COL;
        mineScene->m_minesum = COMMON::HIGH_MINENUMS;
    }
    else if (actions == customAction)
    {
        CustomDialog *customdialog = new CustomDialog(this);
        customdialog->open();
        this->connect(customdialog, SIGNAL(signal_sendCustomset(int,int,int)), this, SLOT(slot_acceptcustomgame(int,int,int)));
    }
    this->writeSetting();
    this->slot_newgame();
}

void MainWindow::slot_acceptcustomgame(int col, int row, int mine)
{

    mineScene->m_crrentlevel = COMMON::CUSTOM_DIFF;
    mineScene->m_scenecol = col;
    mineScene->m_scenerow = row;
    mineScene->m_minesum = mine;
    this->writeSetting();
    this->slot_newgame();
}

void MainWindow::slot_displayhero()
{
    hero *herodialog = new hero;
    herodialog->exec();
}

void MainWindow::slot_colorAction()
{

}

void MainWindow::slot_soundAction()
{

}

void MainWindow::slot_heroupdate()
{
    int t_record;
    int t_time = 0;
    QString heroname;
    bool ok;
    if (mineScene->m_crrentlevel == COMMON::LOW_DIFF)
    {
        QSettings *settings = new QSettings("../herodialog.ini", QSettings::IniFormat, this);
        settings->beginGroup("low");
        t_record = settings->value("low_R").toInt();
        settings->endGroup();

        if (t_record == 0)
            t_record = 999;
        t_time = secondLCD->value();

        if (t_time < t_record)
        {
            settings->beginGroup("low");
            settings->setValue("low_R", t_time);
            settings->endGroup();
            heroname = QInputDialog::getText(this, "恭喜刷新纪录！", "请输入你的名字", QLineEdit::Normal, "张三", &ok);
            if (ok)
            {
                settings->beginGroup("low");
                settings->setValue("low_N", heroname);
                settings->setValue("low_R", t_time);
                settings->endGroup();

                int button = QMessageBox::question(this, tr("记录已更新"), tr("是否开始新游戏？"), QMessageBox::Ok | QMessageBox::Cancel);
                if (button == QMessageBox::Ok)
                    this->slot_newgame();
            }
        }
    }
    if (mineScene->m_crrentlevel == COMMON::MEDIUM_DIFF)
    {
        QSettings *settings = new QSettings("../herodialog.ini", QSettings::IniFormat, this);
        settings->beginGroup("medium");
        t_record = settings->value("medium_R").toInt();
        settings->endGroup();
        t_time = secondLCD->value();

        if (t_time < t_record)
        {
            settings->beginGroup("medium");
            settings->setValue("medium_R", t_time);
            settings->endGroup();
            heroname = QInputDialog::getText(this, "恭喜刷新纪录！", "请输入你的名字", QLineEdit::Normal, "张三", &ok);
            if (ok)
            {
                settings->beginGroup("medium");
                settings->setValue("medium_N", heroname);
                settings->setValue("medium_R", t_time);
                settings->endGroup();

                int button = QMessageBox::question(this, tr("记录已更新"), tr("是否开始新游戏？"), QMessageBox::Ok | QMessageBox::Cancel);
                if (button == QMessageBox::Ok)
                    this->slot_newgame();
            }
        }
    }
    if (mineScene->m_crrentlevel == COMMON::HIGH_DIFF)
    {
        QSettings *settings = new QSettings("../herodialog.ini", QSettings::IniFormat, this);
        settings->beginGroup("high");
        t_record = settings->value("high_R").toInt();
        settings->endGroup();
        t_time = secondLCD->value();

        if (t_time < t_record)
        {
            settings->beginGroup("high");
            settings->setValue("high_R", t_time);
            settings->endGroup();
            heroname = QInputDialog::getText(this, "恭喜刷新纪录！", "请输入你的名字", QLineEdit::Normal, "张三", &ok);
            if (ok)
            {
                settings->beginGroup("high");
                settings->setValue("high_N", heroname);
                settings->setValue("high_R", t_time);
                settings->endGroup();

                int button = QMessageBox::question(this, tr("记录已更新"), tr("是否开始新游戏？"), QMessageBox::Ok | QMessageBox::Cancel);
                if (button == QMessageBox::Ok)
                    this->slot_newgame();
            }
        }
    }

}

void MainWindow::slot_displayminenums(int flagmines)
{
    mineLCD->display(mineScene->m_minesum - flagmines);
}

void MainWindow::slot_dispalytimes()
{
    if (!mineScene->m_isGameOver)
    {
        m_time++;
        secondLCD->display(m_time);
    }
    else
        m_timer->stop();
}

void MainWindow::slot_about()
{

}


MainWindow::~MainWindow()
{

}
