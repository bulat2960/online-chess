#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>

#include "blockimage.h"
#include "figureimage.h"
#include "game/figure.h"
#include "game/block.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT

public:
    Scene(QObject* parent = nullptr);

public slots:
    void addBlocks(const QList<Block*> blocks);
    void addFigures(const QList<Figure*> whiteFigures, const QList<Figure*> blackFigures);

    void updateAvailableTurns(const QList<Block*> blocks);
    void clearAvailableTurns(const QList<Block*> blocks);

    void updateFigurePosition(Figure* figure);

signals:
    void figureClicked(Figure* figure);
    void blockClicked(Block* block);

private:
    QMap<Block*, BlockImage*> m_blocks;
    QMap<BlockImage*, Block*> m_blocksReversed;

    QMap<Figure*, FigureImage*> m_figures;
    QMap<FigureImage*, Figure*> m_figuresReversed;

    QMap<FigureType, QString> m_types;
    QMap<FigureSide, QString> m_sides;

    void handleFigureImageClick();
    void handleBlockImageClick();
};

#endif // SCENE_H
