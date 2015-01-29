#include "playertile.h"
#include "Engine.h"
#include <QKeyEvent>
#include <QDebug>

void PlayerTile::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_A) {
        setPos(x() - Engine::TILE_SIZE, y());
    } else if (event->key() == Qt::Key_D) {
        setPos(x() + Engine::TILE_SIZE, y());
    } else if (event->key() == Qt::Key_W) {
        setPos(x(), y() - Engine::TILE_SIZE);
    } else if (event->key() == Qt::Key_S) {
        setPos(x(), y() + Engine::TILE_SIZE);
    }else if (event->key() == Qt::Key_Escape) {
        Engine::stop();
    }
}
