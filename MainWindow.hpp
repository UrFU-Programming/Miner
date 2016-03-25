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

    Field *field() const { return m_field; }

    void newGame();
    void resizeField(int width, int height);

protected:
    void resizeEvent(QResizeEvent *event);

protected slots:
    void updateSceneScale();
    void onFieldNumberOfFlagsChanged(int number);
    void onFieldStateChanged();

private slots:
    void on_action_NewGame_triggered();

    void on_actionDifficultyNovice_triggered();
    void on_actionDifficultyIntermediate_triggered();
    void on_actionDifficultyExpert_triggered();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *m_scene;
    QGraphicsRectItem *m_fieldItem;
    QGraphicsSimpleTextItem *m_gameStateText;
    QGraphicsRectItem *m_gameStateRect;
    Field *m_field;
};

#endif // MAINWINDOW_H
