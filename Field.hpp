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
    Q_PROPERTY(State state READ state NOTIFY stateChanged)
    Q_PROPERTY(bool resetInProgress READ resetInProgress NOTIFY progressChanged)

public:
    enum State {
        StateIdle,
        StateStarted,
        StateEnded
    };

    Q_ENUM(State)

    Field();

    void setSize(int width, int height);
    void setNumberOfMines(int number);

    void generate(int x, int y);
    void lose();
    bool isGenerated() const { return m_generated; }
    bool resetInProgress() const { return m_resetInProgress; }


    int width() const { return m_width; }
    int height() const { return m_height; }
    int numberOfMines() const { return m_numberOfMines; }
    int numberOfFlags() const { return m_numberOfFlags; }
    State state() const { return m_state; }

    Q_INVOKABLE Cell *cellAt(int x, int y) const;

public slots:
    void startNewGame();

protected slots:
    void onCellOpened(int x, int y);
    void onCellMarkChanged();

signals:
    void numberOfFlagsChanged(int numberOfFlags);
    void stateChanged(State newState);
    void progressChanged(bool isResetting);

    void widthChanged(int newWidth);
    void heightChanged(int newHeight);

private:
    QVector<Cell*> m_cells;

    int m_width;
    int m_height;
    bool m_generated;
    bool m_resetInProgress;

    int m_numberOfMines;
    int m_numberOfFlags;
    int m_numberOfOpenedCells;
    State m_state;

    void win();
    void setState(State newState);
};

#endif // FIELD_HPP
