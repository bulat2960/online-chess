#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>

class View : public QGraphicsView
{
    Q_OBJECT

public:
    View(QGraphicsScene* scene, QWidget* parent = nullptr);
};

#endif // VIEW_H
