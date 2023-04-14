#include "game.h"

#include "globals.h"

Game::Game()
{
    initBlocks();
    initFigures();
}

void Game::sendMathDataToDisplay()
{
    emit blocksInitialized(matrixToList());
    emit figuresInitialized(m_whiteFigures, m_blackFigures);
}

void Game::initFigures()
{
    m_whiteFigures = initSide(2, 1, FigureSide::WHITE);
    m_blackFigures = initSide(7, 8, FigureSide::BLACK);
}

void Game::initBlocks()
{
    for (int y = 1; y <= MATRIX_SIZE; y++)
    {
        QList<Block*> blocks;
        for (int x = 1; x <= MATRIX_SIZE; x++)
        {
            Block* block = new Block(x, y);
            blocks.append(block);
        }
        m_blockMatrix.insert(y, blocks);
    }

    // Here is the corresponding init:
    // (1,1) (1,2) (1,3) (1,4) ....
    // (2,1) (2,2) (2,3) (2,4) ....
    // (3,1) (3,2) (3,3) (3,4) ....
    // (4,1) (4,2) (4,3) (4,4) ....

    // i - row
    // j - column
    // So m_blocksMatrix[i][j] returns Block(i + 1, j + 1)
}

#include <QDebug>

QList<Figure*> Game::initSide(int pawnsRow, int specialFiguresRow, FigureSide side)
{
    const QList<FigureType> figureTypesList = {
        FigureType::ROOK,
        FigureType::HORSE,
        FigureType::ELEPHANT,
        FigureType::KING,
        FigureType::QUEEN,
        FigureType::ELEPHANT,
        FigureType::HORSE,
        FigureType::ROOK,
    };

    QList<Figure*> figures;

    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        FigureType figureType = figureTypesList[i];
        Figure* specialFigure = new Figure(figureType, side, i + 1, specialFiguresRow);
        Figure* pawn = new Figure(FigureType::PAWN, side, i + 1, pawnsRow);

        figures.append(specialFigure);
        figures.append(pawn);

        m_blockMatrix[pawnsRow][i]->figure = pawn;
        m_blockMatrix[specialFiguresRow][i]->figure = specialFigure;
    }

    return figures;
}

void Game::handleBlockClick(Block* block)
{
    if (not m_availableTurns.contains(block))
    {
        resetAvailableTurnsSelection();
        return;
    }

    Block* moveFromBlock = getBlock(m_currentTurnFigure->x, m_currentTurnFigure->y);
    moveFromBlock->figure = nullptr;
    block->figure = m_currentTurnFigure;

    m_currentTurnFigure->x = block->x;
    m_currentTurnFigure->y = block->y;

    emit figurePositionUpdated(m_currentTurnFigure);

    resetAvailableTurnsSelection();
}

void Game::handleFigureClick(Figure* figure)
{
    resetAvailableTurnsSelection();

    m_currentTurnFigure = figure;
    m_availableTurns = getAvailableTurns(figure);
    emit availableTurnsUpdateRequested(m_availableTurns);
}

void Game::resetAvailableTurnsSelection()
{
    emit availableTurnsClearRequested(m_availableTurns);
    m_availableTurns.clear();
}

