#include "Headers/graphwindow.h"
#include "Headers/algorithm.h"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GraphWindow w;

    w.show();
    return a.exec();
}
