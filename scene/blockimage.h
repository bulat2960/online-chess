#ifndef BLOCKIMAGE_H
#define BLOCKIMAGE_H

#include <QObject>
#include <QGraphicsRectItem>

class BlockImage : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    BlockImage(const QColor& color);

    void setColor(const QColor& color);
    void resetColor();

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

signals:
    void clicked();

private:
    QColor m_currentColor;
    QColor m_baseColor;
};

#endif // BLOCKIMAGE_H
