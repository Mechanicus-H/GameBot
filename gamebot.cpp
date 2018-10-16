#include "gamebot.h"

GameBot::GameBot(QWidget *parent)
    : QWidget(parent)
{
    startTimer(2);

    setFixedSize(200, 75);

    lblX=new QLabel;
    lblY=new QLabel;
    lblClick=new QLabel;


    QHBoxLayout *box=new QHBoxLayout;
    box->addWidget(lblX);
    box->addWidget(lblY);
    box->addWidget(lblClick);

    setLayout(box);

    Qt::WindowFlags flag=Qt::WindowStaysOnTopHint;
    setWindowFlags(flag);

}

GameBot::~GameBot()
{

}
//-----------------------------------------------
void GameBot::slotSetClick(QTime time)
{
    lblClick->setText("Last click: "+ time.toString("hh:mm:ss"));
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
}
//-----------------------------------------------
void GameBot::mouseMoveEvent(QMouseEvent *me)
{
    QWidget::mouseMoveEvent(me);
}
//-----------------------------------------------
























