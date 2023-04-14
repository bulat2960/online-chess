#ifndef FIGUREIMAGE_H
#define FIGUREIMAGE_H

#include <QObject>
#include <QGraphicsPixmapItem>

class FigureImage : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    FigureImage(const QString& imageName, QGraphicsItem* parent = nullptr);

    void setImageName(const QString& imageName);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

signals:
    void clicked();

private:
    QPixmap m_pixmap;
};

#endif // FIGUREIMAGE_H
