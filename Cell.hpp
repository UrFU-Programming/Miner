#ifndef CELL_HPP
#define CELL_HPP

#include <QVector>
#include <QObject>

class Cell : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool haveMine READ haveMine NOTIFY haveMineChanged)
    Q_PROPERTY(bool isOpen READ isOpen NOTIFY isOpenChanged)
    Q_PROPERTY(bool isExploded READ isExploded NOTIFY isExplodedChanged)
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

    int x() const { return m_x; }
    int y() const { return m_y; }
    Mark mark() const { return m_mark; }

    int minesAround() const;

    bool haveMine() const { return m_haveMine; }
    bool isOpen() const { return m_open; }
    bool isExploded() const { return m_exploded; }

    void setHaveMine(bool haveMine);
    void reset();
    void setNeighbors(const QVector<Cell*> &neighbors);
    void reveal();

    QVector<Cell*> getNeighbors() const;

public slots:
    void open();
    void toggleMark();
    void tryToOpenAround();

signals:
    void opened(int x, int y);
    void markChanged(Mark newMark);
    void haveMineChanged(bool haveMine);
    void isOpenChanged(bool isOpen);
    void isExplodedChanged(bool isExploded);
    void minesAroundChanged(bool minesAround);

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
