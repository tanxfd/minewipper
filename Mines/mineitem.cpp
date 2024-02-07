#include <QMessageBox>
#include "mineitem.h"
#include "minescene.h"

MineItem::MineItem(int t_x,int t_y,QPixmap,QGraphicsPixmapItem *parent): QGraphicsPixmapItem (parent) , m_X(t_x) , m_Y(t_y)
{
    this->setPixmap(QPixmap(":/images/cover1.png"));
    m_isMine = false;
    m_isOpened = false;
    m_isrightsigned = false;
    m_aroundMineNum = 0;
    m_rMouseKeyNum = 0;
}

void MineItem::mousePressEvent(QGraphicsSceneMouseEvent *event) //鼠标点击事件(右键)
{

    MineScene *minescene = (MineScene *)this->scene();
    if (minescene->m_isGameOver || this->m_isOpened)
        return;

    while (event->button() == Qt::LeftButton && !m_isrightsigned)
    {
        this->setPixmap(QPixmap(":/images/gradual_1.png"));
        break;
    }

    while (event->button() == Qt::RightButton)
    {
        m_rMouseKeyNum++;
        if (m_rMouseKeyNum <= 2)
        {
            if (1 == m_rMouseKeyNum)
            {
                minescene->m_signedMineNum++;
                this->setPixmap(QPixmap(":/images/flag1.png"));
                emit sig_resetMineNum(minescene->m_signedMineNum);
                if (this->m_isMine)
                    minescene->m_rightMineNum++;
            }
            else if (2 == m_rMouseKeyNum)
            {
                minescene->m_signedMineNum--;
                this->setPixmap(QPixmap(":/images/interrogation1_1.png"));
                emit sig_resetMineNum(minescene->m_signedMineNum);
                if (this->m_isMine)
                    minescene->m_rightMineNum++;
            }
        }
        else if (m_rMouseKeyNum == 3)
        {
            m_rMouseKeyNum = 0;
            this->setPixmap(QPixmap(":/images/cover1.png"));
        }
        break;
    }
}

void MineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)  //鼠标释放事件（左键）
{
    MineScene *minescene = (MineScene *)this->scene();
//    minescene->m_remainNoMines = minescene->m_scenecol * minescene->m_scenerow - minescene->m_minesum;
    if (minescene->m_isGameOver || this->m_isOpened || this->m_isrightsigned)
        return;

    if (event->button() == Qt::LeftButton)
    {
        this->m_isOpened = true;
        if (m_isMine)
        {
            this->setPixmap(QPixmap(":/images/mine1.png"));
            minescene->openAllItems();
            minescene->m_isGameOver = true;
            int button = QMessageBox::question((QWidget *)minescene->parent(), tr("游戏失败"), tr("是否开始新游戏？"), QMessageBox::Ok | QMessageBox::Cancel);
            if (button == QMessageBox::Ok)
                emit minescene->sig_scenenewGame();
        }
        else
        {
            if (m_aroundMineNum == 0)
            {
                this->setPixmap(QPixmap(":/images/mine1-0"));
                minescene->expendWater(this);

            }
            else
            {
                QString path =  tr(":/images/mine1-") + QString::number(m_aroundMineNum )+tr(".png");
                this->setPixmap(QPixmap(path));

            }
        }
        minescene->m_remainNoMines--;
        if (minescene->m_remainNoMines == 0)
        {
            minescene->m_isGameOver = true;
            minescene->openAllItems();
            emit minescene->sig_successPassGame();
        }
    }
}


