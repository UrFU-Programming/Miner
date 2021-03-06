#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include "Field.hpp"

#include "CellItem.hpp"

#include <QGLWidget>
#include <QGraphicsScene>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_scene = new QGraphicsScene();
    m_field = new Field();
    m_field->setSize(8, 8);
    m_field->setNumberOfMines(10);

    ui->graphicsView->setScene(m_scene);
    ui->graphicsView->setViewport(new QGLWidget());

    for (int y = 0; y < m_field->height(); ++y) {
        for (int x = 0; x < m_field->width(); ++x) {
            m_scene->addItem(new CellItem(m_field->cellAt(x, y)));
        }
    }

    m_field->generate();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QTimer::singleShot(0, this, SLOT(updateSceneScale()));
}

void MainWindow::updateSceneScale()
{
    ui->graphicsView->fitInView(m_scene->sceneRect(), Qt::KeepAspectRatio);
}
