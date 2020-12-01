#include "game2scene.h"
#include <QtGui>
#include <stdlib.h>
#include <QMessageBox>
#include <QLineEdit>
#include <QInputDialog>


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

    while(player2.isNull() || player2.isEmpty()){
        player2 = QInputDialog::getText(0, tr("QInputDialog::getText()"),
                                        tr("User name:"), QLineEdit::Normal,
                                        QDir::home().dirName());
    }
}

void Game2Scene::forceAddPawn(Pawn *pawn){
    int xPosition = pawn->xPos * 80;
    int yPosition = pawn->yPos * 80;

    xPosition += ((Game2Scene::BOARD_LENGTH/8) - (Game2Scene::BOARD_LENGTH/10))/2;
    yPosition += ((Game2Scene::BOARD_LENGTH/8) - (Game2Scene::BOARD_LENGTH/10))/2;
    pawn->setPos(xPosition,yPosition);
    this->addItem(pawn);
    pawns[pawn->xPos][pawn->yPos]=pawn;
}

void Game2Scene::addPawn(Pawn *pawn){

    if (pawns[pawn->xPos][pawn->yPos] == nullptr){

        int xPosition = pawn->xPos * 80;
        int yPosition = pawn->yPos * 80;

        xPosition += ((Game2Scene::BOARD_LENGTH/8) - (Game2Scene::BOARD_LENGTH/10))/2;
        yPosition += ((Game2Scene::BOARD_LENGTH/8) - (Game2Scene::BOARD_LENGTH/10))/2;

        QList<Pawn*>* pawnsOfInterest = getPawnsOfInterest(pawn);
        bool didChangeColor=false;
        for (int i=0;i<pawnsOfInterest->size();i++){
            Pawn *pawnOfInterest= pawnsOfInterest->at(i);
            int xInc=0;
            int yInc=0;
            if (pawnOfInterest->yPos>pawn->yPos){
                yInc=+1;
            }
            if (pawnOfInterest->yPos<pawn->yPos){
                yInc=-1;
            }
            if (pawnOfInterest->xPos>pawn->xPos){
                xInc=+1;
            }
            if (pawnOfInterest->xPos<pawn->xPos){
                xInc=-1;
            }

           QList<Pawn *> *pawnLine=new QList<Pawn*>();
           int xPawnLine=pawnOfInterest->xPos;
           int yPawnLine=pawnOfInterest->yPos;
           while ((xPawnLine>=0 && xPawnLine<=7) && (yPawnLine>=0 && yPawnLine<=7) && (pawns[xPawnLine][yPawnLine]!=nullptr) && (pawns[xPawnLine][yPawnLine]->type==pawnOfInterest->type)){
                pawnLine->append(pawns[xPawnLine][yPawnLine]);
                xPawnLine+=xInc;
                yPawnLine+=yInc;
           }
           if(!((xPawnLine>=0 && xPawnLine<=7) && (yPawnLine>=0 && yPawnLine<=7) && (pawns[xPawnLine][yPawnLine]!=nullptr) && (pawns[xPawnLine][yPawnLine]->type==player))){
                pawnLine=new QList<Pawn*>();
           }

           for(int i=0;i<pawnLine->size();i++){
               Pawn *newPawn=new Pawn(nullptr,player,pawnLine->at(i)->xPos,pawnLine->at(i)->yPos);
               forceAddPawn(newPawn);
               delete pawnLine->at(i);
               didChangeColor=true;
           }
        }

        if (didChangeColor){
            forceAddPawn(pawn);
            changePlayer();
            if(gameIsFull()){
                calculateScore();
                if (blackScore > whiteScore){
                    QMessageBox::information(0,"Game Ended", "Black won with score: " + QString::number(blackScore));
                } else if (blackScore < whiteScore){
                    QMessageBox::information(0,"Game Ended", "White won with score: " + QString::number(whiteScore));
                } else {
                     QMessageBox::information(0,"Game Ended", "Tie with score: " + QString::number(whiteScore));
                }
            } else if (!playerHasMoves()){
                changePlayer();
                if(!playerHasMoves()){
                    calculateScore();
                    if (blackScore > whiteScore){
                        QMessageBox::information(0,"Game Ended", "Black won with score: " + QString::number(blackScore));
                    } else if (blackScore < whiteScore){
                        QMessageBox::information(0,"Game Ended", "White won with score: " + QString::number(whiteScore));
                    } else {
                         QMessageBox::information(0,"Game Ended", "Tie with score: " + QString::number(whiteScore));
                    }
                }
            }
        }
    }
}

void Game2Scene::changePlayer(){
    if (player==PawnType::BLACK){
        player=PawnType::WHITE;
    }
    else {
        player=PawnType::BLACK;
    }
    MainWindow::getInstance()->changePlayer();
}

void Game2Scene::calculateScore(){
    whiteScore=0;
    blackScore=0;
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            if (pawns[i][j] != nullptr){
                if(pawns[i][j]->type == PawnType::WHITE){
                    whiteScore++;
                } else if (pawns[i][j]->type == PawnType::BLACK){
                    blackScore++;
                }
            }
        }
    }
}

bool Game2Scene::gameIsFull(){
    QList<Pawn*>* emptyPawns = new QList<Pawn*>();
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            if (pawns[i][j] == nullptr){
                emptyPawns->append(pawns[i][j]);
            }
        }
    }

    if(emptyPawns->size() == 0){
        return true;
    } else {
        return false;
    }
}


bool Game2Scene::playerHasMoves(){
    QList<Pawn*>* emptyPawns = new QList<Pawn*>();
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            if (pawns[i][j] == nullptr){
                emptyPawns->append(new Pawn(nullptr,player,i,j));
            }
        }
    }

    for(int i=0; i<emptyPawns->size(); i++){
        Pawn* pawn = emptyPawns->at(i);
        QList<Pawn*>* pawnsOfInterest = getPawnsOfInterest(pawn);
        for (int i=0;i<pawnsOfInterest->size();i++){
            Pawn *pawnOfInterest= pawnsOfInterest->at(i);
            int xInc=0;
            int yInc=0;
            if (pawnOfInterest->yPos>pawn->yPos){
                yInc=+1;
            }
            if (pawnOfInterest->yPos<pawn->yPos){
                yInc=-1;
            }
            if (pawnOfInterest->xPos>pawn->xPos){
                xInc=+1;
            }
            if (pawnOfInterest->xPos<pawn->xPos){
                xInc=-1;
            }

           QList<Pawn *> *pawnLine=new QList<Pawn*>();
           int xPawnLine=pawnOfInterest->xPos;
           int yPawnLine=pawnOfInterest->yPos;
           while ((xPawnLine>=0 && xPawnLine<=7) && (yPawnLine>=0 && yPawnLine<=7) && (pawns[xPawnLine][yPawnLine]!=nullptr) && (pawns[xPawnLine][yPawnLine]->type==pawnOfInterest->type)){
                pawnLine->append(pawns[xPawnLine][yPawnLine]);
                xPawnLine+=xInc;
                yPawnLine+=yInc;
           }
           if(!((xPawnLine>=0 && xPawnLine<=7) && (yPawnLine>=0 && yPawnLine<=7) && (pawns[xPawnLine][yPawnLine]!=nullptr) && (pawns[xPawnLine][yPawnLine]->type==player))){
                pawnLine=new QList<Pawn*>();
           }

           if(pawnLine->size()>0){
               return true;
           }
        }
    }
    return false;
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
