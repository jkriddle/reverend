#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QTime>
#include <QTimer>
#include "Engine.h"
#include "playertile.h"
#include "gamewindow.h"
#include <QDebug>

GameWindow::GameWindow()
{
    m_scene = new QGraphicsScene();

    //scene->setSceneRect(0, 0, Engine::getScreenWidth(), Engine::getScreenHeight());

    m_scene->setBackgroundBrush(Qt::black);

    // Grass
    int xTiles = Engine::getScreenWidth() / Engine::TILE_SIZE;
    int yTiles = Engine::getScreenHeight() / Engine::TILE_SIZE;

    QImage *grass = new QImage("D:\\Projects\\reverend\\grass.png");
    if(!grass->isNull()) {
       m_grassBrush = new QBrush(*grass);
   }

    for(int x = 0; x < xTiles; x++) {
        for(int y = 0; y < yTiles; y++) {
            QGraphicsRectItem *rect = new QGraphicsRectItem();
            rect->setRect(Engine::TILE_SIZE * x, Engine::TILE_SIZE * y, Engine::TILE_SIZE, Engine::TILE_SIZE);
            rect->setPen(Qt::NoPen);
            rect->setBrush(*m_grassBrush);
            m_scene->addItem(rect);
        }
    }

    // Player
    player = new PlayerTile();
    QImage *image = new QImage("D:\\Projects\\reverend\\player.png");
    if(!image->isNull()) {
       m_playerBrush = new QBrush(*image);
       player->setBrush(*m_playerBrush);
   }

    player->setRect(0, 0, Engine::TILE_SIZE, Engine::TILE_SIZE);
    player->setPen(Qt::NoPen);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    m_scene->addItem(player);

    QGraphicsView *view = new QGraphicsView(m_scene);
    // view->showFullScreen();
    // view.setDragMode(QGraphicsView::NoDrag);
    view->setRenderHint(QPainter::Antialiasing);
    //view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Reverend"));
    //view->setFixedSize(Engine::getScreenWidth(), Engine::getScreenHeight());
    view->show();

}


GameWindow::~GameWindow()
{

}

void GameWindow::draw() {

}


// Main Game Loop
void GameWindow::update() {

}


