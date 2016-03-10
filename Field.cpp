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

void Field::setNumberOfMines(int number)
{
    m_numberOfMines = number;
}

void Field::generate()
{
    int minesToPlace = m_numberOfMines;

    while (minesToPlace > 0) {
        Cell *cell = m_cells.at(qrand() % m_cells.count());

        if (cell->haveMine()) {
            continue;
        }

        cell->setHaveMine(true);
        --minesToPlace;
    }
}

Cell *Field::cellAt(int x, int y) const
{
    return m_cells.at(x + y * m_width);
}
