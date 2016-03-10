#include "Cell.hpp"

Cell::Cell(int x, int y)
{
    m_x = x;
    m_y = y;

    m_haveMine = false;
}

void Cell::setHaveMine(bool haveMine)
{
    m_haveMine = haveMine;
}
