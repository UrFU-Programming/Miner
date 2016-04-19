#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QGraphicsScene;
class Field;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void newGame();
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event);

protected slots:
    void updateSceneScale();
    void onFieldNumberOfFlagsChanged(int number);

private slots:
    void on_actionNewGame_triggered();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *m_scene;
    Field *m_field;
};

#endif // MAINWINDOW_H
