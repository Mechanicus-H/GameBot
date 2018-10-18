#include "gamebot.h"

GameBot::GameBot(QWidget *parent)
    : QWidget(parent)
{
    isRecord=false;
    isExec=false;
    startTimer(2);
    timer=0;

    resize(300, 75);
    setWindowFlags(Qt::WindowStaysOnTopHint);


    lblX=new QLabel;
    lblY=new QLabel;
    lblClick=new QLabel;
    winProgStatus=new QTextEdit;
    winProgStatus->setReadOnly(true);

    startRecord=new QPushButton("Start record");
    connect(startRecord, SIGNAL(clicked()), this, SLOT(slotStartRecord()));

    stopRecord=new QPushButton("Stop Record");
    connect(stopRecord, SIGNAL(clicked()), this, SLOT(slotStopRecord()));

    startProgram=new QPushButton("Start Program");
    connect(startProgram, SIGNAL(clicked()), this, SLOT(slotStartProgram()));

    QHBoxLayout *box=new QHBoxLayout;
    box->addWidget(lblX);
    box->addWidget(lblY);
    box->addWidget(lblClick);

    QVBoxLayout *Vbox=new QVBoxLayout;
    Vbox->addLayout(box);
    Vbox->addWidget(startRecord);
    Vbox->addWidget(stopRecord);
    Vbox->addWidget(startProgram);
    Vbox->addWidget(winProgStatus);

    setLayout(Vbox);

}

GameBot::~GameBot()
{

}
//-----------------------------------------------
void GameBot::slotSetClick(QTime time)
{
    lblClick->setText("Last click: "+ time.toString("hh:mm:ss:zzz"));
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
    slotSetClick(lastClick);
}
//-----------------------------------------------

//-----------------------------------------------
void GameBot::timerEvent(QTimerEvent *te)
{
    cursorPosition=cursor().pos();

    timer+=2;
    slotShowMouseState();



    QWidget::timerEvent(te);
}
//-----------------------------------------------
void GameBot::mouseMoveEvent(QMouseEvent *me)
{


    QWidget::mouseMoveEvent(me);
}
//-----------------------------------------------
void GameBot::keyPressEvent(QKeyEvent *ke)
{
    if(isRecord)
    {
        int ms= timer;
        timer=0;


        if(ke->key()==Qt::Key_K)
        {
            program.push_back(Action(act_type::wait, ms));
            program.push_back(Action(act_type::left_click, cursorPosition));

            winProgStatus->append(
                        "Wait: "+ QString::number(ms)+
                        "\nLeft click, x: "+QString::number(cursorPosition.x())
                        + ", y: " +QString::number(cursorPosition.y())
                        );
        }
        else if(ke->key()==Qt::Key_L)
        {
            program.push_back(Action(act_type::wait, ms));
            program.push_back(Action(act_type::right_click, cursorPosition));

            winProgStatus->append(
                        "Wait: "+ QString::number(ms)+
                        "\nRight click, x: "+QString::number(cursorPosition.x())
                        + ", y: " +QString::number(cursorPosition.y())
                        );

        }
        else if(ke->key()==Qt::Key_D)
        {
            program.push_back(Action(act_type::wait, ms));
            program.push_back(Action(act_type::drag, cursorPosition, QPoint(0,0)));

            winProgStatus->append(
                        "Wait: "+ QString::number(ms)+
                        "\nDrag start, x: "+QString::number(cursorPosition.x())
                        + ", y: " +QString::number(cursorPosition.y())
                        );
        }
        else if(ke->key()==Qt::Key_S)
        {
            program.last().setTarget(cursorPosition);

            winProgStatus->append(
                        "Drag stop, x: "+QString::number(cursorPosition.x())
                        + ", y: " +QString::number(cursorPosition.y())
                        );
        }
        else if(ke->key()==Qt::Key_E && ke->modifiers()==Qt::CTRL && isExec)
        {
            isExec=false;
            winProgStatus->append( "Program execution stop" );
        }

        lastClick=QTime::currentTime();
    }
}
//-----------------------------------------------

// SLOTS
//-----------------------------------------------
void GameBot::slotStartRecord()
{
    isRecord=true;
    program.clear();
    timer=0;
    winProgStatus->append(
                "Start record"
                );

}
//-----------------------------------------------
void GameBot::slotStopRecord()
{
    isRecord=false;
    winProgStatus->append(
                "Stop record\nProgram size: "+
                QString::number(program.size())
                );

}
//-----------------------------------------------
void GameBot::slotStartProgram()
{
//    if(isRecord) return;

    qDebug() << "Start";

    winProgStatus->append(
                "Start program "+
                QTime::currentTime().toString("hh:mm:ss")
                );

     isExec=true;
     const int size=program.size();
     while(isExec)
     {
         for(int i=0; i<size; i++)
             program[i].exec();
         if(!isExec) return;
     }
}

//-----------------------------------------------
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

int toMsecs(const QTime& time)
{
    int ms= time.second()*1000 + time.msec();
    ms+=time.minute()*60*1000;

    return ms;
}


























