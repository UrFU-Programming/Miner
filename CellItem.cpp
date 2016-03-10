#include "CellItem.hpp"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSimpleTextItem>
#include <QPainter>

#include "Cell.hpp"

const int cellSize = 32;

CellItem::CellItem(Cell *cell) :
    QGraphicsItem()
{
    m_cell = cell;
    m_text = new QGraphicsSimpleTextItem(this);

    QFont f = m_text->font();
    f.setPixelSize(cellSize - 4);
    m_text->setFont(f);

    setPos(m_cell->x() * cellSize, m_cell->y() * cellSize);

    setAcceptedMouseButtons(Qt::LeftButton);
}

QRectF CellItem::boundingRect() const
{
    return QRectF(0, 0, cellSize, cellSize);
}

void CellItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setRenderHint(QPainter::HighQualityAntialiasing);

    painter->drawRect(0, 0, cellSize, cellSize);

    if (m_cell->haveMine()) {
        m_text->setText("+");
    }
}

void CellItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->accept();
}

void CellItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_cell->open();
    }

    update();
}
