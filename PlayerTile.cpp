#include "PlayerTile.h"
#include <QKeyEvent>

void PlayerTile::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_A) {
        setPos(x()-32, y());
    } else if (event->key() == Qt::Key_D) {
        setPos(x()+32, y());
    } else if (event->key() == Qt::Key_W) {
        setPos(x(), y()-32);
    } else if (event->key() == Qt::Key_S) {
        setPos(x(), y()+32);
    }
}
