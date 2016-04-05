#ifndef FIELD_HPP
#define FIELD_HPP

#include <QObject>
#include <QVector>

class Cell;

class Field : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int width READ width NOTIFY widthChanged)
    Q_PROPERTY(int height READ height NOTIFY heightChanged)
    Q_PROPERTY(State state READ state NOTIFY stateChanged)
    Q_PROPERTY(bool resetInProgress READ resetInProgress NOTIFY resetInProgressChanged)
public:
    enum State {
        StateIdle,
        StateStarted,
        StateEnded
    };
    Q_ENUM(State)

    Field();

    State state() const { return m_state; }
    bool resetInProgress() const { return m_resetInProgress; }
    bool isGenerated() const;

    void setSize(int width, int height);

    int numberOfMines() const { return m_numberOfMines; }
    void setNumberOfMines(int number);

    void generate(int x, int y);

    int width() const { return m_width; }
    int height() const { return m_height; }

    Q_INVOKABLE Cell *cellAt(int x, int y) const;

signals:
    void numberOfFlagsChanged(int number);
    void stateChanged();
    void resetInProgressChanged(bool reset);

    void widthChanged(int newWidth);
    void heightChanged(int newHeight);

public slots:
    void startNewGame();

protected slots:
    void onCellOpened(int x, int y);
    void onCellMarkChanged();

private:
    void setState(State newState);
    void setResetInProgress(bool reset);

    void lose();
    void win();

    QVector<Cell*> m_cells;

    State m_state;

    int m_width;
    int m_height;

    int m_numberOfMines;
    int m_numberOfFlags;
    int m_numberOfOpenCells;

    bool m_resetInProgress;
    bool m_generated;
};

#endif // FIELD_HPP
