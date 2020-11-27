#include "mycion.h"
#include<QDebug>
#include"mycion.h"

//MyCion::MyCion(QWidget *parent) : QPushButton(parent)
//{

//}
MyCion::MyCion(QString btnImg)
{
    QPixmap pix;
    bool ret = pix.load(btnImg);
    if(!ret)
    {
        QString str=QString ("图片%1加载失败").arg(btnImg);
        qDebug()<<str;
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
    //初始化定时器对象
    timer1=new QTimer(this);
    timer2=new QTimer(this);
    //监听正面翻反面的信号，并且反转金币
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        //
        //如果翻完了    将min重置为1
        if(this->min>this->max)
        {
            this->min=1;
            isAnimation=false;
            timer1->stop();
        }
    });

    //监听反面翻正面的信号，并且反转金币
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str=QString(":/res/Coin000%1.png").arg(this->max--);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px;}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        //如果翻完了    将min重置为1
        if(this->max<this->min)
        {
            this->max=8;
            isAnimation=false;
            timer2->stop();
        }
    });
}
void MyCion::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation||this->isWin)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}



//改变正反面的标志的方法
void MyCion::changeFlag(){
    //如果是正面  翻成反面
    if((this)->flag)
    {
        timer1->start(30);//开始做动画
        isAnimation=true;
        this->flag=false;


    }
    //如果是反面
    else {
        timer2->start(30);//开始做动画
        isAnimation=true;
        this->flag=true;

    }
}
