#include "chooselevelsence.h"
#include <QMenuBar>
#include <QPainter>
#include <mypushbutton.h>
#include <QPushButton>
#include <QDebug>
#include <QLabel>
#include <QTimer>
#include <QSound>
ChooseLevelSence::ChooseLevelSence(QWidget *parent) : QMainWindow(parent)
{
//    配置选择关卡场景
    this->setFixedSize(390,570);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("选择关卡场景");

//    创建菜单栏
    QMenuBar * bar= menuBar();
    setMenuBar(bar);

    QMenu *startMenu=bar->addMenu("开始");
    QAction * quitAction =startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=]()
    {
        this->close();

    });
//    返回按钮
    QSound *backSound=new QSound(":/res/BackButtonSound.wav");
    MyPushButton *backBtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    //准备选择关卡按钮的音效
    QSound *chooseSound=new QSound(":/res/TapButtonSound.wav");


//    点击返回

    connect(backBtn,&MyPushButton::clicked,[=]()
    {
//        qDebug()<<"点击了返回按钮";

        backSound->play();
        //告诉主场景 我返回了 主场景监听返回信号
        QTimer::singleShot(500,this,[=]()
        {
            emit this->chooseSenceBack();
        });
    });
//    创建选择关卡的按钮
    for (int i=0;i<20 ;i++ )
    {
        MyPushButton *menuBtn=new MyPushButton(":/res/LevelIcon.png","");
        menuBtn->setParent(this);
        menuBtn->move(i%4*80+60,i/4*80+150);
        connect(menuBtn,&MyPushButton::clicked,[=]()
        {
//            按钮的点击事件
            QString str=QString("您选择的是第%1关").arg(i+1);
            qDebug()<<str;
            chooseSound->play();
//            进入到游戏场景
            this->hide();//将选关场景隐藏掉 并创建游戏显示
            play=new PlayScene(i+1);
            //设置游戏场景的初始位置
            play->setGeometry(this->geometry());
            play->show();


            connect(play,&PlayScene::chooseSenceBack,[=]()
            {
                this->setGeometry(play->geometry());
                this->show();
                delete play;
                play=NULL;

            });
        });
//        menuBtn->setText(QString::number(i+1));  显示效果不好  采用QLabel
        QLabel *label=new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(i%4*80+50,i/4*80+150);
//        设置label上的对齐方式
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        // 设置鼠标穿透  QWidget 51号属性
        label->setAttribute(Qt::WA_TransparentForMouseEvents);


    }
}
void ChooseLevelSence::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

//    加载标题
    pix.load (":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width ())*0.5,30,pix.width(),pix.height (),pix);
}
