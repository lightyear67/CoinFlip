#ifndef PLAYSENE_H
#define PLAYSENE_H

#include <QMainWindow>
#include"mycion.h"

class PlaySene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlaySene(QWidget *parent = nullptr);

    PlaySene(int levelNum);
    int levelIndex;//内部成员属性  记录所选关卡

    //重写paintEvent事件
    void paintEvent(QPaintEvent *);

    int gameArray[4][4];//二维数组   维护每个关卡的具体数据

    MyCion *coinBtn[4][4];

    //是否胜利
    bool isWin=false;

signals:
   void ChoseSceneBack();

};

#endif // PLAYSENE_H
