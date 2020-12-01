#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include "game2scene.h"

class MainWindow:public QMainWindow
{
public:
    static MainWindow* getInstance();
    QLabel *playerTurn;
    void changePlayer();

private:
    MainWindow();
    static MainWindow* instance;
};

#endif // MAINWINDOW_H
