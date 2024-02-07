#ifndef MINESCENE_H
#define MINESCENE_H

#include <QGraphicsScene>
#include <QString>
#include <QVector>
#include "mineitem.h"

class MineScene :public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MineScene(QObject *parent = 0);
    QVector< QVector< MineItem *> > m_itemVec;

    int m_scenerow; 		//当前场景行数
    int m_scenecol; 		//当前场景列数
    int m_minesum;  		//当前场景雷数
    int m_crrentlevel;		//当前场景难度级别

    int m_signedMineNum;    //右键标记的雷数
    int m_rightMineNum;     //右键标记正确的雷数
    bool m_isGameOver;      //游戏是否结束
    int m_remainNoMines;    //剩余非雷数

    void initscene();       				//初始化游戏场景
    void countAroundMines(MineItem *t_item);//统计方块周围的雷数
    void openAllItems();    				//打开所有的方块
    void expendWater(MineItem *t_item);    	//扩散函数

signals:
    void sig_successPassGame();     		//游戏成功过关信号
    void sig_scenenewGame();        		//重新开始游戏信号
    void sig_scenedisplayMineNum(int);		//显示雷数信号

};

#endif // MINESCENE_H
