#include "mytextedit.h"
#include <QFocusEvent>
#include <QKeyEvent>

void MyTextEdit::keyPressEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_Space || e->key() == Qt::Key_Enter ||
            e->key() == Qt::Key_Return) {
        return;
    } else {
        QTextEdit::keyPressEvent(e);
    }
}
