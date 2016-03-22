#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include "Field.hpp"

#include "CellItem.hpp"

#include <QGLWidget>
#include <QGraphicsScene>
#include <QTimer>

static const int fieldBorderWidth = CellItem::cellSize / 2;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_scene = new QGraphicsScene();
    m_fieldItem = new QGraphicsRectItem();
    m_fieldItem->setPen(QPen(Qt::black, CellItem::cellSize / 8));

    m_gameStateText = new QGraphicsSimpleTextItem();
    m_gameStateText->setZValue(2);
    QFont font = m_gameStateText->font();
    font.setPixelSize(32);
    m_gameStateText->setFont(font);
    m_gameStateRect = new QGraphicsRectItem();
    m_gameStateRect->setZValue(1);
    m_gameStateRect->setOpacity(0.7);
    m_gameStateRect->setBrush(Qt::lightGray);

    m_scene->addItem(m_gameStateText);
    m_scene->addItem(m_gameStateRect);

    m_field = new Field();

    connect(m_field, SIGNAL(numberOfFlagsChanged(int)), this, SLOT(onFieldNumberOfFlagsChanged(int)));
    connect(m_field, SIGNAL(stateChanged()), this, SLOT(onFieldStateChanged()));

    QGLFormat f = QGLFormat::defaultFormat();
    f.setSampleBuffers(false);
    f.setSamples(4);

    ui->graphicsView->setViewport(new QGLWidget(f));
    ui->graphicsView->setScene(m_scene);

    resizeField(8, 8);
    m_field->setNumberOfMines(10);

    m_scene->addItem(m_fieldItem);

    newGame();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::newGame()
{
    m_field->prepare();
    m_scene->update();
}

void MainWindow::resizeField(int width, int height)
{
    for (QGraphicsItem *cell : m_fieldItem->childItems()) {
        delete cell;
    }

    m_field->setSize(width, height);
    m_fieldItem->setRect(0, 0,
                         width * CellItem::cellSize + fieldBorderWidth * 2,
                         height * CellItem::cellSize + fieldBorderWidth * 2);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            CellItem *newItem = new CellItem(m_field->cellAt(x, y), m_fieldItem);
            newItem->setPos(x * CellItem::cellSize + fieldBorderWidth,
                            y * CellItem::cellSize + fieldBorderWidth);
        }
    }
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

void MainWindow::onFieldStateChanged()
{
    if (m_field->state() == Field::StateEnded) {
        m_gameStateText->setText("Game over");
        m_gameStateText->setPos((m_fieldItem->boundingRect().width() - m_gameStateText->boundingRect().width()) / 2,
                               (m_fieldItem->boundingRect().height() - m_gameStateText->boundingRect().height()) / 2);

        int rectHeight = m_fieldItem->boundingRect().height() * 0.3;

        m_gameStateRect->setRect(0, (m_fieldItem->boundingRect().height() - rectHeight) / 2, m_field->width() * CellItem::cellSize + fieldBorderWidth * 2, rectHeight);
        m_gameStateText->setVisible(true);
        m_gameStateRect->setVisible(true);
    } else {
        m_gameStateText->setVisible(false);
        m_gameStateRect->setVisible(false);
    }
}

void MainWindow::on_action_NewGame_triggered()
{
    newGame();
}

void MainWindow::on_actionDifficultyNovice_triggered()
{
    resizeField(8, 8);
    m_field->setNumberOfMines(10);
    newGame();
    updateSceneScale();
}

void MainWindow::on_actionDifficultyIntermediate_triggered()
{
    resizeField(16, 16);
    m_field->setNumberOfMines(40);
    newGame();
    updateSceneScale();
}

void MainWindow::on_actionDifficultyExpert_triggered()
{
    resizeField(16, 30);
    m_field->setNumberOfMines(99);
    newGame();
    updateSceneScale();
}
