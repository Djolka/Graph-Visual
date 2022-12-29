#include "Headers/graphwindow.h"
#include "Headers/algorithm.h"
#include "Headers/graph.h"
#include "Headers/node.h"
#include "Headers/edge.h"

#include<iostream>
#include <string>

#include <QVector>
#include <QString>


#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    GraphWindow w;

    w.show();
    return a.exec();
}
