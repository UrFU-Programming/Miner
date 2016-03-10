#ifndef CELL_HPP
#define CELL_HPP

class Cell
{
public:
    Cell(int x, int y);

    int x() const { return m_x; }
    int y() const { return m_y; }

    bool haveMine() const { return m_haveMine; }
    void setHaveMine(bool haveMine);

private:
    int m_x;
    int m_y;

    bool m_haveMine;

};

#endif // CELL_HPP
