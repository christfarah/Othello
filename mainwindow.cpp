#include "mainwindow.h"

MainWindow* MainWindow::instance=nullptr;
MainWindow::MainWindow()
{
    QFrame *frame = new QFrame;
    QVBoxLayout *frameLayout = new QVBoxLayout(frame);
    playerTurn=new QLabel("Player: Black");
    frameLayout->addWidget(playerTurn);
    frameLayout->setAlignment(Qt::AlignCenter);

    QFrame *frame2 = new QFrame;
    QVBoxLayout *frameLayout2 = new QVBoxLayout(frame2);
    frameLayout2->addWidget(frame);
    QGraphicsView* view = new QGraphicsView();
    Game2Scene* scene2 = new Game2Scene();
    view->setFixedSize(Game2Scene::BOARD_LENGTH, Game2Scene::BOARD_LENGTH);
    view->setHorizontalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view->setVerticalScrollBarPolicy((Qt::ScrollBarAlwaysOff));
    view->setScene(scene2);
    view->show();
    frameLayout2->addWidget(view);
    frameLayout2->setAlignment(Qt::AlignCenter);
    setCentralWidget(frame2);
    setWindowTitle(tr("Othello"));

}

MainWindow* MainWindow::getInstance(){
    if (instance==nullptr){
        instance=new MainWindow();
    }
    return instance;
}

void MainWindow::changePlayer(){
    if (playerTurn->text()=="Player: Black"){
        playerTurn->setText("Player: White");
    }
    else {
        playerTurn->setText("Player: Black");
    }
}
