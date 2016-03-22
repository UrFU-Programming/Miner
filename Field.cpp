#include "Field.hpp"

#include "Cell.hpp"

Field::Field() :
    QObject()
{

}

bool Field::isGenerated() const
{
    return m_generated;
}

void Field::setSize(int width, int height)
{
    m_width = width;
    m_height = height;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            Cell *cell = new Cell(x, y);
            connect(cell, SIGNAL(opened(int,int)), this, SLOT(onCellOpened(int,int)));
            connect(cell, SIGNAL(markChanged(Mark)), this, SLOT(onCellMarkChanged()));
            m_cells.append(cell);
        }
    }
}

void Field::setNumberOfMines(int number)
{
    m_numberOfMines = number;
}

void maybeAddCell(QVector<Cell*> *vector, Cell *cell)
{
    if (cell) {
        vector->append(cell);
    }
}

void Field::prepare()
{
    m_generated = false;

    for (Cell *cell : m_cells) {
        cell->reset();

        QVector<Cell*> neighbors;
        for (int x = cell->x() - 1; x <= cell->x() + 1; ++x) {
            maybeAddCell(&neighbors, cellAt(x, cell->y() - 1));
            maybeAddCell(&neighbors, cellAt(x, cell->y() + 1));
        }
        maybeAddCell(&neighbors, cellAt(cell->x() - 1, cell->y()));
        maybeAddCell(&neighbors, cellAt(cell->x() + 1, cell->y()));

        cell->setNeighbors(neighbors);
    }

    m_numberOfFlags = 0;
    emit numberOfFlagsChanged(m_numberOfFlags);

    m_numberOfOpenCells = 0;
}

void Field::generate(int x, int y)
{
    m_generated = true;

    Cell *banned = cellAt(x, y);
    QVector<Cell*> bannedCells = banned->getNeighbors();
    bannedCells.append(banned);

    int minesToPlace = m_numberOfMines;

    while (minesToPlace > 0) {
        Cell *cell = m_cells.at(qrand() % m_cells.count());

        if (bannedCells.contains(cell)) {
            continue;
        }

        if (cell->haveMine()) {
            continue;
        }

        cell->setHaveMine(true);
        --minesToPlace;
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

void Field::onCellOpened(int x, int y)
{
    if (!isGenerated()) {
        generate(x, y);
    }

    ++m_numberOfOpenCells;
}

void Field::onCellMarkChanged()
{
    m_numberOfFlags = 0;
    for (Cell *cell : m_cells) {
        if (cell->mark() == Cell::MarkFlagged) {
            ++m_numberOfFlags;
        }
    }
    emit numberOfFlagsChanged(m_numberOfFlags);
}
