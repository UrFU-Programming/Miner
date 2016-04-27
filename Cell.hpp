#ifndef CELL_HPP
#define CELL_HPP

#include <QVector>
#include <QObject>

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

    int x() const { return m_x; }
    int y() const { return m_y; }
    Mark mark() const { return m_mark; }

    int minesAround() const;

    bool haveMine() const { return m_haveMine; }
    bool isOpen() const { return m_open; }

    void setHaveMine(bool haveMine);
    void open();
    void reset();
    void toggleMark();
    void tryToOpenAround();
    void setNeighbors(const QVector<Cell*> &neighbors);
    void reveal();

    QVector<Cell*> getNeighbors() const;

signals:
    void opened(int x, int y);
    void markChanged(Mark newMark);

private:
    int m_x;
    int m_y;
    Mark m_mark;

    bool m_haveMine;
    bool m_open;
    bool m_exploded;

    QVector <Cell*> m_neighbors;

};

#endif // CELL_HPP
