#include "scene.h"

#include "globals.h"

Scene::Scene(QObject* parent) : QGraphicsScene(parent)
{
    m_types =
    {
        {FigureType::ROOK, "rook"},
        {FigureType::HORSE, "horse"},
        {FigureType::ELEPHANT, "bishop"},
        {FigureType::KING, "king"},
        {FigureType::QUEEN, "queen"},
        {FigureType::PAWN, "pawn"},
    };

    m_sides =
    {
        {FigureSide::BLACK, "black"},
        {FigureSide::WHITE, "white"},
    };
}

void Scene::addBlocks(const QList<Block*> blocks)
{
    for (const auto& block : blocks)
    {
        QColor color = ((block->x + block->y) % 2) == 0 ? Qt::gray : Qt::black;
        BlockImage* blockImage = new BlockImage(color);

        m_blocks.insert(block, blockImage);
        m_blocksReversed.insert(blockImage, block);

        int graphicalX = (block->x - 1) * GRAPHICAL_SIZE;
        int graphicalY = (MATRIX_SIZE - block->y) * GRAPHICAL_SIZE;
        blockImage->setPos(graphicalX, graphicalY);
        addItem(blockImage);

        connect(blockImage, &BlockImage::clicked, this, &Scene::handleBlockImageClick);
    }
}

void Scene::addFigures(const QList<Figure*> whiteFigures, const QList<Figure*> blackFigures)
{
    QList<Figure*> figures = whiteFigures + blackFigures;

    for (const auto& figure : figures)
    {
        FigureType type = figure->type;
        FigureSide side = figure->side;

        QString sideText = m_sides[side];
        QString typeText = m_types[type];
        QString imageName = QStringLiteral("%1-%2").arg(sideText).arg(typeText);

        FigureImage* figureImage = new FigureImage(imageName);

        m_figures.insert(figure, figureImage);
        m_figuresReversed.insert(figureImage, figure);

        int graphicalX = (figure->x - 1) * GRAPHICAL_SIZE;
        int graphicalY = (MATRIX_SIZE - figure->y) * GRAPHICAL_SIZE;
        figureImage->setPos(graphicalX, graphicalY);
        addItem(figureImage);

        connect(figureImage, &FigureImage::clicked, this, &Scene::handleFigureImageClick);
    }
}

void Scene::handleFigureImageClick()
{
    FigureImage* image = dynamic_cast<FigureImage*>(QObject::sender());
    Figure* figure = m_figuresReversed[image];

    emit figureClicked(figure);
}

void Scene::handleBlockImageClick()
{
    BlockImage* image = dynamic_cast<BlockImage*>(QObject::sender());
    Block* block = m_blocksReversed[image];

    emit blockClicked(block);
}

void Scene::updateAvailableTurns(const QList<Block*> blocks)
{
    for (const auto& block : blocks)
    {
        BlockImage* image = m_blocks[block];
        image->setColor(Qt::red);
    }
}

void Scene::clearAvailableTurns(const QList<Block*> blocks)
{
    for (const auto& block : blocks)
    {
        BlockImage* image = m_blocks[block];
        image->resetColor();
    }
}

void Scene::updateFigurePosition(Figure* figure)
{
    FigureImage* image = m_figures[figure];
    int graphicalX = (figure->x - 1) * GRAPHICAL_SIZE;
    int graphicalY = (MATRIX_SIZE - figure->y) * GRAPHICAL_SIZE;
    image->setPos(graphicalX, graphicalY);
}
