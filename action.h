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
    ACTION type;    // Тип действия
    QPoint target;  // Целевая точка
    QPoint begin;   // Точка начала действия
    QString text;   // Если нужно ввести текст
    Qt::Key key;        // Если нужно нажать клавишу
    int delay;      // Задержка в милисекундах
    Qt::KeyboardModifiers modifier;   // модификаторы (CTRL/Alt...). Сохраняются как Qt::Modifier
};

// Utilites

QString toString(const Action& act);        // Action в строку. Для сохранения в файл/вывода в терминал
Action fromString(const QString& str);      // Из строки. Чтение из файла/терминала.
QPoint pointFromString(const QString& str); // QPoint из строки вида (xxx,yyy) , предполагаются int'ы

#endif // ACTION_H
