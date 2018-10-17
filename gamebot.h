#ifndef GAMEBOT_H
#define GAMEBOT_H

#include <QWidget>
#include <QtWidgets>
#include "action.h"

class GameBot : public QWidget
{
    Q_OBJECT
private:
    QPoint cursorPosition;
    QTime lastClick;

    QLabel *lblX;
    QLabel *lblY;
    QLabel *lblClick;
    QTextEdit *winProgStatus;
    QPushButton *startRecord;
    QPushButton *stopRecord;
    QPushButton *startProgram;

    bool isRecord;
    QVector<Action> program;

public:
    GameBot(QWidget *parent = 0);
    ~GameBot();

    void timerEvent(QTimerEvent *te);
    void focusOutEvent(QFocusEvent *fe);
    void mouseMoveEvent(QMouseEvent *me);
    void keyPressEvent(QKeyEvent *ke);
public slots:
    void slotShowMouseState();
    void slotSetX(int x);
    void slotSetY(int y);
    void slotSetClick(QTime time);
    void slotStartRecord();
    void slotStopRecord();
    void slotStartProgram();
};

#endif // GAMEBOT_H
