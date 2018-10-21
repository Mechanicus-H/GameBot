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
    QTime programTime;
    QTimer *actionDelayTimer;

    uint timer;

    QLabel *lblX;
    QLabel *lblY;
    QLabel *lblClick;
    QTextEdit *systemConsole;
    QPushButton *startRecord;
    QPushButton *stopRecord;
    QPushButton *startProgram;
    QPushButton *saveProgram;
    QPushButton *loadProgram;

    bool isRecord;
    bool isExec;

    int curentAction;

    int totalSec;

    QVector<Action> program;

public:
    GameBot(QWidget *parent = 0);
    virtual ~GameBot();

    void timerEvent(QTimerEvent *te);
    void keyPressEvent(QKeyEvent *ke);
    void moveTo(const QPoint& targ);
    void computeTotalSec();
    void saveToFile(const QString& fileName);
    void loadFromFile(const QString& fileName);

public slots:
    void slotShowMouseState();
    void slotSetX(int x);
    void slotSetY(int y);
    void slotSetStatus();
    void slotStartRecord();
    void slotStopRecord();
    void slotStartProgram();
    void slotExecuteAction();
    void slotSave();
    void slotLoad();

signals:
    void signalCycleEnd();

};

QTime operator-(const QTime& t1, const QTime& t2);
int toMsecs(const QTime& time);
QString createMessage(const Action& act);

#endif // GAMEBOT_H
