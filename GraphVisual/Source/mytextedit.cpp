#include "Headers/mytextedit.h"
#include <QKeyEvent>
#include <QFocusEvent>

void MyTextEdit::keyPressEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_Tab || e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return) {
        this->focusNextPrevChild(true);
    } else {
        QTextEdit::keyPressEvent(e);
    }
}
