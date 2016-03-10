#ifndef FIELD_HPP
#define FIELD_HPP

#include <QVector>

class Cell;

class Field
{
public:
    Field();

    void setSize(int width, int height);
    void setNumberOfMines(int number);

    void generate();

    int width() const { return m_width; }
    int height() const { return m_height; }

    Cell *cellAt(int x, int y) const;

private:
    QVector<Cell*> m_cells;

    int m_width;
    int m_height;

    int m_numberOfMines;
};

#endif // FIELD_HPP
