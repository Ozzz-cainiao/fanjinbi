#include "mypushbutton.h"
#include <QDebug>
#include<QPropertyAnimation>  //动画对象的头文件

//参数1  正常显示图片路径  参数2  按下后切换图片路径
MyPushButton::MyPushButton(QString normalImg,QString pressImg)
{
    this->normalPath = normalImg;
    this->pressPath = pressImg;

    //创建QPixmap对象
    QPixmap pix;
    bool ret = pix.load(this->normalPath);  //ret用于报错加载成功与否的结果
    if(!ret)
    {
        QString str = QString("图片加载失败，失败的路径是： %1").arg(this->normalPath);
        qDebug()<<str;
    }
    //如果成功
    //设置按钮固定尺寸
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则样式
    this->setStyleSheet("QPushButton{border:0px;}");  //有点类似于网页设计中的CSS语法
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));
}
//向上跳
void MyPushButton::zoom1()
{
//    创建动态对象
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
//    设置动画的时间间隔
    animation->setDuration(200);
//    起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
//    结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
//    设置弹跳曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
//    执行动画
    animation->start();
}
//向下跳
void MyPushButton::zoom2()
{
    //    创建动态对象
        QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    //    设置动画的时间间隔
        animation->setDuration(200);
    //    起始位置
        animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //    结束位置
        animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //    设置弹跳曲线
        animation->setEasingCurve(QEasingCurve::OutBounce);
    //    执行动画
        animation->start();

}
void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    //相当于做了一层拦截
    if(this->pressPath!="")//传入的图片不为空 需要切换图片
    {
        QPixmap pix;
        bool ret = pix.load(this->pressPath);  //ret用于报错加载成功与否的结果
        if(!ret)
        {
            QString str = QString("图片加载失败，失败的路径是： %1").arg(this->normalPath);
            qDebug()<<str;
        }
        //如果成功
        //设置按钮固定尺寸
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则样式
        this->setStyleSheet("QPushButton{border:0px;}");  //有点类似于网页设计中的CSS语法
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
//    让父类执行其他内容
    return QPushButton::mousePressEvent(e);


}
void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    //相当于做了一层拦截
    if(this->pressPath!="")//传入的图片不为空 需要切换成初始图片
    {
        QPixmap pix;
        bool ret = pix.load(this->normalPath);  //ret用于报错加载成功与否的结果
        if(!ret)
        {
            QString str = QString("图片加载失败，失败的路径是： %1").arg(this->normalPath);
            qDebug()<<str;
        }
        //如果成功
        //设置按钮固定尺寸
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则样式
        this->setStyleSheet("QPushButton{border:0px;}");  //有点类似于网页设计中的CSS语法
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
//    让父类执行其他内容
    return QPushButton::mouseReleaseEvent(e);

}

