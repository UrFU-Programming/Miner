#ifndef FIELD_HPP
#define FIELD_HPP

#include <QObject>
#include <QVector>

class Cell;

class Field : public QObject
{
    Q_OBJECT
public:
    Field();

    bool isGenerated() const;

    void setSize(int width, int height);
    void setNumberOfMines(int number);

    void prepare();
    void generate(int x, int y);

    int width() const { return m_width; }
    int height() const { return m_height; }

    Cell *cellAt(int x, int y) const;

protected slots:
    void onCellOpened(int x, int y);

private:
    QVector<Cell*> m_cells;

    int m_width;
    int m_height;

    int m_numberOfMines;

    bool m_generated;
};

#endif // FIELD_HPP