QList<Block*> Game::getAvailableTurns(Figure* figure)
{
    QList<Block*> blocks;

    QMap<QString, QList<Block*>> turnsByDirection =
    {
        {"TOP", checkTop(figure)},
        {"BOTTOM", checkBottom(figure)},
        {"LEFT", checkLeft(figure)},
        {"RIGHT", checkRight(figure)},
        {"TOPLEFT", checkTopLeft(figure)},
        {"TOPRIGHT", checkTopRight(figure)},
        {"BOTTOMLEFT", checkBottomLeft(figure)},
        {"BOTTOMRIGHT", checkBottomRight(figure)},
    };

    if (figure->type == FigureType::PAWN)
    {
        bool isWhite = (figure->side == FigureSide::WHITE);
        QString direction = isWhite ? "TOP" : "BOTTOM";
        QList<Block*> result = turnsByDirection[direction];

        bool isWhiteBeginningPawn = figure->y == 2 and figure->side == FigureSide::WHITE;
        bool isBlackBeginningPawn = figure->y == 7 and figure->side == FigureSide::BLACK;
        bool isBeginningPawn = isWhiteBeginningPawn or isBlackBeginningPawn;

        int figuresLeft = isBeginningPawn ? 2 : 1;
        blocks = reduceToCount(result, figuresLeft);
    }
    else if (figure->type == FigureType::ROOK)
    {
        QStringList directions = {"TOP", "BOTTOM", "LEFT", "RIGHT"};

        for (const auto& direction : directions)
        {
            blocks += turnsByDirection[direction];
        }
    }
    else if (figure->type == FigureType::ELEPHANT)
    {
        QStringList directions = {"TOPLEFT", "TOPRIGHT", "BOTTOMLEFT", "BOTTOMRIGHT"};

        for (const auto& direction : directions)
        {
            blocks += turnsByDirection[direction];
        }
    }
    else if (figure->type == FigureType::KING or figure->type == FigureType::QUEEN)
    {
        QStringList directions = turnsByDirection.keys();

        for (const auto& direction : directions)
        {
            QList<Block*> directionBlocks = turnsByDirection[direction];
            if (figure->type == FigureType::QUEEN)
            {
                directionBlocks = reduceToCount(directionBlocks, 1);
            }
            blocks += directionBlocks;
        }
    }

    return blocks;
}

QList<Block*> Game::matrixToList()
{
    QList<Block*> result;

    for (const auto& key : m_blockMatrix.keys())
    {
        result.append(m_blockMatrix[key]);
    }

    return result;
}

Block* Game::getBlock(int x, int y)
{
    if (x < 1 or x > 8)
    {
        return nullptr;
    }

    if (y < 1 or y > 8)
    {
        return nullptr;
    }

    return m_blockMatrix[y][x - 1];
}

QList<Block*> Game::checkDirection(Figure* figure, int addX, int addY)
{
    int currentX = figure->x + addX;
    int currentY = figure->y + addY;

    FigureSide side = figure->side;

    QList<Block*> blocks;

    while (true)
    {
        Block* block = getBlock(currentX, currentY);

        if (not block)
        {
            break;
        }

        Figure* blockFigure = block->figure;

        if (not blockFigure)
        {
            blocks.append(block);
        }
        else
        {
            FigureSide blockFigureSide = blockFigure->side;

            if (blockFigureSide != side)
            {
                blocks.append(block);
            }

            break;
        }

        currentX += addX;
        currentY += addY;
    }

    return blocks;
}

QList<Block*> Game::checkTop(Figure* figure)
{
    return checkDirection(figure, 0, 1);
}

QList<Block*> Game::checkBottom(Figure* figure)
{
    return checkDirection(figure, 0, -1);
}

QList<Block*> Game::checkLeft(Figure* figure)
{
    return checkDirection(figure, -1, 0);
}

QList<Block*> Game::checkRight(Figure* figure)
{
    return checkDirection(figure, 1, 0);
}

QList<Block*> Game::checkTopLeft(Figure* figure)
{
    return checkDirection(figure, -1, 1);
}

QList<Block*> Game::checkTopRight(Figure* figure)
{
    return checkDirection(figure, 1, 1);
}

QList<Block*> Game::checkBottomLeft(Figure* figure)
{
    return checkDirection(figure, -1, -1);
}

QList<Block*> Game::checkBottomRight(Figure* figure)
{
    return checkDirection(figure, 1, -1);
}

QList<Block*> Game::reduceToCount(QList<Block*> blocks, int count)
{
    QList<Block*> result;

    while (not blocks.isEmpty() and count != 0)
    {
        result.append(blocks.takeFirst());
        count--;
    }

    return result;
}
