#include "mycoin.h"
#include <QDebug>
#include <QTimer>
//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{

//}
MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix;
    bool ret= pix.load(btnImg);
    if(!ret)
    {
        QString str=QString("图片 %1 加载失败").arg(btnImg);
        qDebug()<<str;
        return;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    //    初始化定时器对象
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //监听正面翻反面的信号
    connect(timer1,&QTimer::timeout,[=]()
    {
        QPixmap pix;
        QString str=QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        //判断 如果翻完了 将min重置为1
        if(this->min > this->max)
        {
            this->min=1;
            isAnimation=0;
            timer1->stop();
        }
    });
    //监听反面翻正面的信号
    connect(timer2,&QTimer::timeout,[=]()
    {
        QPixmap pix;
        QString str=QString(":/res/Coin000%1.png").arg(this->max--);
        pix.load(str);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        //判断 如果翻完了 将min重置为1
        if(this->max < this->min)
        {
            this->max=8;
            isAnimation=0;
            timer2->stop();
        }

    });
}

//改变正反面标志的方法
void MyCoin::changeFlag()
{
    //    如果是正 翻反面
    if(this->flag)
    {
        timer1->start(50);
        this->flag=false;
        isAnimation=1;//开始做动画

    }
    else
    {
        timer2->start(50);
        this->flag=true;
        isAnimation=1;
    }

}
 void MyCoin::mousePressEvent(QMouseEvent *e)
 {
     if(this->isAnimation|this->isWin)
     {
         return;
     }
     else
     {
         return QPushButton::mousePressEvent(e);
     }
 }
