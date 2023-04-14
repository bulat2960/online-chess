#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

#include "scene/view.h"
#include "scene/scene.h"
#include "game/game.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);

private:
    View* m_view {nullptr};
    Scene* m_scene {nullptr};
    Game* m_game {nullptr};
};

#endif // MAINWINDOW_H
