#include "Headers/graphwindow.h"
#include "Headers/algorithm.h"
#include "Headers/graph.h"
#include "Headers/node.h"
#include "Headers/edge.h"

#include <string>

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    GraphWindow w;
    a.setWindowIcon(QIcon(":/Resources/logo.ico"));
    w.show();
    return a.exec();
}
