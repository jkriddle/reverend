#ifndef PLAYERTILE_H
#define PLAYERTILE_H

#include <QGraphicsItem>

class PlayerTile: public QGraphicsRectItem{
public:
    void keyPressEvent(QKeyEvent *event);
};

#endif // PLAYERTILE_H

