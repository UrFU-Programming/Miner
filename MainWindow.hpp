#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QGraphicsSimpleTextItem;
class QGraphicsRectItem;
class QGraphicsScene;
class Field;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void newGame();

protected:
    void resizeEvent(QResizeEvent *event);

protected slots:
    void updateSceneScale();
    void onFieldNumberOfFlagsChanged(int number);
    void onFieldStateChanged();

private slots:
    void on_action_NewGame_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *m_scene;
    QGraphicsRectItem *m_fieldItem;
    QGraphicsSimpleTextItem *m_gameStateText;
    Field *m_field;
};

#endif // MAINWINDOW_H
