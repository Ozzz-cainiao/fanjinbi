#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:

    //封装的按钮，有两种功能 参数1  正常显示图片路径  参数2  按下后切换图片路径
    //只有当第二个参数不为空，才需要切图  //按下鼠标时显示一张图片，松开鼠标时恢复原来的效果
    MyPushButton(QString normalImg,QString pressImg=" ");

//    成员属性  保存用户传入的默认显示路径
    QString normalPath;
    QString pressPath;
//    弹跳特效
    void zoom1();//向上跳
    void zoom2();//向下跳
//    重写按钮 按下 和 释放操作
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:

public slots:
};

#endif // MYPUSHBUTTON_H

