#ifndef MYCION_H
#define MYCION_H

#include <QPushButton>
#include<QTimer>

class MyCion : public QPushButton
{
    Q_OBJECT
public:
    explicit MyCion(QWidget *parent = nullptr);
    //参数代表金币或银币
    MyCion(QString btnImg);
    //金币属性
    int posX;
    int posY;
    bool flag;


    //改变标志的方法
    void changeFlag();
    QTimer *timer1;
    QTimer *timer2;
    int min=1;
    int max=8;

    //执行动画的标志
    bool isAnimation=false;

    //重写  按下
    void mousePressEvent(QMouseEvent *e);

    //是否胜利
    bool isWin=false;

signals:

};

#endif // MYCION_H
