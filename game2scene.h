#ifndef GAME2SCENE_H
#define GAME2SCENE_H
#include <QGraphicsScene>
#include <QPixmap>
#include <QtWidgets>
#include "pawn.h"
#include "mainwindow.h"




class Game2Scene: public QGraphicsScene
{
    Q_OBJECT
public:
    static int BOARD_LENGTH;

    PawnType player;
    Game2Scene();

    Pawn* pawns[8][8];

    QLabel* black_label;
    QLabel* white_label;

    QLabel* black_value;
    QLabel* white_value;


    QLabel* goodluck;

    QPushButton* pass;

    void addPawn(Pawn* pawn);
    void forceAddPawn(Pawn* pawn);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    QList<Pawn*>* getPawnsOfInterest(Pawn* pawn);
signals:

public slots:


};


#endif // GAME2SCENE_H
