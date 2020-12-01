#include <QtGui>
#include "game2scene.h"
#include <QDateTime>
#include <QThread>
#include <QSplashScreen>


class I : public QThread
{
public:
        static void sleep(unsigned long secs) {
                QThread::sleep(secs);
        }
};

int main(int argc, char *argv[])
{

//    Q_INIT_RESOURCE(qrollit);

    QApplication app(argc, argv);
    QPixmap pixmap(":/images/ot.png");
    QSplashScreen splash(pixmap);

    splash.show();
    QGraphicsView* view = new QGraphicsView();
    Game2Scene* scene2 = new Game2Scene();
    view->setFixedSize(Game2Scene::BOARD_LENGTH, Game2Scene::BOARD_LENGTH);
    view->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view->setScene(scene2);
    I::sleep(2);
    view->show();

    splash.finish(view);
    return app.exec();
}

