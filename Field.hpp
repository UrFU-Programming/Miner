#ifndef FIELD_HPP
#define FIELD_HPP

#include <QVector>
#include <QObject>

class Cell;

class Field : public QObject
{
    Q_OBJECT
public:
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

    Cell *cellAt(int x, int y) const;

protected slots:
    void onCellOpened(int x, int y);
    void onCellMarkChanged();

signals:
    void numberOfFlagsChanged(int numberOfFlags);

private:
    QVector<Cell*> m_cells;

    int m_width;
    int m_height;
    bool m_generated;

    int m_numberOfMines;
    int m_numberOfFlags;
    int m_numberOfOpenedCells;
};

#endif // FIELD_HPP
