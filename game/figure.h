#ifndef FIGURE_H
#define FIGURE_H

enum class FigureType
{
    PAWN,
    ROOK,
    HORSE,
    ELEPHANT,
    KING,
    QUEEN,
};

enum class FigureSide
{
    WHITE,
    BLACK,
};

struct Figure
{
    Figure(FigureType type, FigureSide side, int x, int y)
    {
        this->type = type;
        this->side = side;
        this->x = x;
        this->y = y;
    }

    FigureType type;
    FigureSide side;
    int x;
    int y;
};

#endif // FIGURE_H
