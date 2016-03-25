#ifndef CELL_HPP
#define CELL_HPP

#include <QObject>
#include <QVector>

class Cell : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool haveMine READ haveMine NOTIFY haveMineChanged)
    Q_PROPERTY(bool isOpen READ isOpen NOTIFY isOpenChanged)
    Q_PROPERTY(bool exploded READ isExploded NOTIFY explodedChanged)
    Q_PROPERTY(int minesAround READ minesAround NOTIFY minesAroundChanged)
    Q_PROPERTY(Mark mark READ mark NOTIFY markChanged)
public:
    enum Mark {
        MarkNothing,
        MarkFlagged,
        MarkQuestioned
    };
    Q_ENUM(Mark)

    Cell(int x = 0, int y = 0);

    void reset();

    int x() const { return m_x; }
    int y() const { return m_y; }

    int minesAround() const;

    bool haveMine() const { return m_haveMine; }
    void setHaveMine(bool haveMine);

    bool isOpen() const { return m_open; }
    bool isExploded() { return m_exploded; }
    void reveal();

    Mark mark() const { return m_mark; }

    QVector<Cell*> getNeighbors() const;
    void setNeighbors(const QVector<Cell*> &neighbors);

public slots:
    void open();
    void tryToOpenAround();
    void toggleMark();

signals:
    void opened(int x, int y);
    void isOpenChanged(bool newIsOpen);
    void markChanged(Mark newMark);
    void haveMineChanged(bool haveMine);
    void minesAroundChanged(int newCount);
    void explodedChanged(bool exploded);

private:
    QVector<Cell*> m_neighbors;

    int m_x;
    int m_y;

    bool m_haveMine;
    bool m_open;
    bool m_exploded;

    Mark m_mark;

};

#endif // CELL_HPP
