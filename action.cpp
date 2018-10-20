#include "action.h"


/*
struct Action
{
    ACTION type;
    QPoint target;
    QPoint begin;
    QString text;
    int delay;
    int modifiers;
};
 */

//-----------------------------------------------

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
    case Qt::Key_Alt: result+="Alt"; break;
    case Qt::Key_Control: result+="Ctrl"; break;
    case Qt::Key_Shift: result+="Shift"; break;
    case Qt::Key_AltGr: result+="Ctrl+Alt"; break;
    default: result+="None"; break;
    }
    result+="\n}\n";
//    qDebug() << result;
    return result;

}
