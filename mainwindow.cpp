#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <mypushbutton.h>
#include <QDebug>
#include <QTimer>
#include <QSound>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //    点击菜单项  实现退出
    connect (ui->actionExit,&QAction::triggered,[=]()
    {
        this->close ();
    });
    this->setFixedSize (390,570);//设置固定尺寸
    this->setWindowTitle ("翻金币");//设置窗口标题
    this->setWindowIcon (QIcon(":/res/Coin0001.png"));//设置图标

    //准备开始按钮的音效
    QSound *startSound=new QSound(":/res/TapButtonSound.wav");
//    startSound->setLoops(-1);
//    startSound->play();
    //    创建开始按钮
    MyPushButton *startbtn=new MyPushButton(":/res/MenuSceneStartButton.png","");
    startbtn->setParent (this);
    startbtn->move (this->width ()*0.5-startbtn->width()*0.5,this->height()*0.7);

    //    实例化选择关卡的场景
    chooseSence =new ChooseLevelSence;
    //监听选择关卡到返回的信号
    connect(chooseSence,&ChooseLevelSence::chooseSenceBack,[=]()
    {
        this->setGeometry(chooseSence->geometry());
        chooseSence->hide();
        this->show();//重新显示主场景
    });
    connect(startbtn,&QPushButton::clicked,[=]()
    {
        qDebug()<<"点击了开始";
        startSound->play();
        startbtn->zoom1();
        startbtn->zoom2();
        //        延时进入到选择关卡的场景中
        QTimer::singleShot(500,this,[=]()
        {
            //设置choosesence场景的位置
            chooseSence->setGeometry(this->geometry());
            //自身隐藏
            this->hide();
            //显示选择关卡的场景

            chooseSence->show();
        });

    });

}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load (":/res/PlayLevelSceneBg.png");
    painter.drawPixmap (0,0,this->width (),this->height (),pix);//背景适应窗口尺寸
    pix.load (":/res/Title.png");
    pix=pix.scaled (pix.width ()*0.5,pix.height ()*0.5);
    painter.drawPixmap (10,30,pix);

}
MainWindow::~MainWindow()
{
    delete ui;
}

