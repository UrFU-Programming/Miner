#include "MainWindow.hpp"
#include <QApplication>

#include <QtQml>

#include "Field.hpp"
#include "Cell.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qmlRegisterType<Field>("GameComponents", 1, 0, "Field");
    qmlRegisterType<Cell>("GameComponents", 1, 0, "Cell");

    MainWindow w;
    w.show();

    return a.exec();
}
