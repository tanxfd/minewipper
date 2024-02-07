#include <time.h>
#include "minescene.h"
#include "mineitem.h"

QPoint t_around[8] =
{
        QPoint(-1,-1),
        QPoint(-1,0),
        QPoint(-1,1),
        QPoint(0,-1),
        QPoint(0,1),
        QPoint(1,-1),
        QPoint(1,0),
        QPoint(1,1)
};

MineScene::MineScene(QObject *parent)
{

    m_signedMineNum = 0;    //右键标记的雷数
    m_rightMineNum = 0;     //右键标记正确的雷数
    m_isGameOver = false;      //游戏是否结束

}


void MineScene::initscene()       				//初始化游戏场景
{
    m_remainNoMines = m_scenecol * m_scenerow - m_minesum;    //剩余非雷数
    for (int i = 0; i < m_scenerow; i++)		//在场景布置游戏方格
    {
        QVector <MineItem *> t_vec;
        for (int j = 0; j < m_scenecol; j++)
        {
            MineItem *item_Vec = new MineItem(i ,j ,QPixmap(":/images/cover1.png"));
            item_Vec->setPos(i * COMMON::MAPWIDTH, j * COMMON::MAPHEIGHT);
            this->addItem(item_Vec);
            t_vec.push_back(item_Vec);
        }
        this->m_itemVec.push_back(t_vec);
    }

    srand(time(NULL));
    for (int i = 0; i < m_minesum; i++)			//在游戏方格上随机布雷
    {
        int i_row = rand() % m_scenerow;
        int i_col = rand() % m_scenecol;
        if (!this->m_itemVec[i_row][i_col]->m_isMine)
        {
            this->m_itemVec[i_row][i_col]->m_isMine = true;
            this->countAroundMines(this->m_itemVec[i_row][i_col]);
        }

    }
    for (int i = 0; i < m_scenerow; i++)
    {
        for (int j = 0; j < m_scenecol; j++)
        {
            this->connect(m_itemVec[i][j], SIGNAL(sig_restartGame()), this, SIGNAL(sig_scenenewGame()));
            this->connect(m_itemVec[i][j], SIGNAL(sig_resetMineNum(int)), this, SIGNAL(sig_scenedisplayMineNum(int)));
        }
    }
}

void MineScene::countAroundMines(MineItem *t_item)//统计方块周围的雷数
{
    if(t_item == NULL || !t_item->m_isMine)
        return;
    else
    {
        for (int i = 0; i < 8; i++)
        {
            int t_x = t_item->m_X + t_around[i].x();
            int t_y = t_item->m_Y + t_around[i].y();

            if (t_x < 0 || t_y < 0 || t_x >= this->m_scenerow || t_y >= this->m_scenecol)
                continue;
            if (m_itemVec[t_x][t_y]->m_isMine)
                continue;
            m_itemVec[t_x][t_y]->m_aroundMineNum++;

        }
    }
}

void MineScene::openAllItems()    				//打开所有的方块
{
    //如果游戏已结束，打开所有方块
    if(!this->m_isGameOver)
        return;

    for (int i = 0; i < m_scenerow; i++)
    {
        for (int j = 0; j < m_scenecol; j++)
        {
            m_itemVec[i][j]->m_isOpened = true;
            if (m_itemVec[i][j]->m_isMine)
            {
                m_itemVec[i][j]->setPixmap(QPixmap(":/images/mine1.png"));

            }
            else
            {
                QString path = tr("://images/mine1-") + QString::number(m_itemVec[i][j]->m_aroundMineNum)+tr(".png");
                m_itemVec[i][j]->setPixmap(path);
            }
        }
    }
}

void MineScene::expendWater(MineItem *t_item)    	//扩散函数
{
    if (!m_isGameOver || m_rightMineNum == m_minesum)
        this->openAllItems();

    for (int i = 0; i <= 8; i++)//无需考虑周围有雷的情况
    {
        int t_x = t_item->m_X + t_around[i].x();
        int t_y = t_item->m_Y + t_around[i].y();
        if (t_x < 0 || t_y < 0 || t_x >= this->m_scenerow || t_y >= this->m_scenecol)
            continue;
        else if (m_itemVec[t_x][t_y]->m_isOpened)
            continue;
        else if (this->m_itemVec[t_x][t_y]->m_rMouseKeyNum > 0)
            continue;

        //当当前方块已打开时，剩余非雷数量减1
        m_itemVec[t_x][t_y]->m_isOpened = true;
        this->m_remainNoMines--;

        int itemnum = m_itemVec[t_x][t_y]->m_aroundMineNum;//当前方块的周围雷数
        if(0 == itemnum)
        {
            expendWater(m_itemVec[t_x][t_y]);

        }

        QString path = tr(":/images/mine1-") + QString::number(m_itemVec[t_x][t_y]->m_aroundMineNum )+tr(".png");
        m_itemVec[t_x][t_y]->setPixmap(QPixmap(path));

    }

    while (m_remainNoMines == 0)
    {
        m_isGameOver = true;
        this->openAllItems();
        emit sig_successPassGame();
    }
}

