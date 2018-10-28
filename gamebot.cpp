#include "gamebot.h"

GameBot::GameBot(QWidget *parent)
    : QWidget(parent)
{
    modif=Qt::NoModifier;

    isRecord=false;
    isExec=false;
    startTimer(2);
    timer=0;
    actionDelayTimer=new QTimer;

    resize(300, 75);
    setWindowFlags(Qt::WindowStaysOnTopHint);

    modifs=new QLabel;
    updateModifInfo();

    lblX=new QLabel;
    lblY=new QLabel;
    lblClick=new QLabel;
    systemConsole=new QTextEdit;
    systemConsole->setReadOnly(true);



    startRecord=new QPushButton("Start record");
    connect(startRecord, SIGNAL(clicked()), this, SLOT(slotStartRecord()));

    stopRecord=new QPushButton("Stop Record");
    connect(stopRecord, SIGNAL(clicked()), this, SLOT(slotStopRecord()));

    saveProgram=new QPushButton("Save Program");
    connect(saveProgram, SIGNAL(clicked()), this, SLOT(slotSave()));

    loadProgram=new QPushButton("Load Program");
    connect(loadProgram, SIGNAL(clicked()), this, SLOT(slotLoad()));

    startProgram=new QPushButton("Start Program");
    connect(startProgram, SIGNAL(clicked()), this, SLOT(slotStartProgram()));

    QHBoxLayout *line1=new QHBoxLayout;
    QHBoxLayout *line2=new QHBoxLayout;
    QHBoxLayout *line3=new QHBoxLayout;

    line1->addWidget(lblX);
    line1->addWidget(lblY);
    line1->addWidget(lblClick);

    line2->addWidget(startRecord);
    line2->addWidget(stopRecord);

    line3->addWidget(saveProgram);
    line3->addWidget(loadProgram);

    QVBoxLayout *Vbox=new QVBoxLayout;
    Vbox->addLayout(line1);
    Vbox->addLayout(line2);
    Vbox->addLayout(line3);
    Vbox->addWidget(modifs);

    Vbox->addWidget(startProgram);
    Vbox->addWidget(systemConsole);

    setLayout(Vbox);
    slotSetStatus();
}
//-----------------------------------------------
GameBot::~GameBot()
{

}
//-----------------------------------------------

void GameBot::saveToFile(const QString& fileName)
{
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly))
    {
        systemConsole->append("File: \""+fileName+"\" open");
        QTextStream stream(&file);
        for(int i=0; i<program.size(); i++)
        {
            stream << toString(program.at(i));
        }
    }
    file.close();
    systemConsole->append("Program saved");
}

