#include "figureimage.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QDrag>
#include <QMimeData>

#include "globals.h"

FigureImage::FigureImage(const QString &imageName, QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent)
{
    setImageName(imageName);
}

void FigureImage::setImageName(const QString& imageName)
{
    m_pixmap = QPixmap(QStringLiteral(":/assets/%1.png").arg(imageName));
}

QRectF FigureImage::boundingRect() const
{
    return QRectF(0, 0, GRAPHICAL_SIZE, GRAPHICAL_SIZE);
}

QPainterPath FigureImage::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void FigureImage::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmap(boundingRect().toRect(), m_pixmap);
}

void FigureImage::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    Q_UNUSED(event);

    emit clicked();
}
