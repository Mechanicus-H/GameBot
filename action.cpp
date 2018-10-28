#include "action.h"
#include <algorithm>
#include <QStringList>




//-----------------------------------------------
/*
Выведет строчку вида:

# ACTION_LEFTCLICK
{
begin(0, 0)
target(1793, 198)
text: ""
delay: 1000
modifier: None
}

*/
QString toString(const Action &act)
{
    QString result="# ";

    switch (act.type)
    {
    case ACTION_WAIT: result+="ACTION_WAIT"; break;
    case ACTION_LEFTCLICK: result+="ACTION_LEFTCLICK"; break;
    case ACTION_RIGHTCLICK: result+="ACTION_RIGHTCLICK"; break;
    case ACTION_MOVETO: result+="ACTION_MOVETO"; break;
    case ACTION_DRAG: result+="ACTION_DRAG"; break;
    case ACTION_INPUTTEXT: result+="ACTION_INPUTTEXT"; break;
    case ACTION_PRESSKEY: result+="ACTION_PRESSKEY"; break;
    default: return result; break;
    }
    result+="\n{\n";
    result+="begin(" + QString::number(act.begin.x())+
            ", " + QString::number(act.begin.y()) + ")\n";

    result+="target(" + QString::number(act.target.x())+
            ", " + QString::number(act.target.y()) + ")\n";

    result+="text: \"" + act.text +"\"\n";

    result+="delay: " +QString::number(act.delay)+"\n";

    result+="modifier: ";

    switch (act.modifier)
    {
    case Qt::AltModifier: result+="Alt"; break;
    case Qt::ControlModifier: result+="Ctrl"; break;
    case Qt::ShiftModifier: result+="Shift"; break;
    default: result+="None"; break;
    }
    result+="\n}\n";
//    qDebug() << result;
    return result;

}
//-----------------------------------------------

Action fromString(const QString& str)
{
    Action result;

    QStringList list=str.split("\n");
    list[0].remove(' ');
    list[0].remove('#');
//    qDebug() << list[0];

    if(list.at(0) == "ACTION_WAIT") result.type=ACTION_WAIT;
    else if(list.at(0) == "ACTION_LEFTCLICK") result.type=ACTION_LEFTCLICK;
    else if(list.at(0) == "ACTION_RIGHTCLICK") result.type=ACTION_RIGHTCLICK;
    else if(list.at(0) == "ACTION_MOVETO") result.type=ACTION_MOVETO;
    else if(list.at(0) == "ACTION_DRAG") result.type=ACTION_DRAG;
    else if(list.at(0) == "ACTION_INPUTTEXT") result.type=ACTION_INPUTTEXT;
    else if(list.at(0) == "ACTION_PRESSKEY") result.type=ACTION_PRESSKEY;

    QString workString=list[2];
    QStringList workList=workString.split('(');
    result.begin=pointFromString(workList.at(1));

    workString=list[3];
    workList=workString.split('(');
    result.target=pointFromString(workList.at(1));

    workString=list[4];
    workList=workString.split('"');
    result.text=workList.at(1);
//    qDebug() << result.text;

    workString=list[5];
    workList=workString.split(' ');
    result.delay=workList.at(1).toInt();
//    qDebug() << workList[1] << result.delay;

    workString=list[6];
    workList=workString.split(' ');
//    qDebug() << workList[1];
    if(std::count(workList.begin(), workList.end(), "Alt")) result.modifier=Qt::AltModifier;
    else if(std::count(workList.begin(), workList.end(), "Ctrl")) result.modifier=Qt::ControlModifier;
    else if(std::count(workList.begin(), workList.end(), "Shift")) result.modifier=Qt::ShiftModifier;

    return result;
}
//-----------------------------------------------
QPoint pointFromString(const QString& str)
{
    QPoint result;

    QStringList list=str.split(",");

    list[0].remove(" "); list[1].remove(" ");
    list[1].remove(")");

    result.setX(list[0].toInt());
    result.setY(list[1].toInt());
//    qDebug() << "strX: " << list[0] << ", intX: " << result.x() ;
//    qDebug() << "strY: " << list[1] << ", intY: " << result.y() ;
    return result;
}
