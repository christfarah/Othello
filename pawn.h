#ifndef BLACKPAWN_H
#define BLACKPAWN_H

#include <QObject>
#include <QGraphicsPixmapItem>

enum PawnType {
    BLACK,
    WHITE
};

class Pawn: public QObject, public QGraphicsPixmapItem
{
public:
    PawnType type;
    int x;
    int y;
    explicit Pawn(QObject *parent = nullptr, PawnType type = PawnType::BLACK, int x = 0, int y = 0);

    void changeColor(PawnType type);
    bool isInMyBorder(Pawn* pawn);
};

#endif // BLACKPAWN_H
