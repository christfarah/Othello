#include "pawn.h"
#include "game2scene.h"

Pawn::Pawn(QObject *parent, PawnType type, int x, int y) : QObject(parent)
{
    int length = Game2Scene::BOARD_LENGTH/10;
    this->x = x;
    this->y = y;
    this->type=type;
    if (type == PawnType::BLACK){
        this->setPixmap((QPixmap(":/images/pion_noir.png")).scaled(length, length));
    } else {
        this->setPixmap((QPixmap(":/images/pion_blanc.png")).scaled(length, length));
    }
}

bool Pawn::isInMyBorder(Pawn *pawn){
    if(x == pawn->x && y == pawn->y){
        return false;
    }

    if((pawn->x <= x+1) && (pawn->x >= x-1) && (pawn->y <= y+1) && (pawn->y >= y-1)){
        return true;
    }

    return false;
}
