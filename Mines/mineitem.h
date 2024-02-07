#ifndef MINEITEM_H
#define MINEITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include "common.h"
class MineItem :public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit MineItem(int t_x,int t_y,QPixmap itempixmap,QGraphicsPixmapItem *parent = 0);
    int  m_X;           	//容器的行数
    int  m_Y;            	//容器的列数
    bool m_isMine;          //是否为雷
    bool m_isOpened;        //是否打开
    bool m_isrightsigned;	//正确的标记动作
    int  m_aroundMineNum;	//雷周围的其他雷数
    int  m_rMouseKeyNum;	//右键点击的次数


    void mousePressEvent(QGraphicsSceneMouseEvent *event); 			//鼠标点击事件(右键)
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);  		//鼠标释放事件（左键）
//    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event); 	//鼠标左键双击事件

signals:
    void sig_restartGame();   //重新开始游戏信号
    void sig_resetMineNum(int t_signedMineNum); //重设雷数信号

};

#endif // MINEITEM_H
