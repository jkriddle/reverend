#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QTime>
#include <QTimer>
#include "Engine.h"
#include "playertile.h"
#include <QDebug>
#include "gamewindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    GameWindow *window = new GameWindow();

    // Game Loop
    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), window, SLOT(update()));
    timer.start(1000 / 33);

    return app.exec();
}
