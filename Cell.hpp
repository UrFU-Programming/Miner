#ifndef CELL_HPP
#define CELL_HPP

#include <QVector>
#include <QObject>

class Field;

class Cell : public QObject
{
    Q_OBJECT
public:
    Cell(Field *field, int x, int y);

    int x() const { return m_x; }
    int y() const { return m_y; }
    int mark() const { return m_mark; }

    int minesAround() const;

    bool haveMine() const { return m_haveMine; }
    void setHaveMine(bool haveMine);

    bool isOpen() const { return m_open; }
    void open();
    void reset();
    void toggleMark();
    void tryToOpenAround();
    void setNeighbors(const QVector<Cell*> &neighbors);

    QVector<Cell*> getNeighbors() const;

signals:
    void opened(int x, int y);

private:
    Field *m_field;

    int m_x;
    int m_y;
    int m_mark;

    bool m_haveMine;
    bool m_open;

    QVector <Cell*> m_neighbors;

};

#endif // CELL_HPP
