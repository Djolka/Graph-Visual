#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QTextEdit>

class MyTextEdit : public QTextEdit
{
public:
    MyTextEdit(QWidget *parent = 0) : QTextEdit(parent) {}
    void keyPressEvent(QKeyEvent *e);
};

#endif // MYTEXTEDIT_H
