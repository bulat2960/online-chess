#ifndef GAME_H
#define GAME_H

#include <QList>
#include <QObject>
#include <QMap>

#include "figure.h"
#include "block.h"

class Game : public QObject
{
    Q_OBJECT
public:
    Game();

    void initFigures();
    void initBlocks();

    void sendMathDataToDisplay();

public slots:
    void handleBlockClick(Block* block);
    void handleFigureClick(Figure* figure);

signals:
    void figuresInitialized(const QList<Figure*> whiteFigures,
                            const QList<Figure*> blackFigures);

    void blocksInitialized(const QList<Block*> blocks);

    void availableTurnsClearRequested(const QList<Block*> blocks);
    void availableTurnsUpdateRequested(const QList<Block*> blocks);

    void figurePositionUpdated(Figure* figure);

private:
    QList<Figure*> m_blackFigures;
    QList<Figure*> m_whiteFigures;

    QMap<int, QList<Block*>> m_blockMatrix;

    QList<Figure*> initSide(int pawnsRow, int specialFiguresRow, FigureSide side);

    Figure* m_currentTurnFigure {nullptr};
    QList<Block*> m_availableTurns;

    void resetAvailableTurnsSelection();
    QList<Block*> getAvailableTurns(Figure* figure);

    QList<Block*> matrixToList();

    Block* getBlock(int x, int y);

    QList<Block*> checkDirection(Figure* figure, int addX, int addY);

    QList<Block*> checkTop(Figure* figure);
    QList<Block*> checkBottom(Figure* figure);
    QList<Block*> checkLeft(Figure* figure);
    QList<Block*> checkRight(Figure* figure);

    QList<Block*> checkTopLeft(Figure* figure);
    QList<Block*> checkTopRight(Figure* figure);
    QList<Block*> checkBottomLeft(Figure* figure);
    QList<Block*> checkBottomRight(Figure* figure);

    QList<Block*> reduceToCount(QList<Block*> blocks, int count);

};

#endif // GAME_H
