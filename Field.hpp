#ifndef FIELD_HPP
#define FIELD_HPP

#include <QVector>
#include <QObject>

class Cell;

class Field : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int width READ width NOTIFY widthChanged)
    Q_PROPERTY(int height READ height NOTIFY heightChanged)
public:
    enum State {
        StateIdle,
        StateStarted,
        StateEnded
    };

    Field();

    void setSize(int width, int height);
    void setNumberOfMines(int number);

    void generate(int x, int y);
    void prepare();
    void lose();
    bool isGenerated() const { return m_generated; }

    int width() const { return m_width; }
    int height() const { return m_height; }
    int numberOfMines() const { return m_numberOfMines; }
    int numberOfFlags() const { return m_numberOfFlags; }
    State state() const { return m_state; }

    Cell *cellAt(int x, int y) const;

protected slots:
    void onCellOpened(int x, int y);
    void onCellMarkChanged();

signals:
    void numberOfFlagsChanged(int numberOfFlags);
    void stateChanged(State newState);

    void widthChanged(int newWidth);
    void heightChanged(int newHeight);

private:
    QVector<Cell*> m_cells;

    int m_width;
    int m_height;
    bool m_generated;

    int m_numberOfMines;
    int m_numberOfFlags;
    int m_numberOfOpenedCells;
    State m_state;

    void win();
    void setState(State newState);
};

#endif // FIELD_HPP
