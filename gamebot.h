#ifndef GAMEBOT_H
#define GAMEBOT_H

#include <QWidget>
#include <QtWidgets>

class GameBot : public QWidget
{
    Q_OBJECT
private:
    QPoint cursorPosition;
    QTime lastClick;
    QLabel *lblX;
    QLabel *lblY;
    QLabel *lblClick;

public:
    GameBot(QWidget *parent = 0);
    ~GameBot();

    void timerEvent(QTimerEvent *te);
    void focusOutEvent(QFocusEvent *fe);
    void mouseMoveEvent(QMouseEvent *me);

    void mousePressEvent(QMouseEvent *me)
    {

    }

public slots:
    void slotShowMouseState();
    void slotSetX(int x);
    void slotSetY(int y);
    void slotSetClick(QTime time);
};

#endif // GAMEBOT_H
