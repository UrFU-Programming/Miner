#ifndef FIELD_HPP
#define FIELD_HPP

#include <QObject>
#include <QVector>

class Cell;

class Field : public QObject
{
    Q_OBJECT
public:
    enum State {
        StateIdle,
        StateStarted,
        StateEnded
    };

    Field();

    State state() const { return m_state; }
    bool isGenerated() const;

    void setSize(int width, int height);

    int numberOfMines() const { return m_numberOfMines; }
    void setNumberOfMines(int number);

    void prepare();
    void generate(int x, int y);

    int width() const { return m_width; }
    int height() const { return m_height; }

    Cell *cellAt(int x, int y) const;

signals:
    void numberOfFlagsChanged(int number);
    void stateChanged();

protected slots:
    void onCellOpened(int x, int y);
    void onCellMarkChanged();

private:
    void setState(State newState);

    void lose();
    void win();

    QVector<Cell*> m_cells;

    State m_state;

    int m_width;
    int m_height;

    int m_numberOfMines;
    int m_numberOfFlags;
    int m_numberOfOpenCells;

    bool m_generated;
};

#endif // FIELD_HPP
