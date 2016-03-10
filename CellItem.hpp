#ifndef CELLITEM_HPP
#define CELLITEM_HPP

#include <QGraphicsItem>

class Cell;

class CellItem : public QGraphicsItem
{
public:
    CellItem(Cell *cell);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    Cell *m_cell;
};

#endif // CELLITEM_HPP
