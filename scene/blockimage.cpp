#include "blockimage.h"

#include <QBrush>
#include <QPainter>

#include "globals.h"

BlockImage::BlockImage(const QColor& color) : QObject(), QGraphicsRectItem()
{
    m_baseColor = color;
    m_currentColor = color;
}

void BlockImage::setColor(const QColor& color)
{
    m_currentColor = color;
    update(boundingRect());
}

void BlockImage::resetColor()
{
    setColor(m_baseColor);
}

QRectF BlockImage::boundingRect() const
{
    return QRectF(0, 0, GRAPHICAL_SIZE, GRAPHICAL_SIZE);
}

QPainterPath BlockImage::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
};

void BlockImage::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->fillRect(boundingRect(), QBrush(m_currentColor));
}

void BlockImage::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event);

    emit clicked();
}
