#ifndef GAMEBOT_H
#define GAMEBOT_H

#include <QWidget>

class GameBot : public QWidget
{
    Q_OBJECT

public:
    GameBot(QWidget *parent = 0);
    ~GameBot();
};

#endif // GAMEBOT_H
