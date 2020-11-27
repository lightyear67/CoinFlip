#ifndef CHOSELEVELSCENE_H
#define CHOSELEVELSCENE_H

#include <QMainWindow>
#include<playsene.h>
class ChoseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChoseLevelScene(QWidget *parent = nullptr);
    //重写绘图事件
    void paintEvent(QPaintEvent *);

    //游戏对象指针
     PlaySene *play= NULL;

signals:
    //写一个自定义的信号,告诉主场景  点击了返回
    void ChoseSceneBack();


};

#endif // CHOSELEVELSCENE_H
