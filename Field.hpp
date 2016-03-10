#ifndef FIELD_HPP
#define FIELD_HPP

#include <QVector>

class Cell;

class Field
{
public:
    Field();

    void setSize(int width, int height);

    int width() const { return m_width; }
    int height() const { return m_height; }

    Cell *cellAt(int x, int y) const;

private:
    QVector<Cell*> m_cells;

    int m_width;
    int m_height;

};

#endif // FIELD_HPP
