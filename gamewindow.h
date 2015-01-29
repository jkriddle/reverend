#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QObject>
#include <QGraphicsScene>
#include "playertile.h"

class GameWindow : public QObject
{
    Q_OBJECT

private:
    QGraphicsScene *m_scene;
    QGraphicsView *m_view;
    QBrush *m_grassBrush;
    QBrush *m_playerBrush;
    PlayerTile *m_player;

public:
    GameWindow();
    ~GameWindow();
    void draw();

public slots:
    void update();

};

#endif // GAMEWINDOW_H
