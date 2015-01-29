#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include "PlayerTile.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene *scene = new QGraphicsScene();
    scene->setBackgroundBrush(Qt::black);
    PlayerTile *rect = new PlayerTile();

    QImage *image = new QImage("D:\\Projects\\CPP\\Game\\Survive\\player.png");

    if(!image->isNull()) {
       QBrush *brush = new QBrush(*image);
       rect->setBrush(*brush);
   }

    rect->setRect(0, 0, 32, 32);
    rect->setFlag(QGraphicsItem::ItemIsFocusable);
    rect->setFocus();

    scene->addItem(rect);
    QGraphicsView *view = new QGraphicsView(scene);
   // view->showFullScreen();
    view->show();
    return a.exec();
}
