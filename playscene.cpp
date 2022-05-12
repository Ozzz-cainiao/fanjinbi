#include "playscene.h"
#include <QDebug>
#include <QMenu>
#include <QMenuBar>
#include <QPainter>
#include <mypushbutton.h>
#include <QTimer>
#include <QLabel>
#include <mycoin.h>
#include "dataconfig.h"
#include <QPropertyAnimation>
#include <QSound>

//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}
PlayScene::PlayScene(int levelNum)
{
    QString str=QString("您进入了第%1关").arg(levelNum);
    qDebug()<<str;
    this->levelIndex=levelNum;

    //    初始化游戏场景
    this->setFixedSize(390,570);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("游戏场景");
    //    创建菜单栏
    QMenuBar * bar= menuBar();
    setMenuBar(bar);

    QMenu *startMenu=bar->addMenu("开始");
    QAction * quitAction =startMenu->addAction("退出");
    //    退出游戏
    connect(quitAction,&QAction::triggered,[=]()
    {
        this->close();

    });

    //    返回按钮
    MyPushButton *backBtn=new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    //加载音乐资源
    QSound *backSound=new QSound(":/res/BackButtonSound.wav");
    QSound *flipSound=new QSound(":/res/ConFlipSound.wav");
    QSound *winSound=new QSound(":/res/LevelWinSound.wav");
    //    点击返回
    connect(backBtn,&MyPushButton::clicked,[=]()
    {
        backSound->play();
        qDebug()<<"游戏界面点击了返回按钮";
        QTimer::singleShot(500,this,[=]()
        {
            emit this->chooseSenceBack();
        });
    });
    //    显示当前关卡数：
    QLabel *label=new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    QString str1=QString("Level:%1").arg(this->levelIndex);
    //    将字体设置到标签中
    label->setFont(font);
    label->setText(str1);
    label->setGeometry(30,this->height()-50,120,50);

    //    初始化每个关卡的二维数组
    dataConfig config;
    for (int i=0;i<4 ;i++ )
    {
        for (int j=0;j<4 ;j++ )
        {
            this->gameArray[i][j]=config.mData[this->levelIndex][i][j];
        }

    }

    //胜利背景显示
    QLabel *winLabel=new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setParent(this);
    winLabel->setPixmap(tmpPix);
    winLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());
    //    显示金币背景图案
    for (int i=0;i<4 ;i++ )
    {
        for (int j=0;j<4 ;j++ )
        {
            //            绘制背景图片
            QLabel *label=new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode.png"));
            label->setParent(this);
            label->move(80+i*50,180+j*50);

            //            创建金币
            if(this->gameArray[i][j]==1)
            {
                str=":/res/Coin0001.png";
            }
            else
            {
                str=":/res/Coin0008.png";
            }
            MyCoin *mycoin=new MyCoin(str);
            mycoin->setParent(this);
            mycoin->move(84+i*50,184+j*50);
            //            给金币属性赋值
            mycoin->posX=i;
            mycoin->posY=j;
            mycoin->flag=this->gameArray[i][j];//1正面0反面
            //            将金币放入金币的二维数组中，以便后期维护
            coinBtn[i][j]=mycoin;
            //点击金币  进行翻转
            connect(mycoin,&MyCoin::clicked,[=]()
            {
                flipSound->play();
                //点击按钮 将所有金币先禁用
                for (int i=0;i<4 ;i++ )
                {
                    for (int j=0;j<4 ;j++ )
                    {
                        this->coinBtn[i][j]->isWin=1;
                    }
                }

                mycoin->changeFlag();
                this->gameArray[i][j]=this->gameArray[i][j]==0?1:0;
                //                加一个延时
                QTimer::singleShot(100,this,[=]()
                {

                    // 翻转周围金币
                    if(mycoin->posX+1<=3)//周围的右侧金币翻转条件
                    {
                        coinBtn[mycoin->posX+1][mycoin->posY]->changeFlag();
                        this->gameArray[mycoin->posX+1][mycoin->posY]=this->gameArray[mycoin->posX+1][mycoin->posY]==0?1:0;
                    }
                    if(mycoin->posX-1>=0)//周围的左侧金币翻转条件
                    {
                        coinBtn[mycoin->posX-1][mycoin->posY]->changeFlag();
                        this->gameArray[mycoin->posX-1][mycoin->posY]=this->gameArray[mycoin->posX-1][mycoin->posY]==0?1:0;
                    }
                    if(mycoin->posY+1<=3)//周围的下侧金币翻转条件
                    {
                        coinBtn[mycoin->posX][mycoin->posY+1]->changeFlag();
                        this->gameArray[mycoin->posX][mycoin->posY+1]=this->gameArray[mycoin->posX][mycoin->posY+1]==0?1:0;
                    }
                    if(mycoin->posY-1>=0)//周围的上侧金币翻转条件
                    {
                        coinBtn[mycoin->posX][mycoin->posY-1]->changeFlag();
                        this->gameArray[mycoin->posX][mycoin->posY-1]=this->gameArray[mycoin->posX][mycoin->posY-1]==0?1:0;
                    }
                    //翻完金币后
                    for (int i=0;i<4 ;i++ )
                    {
                        for (int j=0;j<4 ;j++ )
                        {
                            this->coinBtn[i][j]->isWin=0;
                        }
                    }
                    //金币翻完后 判断是否胜利
                    this->isWin=1;

                    for (int i=0;i<4 ;i++ )
                    {
                        for (int j=0;j<4 ;j++ )
                        {
                            if(coinBtn[i][j]->flag==0)
                            {
                                this->isWin=0;
                                break;
                            }
                        }
                    }

                    if(this->isWin==1)
                    {
                        //胜利了！
                        winSound->play();
                        qDebug()<<"游戏胜利了！";
                        //将所有按钮的胜利标志改为true
                        for (int i=0;i<4 ;i++ )
                        {
                            for (int j=0;j<4 ;j++ )
                            {
                                coinBtn[i][j]->isWin=1;
                            }
                        }
                        //胜利的图片砸下来
                        QPropertyAnimation *animation=new QPropertyAnimation(winLabel,"geometry");
                        //设置时间间隔
                        animation->setDuration(1000);
                        //设置开始 阶数位置 设置曲线
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+120,winLabel->width(),winLabel->height()));
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start();


                    }
                });

            });

        }
    }
}
void PlayScene::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //    加载标题
    pix.load (":/res/Title.png");
    pix=pix.scaled (pix.width ()*0.5,pix.height ()*0.5);
    painter.drawPixmap (10,30,pix);
}



