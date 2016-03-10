#include "CellItem.hpp"

#include <QPainter>

#include "Cell.hpp"

const int cellSize = 32;

CellItem::CellItem(Cell *cell) :
    QGraphicsItem()
{
    m_cell = cell;

    setPos(m_cell->x() * cellSize, m_cell->y() * cellSize);
}

QRectF CellItem::boundingRect() const
{
    return QRectF(0, 0, cellSize, cellSize);
}

void CellItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawRect(0, 0, cellSize, cellSize);
}
