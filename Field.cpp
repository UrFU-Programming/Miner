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
            m_cells.append(new Cell(this, x, y));
        }
    }
}

void Field::setNumberOfMines(int number)
{
    m_numberOfMines = number;
}

void Field::generate(int x, int y)
{
    qsrand(10);

    Cell *banned = cellAt(x, y);
    QVector<Cell*> bannedCells = banned->getNeighbors();
    bannedCells.append(banned);

    int minesToPlace = m_numberOfMines;

    while (minesToPlace > 0) {
        Cell *cell = m_cells.at(qrand() % m_cells.count());

        if (cell->haveMine() || bannedCells.contains(cell)) {
            continue;
        }

        cell->setHaveMine(true);
        --minesToPlace;
    }

    m_generated = true;
}

void Field::prepare()
{
    m_generated = false;

    for (int i = 0; i < m_cells.size();i++) {
        m_cells[i]->reset();
    }
}

void Field::lose()
{
    for (int i = 0; i < m_cells.size(); i++) {
        m_cells[i]->open();
    }
}

Cell *Field::cellAt(int x, int y) const
{
    if (x < 0 || x >= m_width) {
        return 0;
    }
    if (y < 0 || y >= m_height) {
        return 0;
    }

    return m_cells.at(x + y * m_width);
}
