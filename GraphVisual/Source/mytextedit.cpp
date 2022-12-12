#include "Headers/mytextedit.h"
#include <QKeyEvent>
#include <QFocusEvent>

void MyTextEdit::keyPressEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_Space || e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return) {
        return;
    } else {
        QTextEdit::keyPressEvent(e);
    }
}
