#ifndef ACTION_H
#define ACTION_H

#include <QObject>
#include <QCursor>
#include <QDebug>
#include <QtCore>
#include <QApplication>
#include <windows.h>

namespace act_type
{
 int const
        wait=0,
        left_click=1,
        right_click=2;
}


class Action
{
private:
    int type;
    QPoint target;
    int ms;
    QCursor *cursor;
public:
    Action(){}
    explicit Action(int _type, int _seconds); // for wait
    explicit Action(int _type, QPoint _target); // for click
    void moveToTarget();
    void exec();
    void setCursor(QCursor *c);

signals:

public slots:

};

void rightClick(QPoint target, int keyModifiers=0);
void leftClick(QPoint target, int keyModifiers=0);



#endif // ACTION_H
