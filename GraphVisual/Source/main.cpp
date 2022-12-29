#include "Headers/graphwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    GraphWindow w;
    a.setWindowIcon(QIcon(":/Resources/logo.ico"));
    w.show();
    return a.exec();
}
