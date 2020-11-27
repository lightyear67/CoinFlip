#include "choselevelscene.h"
#include<QMenuBar>
#include<QPainter>
#include<mypushbutton.h>
#include<QDebug>
#include<QTimer>
#include<QLabel>
#include<QSound>

ChoseLevelScene::ChoseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //配置选择关卡的配置
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("选择关卡");
    //创建菜单栏
    QMenuBar * bar =menuBar();
    setMenuBar(bar);
    //创建开始菜单
    QMenu* startMenu = bar->addMenu("开始");
    //创建退出  菜单项
    QAction *quitAction =startMenu->addAction("退出");
    //点击退出   退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //选择关卡按钮音效
    QSound *chooseSound =new QSound(":/res/TapButtonSound.wav");
    //返回音效
    QSound *backSound =new QSound(":/res/BackButtonSound.wav");

    //返回游戏
    MyPushButton *backBtn =new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //点击返回
    connect(backBtn,&QPushButton::clicked,[=](){


        //告诉主场景  我返回了  主场景监听ChoseLevelScene的返回按钮
        //播放返回按钮音乐
        backSound->play();
        //延时返回
        QTimer::singleShot(0,[=](){
            emit this->ChoseSceneBack();
        });

    });
    //创建选择关卡按钮
    for(int i=0;i<20;i++)
    {
        MyPushButton * menuBtn =new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(i%4*60+40,i/4*90+100);
        connect(menuBtn,&MyPushButton::clicked,[=](){
            QString str=QString("第%1关").arg(i+1);
            qDebug()<<str;
            chooseSound->play();

            //进入到游戏场景
            this->hide();
           play = new PlaySene(i+1);
           //设置游戏场景的初始位置
           play->setGeometry(this->geometry());
           play->show();



           connect(play,&PlaySene::ChoseSceneBack,[=](){
               this->setGeometry(play->geometry());
               this->show();
               delete play;
               play=NULL;
           });
        });

       QLabel *label =new QLabel;
       label->setParent(this);
       label->setFixedSize(menuBtn->width(),menuBtn->height());
       label->setText(QString::number(i+1));
       label->move(i%4*60+40,i/4*90+100);

       //设置label上的文字对齐方式  水平、垂直居中
       label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
       //设置让鼠标进行穿透
       label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }

}


void  ChoseLevelScene::paintEvent(QPaintEvent *){
   QPainter painter(this) ;
   QPixmap pix;
   pix.load(":/res/OtherSceneBg.jpg");
   painter.drawPixmap(0,0,this->width(),this->height(),pix);

   //图标
   pix.load(":/res/Title.png");
   pix=pix.scaled(pix.width(),pix.height()*0.8);
   painter.drawPixmap(20,20,pix);
}

