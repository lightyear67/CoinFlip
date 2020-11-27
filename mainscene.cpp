#include "mainscene.h"
#include "ui_mainscene.h"
#include"QPainter"
#include"mypushbutton.h"
#include"QDebug"
#include<QTimer>
#include<QSound>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //配置主场景

    //设置固定大小
    setFixedSize(320,588);
    //设置图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置标题
    setWindowTitle("翻金币主场景");
    //退出按钮的实现
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    //准备开始按钮的音效
    QSound *startSound = new QSound(":/res/TapButtonSound.wav");

    //开始按钮
    MyPushButton *startBtn=new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.4);

    //实例化选择关卡场景
    choseScene = new ChoseLevelScene;

    //监听选择关卡的返回按钮的信号
    connect(choseScene,&ChoseLevelScene::ChoseSceneBack,this,[=](){
        this->setGeometry(choseScene->geometry());
       choseScene->hide();//选择关卡隐藏
       this->show();//开始场景显示
    });

    connect(startBtn,&QPushButton::clicked,[=](){


        //播放开始音效
        startSound->play();

        //做一个弹起的特效
        startBtn->zoom1();
        //startBtn->zoom2();

        //自己做的简单弹跳   无弹跳曲线
//        startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7+3);
//    });
//    connect(startBtn,&QPushButton::released,[=](){
//        qDebug()<<"释放了开始";
//        //做一个弹起的特效
//        startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7-3);

        //延时进入到关卡场景中
        QTimer::singleShot(180,this,[=](){
            //设置ChooseScene场景的位置
            choseScene->setGeometry(this->geometry());
            //进入选择关卡场景
            //自身隐藏
            this->hide();
            //显示选择关卡的场景
            choseScene->show();
        });




    });
}


 void MainScene::paintEvent(QPaintEvent *){
     QPainter painter(this);
     QPixmap pix;
     pix.load(":/res/PlayLevelSceneBg.jpg");
     painter.drawPixmap(0,0,this->width(),this->height(),pix);

     //画背景图标
     pix.load(":/res/Title.png");
     pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
     painter.drawPixmap(20,20,pix);
 }

MainScene::~MainScene()
{
    delete ui;
}

