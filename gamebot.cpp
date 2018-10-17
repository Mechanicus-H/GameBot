#include "gamebot.h"

GameBot::GameBot(QWidget *parent)
    : QWidget(parent)
{
    isRecord=false;
    startTimer(2);

    resize(300, 75);

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
void GameBot::focusOutEvent(QFocusEvent *fe)
{
    this->activateWindow();
    QWidget::focusOutEvent(fe);
}
//-----------------------------------------------
void GameBot::timerEvent(QTimerEvent *te)
{
    cursorPosition=cursor().pos();

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
    int ms=QTime::currentTime().msec()-lastClick.msec();
    if(ke->key()==Qt::Key_K)
    {
        program.push_back(Action(act_type::wait, ms));
        program.push_back(Action(act_type::left_click, cursorPosition));
    }
    else if(ke->key()==Qt::Key_L)
    {
        program.push_back(Action(act_type::wait, ms));
        program.push_back(Action(act_type::right_click, cursorPosition));
    }
    else if(ke->key()==Qt::Key_E && isRecord)
    {
        isRecord=false;
        winProgStatus->append(
                    "Program size: "+
                    QString::number(program.size())+
                    "\n"
                    );
    }

    lastClick=QTime::currentTime();
}
//-----------------------------------------------

// SLOTS
//-----------------------------------------------
void GameBot::slotStartRecord()
{
    winProgStatus->append(
                "Start record\n"
                );

}
//-----------------------------------------------
void GameBot::slotStopRecord()
{

}
//-----------------------------------------------
void GameBot::slotStartProgram()
{

}






















