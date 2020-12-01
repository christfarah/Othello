#include "game2scene.h"
#include <QtGui>
#include <stdlib.h>
#include <QMessageBox>


Game2Scene::Game2Scene()
{
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            pawns[i][j] = nullptr;
        }
    }

    player=PawnType::BLACK;
    this->setBackgroundBrush(QBrush(QImage(":/images/checker.png").scaledToHeight(BOARD_LENGTH).scaledToWidth(BOARD_LENGTH)));
    this->setSceneRect(0,0,BOARD_LENGTH,BOARD_LENGTH);

    Pawn* blackPawn1 = new Pawn(nullptr, PawnType::BLACK, 3,3);
    this->forceAddPawn(blackPawn1);

    Pawn* whitePawn1 = new Pawn(nullptr, PawnType::WHITE, 3,4);
    this->forceAddPawn(whitePawn1);

    Pawn* blackPawn2 = new Pawn(nullptr, PawnType::BLACK, 4,4);
    this->forceAddPawn(blackPawn2);

    Pawn* whitePawn2 = new Pawn(nullptr, PawnType::WHITE, 4,3);
    this->forceAddPawn(whitePawn2);
}

void Game2Scene::forceAddPawn(Pawn *pawn){
    int xPosition = pawn->x * 80;
    int yPosition = pawn->y * 80;

    xPosition += ((Game2Scene::BOARD_LENGTH/8) - (Game2Scene::BOARD_LENGTH/10))/2;
    yPosition += ((Game2Scene::BOARD_LENGTH/8) - (Game2Scene::BOARD_LENGTH/10))/2;
    pawn->setPos(xPosition,yPosition);
    this->addItem(pawn);
    pawns[pawn->x][pawn->y]=pawn;
}

void Game2Scene::addPawn(Pawn *pawn){

    if (pawns[pawn->x][pawn->y] == nullptr){

        int xPosition = pawn->x * 80;
        int yPosition = pawn->y * 80;

        xPosition += ((Game2Scene::BOARD_LENGTH/8) - (Game2Scene::BOARD_LENGTH/10))/2;
        yPosition += ((Game2Scene::BOARD_LENGTH/8) - (Game2Scene::BOARD_LENGTH/10))/2;

        QList<Pawn*>* pawnsOfInterest = getPawnsOfInterest(pawn);

    }
}

QList<Pawn*>* Game2Scene::getPawnsOfInterest(Pawn *pawn){
    QList<Pawn*>* pawnsOfInterest = new QList<Pawn*>();
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            if((pawns[i][j] != nullptr) && (pawns[i][j]->type!=player) && (pawn->isInMyBorder(pawns[i][j]))){
                pawnsOfInterest->append(pawns[i][j]);
            }
        }
    }
    return pawnsOfInterest;
}

void Game2Scene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    int x = event->scenePos().x()/80;
    int y = event->scenePos().y()/80;

    Pawn* pawn = new Pawn(nullptr, player, x, y);
    this->addPawn(pawn);
}

int Game2Scene::BOARD_LENGTH = 640;
