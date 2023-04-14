#include "mainwindow.h"

#include <QHBoxLayout>

#include "globals.h"

MainWindow::MainWindow(QWidget* parent) : QWidget(parent)
{
    m_scene = new Scene;
    m_view = new View(m_scene);

    m_game = new Game;
    connect(m_game, &Game::figuresInitialized, m_scene, &Scene::addFigures);
    connect(m_game, &Game::blocksInitialized, m_scene, &Scene::addBlocks);

    connect(m_game, &Game::availableTurnsUpdateRequested,
            m_scene, &Scene::updateAvailableTurns);

    connect(m_game, &Game::availableTurnsClearRequested,
            m_scene, &Scene::clearAvailableTurns);

    connect(m_game, &Game::figurePositionUpdated,
            m_scene, &Scene::updateFigurePosition);

    m_game->sendMathDataToDisplay();

    connect(m_scene, &Scene::blockClicked, m_game, &Game::handleBlockClick);
    connect(m_scene, &Scene::figureClicked, m_game, &Game::handleFigureClick);

    const int boardSize = MATRIX_SIZE * GRAPHICAL_SIZE;
    m_view->setSceneRect(QRectF(0, 0, boardSize, boardSize));
    m_view->setMinimumSize(boardSize + 10, boardSize + 10);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(m_view);
}
