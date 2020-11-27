#include "mypushbutton.h"
#include<QDebug>
#include<mypushbutton.h>
#include<QPropertyAnimation>

//MyPushButton::MyPushButton(QWidget *parent) : QPushButton(parent)
//{

//}


 MyPushButton::MyPushButton(QString normalImg,QString pressImg){
     this->normalImgPath=normalImg;
     this->pressImgPath=pressImg;

     QPixmap pix;
    bool ret = pix.load(normalImg);
    if(!ret)
    {
       qDebug()<<"图片加载失败";
        return;
    }
    //设置图片固定大小
    this->setFixedSize(pix.width(),pix.height());

    //设置不规则图片样式
    this->setStyleSheet("QPushButton{border:0px;}");

    //设置图标
    this->setIcon(pix);

    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));


 }

 void MyPushButton::zoom1(){
     QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
     //设置时间间隔
     animation->setDuration(200);
     //起始位置
     animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

     //结束位置
     animation->setStartValue(QRect(this->x(),this->y()+8,this->width(),this->height()));

     //设置弹跳曲线
     animation->setEasingCurve(QEasingCurve::OutBounce);
     //  执行动画
      animation->start();
 }
 void MyPushButton::zoom2(){
     QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
     //设置时间间隔
     animation->setDuration(400);
     //起始位置
     animation->setStartValue(QRect(this->x(),this->y()+8,this->width(),this->height()));

     //结束位置
     animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

     //设置弹跳曲线
     animation->setEasingCurve(QEasingCurve::OutBounce);
     //  执行动画
      animation->start();


 }

 void MyPushButton::mousePressEvent(QMouseEvent *e){
     if(this->pressImgPath!="")//传入的图片不为空  说明有按下状态  需要切换
     {
         QPixmap pix;
         bool ret = pix.load(pressImgPath);
         if(!ret)
         {
            qDebug()<<"图片加载失败";
             return;
         }
         //设置图片固定大小
         this->setFixedSize(pix.width(),pix.height());

         //设置不规则图片样式
         this->setStyleSheet("QPushButton{border:0px;}");

         //设置图标
         this->setIcon(pix);

         //设置图标大小
         this->setIconSize(QSize(pix.width(),pix.height()));


     }

     //让父类执行其他的内容
     return QPushButton::mousePressEvent(e);
 }
 void MyPushButton::mouseRelesseEvent(QMouseEvent *e){

     if(this->pressImgPath!="")//传入的图片不为空  说明有按下状态  需要切换成初始图片
     {
         QPixmap pix;
         bool ret = pix.load(this->normalImgPath);
         if(!ret)
         {
            qDebug()<<"图片加载失败";
             return;
         }
         //设置图片固定大小
         this->setFixedSize(pix.width(),pix.height());

         //设置不规则图片样式
         this->setStyleSheet("QPushButton{border:0px;}");

         //设置图标
         this->setIcon(pix);

         //设置图标大小
         this->setIconSize(QSize(pix.width(),pix.height()));


     }

     //让父类执行其他的内容
     return QPushButton::mouseReleaseEvent(e);
 }

