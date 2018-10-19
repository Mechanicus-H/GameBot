#ifndef ACTION_H
#define ACTION_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QtCore>
#include <windows.h>


// Типы действий
#define ACTION int
#define ACTION_WAIT 0
#define ACTION_LEFTCLICK 1
#define ACTION_RIGHTCLICK 2
#define ACTION_MOVETO 3
#define ACTION_DRAG 4
#define ACTION_PRESSKEY 5
#define ACTION_INPUTTEXT 6

struct Action
{
    ACTION type;
    QPoint target;
    QPoint begin;
    QString text;
    int delay;
    int modifiers;
};

// Utilites



#endif // ACTION_H
