#include "MainWindow.hpp"
#include <QApplication>

#include <QtQml>

#include "Field.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qmlRegisterType<Field>("GameComponents", 1, 0, "Field");

    MainWindow w;
    w.show();

    return a.exec();
}
