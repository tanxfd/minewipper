#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QWidget>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSettings>
#include <QLCDNumber>
#include <QMainWindow>
#include <QPalette>
#include <QColorDialog>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QPixmap>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QInputDialog>
#include <QTimeLine>
#include <QTimer>
#include <time.h>
#include "common.h"
#include "customdialog.h"
#include "hero.h"
#include "minescene.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QAction *newAction;
    QAction *lowAction;
    QAction *mediumAction;
    QAction *highAction;
    QAction *customAction;
    
    QAction *heroAction;
    QAction *colorAction;
    QAction *soundAction;
    QAction *exitAction;
    QAction *aboutAction;

    QWidget *centralGet;
    QGraphicsView *mineView;
    MineScene *mineScene;
    QLCDNumber *mineLCD;
    
    QLCDNumber *secondLCD;
    QPushButton *rabbitButton;
    int m_time;			//当前用时数
    QTimer *m_timer;	//计时器

    void CreatAction();
    void CreatMenu();
    void readSetting();
    void writeSetting();

public slots:
    void slot_newgame();
    void slot_newgamebydiff(QAction *actions);
    void slot_acceptcustomgame(int, int, int);
    void slot_displayhero();
    void slot_colorAction();
    
    void slot_soundAction();
    void slot_heroupdate();
    void slot_displayminenums(int flagmines);
    void slot_dispalytimes();
    void slot_about();

};

#endif // MAINWINDOW_H
