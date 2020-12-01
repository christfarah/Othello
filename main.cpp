#include <QtGui>
#include "game2scene.h"
#include "mainwindow.h"
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

    QApplication app(argc, argv);
    QPixmap pixmap(":/images/ot.png");
    QSplashScreen splash(pixmap);
    QMainWindow *view=MainWindow::getInstance();
    splash.show();
    I::sleep(2);
    view->show();
    splash.finish(view);
    return app.exec();
}

