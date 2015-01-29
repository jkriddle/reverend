#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QTime>
#include <QTimer>
#include "Engine.h"
#include "PlayerTile.h"
#include <QDebug>

void addGrass(QGraphicsScene *scene) {
    QBrush *brush;
    int xTiles = Engine::getScreenWidth() / Engine::TILE_SIZE;
    int yTiles = Engine::getScreenHeight() / Engine::TILE_SIZE;
    QImage *grass = new QImage("D:\\Projects\\reverend\\grass.png");

    if(!grass->isNull()) {
       brush = new QBrush(*grass);
   }

    for(int x = 0; x < xTiles; x++) {
        for(int y = 0; y < yTiles; y++) {
            QGraphicsRectItem *rect = new QGraphicsRectItem();
            rect->setRect(Engine::TILE_SIZE * x, Engine::TILE_SIZE * y, Engine::TILE_SIZE, Engine::TILE_SIZE);
            rect->setPen(Qt::NoPen);
            rect->setBrush(*brush);
            scene->addItem(rect);
        }
    }
}

void addPlayer(QGraphicsScene *scene) {

    PlayerTile *rect = new PlayerTile();
    QImage *image = new QImage("D:\\Projects\\reverend\\player.png");

    if(!image->isNull()) {
       QBrush *brush = new QBrush(*image);
       rect->setBrush(*brush);
   }

    rect->setRect(0, 0, Engine::TILE_SIZE, Engine::TILE_SIZE);
    rect->setPen(Qt::NoPen);
    rect->setFlag(QGraphicsItem::ItemIsFocusable);
    rect->setFocus();

    scene->addItem(rect);

}

void update(QGraphicsScene *scene) {
    qDebug() << "UPDATE";
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    QGraphicsScene *scene = new QGraphicsScene();
    //scene->setSceneRect(0, 0, Engine::getScreenWidth(), Engine::getScreenHeight());

    scene->setBackgroundBrush(Qt::black);

    addGrass(scene);
    addPlayer(scene);


    QGraphicsView *view = new QGraphicsView(scene);
    // view->showFullScreen();
    // view.setDragMode(QGraphicsView::NoDrag);
    //view->setRenderHint(QPainter::Antialiasing);
    //view->setCacheMode(QGraphicsView::CacheBackground);
    //view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    //view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Reverend"));

    //view->setFixedSize(Engine::getScreenWidth(), Engine::getScreenHeight());
    view->show();


    return app.exec();
}
