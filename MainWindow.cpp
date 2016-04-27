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

    m_gameStateText = new QGraphicsSimpleTextItem();
    QFont s = m_gameStateText->font();
    s.setPixelSize(32);
    m_gameStateText->setFont(s);
    m_gameStateText->setZValue(2);

    m_scene = new QGraphicsScene();
    m_field = new Field();
    m_field->setSize(8, 8);
    m_field->setNumberOfMines(10);

    QGLFormat f = QGLFormat::defaultFormat();
    f.setSampleBuffers(true);
    f.setSamples(4);

    ui->graphicsView->setViewport(new QGLWidget(f));
    ui->graphicsView->setScene(m_scene);

    m_scene->addItem(m_gameStateText);

    for (int y = 0; y < m_field->height(); ++y) {
        for (int x = 0; x < m_field->width(); ++x) {
            m_scene->addItem(new CellItem(m_field->cellAt(x, y)));
        }
    }

    newGame();

    connect(m_field, SIGNAL(numberOfFlagsChanged(int)), this, SLOT(onFieldNumberOfFlagsChanged(int)));
    connect(m_field, SIGNAL(stateChanged(State)), this, SLOT(onFieldStateChanged()));

    m_field->generate(x(), y());
}

void MainWindow::newGame()
{
    m_field->prepare();
    m_scene->update();
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

void MainWindow::onFieldNumberOfFlagsChanged(int number)
{
    ui->minesLabel->setText(QString("%1/%2").arg(number).arg(m_field->numberOfMines()));
}

void MainWindow::on_actionNewGame_triggered()
{
    newGame();
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::onFieldStateChanged()
{
    if (m_field->state() == Field::StateEnded) {
        m_gameStateText->setText("Game over");
        m_gameStateText->setPos((m_scene->width() - m_gameStateText->boundingRect().width()) / 2,
                                (m_scene->height() - m_gameStateText->boundingRect().height()) / 2);
        m_gameStateText->setVisible(true);
    } else {
        m_gameStateText->setVisible(false);
    }
}