//-----------------------------------------------
void GameBot::timerEvent(QTimerEvent *te)
{
    cursorPosition=cursor().pos();

    timer+=2;
    slotShowMouseState();



    QWidget::timerEvent(te);
}
//-----------------------------------------------
void GameBot::keyPressEvent(QKeyEvent *ke)
{

    Action act;

    if(isExec)
    {
        if(ke->key()==Qt::Key_F8)
        {
            isExec=false;
            systemConsole->append("Execute Stoped");
        }
    }


    if(isRecord)
    {
        int ms= timer;
        timer=0;

        if(ke->key()==Qt::Key_7) // Left
        {
            act.type=ACTION_LEFTCLICK;
            act.delay=ms;
            act.target=cursorPosition;
            act.modifier=modif;
            program.push_back(act);

            systemConsole->append(createMessage(act));
        }
        else if(ke->key()==Qt::Key_9) // Right
        {
            act.type=ACTION_RIGHTCLICK;
            act.delay=ms;
            act.target=cursorPosition;
            act.modifier=modif;
            program.push_back(act);

            systemConsole->append(createMessage(act));
        }
        else if(ke->key()==Qt::Key_8) // Move to
        {
            act.type=ACTION_MOVETO;
            act.delay=ms;
            act.target=cursorPosition;
            act.modifier=modif;
            program.push_back(act);

            systemConsole->append(createMessage(act));
        }
        else if(ke->key()==Qt::Key_4) // Start drag
        {
            act.type=ACTION_DRAG;
            act.delay=ms;
            act.begin=cursorPosition;
            act.modifier=modif;
            program.push_back(act);
        }
        else if(ke->key()==Qt::Key_6)
        {
            if(program.last().type==ACTION_DRAG)
            {
                program.last().target=cursorPosition;
                systemConsole->append(createMessage(program.last()));
            }
        }
        else if(ke->key()==Qt::Key_Shift)
        {
            if(modif!=Qt::ShiftModifier) modif=Qt::ShiftModifier;
            else modif=Qt::NoModifier;
        }
        else if(ke->key()==Qt::Key_Control)
        {
            if(modif!=Qt::ControlModifier) modif=Qt::ControlModifier;
            else modif=Qt::NoModifier;
        }
        else if(ke->key()==Qt::Key_Alt)
        {
            if(modif!=Qt::AltModifier) modif=Qt::AltModifier;
            else modif=Qt::NoModifier;
        }
        updateModifInfo();


//        qDebug() << toString(act);
        computeTotalSec();
    }
}
//-----------------------------------------------
void GameBot::updateModifInfo()
{
    QString result="Active modifier: ";

    if(modif==Qt::NoModifier) result+="None";
    else if(modif==Qt::AltModifier) result+="Alt";
    else if(modif==Qt::ControlModifier) result+="Ctrl";
    else if(modif==Qt::ShiftModifier) result+="Shift";

    modifs->setText(result);
}
//-----------------------------------------------
void GameBot::moveTo(const QPoint &targ)
{
    QCursor curs=cursor();
    QPoint position=cursorPosition;

            int incX = position.x()<targ.x() ? 1 : -1,
                incY = position.y()<targ.y() ? 1 : -1;

            while(position!=targ)
            {
                if(position.x() !=  targ.x())
                    position.setX( position.x()+incX );
                if(position.y() != targ.y())
                    position.setY( position.y()+incY );

                curs.setPos(QApplication::screens().first(), position);
                Sleep(1);
            }
}
//-----------------------------------------------
void GameBot::computeTotalSec()
{
    float floatSec=0;
    int size=program.size();
    for(int i=0; i<size; i++)
    {
        floatSec+=float(program.at(i).delay)*0.001;
    }
    totalSec=int(floatSec);
}
//-----------------------------------------------
void GameBot::loadFromFile(const QString &fileName)
{
    QFile file(fileName);

    if(file.open(QIODevice::ReadOnly))
    {
        systemConsole->append("Read from file " + fileName);
        program.clear();

        QString data=file.readAll();
        QStringList list=data.split("#");

        for(int i=0; i<list.size(); i++)
        {

            if(list.at(i).size()<10) continue;
//            qDebug() << QString::number(i);
//            qDebug() << list.at(i);

            Action act=fromString(list.at(i));
            program.push_back(act);
        }
    }

    systemConsole->append(
                QTime::currentTime().toString("hh:mm:ss")+" "+
                "Readed " + QString::number(program.size())+
                " actions"
                );
    slotSetStatus();
}
//-----------------------------------------------
void GameBot::pressModif(const Action& act)
{
    if(act.modifier==Qt::NoModifier) return;

    switch (act.modifier)
    {
    case Qt::ControlModifier: keybd_event(VK_CONTROL, 0x9d, 0, 0); break;
    case Qt::AltModifier: keybd_event(VK_SHIFT, 0xaa, 0, 0); break;
    case Qt::ShiftModifier: keybd_event(VK_MENU, 0xb8, 0, 0); break;
    }
    Sleep(50);

}
//-----------------------------------------------
void GameBot::releaseModif(const Action& act)
{
    if(act.modifier==Qt::NoModifier) return;

    switch (act.modifier)
    {
    case Qt::ControlModifier: keybd_event(VK_CONTROL, 0x9d, KEYEVENTF_KEYUP, 0); break;
    case Qt::AltModifier: keybd_event(VK_SHIFT, 0xaa, KEYEVENTF_KEYUP, 0); break;
    case Qt::ShiftModifier: keybd_event(VK_MENU, 0xb8, KEYEVENTF_KEYUP, 0); break;
    }
    Sleep(50);

}
//===============================================
// SLOTS
//-----------------------------------------------
void GameBot::slotStartRecord()
{
    totalSec=0;

    isRecord=true;
    program.clear();
    timer=0;
    systemConsole->append(
                "Start record"
                );

}
//-----------------------------------------------
void GameBot::slotStopRecord()
{
    isRecord=false;
    programTime=QTime(0,0).addSecs(totalSec);
    systemConsole->append(
                "Stop record\nProgram size: "+
                QString::number(program.size())
                );
    slotSetStatus();

}
//-----------------------------------------------
void GameBot::slotStartProgram()
{
    if(isRecord|| program.size()==0) return;




    systemConsole->append(
                "Start program "+
                QTime::currentTime().toString("hh:mm:ss")
                );
    repaint();

     isExec=true;
     curentAction=0;
     actionDelayTimer->singleShot(program.at(curentAction).delay, this, SLOT(slotExecuteAction()));

}
//-----------------------------------------------
void GameBot::slotSetStatus()
{
    lblClick->setText("Program size: " + QString::number(program.size())+
                      ", time: " + programTime.toString("hh:mm:ss"));
}
//-----------------------------------------------
void GameBot::slotSetX(int x)
{
    lblX->setText("X: " + QString::number(x));
}
//-----------------------------------------------
void GameBot::slotSetY(int y)
{
    lblY->setText("Y: " + QString::number(y));
}
//-----------------------------------------------
void GameBot::slotShowMouseState()
{
    slotSetX(cursorPosition.x());
    slotSetY(cursorPosition.y());
//    slotSetStatus();
}
//-----------------------------------------------
void GameBot::slotExecuteAction()
{
    const int del=50; // задержка после/перед действием
                      // клиент игр обычно подтормаживает пока сообразит что клавиша нажата

    if(isExec==false) return;

    Action act=program.at(curentAction);

    if(act.type==ACTION_MOVETO)
    {
        moveTo(act.target);
    }
    else if(act.type==ACTION_LEFTCLICK)
    {
        pressModif(act);
        moveTo(act.target);
        Sleep(del);
        mouse_event(MOUSEEVENTF_LEFTDOWN,
                    act.target.x(), act.target.y(), 0, 0);
        Sleep(del/2);
        mouse_event(MOUSEEVENTF_LEFTUP,
                    act.target.x(), act.target.y(), 0, 0);
        releaseModif(act);
    }
    else if(act.type==ACTION_RIGHTCLICK)
    {
        pressModif(act);
        moveTo(act.target);
        Sleep(del);
        mouse_event(MOUSEEVENTF_RIGHTDOWN,
                    act.target.x(), act.target.y(), 0, 0);
        Sleep(del/2);
        mouse_event(MOUSEEVENTF_RIGHTUP,
                    act.target.x(), act.target.y(), 0, 0);
        releaseModif(act);
    }
    else if(act.type==ACTION_DRAG)
    {
        moveTo(act.begin);
        Sleep(del);
        mouse_event(MOUSEEVENTF_LEFTDOWN,
                    act.begin.x(), act.begin.y(), 0, 0);
        Sleep(del/2);
        moveTo(act.target);
        Sleep(del);
        mouse_event(MOUSEEVENTF_LEFTUP,
                    act.target.x(), act.target.y(), 0, 0);
    }

    if(curentAction==program.size()-1)
    {
        curentAction=0;
        emit signalCycleEnd();
        systemConsole->append("Cycle end: "+ QTime::currentTime().toString("hh:mm:ss"));
    }
    else curentAction++;
    actionDelayTimer->singleShot(program.at(curentAction).delay, this, SLOT(slotExecuteAction()));



}
//-----------------------------------------------
void GameBot::slotSave()
{
    QString fileName=
            QFileDialog::getSaveFileName(
                this, "Save Program",
                QString(), "*.bt"
                );
    if(fileName.split('.').last()!="bt") fileName+=".bt";
    saveToFile(fileName);
}
//-----------------------------------------------
void GameBot::slotLoad()
{
    QString fileName=
            QFileDialog::getOpenFileName(
                this, "Load Program"
                );
    loadFromFile(fileName);
}
//===============================================

