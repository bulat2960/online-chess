#include "view.h"

View::View(QGraphicsScene* scene, QWidget* parent) : QGraphicsView(scene, parent)
{
    setScene(scene);

    setMouseTracking(true);

    setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
}
