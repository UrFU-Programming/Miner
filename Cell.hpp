#ifndef CELL_HPP
#define CELL_HPP

#include <QObject>
#include <QVector>

class Cell : public QObject
{
    Q_OBJECT
public:
    enum Mark {
        MarkNothing,
        MarkFlagged,
        MarkQuestioned
    };

    Cell(int x, int y);

    void reset();

    int x() const { return m_x; }
    int y() const { return m_y; }

    int minesAround() const;

    bool haveMine() const { return m_haveMine; }
    void setHaveMine(bool haveMine);

    bool isOpen() const { return m_open; }
    void open();
    void tryToOpenAround();

    Mark mark() const { return m_mark; }
    void toggleMark();

    QVector<Cell*> getNeighbors() const;
    void setNeighbors(const QVector<Cell*> &neighbors);

signals:
    void opened(int x, int y);

private:
    QVector<Cell*> m_neighbors;

    int m_x;
    int m_y;

    bool m_haveMine;
    bool m_open;

    Mark m_mark;

};

#endif // CELL_HPP
