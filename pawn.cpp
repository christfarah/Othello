#include "pawn.h"
#include "game2scene.h"

Pawn::Pawn(QObject *parent, PawnType type, int x, int y) : QObject(parent)
{
    int length = Game2Scene::BOARD_LENGTH/10;
    this->xPos = x;
    this->yPos = y;
    this->type=type;
    if (type == PawnType::BLACK){
        this->setPixmap((QPixmap(":/images/pion_noir.png")).scaled(length, length));
    } else {
        this->setPixmap((QPixmap(":/images/pion_blanc.png")).scaled(length, length));
    }
}

bool Pawn::isInMyBorder(Pawn *pawn){
    if(xPos == pawn->xPos && yPos == pawn->yPos){
        return false;
    }

    if((pawn->xPos <= xPos+1) && (pawn->xPos >= xPos-1) && (pawn->yPos <= yPos+1) && (pawn->yPos >= yPos-1)){
        return true;
    }

    return false;
}
