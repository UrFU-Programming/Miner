#ifndef CELL_HPP
#define CELL_HPP

class Cell
{
public:
    Cell(int x, int y);

    int x() const { return m_x; }
    int y() const { return m_y; }

private:
    int m_x;
    int m_y;

};

#endif // CELL_HPP
