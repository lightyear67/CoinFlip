#include "playsene.h"
#include<QDebug>
#include<QMenuBar>
#include<QPainter>
#include<mypushbutton.h>
#include<QTimer>
#include<QLabel>
#include"mycion.h"
#include"dataconfig.h"
#include<QPropertyAnimation>
#include<QSound>
//PlaySene::PlaySene(QWidget *parent) : QMainWindow(parent)
//{

//}
PlaySene::PlaySene(int levelNum)
{
    QString str= QString("进入了第%1关").arg(levelNum);
    qDebug()<<str;
    this->levelIndex=levelNum;


    //初始化游戏场景

    //设置固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻金币场景");

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

    //返回音效
     QSound *backSound =new QSound(":/res/BackButtonSound.wav");
     //胜利音效
     QSound *winSound=new QSound(":/res/LevelWinSound.wav");
     //翻金币音效
     QSound *playSound=new QSound(":/res/ConFlipSound.wav");
    //返回游戏
    MyPushButton *backBtn =new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //点击返回
    connect(backBtn,&QPushButton::clicked,[=](){
        qDebug()<<"返回了选择";
        backSound->play();
        //告诉主场景  我返回了  主场景监听ChoseLevelScene的返回按钮
        //延时返回
        QTimer::singleShot(0,[=](){
            emit this->ChoseSceneBack();
        });

    });

    //显示当前关卡数
    QLabel *label=new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("文泉驿微米黑");
    font.setPointSize(20);
    QString str1 =QString("LEVEL:%1").arg(levelIndex);
    //将字体设置到标签控件中
    label->setFont(font);
    label->setText(str1);
    label->setGeometry(10,520,120,60);


    dataConfig config;
    //初始化每个关卡的二维数组
    for(int i=0;i<4;i++)
    {
        for (int j=0;j<4;j++)
        {
            this->gameArray[i][j]=config.mData[this->levelIndex][i][j];
        }
    }
    //胜利图案显示（先放在窗口之上）
    QLabel *winLabel =new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());
    //显示金币背景图案
    for(int i=0;i<4;i++)
        {
        for (int j=0;j<4;j++)
        {
            //绘制背景图片
            QPixmap pix=QPixmap(":/res/BoardNode(1).png");
            QLabel *label =new QLabel;
            label->setGeometry(0,0,pix.width(),pix.height());
            label->setPixmap(pix);
            label->setParent(this);
            label->move(57+i*50,180+j*50);

            //创建金币
            QString str;

            if(this->gameArray[i][j]==1)
            {
                str=":/res/Coin0001.png";

            }
            else {
                str=":/res/Coin0008.png";
            }
            MyCion *coin =new MyCion(str);
            coin->setParent(this);
            coin->move(59+i*50,182+j*50);

            //给金币属性赋值
            coin->posX=i;
            coin->posY=j;
            coin->flag=this->gameArray[i][j];//1正面 0反面

            //将金币放入到  金币的二维数组里  以便后期的维护
            coinBtn[i][j]=coin;


            //点击金币  进行翻转
            connect(coin,&MyCion::clicked,[=](){


                //点击音效
                playSound->play();
                //金币开始翻转时   禁止点击其他金币
                for (int i=0;i<4;i++)
                {
                    for (int j=0;j<4;j++)
                    {
                       this->coinBtn[i][j]->isWin=true;
                    }
                }


                coin->changeFlag();
                this->gameArray[i][j]=this->gameArray[i][j]==0?1:0;//便于维护



                //翻转周围的硬币

                //延时
                QTimer::singleShot(300,this,[=](){
                    //右侧
                    if(coin->posX+1<=3)
                    {
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX+1][coin->posY]=this->gameArray[coin->posX+1][coin->posY]==0?1:0;
                    }
                    //左侧
                    if(coin->posX-1>=0)
                    {
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX-1][coin->posY]=this->gameArray[coin->posX-1][coin->posY]==0?1:0;
                    }
                    //下侧
                    if(coin->posY+1<=3)
                    {
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY+1]=this->gameArray[coin->posX][coin->posY+1]==0?1:0;
                    }
                    //上侧
                    if(coin->posY-1>=0)
                    {
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY-1]=this->gameArray[coin->posX][coin->posY-1]==0?1:0;
                    }

                    // 翻转完成    解除禁止翻转金币
                    for (int i=0;i<4;i++)
                    {
                        for (int j=0;j<4;j++)
                        {
                            this->coinBtn[i][j]->isWin=false;
                        }
                    }


                    //判断是否胜利
                   this->isWin=true;
                    for (int i=0;i<4;i++)
                    {
                        for (int j=0;j<4;j++)
                        {
                            if(coinBtn[i][j]->flag==false)//只要有一个是反面,就失败
                            {
                                this->isWin=false;
                                break;
                            }
                        }
                    }
                    if(this->isWin==true)
                    {
                        //胜利了
                        winSound->play();
                        qDebug()<<"=========================游戏胜利=============================";
                        //将所有按钮的胜利的标志  改为true
                        {
                            for (int i=0;i<4;i++)
                            {
                                for (int j=0;j<4;j++)
                                {
                                    coinBtn[i][j]->isWin=true;

                                }
                            }
                            //胜利图片移动下来
                            QPropertyAnimation *animation=new QPropertyAnimation(winLabel,"geometry");
                            //设置时间  间隔
                            animation->setDuration(1000);
                            //设置开始位置
                            animation->setStartValue( QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                            //设置结束位置
                            animation->setEndValue( QRect(winLabel->x(),winLabel->y()+144,winLabel->width(),winLabel->height()));
                            //设置缓和曲线
                            animation->setEasingCurve(QEasingCurve::OutBounce);
                            //执行动画
                            animation->start();
                        }
                    }
                });

            });
        }
    }
}


void PlaySene::paintEvent(QPaintEvent *)
{
    QPainter painter(this) ;
    QPixmap pix;
    pix.load(":/res/MenuSceneBg1.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //图标
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width(),pix.height()*0.8);
    painter.drawPixmap(20,20,pix);


}