// Utilites
QTime operator-(const QTime& t1, const QTime& t2)
{
    QTime result;
    int
            h=t1.hour()-t2.hour(),
            m=t1.minute()-t2.minute(),
            s=t1.second()-t2.second(),
            ms=t1.msec()-t2.msec();
    result.setHMS(h,m,s,ms);
    return result;
}
//-----------------------------------------------
int toMsecs(const QTime& time)
{
    int ms= time.second()*1000 + time.msec();
    ms+=time.minute()*60*1000;

    return ms;
}
//-----------------------------------------------
QString createMessage(const Action& act)
{
    QString message;
    if(     act.type==ACTION_LEFTCLICK ||
            act.type==ACTION_RIGHTCLICK||
            act.type==ACTION_MOVETO||
            act.type==ACTION_DRAG
      )
    {
        message="Delay: "+QString::number(act.delay)
                +"ms\n"+
                "Action target x: "+
                QString::number(act.target.x())+
                " y: "+
                QString::number(act.target.y())+"\n";

        if(act.type==ACTION_DRAG)
        {
            message+="Action begin x: "+
                    QString::number(act.begin.x())+
                    " y: "+
                    QString::number(act.begin.y())+"\n"+
                    "Action type: Drag";
        }
        else if(act.type==ACTION_LEFTCLICK)
        {
            message+="Action type: Left Click";
        }
        else if(act.type==ACTION_RIGHTCLICK)
        {
            message+="Action type: Right Click";
        }
        else if(act.type==ACTION_MOVETO)
        {
            message+="Action type: Move to";
        }

    }
    else if(act.type==ACTION_PRESSKEY)
    {
        message="Key: " + act.text +
            "\nAction type: Press Key";
    }
    else if(act.type==ACTION_INPUTTEXT)
    {
        message="Text: " + act.text +
            "\nAction type: Input Text";
    }

    return message;
}


























