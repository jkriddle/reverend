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
    m_player = new PlayerTile();
    QImage *image = new QImage("D:\\Projects\\reverend\\player.png");
    if(!image->isNull()) {
       m_playerBrush = new QBrush(*image);
       m_player->setBrush(*m_playerBrush);
   }

    m_player->setRect(0, 0, Engine::TILE_SIZE, Engine::TILE_SIZE);
    m_player->setPen(Qt::NoPen);
    m_player->setFlag(QGraphicsItem::ItemIsFocusable);
    m_player->setFocus();
    m_player->setPos(Engine::getScreenWidth() / 2 - m_player->rect().width(), Engine::getScreenHeight() / 2 - m_player->rect().height());
    m_scene->addItem(m_player);

    m_view = new QGraphicsView(m_scene);
    m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_view->setRenderHint(QPainter::Antialiasing);
    m_view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    m_view->setWindowTitle(QT_TRANSLATE_NOOP(QGraphicsView, "Reverend"));
    //view->setCacheMode(QGraphicsView::CacheBackground);
    m_view->setFixedSize(Engine::getScreenWidth(), Engine::getScreenHeight());
    m_view->setSceneRect(0, 0, Engine::getScreenWidth(), Engine::getScreenHeight());
    //view->showFullScreen();
    //view.setDragMode(QGraphicsView::NoDrag);
    m_view->show();

}


GameWindow::~GameWindow()
{

}

void GameWindow::draw() {

}

// Main Game Loop
void GameWindow::update() {
    int x = m_player->x() / 2;
    int y = m_player->y() / 2;
    int w = m_scene->width();
    int h = m_scene->height();
    m_scene->setSceneRect(x, y, w, h);
}

