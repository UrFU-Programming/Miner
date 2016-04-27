#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsRectItem>

namespace Ui {
class MainWindow;
}

class QGraphicsScene;
class Field;
class QGraphicsSimpleTextItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void newGame();
    void resizeField(int width, int height);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event);

protected slots:
    void updateSceneScale();
    void onFieldNumberOfFlagsChanged(int number);

private slots:
    void on_actionNewGame_triggered();
    void on_actionExit_triggered();
    void onFieldStateChanged();

    void on_actionBeginner_triggered();

    void on_actionIntermediate_triggered();

    void on_actionExpert_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *m_scene;
    QGraphicsSimpleTextItem *m_gameStateText;
    QGraphicsRectItem *m_fieldItem;
    QGraphicsRectItem *m_gameStateRect;
    Field *m_field;
};

#endif // MAINWINDOW_H
