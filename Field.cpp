#include "Field.hpp"

#include "Cell.hpp"

Field::Field()
{

}

void Field::setSize(int width, int height)
{
    m_width = width;
    m_height = height;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            m_cells.append(new Cell(x, y));
        }
    }
}

Cell *Field::cellAt(int x, int y) const
{
    return m_cells.at(x + y * m_width);
}
