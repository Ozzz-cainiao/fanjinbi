#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
//    explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString btnImg);//参数代表传入的金币路径还是银币路径

//    金币的属性
    int posX;
    int posY;
    bool flag;//正反标志

//    改变标志的方法：
    void changeFlag();
    QTimer *timer1;
    QTimer *timer2;
    int min=1;
    int max=8;

//    执行动画的标志
    bool isAnimation=0;

//    重写按下的状态
    void mousePressEvent(QMouseEvent *e);

    bool isWin=0;

signals:

};

#endif // MYCOIN_H
